/*  This file is part of the program GDB, the GNU debugger.

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
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    */

#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

#define WANT_CPU epiphanybf
#define WANT_CPU_EPIPHANYBF

#include "sim-main.h"
#include "hw-main.h"
#include "hw-device.h"
#include "sim-types.h"
#include "epiphany-desc.h"

#include "cpu.h"

#if WITH_EMESH_SIM
#include "esim/esim.h"
#else
#error "I need WITH_EMESH_SIM. Enable with --enable-emesh-sim"
#endif

/* DEVICE


   epiphany_dma - epiphany dma controller for one channel


   DESCRIPTION


   Implements a dma controller for one channel.


   PROPERTIES

   none

   PORTS

   none
   @todo investigate which ports are needed

   */



union dma_config {
  uint32_t reg;
  struct {
    unsigned dmaen:1;
    unsigned master:1;
    unsigned chainmode:1;
    unsigned startup:1;
    unsigned irqen:1;
    unsigned datasize:2;
    unsigned _rsvd1:3;
    unsigned msgmode:1;
    unsigned _rsvd2:1;
    unsigned shift_src_in:1;
    unsigned shift_dst_in:1;
    unsigned shift_src_out:1;
    unsigned shift_dst_out:1;
    uint16_t next_ptr;
  } __attribute__((packed));
} __attribute__((packed));

union dma_count {
  uint32_t reg;
  struct {
    uint16_t inner_count;
    uint16_t outer_count;
  } __attribute__((packed));
} __attribute__((packed));

union dma_status {
  uint32_t reg;
  struct {
    unsigned dmastate:4;
    unsigned _rsv1:12;
    uint16_t curr_ptr;
  } __attribute__((packed));
} __attribute__((packed));

union dma_stride {
  uint32_t reg;
  struct {
    uint16_t src_stride;
    uint16_t dst_stride;
  } __attribute__((packed));
} __attribute__((packed));

struct epiphany_dma_regs {
  union dma_config	config;
  union dma_stride	stride;
  union dma_count	count;
  uint32_t		src_addr;
  uint32_t		dst_addr;
  uint32_t		auto0;
  uint32_t		auto1;
  union dma_status	status;
} __attribute__((packed));

struct epiphany_dma_descriptor {
  union dma_config	config;
  union dma_stride	inner_stride;
  union dma_count	count;
  union dma_stride	outer_stride;
  uint32_t		src_addr;
  uint32_t		dst_addr;
} __attribute__((packed));

struct epiphany_dma {
  int channel; /* 0 or 1 */
  struct hw_event *handler;
  /* current descriptor */
  struct epiphany_dma_descriptor desc;
};

enum epiphany_dma_reg_t {
  DMA_REG_CONFIG,
  DMA_REG_STRIDE,
  DMA_REG_COUNT,
  DMA_REG_SRC_ADDR,
  DMA_REG_DST_ADDR,
  DMA_REG_AUTO0,
  DMA_REG_AUTO1,
  DMA_REG_STATUS,
  DMA_REG_MAX,
};

enum epiphany_dma_state_t {
  DMA_STATE_IDLE	= 0x0,
  DMA_STATE_ACTIVE	= 0x5,
  DMA_STATE_SLAVE	= 0x6,
  DMA_STATE_WAIT	= 0xa,
  DMA_STATE_PAUSE	= 0xb,
  DMA_STATE_ERROR	= 0xd,
};


static const char * const epiphany_dma_regnames[] =
{
  "dma0config",  "dma0stride", "dma0count", "dma0srcaddr",
  "dma0dstaddr", "dma0auto0",  "dma0auto1", "dma0status",
  "dma1config",  "dma1stride", "dma1count", "dma1srcaddr",
  "dma1dstaddr", "dma1auto0",  "dma1auto1", "dma1status",
};

static const char *reg_name(struct hw *me, int regno)
{
  struct epiphany_dma *dma = hw_data (me);

  return epiphany_dma_regnames[regno + 8 * dma->channel];
}


static void epiphany_dma_hw_event_callback (struct hw *me, void *data);

static void
epiphany_dma_reschedule (struct hw *me, unsigned delay)
{
  struct epiphany_dma *dma = hw_data (me);
  if (dma->handler)
    {
      hw_event_queue_deschedule (me, dma->handler);
      dma->handler = NULL;
    }
  if (!delay)
    return;

  HW_TRACE ((me, "scheduling event in %u", delay));
  dma->handler = hw_event_queue_schedule (me, delay,
					  epiphany_dma_hw_event_callback, dma);
}


static struct epiphany_dma_regs *get_regs (struct hw *me);


static bool
epiphany_dma_load_desc(struct hw *me, struct epiphany_dma_regs *regs)
{
  address_word ret;
  struct epiphany_dma *dma = (struct epiphany_dma *) hw_data (me);

  if (regs->config.next_ptr % 8)
    return false;

  HW_TRACE ((me, "loading descriptor at %#x", regs->config.next_ptr));

  ret = sim_read (hw_system (me), regs->config.next_ptr,
		  (unsigned char *) &dma->desc, sizeof(dma->desc));

  if (ret != sizeof(dma->desc))
    return false;

  regs->config = dma->desc.config;
  regs->stride = dma->desc.inner_stride;
  regs->count = dma->desc.count;
  regs->src_addr = dma->desc.src_addr;
  regs->dst_addr = dma->desc.dst_addr;

  HW_TRACE ((me, "loaded descriptor %#x", regs->config.reg));

  return true;
}

static void
epiphany_dma_hw_event_callback (struct hw *me, void *data)
{
  struct epiphany_dma *dma = (struct epiphany_dma *) data;
  struct epiphany_dma_regs *regs = get_regs (me);
  SIM_CPU *current_cpu = STATE_CPU (hw_system (me), 0);
  const unsigned datasize = 1 << regs->config.datasize;
  address_word ilatst_addr;
  address_word shift_src, shift_dst;
  unsigned char buf[8];
  uint32_t ilatst_val;
  int ret;
  const char *reason = "unknown";

  dma->handler = NULL;

  /* could happen after loading descriptor */
  if (!regs->config.dmaen && !regs->config.startup)
    {
      reason = "invalid configuration";
      goto error; /* ???: or set state to idle */
    }

  if (regs->config.startup)
    {
      HW_TRACE ((me, "dma starting up"));

      if (!epiphany_dma_load_desc (me, regs))
	{
	  reason = "failed loading dma descriptor";
	  goto error;
	}

      regs->status.dmastate = DMA_STATE_ACTIVE;

      epiphany_dma_reschedule (me, 1 + sizeof(dma->desc) / 8);
      return;
    }
  else if (regs->config.master)
    {
      switch (regs->status.dmastate)
	{
	case DMA_STATE_ACTIVE:
	  if (!regs->count.outer_count)
	    {
	      HW_TRACE ((me, "dma transfer done"));

	      if (regs->config.irqen)
		{
		  ilatst_val = 1 << (H_INTERRUPT_DMA0 + dma->channel);
		  epiphanybf_h_all_registers_set (current_cpu, H_REG_SCR_ILATST,
						  ilatst_val);
		}

	      if (regs->config.msgmode && regs->dst_addr >= 0x100000)
		{
		  ilatst_addr =
		    (regs->dst_addr & ~0xfffffULL) |
		    (0xf0000 + (H_REG_SCR_ILATST << 2));
		  ilatst_val = 1 << H_INTERRUPT_MESSAGE;
		  ret = sim_write (hw_system (me), ilatst_addr,
				   (unsigned char *) &ilatst_val, 4);
		  if (ret != 4)
		    {
		      reason = "failed sending MSG interrupt";
		      goto error;
		    }
		}

	      if (!regs->config.chainmode)
		{
		  HW_TRACE ((me, "dma is complete"));
		  regs->status.dmastate = DMA_STATE_IDLE;
		  return;
		}

	      HW_TRACE ((me, "fetching next dma descriptor at %#x",
			 regs->config.next_ptr));
	      if (!epiphany_dma_load_desc (me, regs))
		{
		  reason = "failed loading dma descriptor";
		  goto error;
		}

	      epiphany_dma_reschedule (me, 1 + sizeof(dma->desc) / 8);
	      return;
	    }

	  if (!regs->count.inner_count)
	    {
	      reason = "invalid inner loop count";
	      goto error;
	    }

	  HW_TRACE ((me, "copying %u bytes from %#x to %#x", datasize,
		     regs->src_addr, regs->dst_addr));
	  ret = sim_read (hw_system (me), regs->src_addr, buf, datasize);
	  if (ret != datasize)
	    {
	      reason = "read failed";
	      goto error;
	    }
	  ret = sim_write (hw_system (me), regs->dst_addr, buf, datasize);
	  if (ret != datasize)
	    {
	      reason = "write failed";
	      goto error;
	    }

	  regs->count.inner_count--;
	  if (regs->count.inner_count)
	    {
	      regs->stride = dma->desc.inner_stride;
	      shift_src = regs->config.shift_src_in ? 16 : 0;
	      shift_dst = regs->config.shift_dst_in ? 16 : 0;
	    }
	  else
	    {
	      regs->count.outer_count--;
	      regs->count.inner_count = dma->desc.count.inner_count;
	      regs->stride = dma->desc.outer_stride;
	      shift_src = regs->config.shift_src_out ? 16 : 0;
	      shift_dst = regs->config.shift_dst_out ? 16 : 0;
	    }
	  regs->src_addr += (regs->stride.src_stride << shift_src);
	  regs->dst_addr += (regs->stride.dst_stride << shift_dst);

	  epiphany_dma_reschedule (me, 1);
	  return;
	case DMA_STATE_WAIT:
	case DMA_STATE_PAUSE:
	  /* ??? How do we reach here? */
	default:
	  reason = "internal error / invalid state";
	  goto error;
	}
    }
  else
    {
      /* TODO: Support slave mode */
      reason = "slave mode not implemented";
      goto error;
    }

  return;

error:
  regs->status.dmastate = DMA_STATE_ERROR;
  switch (STATE_ENVIRONMENT (CPU_STATE (current_cpu)))
    {
    case ALL_ENVIRONMENT:
    case USER_ENVIRONMENT:
      hw_abort (me, "dma error: %s", reason);
      break;
    default:
      HW_TRACE ((me, "dma error: %s", reason));
      break;
    }
}


/* Finish off the partially created hw device.  Attach our local
   callbacks.  Wire up our port names etc */

#if 0
static hw_io_read_buffer_method epiphany_dma_io_read_buffer;
static hw_io_write_buffer_method epiphany_dma_io_write_buffer;
#endif
static hw_port_event_method epiphany_dma_port_event;

static const struct hw_port_descriptor epiphany_dma_ports[] = {
  { "di", 0, 0, output_port, }, /* DMA Interrupt */
  { NULL, 0, 0, 0, },
};

static void
epiphany_dma_finish (struct hw *me)
{
  struct hw *parent = hw_parent (me);
  struct epiphany_dma *dma;

  HW_TRACE ((me, "epiphany_dma_finish"));

  dma = HW_ZALLOC (me, struct epiphany_dma);

  if (!strcmp (hw_path (me), "/epiphany_dma@0"))
    dma->channel = 0;
  else if (!strcmp (hw_path (me), "/epiphany_dma@1"))
    dma->channel = 1;
  else
    hw_abort (me,
	      "epiphany_dma_finish: invalid device name: `%s'. Device name must be one of /epiphany_dma@0 or /epiphany_dma@1",
	      hw_path (me));

  set_hw_data (me, dma);

#if 0
  set_hw_io_read_buffer (me, epiphany_dma_io_read_buffer);
  set_hw_io_write_buffer (me, epiphany_dma_io_write_buffer);
#endif
  set_hw_ports (me, epiphany_dma_ports);
  set_hw_port_event (me, epiphany_dma_port_event);
}

static void
epiphany_dma_port_event (struct hw *me,
		     int my_port,
		     struct hw *source,
		     int source_port,
		     int level)
{
  struct epiphany_dma *controller = hw_data (me);
  hw_abort (me, "epiphany_dma_port_event: not implemented");
}

#if 0
static void
epiphany_dma_signal(struct hw *me, address_word addr,
		    address_word nr_bytes, char *transfer, int sigrc)
{
  SIM_CPU *cpu;
  sim_cia cia;
  address_word ip;

  cpu = hw_system_cpu (me);
  cia = cpu ? CPU_PC_GET (cpu) : NULL_CIA;
  ip = CIA_ADDR (cia);

  switch (sigrc)
    {
    case SIM_SIGSEGV:
      sim_io_eprintf(hw_system(me),
		     "%s: %d byte %s to unmapped address 0x%llx at 0x%llx\n",
		     hw_path(me), (int) nr_bytes, transfer,
		     (ulong64) addr, (ulong64) ip);
      break;
    case SIM_SIGBUS:
      sim_io_eprintf(hw_system(me),
		     "%s: %d byte misaligned %s to unmapped address 0x%llx at "
		     "0x%llx\n",
		     hw_path(me), (int) nr_bytes, transfer,
		     (ulong64) addr, (ulong64) ip);
      break;
    default:
      sim_io_eprintf(hw_system(me),
		     "%s: %d byte %s to address 0x%llx at 0x%llx\n",
		     hw_path(me), (int) nr_bytes, transfer,
		     (ulong64) addr, (ulong64) ip);
      break;
    }
  hw_halt (me, sim_stopped, sigrc);
}
#endif

#if 0
static address_word
epiphany_dma_io_read_buffer (struct hw *me,
			 void *dest,
			 int space,
			 address_word base,
			 address_word nr_bytes)
{
  es_state *esim;

  esim = STATE_ESIM(hw_system(me));
#if (WITH_TARGET_ADDRESS_BITSIZE == 64)
  HW_TRACE ((me, "read 0x%16llx %llu", (ulong64) base, (ulong64) nr_bytes));
#else
  HW_TRACE ((me, "read 0x%08lx %u", (long) base, (unsigned int) nr_bytes));
#endif
  if (es_mem_load(esim, base, nr_bytes, (uint8_t *) dest) != ES_OK)
    {
      /** @todo What about SIGBUS (unaligned access) */
      epiphany_dma_signal(me, base, nr_bytes, "read", SIM_SIGSEGV);
      return 0;
    }
  else
    return nr_bytes;
}

static address_word
epiphany_dma_io_write_buffer (struct hw *me,
			  const void *source,
			  int space,
			  address_word base,
			  address_word nr_bytes)
{
  es_state *esim;

  esim = STATE_ESIM(hw_system(me));
#if (WITH_TARGET_ADDRESS_BITSIZE == 64)
  HW_TRACE ((me, "write 0x%16llx %llu", (ulong64) base, (ulong64) nr_bytes));
#else
  HW_TRACE ((me, "write 0x%08lx %u", (long) base, (unsigned int) nr_bytes));
#endif
  if (es_mem_store(esim, base, nr_bytes, (uint8_t *) source) != ES_OK)
    {
      /** @todo What about SIGBUS (unaligned access) */
      epiphany_dma_signal(me, base, nr_bytes, "write", SIM_SIGSEGV);
      return 0;
    }
  else
    return nr_bytes;
}
#endif


const struct hw_descriptor dv_epiphany_dma_descriptor[] = {
  { "epiphany_dma", epiphany_dma_finish, },
  { NULL },
};

static struct epiphany_dma_regs *
get_regs (struct hw *me)
{
  uint32_t *ptr;
  struct epiphany_dma *dma = hw_data (me);
  SIM_CPU *current_cpu = STATE_CPU (hw_system (me), 0);

  assert (current_cpu);
  assert (dma);

  if (dma->channel == 0)
    ptr = &(CPU (h_all_registers[H_REG_DMA0_CONFIG]));
  else if (dma->channel == 1)
    ptr = &(CPU (h_all_registers[H_REG_DMA1_CONFIG]));
  else
    hw_abort (me,
	      "epiphany_dma_finish: invalid device name: `%s'. Device name must be one of dma0 or dma1",
	      hw_path (me));

  return (struct epiphany_dma_regs *) ptr;
}

void
epiphany_dma_set_reg (struct hw *me, int regno, uint32_t val)
{
  struct epiphany_dma_regs *regs = get_regs (me);
  const union dma_config config = { .reg = val };
  const union dma_count  count  = { .reg = val };
  const union dma_status status = { .reg = val };
  const union dma_stride stride = { .reg = val };

  switch (regno)
  {
  case DMA_REG_CONFIG:
    if (regs->status.dmastate != DMA_STATE_IDLE)
      {
	regs->status.dmastate = DMA_STATE_ERROR;
	epiphany_dma_reschedule (me, 0);
	break;
      }

    regs->config = config;
    if (config.dmaen)
      {
	regs->status.dmastate = DMA_STATE_ACTIVE;
	epiphany_dma_reschedule (me, 1);
      }
    else if (config.startup)
      {
	regs->status.dmastate = DMA_STATE_ACTIVE;
	epiphany_dma_reschedule (me, 1);
      }
    break;
  case DMA_REG_STRIDE:
    regs->stride = stride;
    break;
  case DMA_REG_COUNT:
    regs->count = count;
    break;
  case DMA_REG_SRC_ADDR:
    regs->src_addr = val;
    break;
  case DMA_REG_DST_ADDR:
    regs->dst_addr = val;
    break;
  case DMA_REG_AUTO0:
    regs->auto0 = val;
    break;
  case DMA_REG_AUTO1:
    regs->auto1 = val;
    break;
  case DMA_REG_STATUS:
    /* regs->status = status; */
    break;
  default:
    hw_abort (me, "epiphany_dma_finish: invalid register: %d", regno);
  }
}

bool epiphany_dma_active_p (struct hw *me)
{
  struct epiphany_dma *dma = hw_data (me);
  /* struct epiphany_dma_regs *regs = get_regs (me); */

  /* ???: Is this enough, or do we also need to check the regs? */
  return dma->handler != NULL;
}
