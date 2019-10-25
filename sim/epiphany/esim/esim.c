/* Epiphany eMesh functional simulator
   Copyright (C) 2014 Adapteva
   Contributed by Ola Jeppsson

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */


/** @todo Check address overflow (addr+nr_bytes) */

/*@todo rename es_tx_one_* to something better */


/* Need these for correct cpu struct */
#define WANT_CPU epiphanybf
#define WANT_CPU_EPIPHANYBF

#include "sim-main.h"
#include "mem-barrier.h"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

/** @todo Standard errnos should be sufficient for now */
/* Errors are returned as negative numbers. */
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>
#include <sched.h>
#include <sys/file.h>

#include <stdio.h>

#include <pthread.h>

#include "esim.h"
#include "esim-int.h"

#include "epiphany-desc.h"

/*! Get core index in shared memory
 *
 * @warning Does not range check
 *
 * @param[in] esim   ESIM handle
 * @param[in] coreid Coreid
 *
 * @return Core index in shared memory
 */
static signed
es_shm_core_index(const es_state *esim, unsigned coreid)
{
  signed row_offset, col_offset;
  row_offset = ES_CORE_ROW(coreid) - ES_NODE_CFG.row_base;
  col_offset = ES_CORE_COL(coreid) - ES_NODE_CFG.col_base;

  return row_offset*ES_CLUSTER_CFG.cols_per_node + col_offset;
}

/*! Get pointer to core mem
 *
 * @param[in] esim   ESIM handle
 * @param[in] coreid Coreid
 *
 * @return Pointer to start of Epiphany cores memory, or NULL
 */
static volatile uint8_t *
es_shm_core_base(const es_state *esim, unsigned coreid)
{
  signed offset = es_shm_core_index(esim, coreid);
  if (offset < 0 || offset > (signed) ES_CLUSTER_CFG.cores_per_node)
    return NULL;

  return esim->cores_mem + ((size_t) offset) *
   (ES_SHM_CORE_STATE_SIZE+ES_CLUSTER_CFG.core_mem_region);
}

/*! Get node that holds this address. Must be a global address
 *
 * @param[in] esim   ESIM handle
 * @param[in] addr   target (Epiphany) memory address
 *
 * @return Simulator node where addr is located
 */
static signed
es_addr_to_node(const es_state *esim, address_word addr)
{
  unsigned coreid;
  signed row_offset, col_offset, node;

  if (ES_ADDR_IS_EXT_RAM(addr))
    {
      node = ES_CLUSTER_CFG.ext_ram_node;
      goto out;
    }

  coreid = ES_ADDR_TO_CORE(addr);

  row_offset = ES_CORE_ROW(coreid) - ES_CLUSTER_CFG.row_base;
  col_offset = ES_CORE_COL(coreid) - ES_CLUSTER_CFG.col_base;

  if (row_offset < 0 || col_offset < 0)
    {
      node = -EINVAL;
      goto out;
    }

  node = (row_offset/ES_CLUSTER_CFG.rows_per_node) *
	 (ES_CLUSTER_CFG.cols / ES_CLUSTER_CFG.cols_per_node) +
	 (col_offset / ES_CLUSTER_CFG.cols_per_node);

  if (node >= ES_CLUSTER_CFG.nodes)
    {
      node = -EINVAL;
      goto out;
    }

out:
#ifdef ES_DEBUG
  fprintf(stderr, "es_addr_to_node: addr=0x%8x node=%d\n", addr, node);
#endif
  return node;
}


/*! Translate target (Epiphany) address to simulator address
 *
 * @param[in]  esim   ESIM handle
 * @param[out] transl Simulator address
 * @param[in]  addr   target (Epiphany) memory address
 */
static void
es_addr_translate(const es_state *esim, es_transl *transl,
		  address_word addr)
{
  uint8_t *tmp_ptr;
  signed node;
  address_word offset, top;

  if (es_initialized(esim) != ES_OK)
    {
      fprintf(stderr, "ESIM: Not initialized\n");
      transl->location = ES_LOC_INVALID;
      return;
    }

  /* Atomic instructions requires requested address to be global */
  transl->addr_was_global = ES_ADDR_IS_GLOBAL(addr);

  addr = ES_ADDR_TO_GLOBAL(addr);
  transl->addr = addr;
  if ((node = es_addr_to_node(esim, addr)) < 0)
    {
      transl->location = ES_LOC_INVALID;
      return;
    }
  transl->node = node;

  transl->coreid = ES_ADDR_TO_CORE(addr);

  if (transl->node == ES_NODE_CFG.rank)
    {
      if (ES_ADDR_IS_EXT_RAM(addr))
	{
	  transl->location = ES_LOC_RAM;
	  transl->mem = ((uint8_t *) esim->ext_ram) +
	   (addr % ES_CLUSTER_CFG.ext_ram_size);
	  transl->in_region = ES_CLUSTER_CFG.ext_ram_size -
	   (addr % ES_CLUSTER_CFG.ext_ram_size);

	}
      else
	{
	  tmp_ptr = ((uint8_t *) esim->cores_mem) +
	    (es_shm_core_index(esim, transl->coreid) *
	      (ES_SHM_CORE_STATE_SIZE+ES_CLUSTER_CFG.core_mem_region)) +
	      ES_SHM_CORE_STATE_HEADER_SIZE;
	  transl->cpu = (sim_cpu *) tmp_ptr;
	  if (ES_ADDR_IS_MMR(addr))
	    {
	      if (addr % 4)
		{
		  /* Unaligned */
		  /** @todo ES_LOC_UNALIGNED would be more accurate */
		  transl->location = ES_LOC_INVALID;
		}
	      else
		{
		  transl->location = ES_LOC_SHM_MMR;
		  transl->reg = (addr & (ES_CORE_MMR_SIZE-1)) >> 2;
		  /* Point mem to sim cpu struct */
		  /** @todo Could optimize this so that entire region is one
		     transaction */
		  transl->in_region = 4;
		}
	    }
	  else
	    {
	      offset = addr & (ES_CLUSTER_CFG.core_mem_region - 1);
	      top = min (ES_CLUSTER_CFG.core_phys_mem, ES_CORE_MMR_BASE);
	      if (offset >= top)
		{
		  transl->location = ES_LOC_INVALID;
		  return;
		}
	      transl->location = ES_LOC_SHM;
	      transl->mem =
	       ((uint8_t *) esim->cores_mem) +
		(es_shm_core_index(esim, transl->coreid) *
		  (ES_SHM_CORE_STATE_SIZE+ES_CLUSTER_CFG.core_mem_region)) +
		  ES_SHM_CORE_STATE_SIZE +
		  (addr % ES_CLUSTER_CFG.core_mem_region);

	      transl->in_region = top - offset;
	    }
	}
    }
  else /* if (transl->node != ES_NODE_CFG.rank) */
    {
#if WITH_EMESH_NET
      es_net_addr_translate(esim, transl, addr);
#else
      transl->location = ES_LOC_INVALID;
#endif
    }
#ifdef ES_DEBUG
  /** @todo Revisit when adding network support */
  fprintf(stderr, "es_addr_translate: location=%d addr=0x%8x in_region=%ld"
	  " coreid=%d node=%d mem=0x%016lx\n reg=%d shm_offset=0x%016lx\n",
	  transl->location, transl->addr, transl->in_region, transl->coreid,
	  transl->node, (uint64_t) transl->mem, transl->reg,
	  transl->mem-esim->cores_mem);
#endif
}

/*! Translate next target (Epiphany) region address to simulator address
 *
 * @param[in]     esim   ESIM handle
 * @param[in,out] transl Simulator address
 */
static void
es_addr_translate_next_region(const es_state *esim, es_transl *transl)
{
  es_addr_translate(esim, transl, transl->addr+transl->in_region);
}

static int
es_tx_one_shm_load(es_state *esim, es_transaction *tx)
{
  size_t n = min(tx->remaining, tx->sim_addr.in_region);
  memmove(tx->target, tx->sim_addr.mem, n);
  tx->target += n;
  tx->remaining -= n;

  /** @todo Should we return nr of bytes ? */
  return ES_OK;
}


/*! Perform one store to SHM, and advance transaction state
 *
 * @param[in]     esim   ESIM handle
 * @param[in,out] tx     Transaction
 *
 * @return ES_OK on success
 */
static int
es_tx_one_shm_store(es_state *esim, es_transaction *tx)
{
  PCADDR i, invalidate;
  size_t n = min(tx->remaining, tx->sim_addr.in_region);
  memmove(tx->sim_addr.mem, tx->target, n);
  tx->target += n;
  tx->remaining -= n;
  if (tx->sim_addr.coreid == esim->coreid && esim->this_core_cpu_state)
    {
      /* Invalidate all instructions in the range.
       * Instructions are either 2 or 4 bytes long and must be half-word
       * aligned */
      for (i = 0; i < n+1; i += 2)
	{
	  invalidate = ((i+tx->addr) & ~1);
#ifdef ES_DEBUG
	  fprintf(stderr, "Invalidating %08x\n", invalidate);
#endif
	  epiphanybf_scache_invalidate((sim_cpu *) esim->this_core_cpu_state,
				       invalidate);
        }
    }
  else if (tx->sim_addr.location == ES_LOC_SHM)
    {
      /* Signal other CPU simulator a write from another core did occur so that
       * it can flush its scache.
       */
      MEM_BARRIER();
      tx->sim_addr.cpu->external_write = 1;
    }

  return ES_OK;
}

static void
es_shm_mmr_write (es_state *esim, sim_cpu *target_cpu, int reg, USI val)
{
  bool to_self;

  sim_cpu *my_cpu = ES_CPU;
  to_self = !esim->is_client && my_cpu == target_cpu;

  /* If target cpu is local cpu, we can do the write immediately,
   * otherwise we need to serialize it on the target */
  if (!esim->is_client && to_self)
    epiphanybf_h_all_registers_set (my_cpu, reg, val);
  else
    {
      /* Busy-waiting seems to give best performance (compared to
       * pthread_cond_timedwait), even with a large number (1024) of simulated
       * cores.  */

      while (true)
	{
	  /* take remote writeslot lock */
	  CPU_SCR_WRITESLOT_LOCK (target_cpu);

	  if (CPU_SCR_WRITESLOT_EMPTY (target_cpu))
	    break;

	  /* need to release remote cpu lock to get some global progress */
	  CPU_SCR_WRITESLOT_RELEASE (target_cpu);

	  /* Empty local writeslot to break cyclic deadlocks */
	  if (!esim->is_client && !CPU_SCR_WRITESLOT_EMPTY (my_cpu))
	    {
	      CPU_SCR_WRITESLOT_LOCK (my_cpu);
	      epiphanybf_h_all_registers_set (
		  my_cpu,
		  my_cpu->scr_remote_write_reg,
		  my_cpu->scr_remote_write_val);
	      my_cpu->scr_remote_write_reg = -1;
	      my_cpu->scr_remote_write_val = 0xbaadbeef;
	      CPU_SCR_WRITESLOT_SIGNAL (my_cpu);
	      CPU_SCR_WRITESLOT_RELEASE (my_cpu);
	    }
	  else
	    {
	      /* "Punish" processes that don't contribute to global
	       * progress */
	      sched_yield ();
	    }
	}
      target_cpu->scr_remote_write_reg = reg;
      target_cpu->scr_remote_write_val = val;
      CPU_SCR_WAKEUP_SIGNAL (target_cpu);
      CPU_SCR_WRITESLOT_RELEASE (target_cpu);
    }
}

static void
es_shm_tx_mmr_write (es_state *esim, es_transaction *tx, int reg, USI val)
{
  sim_cpu *target_cpu = tx->sim_addr.cpu;

  es_shm_mmr_write(esim, target_cpu, reg, val);
}

/*! Perform one atomic operation to SHM, and advance transaction state
 *
 * @param[in]     esim   ESIM handle
 * @param[in,out] tx     Transaction
 *
 * @return ES_OK on success
 */
static int
es_tx_one_shm_atomic_op(es_state *esim, es_transaction *tx)
{
  union acme_ptr {
    uint8_t  *u8;
    uint16_t *u16;
    uint32_t *u32;
    uint64_t *u64;
  };

  sim_cpu *this_cpu = (sim_cpu *) esim->this_core_cpu_state;

  union acme_ptr rd  = { .u8 = tx->target };
  union acme_ptr mem = { .u8 = tx->sim_addr.mem };
  UDI rdnew = 0;

  /* Atomic OPS require that requested addr is global */
  if (!tx->sim_addr.addr_was_global)
    return -EINVAL;

  /* addr cannot reside in RAM, must be in on-chip memory  */
  if (tx->sim_addr.location != ES_LOC_SHM)
    return -EINVAL;

/* Macros for different atomic op types */
#define atomic_load(Op) \
  ({ \
    UDI _tmp;\
    switch (tx->remaining) \
    { \
    case 1: \
      _tmp = Op(mem.u8, __ATOMIC_SEQ_CST); \
      break; \
    case 2: \
      _tmp = Op(mem.u16, __ATOMIC_SEQ_CST); \
      break; \
    case 4: \
      _tmp = Op(mem.u32, __ATOMIC_SEQ_CST); \
      break; \
    case 8: \
      _tmp = Op(mem.u64, __ATOMIC_SEQ_CST); \
      break; \
    default: \
      return -EINVAL; \
    } \
    _tmp; \
  })

#define atomic_store(Op) \
  switch (tx->remaining) \
  { \
  case 1: \
    Op(mem.u8, *rd.u8, __ATOMIC_SEQ_CST); \
    break; \
  case 2: \
    Op(mem.u16, *rd.u16, __ATOMIC_SEQ_CST); \
    break; \
  case 4: \
    Op(mem.u32, *rd.u32, __ATOMIC_SEQ_CST); \
    break; \
  case 8: \
    Op(mem.u64, *rd.u64, __ATOMIC_SEQ_CST); \
    break; \
  default: \
    return -EINVAL; \
  }

#define atomic_testset(Op) \
  ({ \
    USI _expected = 0; \
    USI _tmp = *rd.u32; \
    switch (tx->remaining) \
    { \
    case 4: \
      Op(mem.u32, &_expected, _tmp, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST); \
      break; \
    default: \
      return -EINVAL; \
    } \
    _expected; \
  })

  switch (tx->ctrlmode)
    {
    case OP_CTRLMODE_TESTSET:
      rdnew = atomic_testset(__atomic_compare_exchange_n);
      if (!rdnew)
	{
	  epiphanybf_h_memory_atomic_set (this_cpu, *rd.u32);
	  epiphanybf_h_memory_atomic_flag_set (this_cpu, 1);
	}
      break;
    default:
      return -EINVAL;
    }
#undef atomic_load
#undef atomic_store
#undef atomic_testset

  if (tx->type == ES_REQ_ATOMIC_LOAD)
    {
    switch (tx->remaining)
      {
      case 1: *rd.u8  = (uint8_t)  rdnew; break;
      case 2: *rd.u16 = (uint16_t) rdnew; break;
      case 4: *rd.u32 = (uint32_t) rdnew; break;
      case 8: *rd.u64 = (uint64_t) rdnew; break;
      default:
	abort ();
      }
    }

  /* Signal other CPU simulator a write from another core did occur so that
   * it can invalidate its scache.
   */
  if (tx->sim_addr.coreid != esim->coreid)
    {
      /* Signal other CPU simulator a write from another core did occur so that
       * it can flush its scache.
       */
      MEM_BARRIER();
      tx->sim_addr.cpu->external_write = 1;
    }

  tx->target += tx->remaining;
  tx->remaining -= tx->remaining;

  return ES_OK;
}

/*! Perform one load or store to MMR, and advance transaction state
 *
 * @param[in]     esim   ESIM handle
 * @param[in,out] tx     Transaction
 *
 * @return ES_OK on success
 */
__attribute__ ((visibility("hidden")))
int
es_tx_one_shm_mmr(es_state *esim, es_transaction *tx)
{
  int reg, n;
  uint32_t *target;
  sim_cpu *current_cpu;

  current_cpu = tx->sim_addr.cpu;

  target = (uint32_t *) tx->target;

  /*
   * @todo Writes are racy by design. We need to verify that this is the
   * correct behavior when we get access to the real hardware.
  */

  /* Alignment was checked in es_addr_translate.
   * Hardware doesn't seem to support reading partial regs so neither do we.
   */
  if (tx->remaining < 4)
    return -EINVAL;

  reg = tx->sim_addr.reg;

  switch (tx->type)
    {
    case ES_REQ_LOAD:
      if (reg < ES_EPIPHANY_NUM_GPRS &&
	  tx->sim_addr.coreid != esim->coreid &&
	  epiphany_cpu_is_active(current_cpu))
	{
	  /* Reading directly from the general-purpose registers by an external
	   * agent is not supported while the CPU is active.
	   * @todo It is unclear if this is allowed from local core so allow it
	   * for now.
	   */
	  n = -EINVAL;
	}
      else
	{
	  *target = epiphanybf_h_all_registers_get(current_cpu, reg);
	  n = 4;
	}
      break;
    case ES_REQ_STORE:
      es_shm_tx_mmr_write(esim, tx, reg, *target);
      n = 4;
      break;

    /*! @todo Implement (if supported by hardware?) */
    /* case ES_REQ_TESTSET: */
    default:
      n = -EINVAL;
    }
  if (n != 4)
    {
      return -EINVAL;
    }
  tx->target += n;
  tx->remaining -= n;

  /** @todo Should we return nr of bytes ? */
  return ES_OK;
}

/*! Perform one portion of transaction (might span more than one region)
 *
 * @param[in]     esim   ESIM handle
 * @param[in,out] tx     Transaction
 *
 * @return ES_OK on success
 */
static int
es_tx_one(es_state *esim, es_transaction *tx)
{
  /** @todo Use function vtable instead? */
  switch (tx->sim_addr.location)
    {
    case ES_LOC_SHM:
    case ES_LOC_RAM:
      switch (tx->type)
	{
	case ES_REQ_LOAD:
	  return es_tx_one_shm_load(esim, tx);
	case ES_REQ_STORE:
	  return es_tx_one_shm_store(esim, tx);
	case ES_REQ_ATOMIC_LOAD:
	case ES_REQ_ATOMIC_STORE:
	  return es_tx_one_shm_atomic_op(esim, tx);
	default:
#ifdef ES_DEBUG
	  fprintf(stderr, "es_tx_one: BUG\n");
#endif
	  return -EINVAL;
	}

      break;

    case ES_LOC_SHM_MMR:
      return es_tx_one_shm_mmr(esim, tx);
      break;

#if WITH_EMESH_NET
    case ES_LOC_NET:
    case ES_LOC_NET_MMR:
    case ES_LOC_NET_RAM:
      return es_net_tx_one(esim, tx);
      break;
#endif

    case ES_LOC_INVALID:
      return -ENOENT;
      break;

    default:
#ifdef ES_DEBUG
      fprintf(stderr, "es_tx_one: invalid memory location\n");
#endif
      return -EINVAL;
      break;
    }
#ifdef ES_DEBUG
      fprintf(stderr, "es_tx_one: BUG.\n");
#endif
  return -EINVAL;
}


/*! Perform transaction (memory access request)
 *
 * @param[in]     esim   ESIM handle
 * @param[in,out] tx     Transaction
 *
 * @return ES_OK on success
 */
static int
es_tx_run(es_state *esim, es_transaction *tx)
{
  int ret;

  es_addr_translate(esim, &tx->sim_addr, tx->addr);
  while (1)
    {
      ret = es_tx_one(esim, tx);
      if (ret != ES_OK || !tx->remaining)
	break;
      es_addr_translate_next_region(esim, &tx->sim_addr);
    }
  return ret;
}

/*! Write to memory
 *
 * @param[in] esim   ESIM handle
 * @param[in] addr   Target (Epiphany) address
 * @param[in] size   Number of bytes
 * @param[in] src    Source buffer
 *
 * @return ES_OK on success
 */
int
es_mem_store(es_state *esim, uint64_t addr, uint64_t size,
	     const void *src)
{
  es_transaction tx = {
    ES_REQ_STORE,
    (uint8_t *) src,
    -1,
    (address_word) addr,
    (address_word) size,
    (address_word) size,
    ES_TRANSL_INIT
  };
  return es_tx_run(esim, &tx);
}

/*! Read from memory
 *
 * @param[in]  esim   ESIM handle
 * @param[in]  addr   Target (Epiphany) address
 * @param[in]  size   Number of bytes
 * @param[out] dst    Destination buffer
 *
 * @return ES_OK on success
 */
int
es_mem_load(es_state *esim, uint64_t addr, uint64_t size,
	    void *dst)
{
  es_transaction tx = {
    ES_REQ_LOAD,
    (uint8_t *) dst,
    -1,
    (address_word) addr,
    (address_word) size,
    (address_word) size,
    ES_TRANSL_INIT
  };
  return es_tx_run(esim, &tx);
}

/*! Perform atomic load access
 *
 * @param[in]  esim   ESIM handle
 * @param[in]  addr   Target (Epiphany) address
 * @param[in]  size   Number of bytes
 * @param[out] dst    Destination buffer
 *
 * @return ES_OK on success
 */
int
es_mem_atomic_load (es_state *esim, int ctrlmode, uint64_t addr, uint64_t size,
		    void *dst)
{
  es_transaction tx = {
    ES_REQ_ATOMIC_LOAD,
    (uint8_t *) dst,
    ctrlmode,
    (address_word) addr,
    (address_word) size,
    (address_word) size,
    ES_TRANSL_INIT
  };
  return es_tx_run(esim, &tx);
}

/*! Perform atomic store access
 *
 * @param[in]  esim   ESIM handle
 * @param[in]  addr   Target (Epiphany) address
 * @param[in]  size   Number of bytes
 * @param[out] src    Source buffer
 *
 * @return ES_OK on success
 */
int
es_mem_atomic_store (es_state *esim, int ctrlmode, uint64_t addr, uint64_t size,
		     const void *src)
{
  es_transaction tx = {
    ES_REQ_ATOMIC_STORE,
    (uint8_t *) src,
    ctrlmode,
    (address_word) addr,
    (address_word) size,
    (address_word) size,
    ES_TRANSL_INIT
  };
  return es_tx_run(esim, &tx);
}


/*! Raise WAND interrupt on all cores in south-east direction
 *
 * This function manages locking by itself,
 *
 * @param[in]  esim          ESIM handle
 *
 * @return true if WAND did propagate (is high) to all nodes in mesh.
 */
static void
es_wand_propagate_se (es_state *esim)
{
  sim_cpu *current_cpu;
  uint32_t coreid;
  uint32_t i, j;
  es_transl transl;

  /* Keep it simple, use a for loop, no radial propagation. */

  for (i = ES_CLUSTER_CFG.row_base;
       i < ES_CLUSTER_CFG.row_base + ES_CLUSTER_CFG.rows; i++)
    {
      for (j = ES_CLUSTER_CFG.col_base;
	   j < ES_CLUSTER_CFG.col_base + ES_CLUSTER_CFG.cols; j++)
	{
	  coreid = ES_COREID (i, j);
	  current_cpu =
	    ({ es_addr_translate(esim, &transl, coreid << 20); transl.cpu; });
	  CPU_WAND_LOCK (current_cpu);

	  assert (   current_cpu->wand_self
		  && current_cpu->wand_east
		  && current_cpu->wand_south);

	  current_cpu->wand_self  = 0;
	  current_cpu->wand_east  = 0;
	  current_cpu->wand_south = 0;
	  es_shm_mmr_write (esim, current_cpu, H_REG_SCR_ILATST,
			    1 << H_INTERRUPT_WAND);
	  CPU_WAND_RELEASE (current_cpu);
	}
    }
}

/*! Propagate WAND in north-west direction
 *
 * It is the responsibility of the caller to lock/unlock the WAND lock for
 * current_cpu upon entering / after the function returns. Returns true iff
 * the WAND have propagated to all cores.
 *
 * @param[in]  esim          ESIM handle
 * @param[in]  coreid        coreid of current cpu
 * @param[in]  current_cpu   sim_cpu struct for current cpu
 *
 * @return true if WAND did propagate (is high) to all nodes in mesh.
 */
static bool
es_wand_propagate_nw (es_state *esim, uint32_t coreid, sim_cpu *current_cpu)
{
  bool northmost, westmost;
  es_transl transl;
  bool propagated_north = false, propagated_west = false;
  uint32_t north_coreid, west_coreid;
  uint32_t row, col;
  sim_cpu *north_cpu, *west_cpu;

  row = ES_CORE_ROW(coreid);
  col = ES_CORE_COL(coreid);

  northmost = row == ES_CLUSTER_CFG.row_base;
  westmost  = col == ES_CLUSTER_CFG.col_base;

  north_coreid = northmost ? 0 : ES_COREID(row - 1, col    );
  west_coreid  = westmost  ? 0 : ES_COREID(row    , col - 1);

  north_cpu = northmost ? NULL :
    ({ es_addr_translate(esim, &transl, north_coreid << 20); transl.cpu; });
  west_cpu  = westmost ?  NULL :
    ({ es_addr_translate(esim, &transl, west_coreid  << 20); transl.cpu; });

  /* Special case when coreid == 0 (which cannot exist),
   * Make wand_self always go 'high'. */
  if (coreid == 0)
    current_cpu->wand_self = 1;

  if (   !current_cpu->wand_self
      || !current_cpu->wand_south
      || !current_cpu->wand_east)
    return false;

  /* This will break if the neighbour core is resided on a different node */
  assert ((!northmost && north_coreid) || (northmost && !north_coreid));
  assert ((!westmost  && west_coreid)  || (westmost  && !west_coreid));

  if (!northmost)
    {
      CPU_WAND_LOCK (north_cpu);
      if (!north_cpu->wand_south) /* check if already propagated */
	{
	  north_cpu->wand_south = 1;
	  propagated_north =
	    es_wand_propagate_nw (esim, north_coreid, north_cpu);
	}
      CPU_WAND_RELEASE (north_cpu);
    }

  if (!westmost)
    {
      CPU_WAND_LOCK (west_cpu);
      if (!west_cpu->wand_east) /* check if already propagated */
	{
	  west_cpu->wand_east = 1;
	  propagated_west =
	    es_wand_propagate_nw (esim, west_coreid, west_cpu);
	}
      CPU_WAND_RELEASE (west_cpu);
    }

  return (westmost && northmost) || (propagated_north || propagated_west);
}

/*! Issue WAND throughout mesh
 *
 * @param[in]  esim   ESIM handle
 *
 * @return ES_OK on success
 */
int
es_wand (es_state *esim)
{
  bool eastmost, southmost;
  uint32_t coreid, row, col;
  sim_cpu *cpu;
  bool propagated_nw = false;

  es_transl transl;

  cpu = (sim_cpu *) esim->this_core_cpu_state;
  coreid = esim->coreid;

  row = ES_CORE_ROW(coreid);
  col = ES_CORE_COL(coreid);

  eastmost  = col == ES_CLUSTER_CFG.col_base + ES_CLUSTER_CFG.cols - 1;
  southmost = row == ES_CLUSTER_CFG.row_base + ES_CLUSTER_CFG.rows - 1;

  CPU_WAND_LOCK (cpu);
  if (cpu->wand_self)
    {
      CPU_WAND_RELEASE (cpu);
      return 0;
    }
  else
    cpu->wand_self = 1;

  if (southmost)
    cpu->wand_south = 1;
  if (eastmost)
    cpu->wand_east = 1;

  propagated_nw = es_wand_propagate_nw (esim, coreid, cpu);
  CPU_WAND_RELEASE (cpu);

  if (propagated_nw)
    es_wand_propagate_se (esim);

  return 0;
}


/*! Send interrupt to other core.
 *
 * If coreid is external ram the operation is a no-op.
 *
 * @param[in]  esim   ESIM handle
 * @param[in]  coreid remote core
 * @param[in]  irq    interrupt to raise
 *
 * @return ES_OK on success
 */
int
es_send_interrupt (es_state *esim, unsigned coreid, unsigned irq)
{
  uint64_t addr;
  uint32_t val;

  val = 1 << irq;
  addr = (coreid << 20) | 0xf0000 | (H_REG_SCR_ILATST << 2);

  return ES_ADDR_IS_EXT_RAM(addr)
    ? ES_OK
    : es_mem_store (esim, addr, 4, (uint8_t *) &val);
}

/*! Validate cluster configuration
 *
 * @param[in] c Cluster configuration
 *
 * @return ES_OK on success
 */
static int
es_validate_cluster_cfg(const es_cluster_cfg *c)
{
  unsigned row, begin, end, mem_coreid_base;
  unsigned cores, nodes;

  cores = c->rows * c->cols;

#define FAIL_IF(Expr, Error_string)\
  if ((Expr))\
    {\
      fprintf(stderr, "ESIM: Invalid config: %s\n", (Error_string));\
      return -EINVAL;\
    }

  FAIL_IF(!c->rows,         "Rows cannot be zero");
  FAIL_IF(!c->cols,         "Cols cannot be zero");
  FAIL_IF(c->row_base+c->rows > 64,
			    "Bottommost core row must be less than 64");
  FAIL_IF(c->col_base+c->cols > 64,
			    "Rightmost core col must be less than 64");

  FAIL_IF((ES_COREID(c->row_base+c->rows-1, c->col_base+c->cols-1)) > 4095,
			    "At least one of core in mesh has coreid > 4095");
  /** @todo Only support 1M for now */
  FAIL_IF(c->core_mem_region != (1<<20),
			    "Currently only 1M core region is supported");
  FAIL_IF(!c->core_mem_region,
			    "Core memory region size is zero");
  FAIL_IF(c->core_mem_region & (c->core_mem_region-1),
			    "Core memory region size must be power of two");

  FAIL_IF(c->core_phys_mem < 32768,
			    "Core SRAM size must be at least 32KB");
  FAIL_IF(c->core_phys_mem > c->core_mem_region,
			    "Core SRAM size cannot be larger than core memory region");

  /* Only support up to 4GB for now */
  FAIL_IF((uint64_t) c->ext_ram_size > (1ULL<<32ULL),
			    "External RAM size too large. Max is 4GB");

  FAIL_IF((address_word)
    (c->ext_ram_base + c->ext_ram_size) < (address_word) c->ext_ram_base &&
    !(c->ext_ram_base && (address_word) (c->ext_ram_base + c->ext_ram_size) == 0),
			    "External RAM would overflow address space");

  FAIL_IF(c->ext_ram_size && (c->ext_ram_size & (c->core_mem_region-1)),
			    "External ram size must be multiple of core mem"
			    " region size.");

  FAIL_IF(c->ext_ram_size && (c->ext_ram_base & (c->core_mem_region-1)),
			    "External ram base must be aligned to core mem"
			    " region size.");

  /** @todo Require external RAM to be on node 0 for now */
  FAIL_IF(c->ext_ram_node != 0,
			    "External RAM must reside on node 0");

  /* WARN: This only works with 1M core mem region size */
  if (c->ext_ram_size)
    {
      /* First core memory shadows */
      mem_coreid_base = c->ext_ram_base / c->core_mem_region;

      for (row = c->row_base; row < c->row_base+c->rows; row++)
	{
	  begin = ES_COREID(row, c->col_base);
	  end = begin + c->cols;
	  FAIL_IF(begin <= mem_coreid_base && mem_coreid_base < end,
				"External RAM shadows core memory");
	}
    }

#undef FAIL_IF
  return ES_OK;
}

/*! Calculate and fill in internal cluster configuration values not specified
 *  by user.
 *
 * @warning This must be called *after* es_validate_config
 *
 * @param[in]     esim     ESIM handle
 */
static void
es_fill_in_internal_cluster_cfg_values(es_state *esim)
{
  unsigned cols_per_node, rows_per_node;
  float ratio, best_ratio;

#if (!WITH_EMESH_NET) && !defined (ESIM_TEST)
  /* Without networking there can be only one node */
  ES_CLUSTER_CFG.nodes = 1;
  ES_CLUSTER_CFG.ext_ram_node = 0;
#endif

  /* Cluster settings */
  ES_CLUSTER_CFG.cores = ES_CLUSTER_CFG.rows * ES_CLUSTER_CFG.cols;
  ES_CLUSTER_CFG.cores_per_node = ES_CLUSTER_CFG.cores / ES_CLUSTER_CFG.nodes;

  /* Calculate number of columns and rows per node.
   * Optimize for most square-like configuration.
   */
  if (ES_CLUSTER_CFG.nodes == 1)
    {
      /* Trivial case */
      ES_CLUSTER_CFG.rows_per_node = ES_CLUSTER_CFG.rows;
      ES_CLUSTER_CFG.cols_per_node = ES_CLUSTER_CFG.cols;
    }
  else
    {
      ES_CLUSTER_CFG.cols_per_node = 0;
      ES_CLUSTER_CFG.rows_per_node = 0;

      /* Initialize with value worse than worst case */
      best_ratio =
       (float) (1 + max (ES_CLUSTER_CFG.cols, ES_CLUSTER_CFG.rows));

      cols_per_node = min(ES_CLUSTER_CFG.cols, ES_CLUSTER_CFG.cores_per_node);
      for (; cols_per_node >= 1; cols_per_node--)
	{
	  rows_per_node = ES_CLUSTER_CFG.cores_per_node / cols_per_node;
	  ratio = ( max ( ((float)cols_per_node), ((float)rows_per_node) ) ) /
		  ( min ( ((float)cols_per_node), ((float)rows_per_node) ) );

	  if (ratio >= best_ratio)
	    break;
	  if (ES_CLUSTER_CFG.cols % cols_per_node)
	    continue;
	  if (ES_CLUSTER_CFG.rows % rows_per_node)
	    continue;
	  if (ES_CLUSTER_CFG.cores_per_node % cols_per_node)
	    continue;
	  if ((rows_per_node * ES_CLUSTER_CFG.nodes * cols_per_node) /
	      ES_CLUSTER_CFG.cols != ES_CLUSTER_CFG.rows)
	    continue;

	  /* Found better candidate */
	  best_ratio = ratio;
	  ES_CLUSTER_CFG.cols_per_node = cols_per_node;
	  ES_CLUSTER_CFG.rows_per_node = rows_per_node;
	}
    }

}

/*! Calculate and fill in internal node configuration values not specified
 *  by user.
 *
 * @warning This must be called *after* es_validate_config and
 * es_fill_in_internal_node_cfg_values.
 *
 * @param[in]     esim     ESIM handle
 * @param[in,out] node     Node configuration
 * @param[in,out] cluster  Cluster configuration
 */
static void
es_fill_in_internal_node_cfg_values(es_state *esim)
{
  /* Node settings */
#if WITH_EMESH_NET
  ES_NODE_CFG.rank = esim->net.rank / ES_CLUSTER_CFG.cores_per_node;
  ES_CLUSTER_CFG.ext_ram_rank =
    ES_CLUSTER_CFG.ext_ram_node * ES_CLUSTER_CFG.cores_per_node;
#else
  ES_NODE_CFG.rank = 0;
  ES_CLUSTER_CFG.ext_ram_rank = 0;
#endif

  {
    unsigned node_row =
     (ES_NODE_CFG.rank * ES_CLUSTER_CFG.cols_per_node) / ES_CLUSTER_CFG.cols;
    ES_NODE_CFG.row_base = ES_CLUSTER_CFG.row_base +
      (ES_CLUSTER_CFG.rows_per_node * node_row);
    ES_NODE_CFG.col_base = ES_CLUSTER_CFG.col_base +
      (ES_CLUSTER_CFG.cols_per_node  * ES_NODE_CFG.rank) % ES_CLUSTER_CFG.cols;
  }
}

/*! Open ESIM shared memory file
 *
 * Open SHM file shared between simulator processes on this node.
 * Use advisory file locking to avoid problem with stale SHM file due to crash.
 *
 * @param[out]    esim     ESIM handle
 * @param[in]     name     name of shm file
 * @param[in,out] flock    Advisory file lock
 *
 * @return ES_OK on success
 */
static int
es_open_shm_file(es_state *esim, char *name, struct flock *flock)
{
  unsigned creator;
  int fd, error, oflag;

  creator = 0;
  fd = -1;
  error = 0;

  /* File must exist when connecting as client */
  oflag = esim->is_client ? (O_RDWR) : (O_RDWR|O_CREAT);

  fd = shm_open(name, oflag, S_IRUSR|S_IWUSR);
  if (fd == -1)
    return -errno;

  if (esim->is_client)
    goto out;

  /* Try to get exclusive lock on shm file */
  flock->l_type   = F_WRLCK;
  error = fcntl(fd, F_SETLK, flock);

  if (!error)
    {
      /* We got exclusive lock */
      creator = 1;

      /* Truncate to 0 to remove any old state */
      if (ftruncate(fd, 0) == -1)
	return -errno;
    }
  else if (error == -1 && (errno == EACCES || errno == EAGAIN))
    {
      creator = 0;
    }
  else
    {
#ifdef ES_DEBUG
      fprintf(stderr, "es_init:shm_open: errno=%d\n", errno);
#endif
      return -errno;
    }

out:
  strncpy(esim->shm_name, name, sizeof(esim->shm_name)-1);
  esim->shm_name[sizeof(esim->shm_name)-1] = '\0';
  esim->fd = fd;
  esim->creator = creator;

  return ES_OK;
}

/*! Truncate ESIM SHM file to right size
 *
 * Truncate ESIM SHM file to right size to accommodate cluster configuration,
 * node configuration, core's state and core's memory.
 *
 * @param[in,out] esim     ESIM handle
 * @param[in]     n        Node configuration
 * @param[in]     c        Cluster configuration
 *
 * @return ES_OK on success
 */
static int
es_truncate_shm_file(es_state *esim, es_node_cfg *n, es_cluster_cfg *c)
{
  size_t size, per_core, cores;

  /* Calculate MMAP file size. */
#if WITH_EMESH_NET
  /* This function is called before es_net_init(), so we don't know how many
   * nodes there are in the cluster. Assume worst case (1 node) and allocate
   * memory for all cores + external RAM.
   */
#endif
  cores = c->rows * c->cols;
  per_core = c->core_mem_region + ES_SHM_CORE_STATE_SIZE;
  size = ES_SHM_CONFIG_SIZE + (cores * per_core) + c->ext_ram_size;

  if (ftruncate(esim->fd, size) == -1)
    {
#ifdef ES_DEBUG
      fprintf(stderr, "es_init:ftruncate: errno=%d\n", errno);
#endif
      return -errno;
    }
  esim->shm_size = size;

  return ES_OK;
}

/*! Wait for creating process to truncate SHM file to correct size
 *
 * Wait for creating sim process (the one with excluse lock) to truncate SHM
 * file.
 *
 * @param[in,out] esim   ESIM handle
 * @param[in,out] flock  advisory file lock to use
 *
 * @return ES_OK on success
 */
static int
es_wait_truncate_shm_file(es_state *esim, struct flock *flock)
{
  struct stat st;

  /* Wait until creating process has downgraded lock
     (and truncated shm file) */
  flock->l_type = F_RDLCK;

  if (fcntl(esim->fd, F_SETLKW, flock))
    {
      return -errno;
    }
  if (fstat(esim->fd, &st) == -1)
    {
#ifdef ES_DEBUG
      fprintf(stderr, "es_init:stat: errno=%d\n", errno);
#endif
      return -errno;
    }

  esim->shm_size = st.st_size;
  return ES_OK;

}

/*! Reset esim state
 *
 * @param[out] esim     ESIM handle
 */
inline static void
es_state_reset(es_state *esim)
{
  memset((void*) esim, 0, sizeof(es_state));
  esim->fd = -1;
}

/*! Initialize esim
 *
 * Actual implementation.
 *
 * @param[in,out] esim          pointer to ESIM handle
 * @param[in]     cluster       Cluster configuration
 * @param[in]     coreid_hint   Coreid hint (not used w. esim-net)
 * @param[in]     client         If true, connect as client.
 *
 * @return On success returns ES_OK and sets handle to allocated
 *         esim structure. On error returns a negative error number and sets
 *         handle to NULL.
 */
static int
es_init_impl(es_state **handle,
	es_cluster_cfg cluster,
	unsigned coreid_hint,
	const char *session_name,
	int client)
{
  int error;
  char shm_name[256];
  es_node_cfg node;
  es_state *esim;
  volatile es_shm_header *shm;
  unsigned msecs_wait;
  unsigned have_core_0;   /* Special case when node first core and row is 0 */
  unsigned sim_processes; /* On this node, core 0 does not have sim proc */
  struct flock flock;      /* Used when opening shm file */

  error = 0;
  msecs_wait = 0;

  flock.l_whence = SEEK_SET;
  flock.l_start  = 0;
  flock.l_len    = 16;      /* Whatever, but must be same in all processes */

  *handle = NULL;
  esim = (es_state *) malloc(sizeof(es_state));
  if (esim == NULL)
    {
      fprintf(stderr, "ESIM: Out of memory\n");
      error = -ENOMEM;
      goto err_out;
    }
  es_state_reset(esim);

  esim->is_client = client;
  esim->session_name = session_name;

  if (session_name)
    {
      snprintf(shm_name, sizeof(shm_name)/sizeof(char)-1, "/esim.u.%d-%s",
	       getuid(), session_name);
    }
  else if (!client && cluster.rows == 1 && cluster.cols == 1)
    {
      /* Use a unique (PID) private name when there is exactly one
       * core and no session name is provided. */
      snprintf(shm_name, sizeof(shm_name)/sizeof(char)-1, "/esim.u%d.p%d",
	       getuid(), getpid());
    }
  else
    {
      snprintf(shm_name, sizeof(shm_name)/sizeof(char)-1, "/esim.u%d",
	       getuid());
    }

  msecs_wait = 0;
  do
    {
      if ((error = es_open_shm_file(esim, shm_name, &flock)) == ES_OK)
	break;

      if (!esim->is_client)
	break;

      /* Notify user we're waiting once */
      if (msecs_wait == 0)
	fprintf(stderr, "ESIM: Will wait 10s for core simulators\n");

      usleep(200000);
      msecs_wait += 200;
    }
  while (msecs_wait <= 10000);
  if (error != ES_OK)
    {
      fprintf(stderr, "ESIM: Could not open esim file `/dev/shm%s'\n", shm_name);
      goto err_out;
    }

  /* Silently truncate physical memory to below MMR region */
  cluster.core_phys_mem = min (cluster.core_phys_mem, ES_CORE_MMR_BASE);

#if WITH_EMESH_NET
  /* Initialize networking */
  if ((error = es_net_init(esim, &cluster)) != ES_OK)
    goto err_out;
#endif

  /* If this process created the file, set its size */
  if (esim->creator)
    {
      if ((error = es_validate_cluster_cfg(&cluster)) != ES_OK)
	{
	  goto err_out;
	}

      if ((error = es_truncate_shm_file(esim, &node, &cluster)) != ES_OK)
	{
	  fprintf(stderr, "ESIM: Could not truncate  esim file `/dev/shm%s'\n",
		  shm_name);
	  goto err_out;
	}

      /* Downgrade exclusive lock to shared lock */
      flock.l_type = F_RDLCK;
      if (fcntl(esim->fd, F_SETLK, &flock))
	{
	  error = -errno;
	  goto err_out;
	}
    }

  else /* if (!creator) */
    {
      if ((error = es_wait_truncate_shm_file(esim, &flock)) != ES_OK)
	goto err_out;
    }

  shm = (es_shm_header*) mmap(NULL,
			      esim->shm_size,
			      PROT_READ|PROT_WRITE, MAP_SHARED,
			      esim->fd,
			      (off_t) 0);
  if (shm == MAP_FAILED)
    {
      fprintf(stderr, "ESIM: mmap failed\n");
      error = -EINVAL;
      goto err_out;
    }

  esim->shm = shm;
  esim->coreid = 0;
  esim->cores_mem = ((uint8_t *) shm) + ES_SHM_CONFIG_SIZE;

  if (esim->creator)
    {
      /* Copy over cluster and node config structs to shared memory */
      memmove((void *) &ES_CLUSTER_CFG, (void *) &cluster,
	     sizeof(es_cluster_cfg));
      memmove((void *) &ES_NODE_CFG, (void *) &node,
	     sizeof(es_node_cfg));

      /* Signal waiting processes that shared memory is ready */
      shm->shm_initialized = 1;
    }
  else /* if (!creator) */
    {
      /* Busy wait for creating process */
      msecs_wait = 0;
      while (!shm->shm_initialized && msecs_wait <= 3000)
	{
	  usleep(5000);
	  msecs_wait += 5;
	}
      if (!shm->shm_initialized)
	{
	  fprintf(stderr, "ESIM: Timed out waiting on shared memory.\n");
	  error = -ETIME;
	  goto err_out;
	}
    }

  if (esim->creator)
    {
      es_fill_in_internal_cluster_cfg_values(esim);
      es_fill_in_internal_node_cfg_values(esim);

      /** @todo Determine what to do with this edge-case and WITH_EMESH_NET. */
      have_core_0 = (!ES_NODE_CFG.col_base && !ES_NODE_CFG.row_base);

      /* Coreid 0 is invalid so we should not wait for it */
      sim_processes = have_core_0 ?
	ES_CLUSTER_CFG.cores_per_node-1 :
	ES_CLUSTER_CFG.cores_per_node;

      /* Initialize pthread barriers */
      {
	pthread_barrierattr_t barr_attr;
	pthread_mutexattr_t   mutex_attr;
	pthread_condattr_t    cond_attr;

	/* Need shared process attributes */
	pthread_barrierattr_init(&barr_attr);
	pthread_barrierattr_setpshared(&barr_attr, PTHREAD_PROCESS_SHARED);
	pthread_mutexattr_init(&mutex_attr);
	pthread_mutexattr_setpshared(&mutex_attr, PTHREAD_PROCESS_SHARED);
	pthread_condattr_init(&cond_attr);
	pthread_condattr_setpshared(&cond_attr, PTHREAD_PROCESS_SHARED);

	/* Initialize barriers */
	pthread_barrier_init((pthread_barrier_t *) &esim->shm->run_barrier,
			     &barr_attr,
			     sim_processes);
	pthread_barrier_init((pthread_barrier_t *) &esim->shm->exit_barrier,
			     &barr_attr,
			     sim_processes);

	/* Initialize client mutex */
	pthread_mutex_init((pthread_mutex_t *) &esim->shm->client_mtx,
			   &mutex_attr);

	/* ... and client cond vars */
	pthread_cond_init((pthread_cond_t *) &esim->shm->client_exit_cond,
			  &cond_attr);
	pthread_cond_init((pthread_cond_t *) &esim->shm->client_run_cond,
			  &cond_attr);


	/* Cleanup */
	pthread_barrierattr_destroy(&barr_attr);
	pthread_mutexattr_destroy(&mutex_attr);
	pthread_condattr_destroy(&cond_attr);
      }

      /* Signal waiting processes that (shared) configuration is ready */
      shm->cfg_initialized = 1;
    }
  else /* if (!creator) */
    {
      /* Busy wait for creating process */
      msecs_wait = 0;
      while (!shm->cfg_initialized && msecs_wait <= 3000)
	{
	  usleep(5000);
	  msecs_wait += 5;
	}
      if (!shm->cfg_initialized)
	{
	  fprintf(stderr, "ESIM: Timed out waiting on config.\n");
	  error = -ETIME;
	  goto err_out;
	}
    }

  /* If external RAM is on this node, set up pointer */
  if (ES_CLUSTER_CFG.ext_ram_node == ES_NODE_CFG.rank)
    {
      esim->ext_ram = ((uint8_t *) shm) + ES_SHM_CONFIG_SIZE +
	ES_CLUSTER_CFG.cores *
	  (ES_CLUSTER_CFG.core_mem_region + ES_SHM_CORE_STATE_SIZE);
    }

  /* Set coreid */
  if (!esim->is_client)
    {
#if WITH_EMESH_NET
      /* Calculate coreid from MPI rank */
      if ((error = es_net_set_coreid_from_rank(esim)) != ES_OK)
	{
	  fprintf(stderr, "ESIM: Could not set coreid.\n");
	  goto err_out;
	}
#else
      /* Set coreid from hint */
      if ((error = es_set_coreid(esim, coreid_hint)) != ES_OK)
	{
	  if (error == -EADDRINUSE)
	    {
	      fprintf(stderr,
		      "ESIM: Could not set coreid to `%u'. Already "
		      "reserved by another simulator process\n",
		      coreid_hint);
	    }
	  else
	    {
	      fprintf(stderr,
		      "ESIM: Could not set coreid to `%u'.\n",
		      coreid_hint);
	    }
	  goto err_out;
	}
#endif
    }

#if WITH_EMESH_NET
  /* Need coreid and this_core_cpu_state */
  if ((error = es_net_init_mmr(esim)) != ES_OK)
    {
      goto err_out;
    }
  /* Now when coreid is set, we can expose SRAM to other processes */
  if ((error = es_net_init_mpi_win(esim)) != ES_OK)
    {
      goto err_out;
    }
#endif

#if !WITH_EMESH_NET
  /* Notify sim processes client is connected */
  if (esim->is_client)
    {
      pthread_mutex_lock((pthread_mutex_t *) &shm->client_mtx);

      /* Fail early if any core is in the process of exiting. */
      if (esim->shm->exiting)
	{
	  if (!esim->shm->clients)
	    pthread_cond_broadcast((pthread_cond_t *) &shm->client_exit_cond);

	  pthread_mutex_unlock((pthread_mutex_t *) &shm->client_mtx);

	  fprintf(stderr, "ESIM: Remote is exiting.\n");
	  error = -EPIPE;
	  goto err_out;
	}

      /* Only support one client for now */
      if (esim->shm->clients)
	{
	  pthread_mutex_unlock((pthread_mutex_t *) &shm->client_mtx);

	  fprintf(stderr, "ESIM: Maximum number of clients already connected.\n");
	  error = -EBUSY;
	  goto err_out;
	}

      esim->shm->clients += 1;

      pthread_mutex_unlock((pthread_mutex_t *) &shm->client_mtx);
    }
#endif

#ifdef ES_DEBUG
  fprintf(stderr,
	  "es_init: shm=0x%llx shm_size=%lld fd=%d coreid=%d shm_name=\"%s\"\n",
	  (ulong64) esim->shm, (ulong64) esim->shm_size, esim->fd,
	  esim->coreid, esim->shm_name);
#endif

ok_out:
  esim->initialized = 1;
  *handle = esim;
  return ES_OK;

err_out:
  es_fini(esim);
  return error;
}


/*! Initialize esim
 *
 * @param[in,out] handle        pointer to ESIM handle
 * @param[in]     cluster       Cluster configuration
 * @param[in]     coreid_hint   Coreid hint (not used w. esim-net)
 * @param[in]     client         If true, connect as client.
 *
 * @return On success returns ES_OK and sets handle to allocated
 *         esim structure. On error returns a negative error number and sets
 *         handle to NULL.
 */
int
es_init(es_state **handle, es_cluster_cfg cluster, unsigned coreid_hint,
	const char *session_name)
{
  return es_init_impl(handle, cluster, coreid_hint, session_name, 0);
}

/*! Connect to eMesh simulator as a client
 *
 * @param[in,out] handle          pointer to ESIM handle
 *
 * @return On success returns ES_OK and sets handle to allocated
 *         esim structure. On error returns a negative error number and sets
 *         handle to NULL.
 */
int
es_client_connect(es_state **handle, const char *session_name)
{
  int rc;
  es_cluster_cfg cluster;

  if ((rc = es_init_impl(handle, cluster, 0, session_name, 1)) != ES_OK)
    return rc;

  es_wait_run(*handle);

  return ES_OK;
}

static void
es_client_stop_cores (es_state *esim)
{
  unsigned i, j;
  uint64_t addr, coreid;
  uint32_t stopcmd = 1;

  for (i = ES_CLUSTER_CFG.row_base;
       i < ES_CLUSTER_CFG.row_base + ES_CLUSTER_CFG.rows;
       i++)
    {
      for (j = ES_CLUSTER_CFG.col_base;
	   j < ES_CLUSTER_CFG.col_base + ES_CLUSTER_CFG.cols;
	   j++)
	{
	  coreid = ES_COREID(i, j);
	  if (coreid == 0)
	    continue;

	  addr = (coreid << 20) | 0xf0000 | (H_REG_SCR_SIMCMD << 2);
	  es_mem_store (esim, addr, 4, (uint8_t *) &stopcmd);
	}
    }
}

/*! Disconnect client from eMesh simulator
 *
 * @param[in,out] esim          pointer to ESIM handle
 * @param[in]     stop          true if simulation should be stopped
 */
void
es_client_disconnect(es_state *esim, bool stop)
{
  if (!esim)
    return;

  if (stop)
    es_client_stop_cores (esim);

  es_wait_exit(esim);
  es_fini(esim);
}

/*! Get raw pointer to a memory region
 *
 * @param[in]     esim          pointer to ESIM handle
 * @param[in]     addr          address
 * @param[in]     size          size
 *
 * @return NULL on failure, base pointer on success.
 */
volatile void
*es_client_get_raw_pointer (es_state *esim, uint64_t addr, uint64_t size)
{
  es_transl transl;

  if (!esim || !esim->ready)
    return NULL;

  es_addr_translate(esim, &transl, addr);

  /* Due to instruction caching we must not return a pointer to core memory */
  if (transl.location != ES_LOC_RAM)
    return NULL;

  if (transl.in_region < size)
    return NULL;

  return (volatile void *) transl.mem;
}


/*! Check if ESIM is initialized
 *
 * @param[in] esim     ESIM handle
 *
 * @return ES_OK if ESIM is initialized, -EINVAL otherwise.
 */
inline int
es_initialized(const es_state* esim)
{
  return ((esim && esim->initialized == 1) ? ES_OK : -EINVAL);
}

/*! Cleanup after ESIM
 *
 * Unmaps mmaped memory, closes SHM file and resets esim handle
 *
 * @param[in,out] esim     ESIM handle
 */
void
es_fini(es_state *esim)
{
#ifdef ES_DEBUG
  fprintf(stderr, "es_fini\n");
#endif

  if (!esim)
    return;

#if WITH_EMESH_NET
  es_net_fini(esim);
#endif

  if (esim->shm)
    munmap((void *) esim->shm, esim->shm_size);

  /* Unlink before close, to avoid race in between file locks are released and
   * unlink.
   */
  if (esim->creator)
    shm_unlink(esim->shm_name);

  /* Close file, will also release all advisory file locks */
  if (esim->fd >= 0)
    close(esim->fd);

  es_state_reset(esim);
  free(esim);
}

static void
es_set_ready(es_state *esim)
{
  if (esim->ready)
      return;

  esim->ready = 1;
  if (!esim->is_client)
    es_atomic_incr32((uint32_t *) &esim->shm->node_core_sims_ready);
}

/*! Wait on other sim processes before starting simulation
 *
 * @param[in,out] esim     ESIM handle
 */
void
es_wait_run(es_state *esim)
{
  /** @todo Would be nice to support Ctrl-C here */

  es_set_ready(esim);

#if WITH_EMESH_NET
      es_net_wait_run(esim);
#else
  if (!esim->is_client)
    {
      pthread_barrier_wait((pthread_barrier_t *) &esim->shm->run_barrier);
      if (esim->creator)
	{
	  pthread_mutex_lock((pthread_mutex_t *) &esim->shm->client_mtx);
	  pthread_cond_broadcast((pthread_cond_t *) &esim->shm->client_run_cond);
	  pthread_mutex_unlock((pthread_mutex_t *) &esim->shm->client_mtx);
	}
    }
  else /* esim->is_client */
    {
      if (esim->shm->node_core_sims_ready < ES_CLUSTER_CFG.cores_per_node)
	{
	  pthread_mutex_lock((pthread_mutex_t *) &esim->shm->client_mtx);
	  pthread_cond_wait((pthread_cond_t *) &esim->shm->client_run_cond,
			    (pthread_mutex_t *) &esim->shm->client_mtx);
	  pthread_mutex_unlock((pthread_mutex_t *) &esim->shm->client_mtx);
	}
      es_set_ready(esim);
    }
#endif
}

/*! Wait on other sim processes before exiting after simulation
 *
 * @param[in] esim     ESIM handle
 */
void
es_wait_exit(es_state *esim)
{
  /** @todo Would be nice to support Ctrl-C here */

#if WITH_EMESH_NET
  es_net_wait_exit(esim);
#else

  /* Exit early */
  if (!esim->ready && !esim->is_client)
    return;

  if (!esim->is_client)
    {
      /* Inform any connecting client we want to exit */
      esim->shm->exiting = 1;

      /* Wait for clients */
      pthread_mutex_lock((pthread_mutex_t *) &esim->shm->client_mtx);
      if (esim->shm->clients)
	{
	  pthread_cond_wait((pthread_cond_t *) &esim->shm->client_exit_cond,
			    (pthread_mutex_t *) &esim->shm->client_mtx);
	}
      pthread_mutex_unlock((pthread_mutex_t *) &esim->shm->client_mtx);

      /* Wait for other sim processes */
      pthread_barrier_wait((pthread_barrier_t *) &esim->shm->exit_barrier);
    }
  else
    {
      pthread_mutex_lock((pthread_mutex_t *) &esim->shm->client_mtx);
      esim->shm->clients -= 1;
      if (esim->shm->exiting && !esim->shm->clients)
	pthread_cond_broadcast((pthread_cond_t *) &esim->shm->client_exit_cond);
      pthread_mutex_unlock((pthread_mutex_t *) &esim->shm->client_mtx);
    }
#endif
}

/*! Check whether a given core-id is valid for current configuration
 *
 * @param[in] esim     ESIM handle
 * @param[in] coreid   Coreid
 *
 * @return ES_OK on success, otherwise -EINVAL
 */
int
es_valid_coreid(const es_state *esim, unsigned coreid)
{
  unsigned row = ES_CORE_ROW(coreid);
  unsigned col = ES_CORE_COL(coreid);
  int valid = (coreid &&
	  ES_NODE_CFG.row_base <= row &&
	  row < ES_NODE_CFG.row_base + ES_CLUSTER_CFG.rows_per_node &&
	  ES_NODE_CFG.col_base <= col &&
	  col < ES_NODE_CFG.col_base + ES_CLUSTER_CFG.cols_per_node);

  return valid ? ES_OK : -EINVAL;
}

/*! Set coreid for this sim process
 *
 * Set coreid for this sim process
 * This can be done at most once.
 *
 * @param[in,out] esim     ESIM handle
 * @param[in]     coreid   Coreid
 *
 * @return ES_OK on success
 */
int
es_set_coreid(es_state *esim, unsigned coreid)
{
  es_shm_core_state_header *header;
  int rc;

  /* Verify that coreid was not already set */
  if (esim->coreid != 0)
    return -EINVAL;

  if (es_valid_coreid(esim, coreid) != ES_OK)
    return -EINVAL;

  header = (es_shm_core_state_header *) es_shm_core_base(esim, coreid);

  if (!header)
    return -EINVAL;

  if (es_cas32(&header->reserved, 0, 1))
    return -EADDRINUSE;

  esim->coreid = coreid;

  esim->this_core_state_header = (es_shm_core_state_header *) header;
  esim->this_core_cpu_state = es_shm_core_base(esim, coreid) +
			      ES_SHM_CORE_STATE_HEADER_SIZE;
  esim->this_core_mem = (uint8_t *) header + ES_SHM_CORE_STATE_SIZE;

  return ES_OK;
}

/*! Set (overwrite) CPU state for this sim process
 *
 * @param[in,out] esim     ESIM handle
 * @param[in]     cpu      Pointer to new CPU data
 * @param[in]     size     Size of CPU data
 *
 * @return Pointer to CPU state address or NULL
 */
void *
es_set_cpu_state(es_state *esim, void *cpu, size_t size)
{

  if (es_valid_coreid(esim, esim->coreid) != ES_OK)
    return NULL;

  if (esim->this_core_cpu_state == cpu)
    return cpu;

  memset((void *)esim->this_core_cpu_state, 0,
	 ES_SHM_CORE_STATE_SIZE - ES_SHM_CORE_STATE_HEADER_SIZE);
  memmove((void *)esim->this_core_cpu_state, cpu, size);

  return (void *) esim->this_core_cpu_state;
}

/*! Get copy of cluster configuration
 *
 * @param[in]  esim     ESIM handle
 * @param[out] cfg      target configuration
 */
void
es_get_cluster_cfg(const es_state *esim, es_cluster_cfg *cfg)
{
  memcpy((void *) cfg, (void *) &ES_CLUSTER_CFG, sizeof(*cfg));
}

/*! Dump node and cluster configuration
 *
 * @param[in] esim     ESIM handle
 */
void
es_dump_config(const es_state *esim)
{
  fprintf(stderr,
	  "es_cluster_cfg = {\n"
	  "  .row_base        = %d\n"
	  "  .col_base        = %d\n"
	  "  .rows            = %d\n"
	  "  .cols            = %d\n"
	  "  .core_mem_region = %zu\n"
	  "  .core_phys_mem   = %zu\n"
	  "  .ext_ram_node    = %d\n"
	  "  .ext_ram_base    = 0x%.16llx\n"
	  "  .ext_ram_size    = %llu\n"
	  "  .cores           = %d\n"
	  "  .nodes           = %d\n"
	  "  .cores_per_node  = %d\n"
	  "  .rows_per_node   = %d\n"
	  "  .cols_per_node   = %d\n"
	  "  .ext_ram_rank    = %d\n"
	  "}\n",
	  ES_CLUSTER_CFG.row_base,
	  ES_CLUSTER_CFG.col_base,
	  ES_CLUSTER_CFG.rows,
	  ES_CLUSTER_CFG.cols,
	  ES_CLUSTER_CFG.core_mem_region,
	  ES_CLUSTER_CFG.core_phys_mem,
	  ES_CLUSTER_CFG.ext_ram_node,
	  (ulong64) ES_CLUSTER_CFG.ext_ram_base,
	  (ulong64) ES_CLUSTER_CFG.ext_ram_size,
	  ES_CLUSTER_CFG.cores,
	  ES_CLUSTER_CFG.nodes,
	  ES_CLUSTER_CFG.cores_per_node,
	  ES_CLUSTER_CFG.rows_per_node,
	  ES_CLUSTER_CFG.cols_per_node,
	  ES_CLUSTER_CFG.ext_ram_rank);
  fprintf(stderr,
	  "es_node_cfg = {\n"
	  "  .rank     = %d\n"
	  "  .row_base = %d\n"
	  "  .col_base = %d\n"
	  "}\n",
	  ES_NODE_CFG.rank,
	  ES_NODE_CFG.row_base,
	  ES_NODE_CFG.col_base);
  fprintf(stderr,
	  ".esim = {\n"
	  "  .initialized            = %d\n"
	  "  .ready                  = %d\n"
	  "  .coreid                 = %d\n"
	  "  .fd                     = %d\n"
	  "  .creator                = %d\n"
	  "  .shm_name               = %s\n"
	  "  .shm_size               = %llu\n"
	  "  .shm                    = 0x%p\n"
	  "  .cores_mem              = 0x%p\n"
	  "  .this_core_mem          = 0x%p\n"
	  "  .this_core_state_header = 0x%p\n"
	  "  .this_core_cpu_state    = 0x%p\n"
	  "  .ext_ram                = 0x%p\n"
	  "}\n",
	  esim->initialized,
	  esim->ready,
	  esim->coreid,
	  esim->fd,
	  esim->creator,
	  esim->shm_name,
	  (ulong64) esim->shm_size,
	  esim->shm,
	  esim->cores_mem,
	  esim->this_core_mem,
	  esim->this_core_state_header,
	  esim->this_core_cpu_state,
	  esim->ext_ram);
}

inline size_t
es_get_core_mem_region_size(const es_state *esim)
{
  return ES_CLUSTER_CFG.core_mem_region;
}
inline size_t
es_get_core_phys_mem_size(const es_state *esim)
{
  return ES_CLUSTER_CFG.core_phys_mem;
}
inline unsigned
es_get_coreid(const es_state *esim)
{
  return esim->coreid;
}


/* Profiling */

static uint64_t
manhattan_distance(unsigned a, unsigned b)
{
  unsigned rowa = ES_CORE_ROW(a);
  unsigned rowb = ES_CORE_ROW(b);
  unsigned cola = ES_CORE_COL(a);
  unsigned colb = ES_CORE_COL(b);

  unsigned row_distance = max(rowa, rowb) - min(rowa, rowb);
  unsigned col_distance = max(cola, colb) - min(cola, colb);

  return row_distance + col_distance;
}

static unsigned
bound_coreid_to_cluster(es_state *esim, unsigned coreid)
{
  unsigned row = ES_CORE_ROW(coreid);
  unsigned col = ES_CORE_COL(coreid);

  /* Do we need to route in N/S direction? */
  bool outside_cluster_we =
    col < ES_CLUSTER_CFG.col_base ||
    col >= ES_CLUSTER_CFG.col_base + ES_CLUSTER_CFG.cols;

  col = max(col, ES_CLUSTER_CFG.col_base);
  col = min(col, ES_CLUSTER_CFG.col_base + ES_CLUSTER_CFG.cols - 1);

  if (outside_cluster_we)
    row = ES_CORE_ROW(esim->coreid);
  else
    {
      row = max(row, ES_CLUSTER_CFG.row_base);
      row = min(row, ES_CLUSTER_CFG.row_base + ES_CLUSTER_CFG.rows - 1);
    }

  return ES_COREID(row, col);
}

/*! Model a load delay
 *
 * This can be used to model both fetch and load.
 * The function only models the NoC delay, not register stalls etc.
 *
 * @param[in] esim     ESIM handle
 * @param[in] addr     target address
 */
unsigned
es_profile_load_stall(es_state *esim, address_word addr)
{
  unsigned tgt_coreid;
  unsigned distance, delay;

  /* TODO: We don't model bank conflicts */
  if (!ES_ADDR_IS_GLOBAL(addr))
    return ES_ADDR_IS_MMR(addr) ? 4 : 0;


  tgt_coreid = ES_ADDR_TO_CORE(addr);
  tgt_coreid = bound_coreid_to_cluster(esim, tgt_coreid);

  distance = manhattan_distance(esim->coreid, tgt_coreid);

  /* TODO: We don't model network push-back / congestion */

  /* This 'formula' adapted from epiphany-examples.git/emesh/emesh-read-latency
   * (distance * 3) can be written as (1.5 * rMesh + 1.5 * cMesh).
   * The full formula might be (I'm guessing here):
   * (2) routerA->network + (rMesh delay (1.5 * distance)) +
   * (2) routerB->memB + (2) memB->routerB +
   * (2) routerB->network + (cMesh delay (1.5 * distance)) +
   * (2) network->routerA + (2) routerA->coreA regfile.
   *
   * NB: Since this function is used for modeling both instruction fetch and
   * load operations, the caller must add the necessary delays for e.g,
   * register stalls.  */
  delay = (distance * 3);

  if (ES_ADDR_IS_MMR(addr))
    delay += 4;

  if (ES_ADDR_IS_EXT_RAM(addr)) {
    /* Rough estimate from testing on Parallella,
     * but it should definately be in the ballpark. */
    delay += 390;
  }

  return delay;
}

/*! Model a store delay
 *
 * @param[in] esim     ESIM handle
 * @param[in] addr     target address
 */
unsigned
es_profile_store_stall(es_state *esim, address_word addr)
{
  /* TODO: We don't model bank conflicts */
  if (!ES_ADDR_IS_GLOBAL(addr))
    return ES_ADDR_IS_MMR(addr) ? 4 : 0;

  /* We're not modeling push-back yet but since off-chip is an order of
   * magnitude slower, add some delay so at least it will show up */
  if (ES_ADDR_IS_EXT_RAM(addr))
    return 2;

  return 0;
}
