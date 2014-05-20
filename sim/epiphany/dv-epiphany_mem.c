/*  This file is part of the program GDB, the GNU debugger.

    Copyright (C) 2014 Ola Jeppsson

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


#include "sim-main.h"
#include "hw-main.h"

#include "sim-types.h"
#if WITH_EMESH_SIM
#include "emesh.h"
#endif

/* DEVICE


   epiphany_mem - epiphany memory virtual device


   DESCRIPTION


   Implements memory m
   TODO: Make more fine-grained so e.g., local mem accesses don't have to go
   through this device.


   PROPERTIES

   none
   TODO:
   Properties needed:
       coreid       - so we can calculate local memory address.
       mem_per_core - so we can experiment with different memory sizes.



   PORTS

   none
   TODO: investigate which ports are needed

   */


/* From Epiphany Reference Manual 3.12.12.18 page 40 and 126. */
/* And from epiphany.c */

/* TODO: These were copied from epiphany.c. Move to separate definition
   include file */
/* Number of general purpose registers (GPRs).  */
#define EPIPHANY_NUM_GPRS  64
/* Number of Special Core Registers (SCRs).  */
#define EPIPHANY_NUM_SCRS  32

#define CORE_MMR_BASE      0xf0000
#define CORE_MMR_SIZE      2048
#define CORE_MMR_GPRS_BASE (CORE_MMR_BASE)
#define CORE_MMR_GPRS_SIZE (EPIPHANY_NUM_GPRS << 2)
#define CORE_MMR_SCRS_BASE 0xf0400
#define CORE_MMR_SCRS_SIZE (EPIPHANY_NUM_SCRS << 2)

#define IS_PARTIALLY_INSIDE_LOCAL_MEM(C,BASE,NR_BYTES) \
  (BASE < C->core_mem_size)
#define IS_INSIDE_LOCAL_MEM(C,BASE,NR_BYTES) \
  (IS_PARTIALLY_INSIDE_LOCAL_MEM(C,BASE,NR_BYTES) && \
  (BASE+NR_BYTES <= C->core_mem_size))

#define IS_PARTIALLY_INSIDE_GLOBAL_MEM(C,BASE,NR_BYTES) \
  ((BASE >= C->global_base_addr) && \
  (BASE < C->global_base_addr+C->core_mem_size))
#define IS_INSIDE_GLOBAL_MEM(C,BASE,NR_BYTES) \
  (IS_PARTIALLY_INSIDE_GLOBAL_MEM(C, BASE, NR_BYTES) && \
  (BASE+NR_BYTES <= C->global_base_addr+C->core_mem_size))

#define IS_INSIDE_LOCAL_MMR(C,BASE,NR_BYTES) \
  (BASE >= CORE_MMR_BASE && BASE+NR_BYTES <= CORE_MMR_BASE+CORE_MMR_SIZE)

#define IS_MMR_GPR(C,ADDR) \
  (CORE_MMR_GPRS_BASE <= ADDR && \
  ADDR < CORE_MMR_GPRS_BASE+CORE_MMR_GPRS_SIZE)

#define IS_MMR_SCR(C,ADDR) \
  (CORE_MMR_SCRS_BASE <= ADDR && \
  ADDR < CORE_MMR_SCRS_BASE+CORE_MMR_SCRS_SIZE)

struct epiphany_mem {
  /* Per instance state */
  unsigned core_id;
  unsigned core_mem_size;             /* Physical memory per core */
  unsigned core_region_size;          /* Memory region per core */
  address_word global_base_addr;      /* base address of global core mem address*/
  unsigned8 *core_mem;                /* Pointer to allocated local memory */
#if WITH_EMESH_SIM
#endif
  /* TODO: Add pointer to MPI struct ... */
};



static const struct hw_port_descriptor epiphany_mem_ports[] = {
  { NULL, },
};


/* Finish off the partially created hw device.  Attach our local
   callbacks.  Wire up our port names etc */

static hw_io_read_buffer_method epiphany_mem_io_read_buffer;
static hw_io_write_buffer_method epiphany_mem_io_write_buffer;
static hw_port_event_method epiphany_mem_port_event;


static void
epiphany_mem_finish (struct hw *me)
{
  /* TODO: Everything is hardcoded, we should read from device tree */
  struct epiphany_mem *controller;

  unsigned_word attach_address;
  unsigned_word alloc_size;
  int attach_space;
  unsigned attach_size;
  reg_property_spec reg;

  HW_TRACE ((me, "epiphany_mem_finish"));

  /* As per Parallella-16 memory map */
  int row = 32;
  int col = 8;

  controller = HW_ZALLOC (me, struct epiphany_mem);
  set_hw_data (me, controller);
  set_hw_io_read_buffer (me, epiphany_mem_io_read_buffer);
  set_hw_io_write_buffer (me, epiphany_mem_io_write_buffer);
  set_hw_ports (me, epiphany_mem_ports);
  set_hw_port_event (me, epiphany_mem_port_event);


#if WITH_EMESH_SIM
#endif

  /* TODO: Initialize epiphany_mem structure from device tree */
  controller->core_id = (row*64+col);
  controller->global_base_addr =
    controller->core_id * EPIPHANY_DEFAULT_MEM_SIZE;

  controller->core_region_size = EPIPHANY_DEFAULT_MEM_SIZE;
  /* We map entire core address space but on Parallella core mem is only 32k */
  controller->core_mem_size = EPIPHANY_DEFAULT_MEM_SIZE;
  alloc_size = controller->core_mem_size * sizeof controller->core_mem_size;
  controller->core_mem = hw_zalloc(me, alloc_size);
  /* Attach ourself to our parent bus */
  /* TODO: Don't map full address space. Local mem should go trough sim
     directly to avoid memcpy??? */
  /* Map full address space (except core local memory) */
  /* Need to do two calls since address size param is target word size and
     full size cannot be expressed with one call */
  hw_attach_address (hw_parent (me), 0, 0, 0, 0x80000000, me);
  hw_attach_address (hw_parent (me), 0, 0, 0x80000000, 0x80000000, me);
}

static void
epiphany_mem_port_event (struct hw *me,
		     int my_port,
		     struct hw *source,
		     int source_port,
		     int level)
{
  struct epiphany_mem *controller = hw_data (me);
  hw_abort (me, "epiphany_mem_port_event: not implemented");
}

#if WITH_EMESH_SIM

static void epiphany_mem_signal(struct hw *me, unsigned_word addr,
			   unsigned nr_bytes, char *transfer, int sigrc)
{
  SIM_CPU *current_cpu;
  address_word ip;

  current_cpu = hw_system_cpu(me);
  sim_cia cia = current_cpu ? CIA_GET (current_cpu) : NULL_CIA;
  ip = CIA_ADDR (cia);

  switch (sigrc)
    {
    case SIM_SIGSEGV:
      sim_io_eprintf(hw_system(me),
		     "%s: %d byte %s at unmapped address 0x%lx at 0x%lx\n",
		     hw_path(me), (int) nr_bytes, transfer,
		     (unsigned long) addr, (unsigned long) ip);
      break;
    case SIM_SIGBUS:
      sim_io_eprintf(hw_system(me),
		     "%s: %d byte misaligned %s at unmapped address 0x%lx at 0x%lx\n",
		     hw_path(me), (int) nr_bytes, transfer,
		     (unsigned long) addr, (unsigned long) ip);
      break;
    default:
      sim_io_eprintf(hw_system(me),
		     "%s: %d byte %s at address 0x%lx at 0x%lx\n",
		     hw_path(me), (int) nr_bytes, transfer,
		     (unsigned long) addr, (unsigned long) ip);
      break;
    }

    hw_halt(me, sim_stopped, sigrc);
}

static unsigned
epiphany_mem_io_read_buffer (struct hw *me,
			 void *dest,
			 int space,
			 unsigned_word base,
			 unsigned nr_bytes)
{
  HW_TRACE ((me, "read 0x%08lx %d", (long) base, (int) nr_bytes));
  es_state *esim = STATE_ESIM(hw_system(me));
  if (es_mem_load(esim, base, nr_bytes, dest) != ES_OK)
    {
      /* TODO: What about SIGBUS (unaligned access) */
      epiphany_mem_signal(me, base, nr_bytes, "read", SIM_SIGSEGV);
    }
  else
    return nr_bytes;
}

static unsigned
epiphany_mem_io_write_buffer (struct hw *me,
			  const void *source,
			  int space,
			  unsigned_word base,
			  unsigned nr_bytes)
{
  es_state *esim = STATE_ESIM(hw_system(me));
  HW_TRACE ((me, "write 0x%08lx %d", (long) base, (int) nr_bytes));
  if (es_mem_store(esim, base, nr_bytes, source) != ES_OK)
    {
      /* TODO: What about SIGBUS (unaligned access) */
      epiphany_mem_signal(me, base, nr_bytes, "write", SIM_SIGSEGV);
    }
  else
    return nr_bytes;

}
#else

/* This is a bit fragile (depends on epiphanybf_*_register internals) */
int
mmr_to_regnr(struct epiphany_mem *controller, unsigned_word addr)
{
  int reg = -1;
  if (IS_MMR_GPR(controller, addr))
    reg = (addr-CORE_MMR_GPRS_BASE) >> 2;
  else if (IS_MMR_SCR(controller, addr))
    reg = EPIPHANY_NUM_GPRS + ((addr-CORE_MMR_SCRS_BASE) >> 2);

#ifdef DEBUG
      fprintf (stderr, "mmr_to_reg reg=%d\n" , reg);
#endif
  return reg;
}

/* TODO: check if is memory mapped register ..... */
static unsigned
epiphany_mem_io_read_buffer (struct hw *me,
			 void *dest,
			 int space,
			 unsigned_word base,
			 unsigned nr_bytes)
{
  struct epiphany_mem *controller = hw_data (me);
  unsigned_word reg;
  int rn, left, size;
  unsigned8 *dest8; /* To avoid void pointer arithmetics */

  HW_TRACE ((me, "read 0x%08lx %d", (long) base, (int) nr_bytes));

  if ((unsigned64)(base) + (unsigned64)(nr_bytes) > (unsigned64)(0xffffffff))
    hw_abort (me, "Address is out of range.");

  /* Translate to core local address */
  /* This will probably be the other way around once we connect more
     simulators
     */
  if (IS_INSIDE_GLOBAL_MEM(controller, base, nr_bytes))
    {
      base -= controller->global_base_addr;
    }

  /* This will match both the local and global address since 'base' was
     adjusted above */
  if (IS_INSIDE_LOCAL_MMR(controller, base, nr_bytes))
    {
      HW_TRACE ((me, "read-mmr 0x%08lx %d", (long) base, (int) nr_bytes));
      if (base % 4 || nr_bytes % 4)
        {
          /* TODO: Add support for unaligned MMR reads */
          hw_abort (me, "Unaligned MMR reads currently not supported.");
        }

      left = nr_bytes;
      dest8 = (unsigned8 *) dest;
      while (left > 0)
        {
          rn = mmr_to_regnr(controller, base);
          if (rn < 0) {
              hw_abort (me, "invalid mmr register");
          }

          size = epiphanybf_fetch_register (hw_system_cpu(me), rn, dest8, 4);
          if ( size != 4 )
            {
              hw_abort (me, "error writing to register");
            }
          left -= size;
          dest8 += size;
          base += size;
        }
    }
  else if (IS_INSIDE_LOCAL_MEM(controller, base, nr_bytes))
    {
      /* Should we check if memory overlap? /return value */
      memcpy ((unsigned8 *)dest, &controller->core_mem[base], nr_bytes);
    }
  else
    {
      hw_abort (me, "Not implemented.");
    }

  return nr_bytes;
}



static unsigned
epiphany_mem_io_write_buffer (struct hw *me,
			  const void *source,
			  int space,
			  unsigned_word base,
			  unsigned nr_bytes)
{
  struct epiphany_mem *controller = hw_data (me);
  unsigned_word reg;
  int rn, left, size;
  unsigned8 *source8; /* To avoid void pointer arithmetics */

  HW_TRACE ((me, "write 0x%08lx %d", (long) base, (int) nr_bytes));

  if ((unsigned64)(base) + (unsigned64)(nr_bytes) > (unsigned64)(0xffffffff))
    hw_abort (me, "Address is out of range.");

  /* Translate to core local address */
  /* This will probably be the other way around once we connect more
     simulators
     */
  if (IS_INSIDE_GLOBAL_MEM(controller, base, nr_bytes))
    {
      base -= controller->global_base_addr;
    }

  /* This will match both the local and global address since 'base' was
     adjusted above */
  if (IS_INSIDE_LOCAL_MMR(controller, base, nr_bytes))
    {
      HW_TRACE ((me, "write-mmr 0x%08lx %d", (long) base, (int) nr_bytes));
      if (base % 4 || nr_bytes % 4)
        {
          /* TODO: Add support for unaligned MMR writes */
          hw_abort (me, "Unaligned MMR writes currently not supported.");
        }

      left = nr_bytes;
      source8 = (unsigned8 *) source;
      while (left > 0)
        {
          rn = mmr_to_regnr(controller, base);
          if (rn < 0) {
              hw_abort (me, "invalid mmr register");
          }

          size = epiphanybf_store_register (hw_system_cpu(me), rn, source8, 4);
          if ( size != 4 )
            {
              hw_abort (me, "error writing to register");
            }
          left -= size;
          source8 += size;
          base += size;
        }
    }
  else if (IS_INSIDE_LOCAL_MEM(controller, base, nr_bytes))
    {
      /* Should we check if memory overlap? /return value */
      memcpy (&controller->core_mem[base], (unsigned8 *)source, nr_bytes);
    }
  else
    {
      hw_abort (me, "Not implemented.");
    }

  return nr_bytes;
}
#endif /* (!WITH_EMESH_SIM) */

const struct hw_descriptor dv_epiphany_mem_descriptor[] = {
  { "epiphany_mem", epiphany_mem_finish, },
  { NULL },
};
