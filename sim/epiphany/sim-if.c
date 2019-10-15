/* Main simulator entry points specific to the EPIPHANY.
   Copyright (C) 1996, 1997, 1998, 1999, 2003, 2007, 2008, 2011
   Free Software Foundation, Inc.
   Contributed by Embecosm on behalf of Adapteva.

   This file is part of GDB, the GNU debugger.

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

#include "sim-main.h"
#include "sim-options.h"

#if (WITH_HW)
#include "sim-hw.h"
#endif

#include "libiberty.h"
#include "bfd.h"

#ifdef HAVE_STRING_H
#include <string.h>
#else
#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif
#endif

#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "sim-options.h"

#if WITH_EMESH_SIM
#include <pthread.h>
#include "esim/esim.h"
#if HAVE_E_XML
#include <epiphany_xml_c.h>
#endif
#endif

#include "ert-workgroup.h"

/* Records simulator descriptor so utilities like epiphany_dump_regs can be
   called from gdb.  */
SIM_DESC current_state=0;
int is_sim_opened=0;

/* Cover function of sim_state_free to free the cpu buffers as well.  */

typedef enum {
  E_OPTION_XML_HDF = OPTION_START, /* Epiphany XML hardware description file */
  E_OPTION_EXT_RAM,
  E_OPTION_COREID,
  E_OPTION_NUM_COLS,
  E_OPTION_NUM_ROWS,
  E_OPTION_FIRST_CORE,
  E_OPTION_ADD_EXT_MEM,
  E_OPTION_EXT_RAM_BASE,
  E_OPTION_EXT_RAM_SIZE,
  E_OPTION_SESSION_NAME,
  E_OPTION_EXTERNAL_FETCH,
  E_OPTION_CORE_MEM,
  /** @todo Add more options:
   * Check es_cluster_cfg in esim.h
   */
} EPIPHANY_OPTIONS;

struct emesh_params {
  /* Required */
  int coreid;
  int num_cols;
  int num_rows;
  int first_coreid;

  /* Extra */
  unsigned mesh_add_ext_ram;
  uint64_t ext_ram_base;
  /* Don't allow crazy large ext ram size for now */
  int64_t ext_ram_size;
  int64_t core_mem;

  char *xml_hdf_file;

  const char *session_name;
};
static struct emesh_params emesh_params = {
  .coreid           = -1,
  .num_cols         = -1,
  .num_rows         = -1,
  .first_coreid     = -1,

  .mesh_add_ext_ram =  1,
  .ext_ram_base     =  0,
  .ext_ram_size     = -1,
  .core_mem        = -1,

  .xml_hdf_file     = NULL,
  .session_name     = NULL,
};

static void free_state (SIM_DESC);
static SIM_RC epiphany_mem_size_option_handler (SIM_DESC, sim_cpu *, int,
						char *, int);
static SIM_RC epiphany_option_handler (SIM_DESC, sim_cpu *, int, char *, int);

#ifdef WITH_EMESH_SIM
static SIM_RC sim_esim_cpu_relocate (SIM_DESC sd, int extra_bytes);
static SIM_RC sim_esim_set_options(SIM_DESC sd, sim_cpu *cpu);
static SIM_RC sim_esim_init(SIM_DESC sd);
#endif


static const OPTION options_epiphany[] =
{

  { {"e-external-memory", optional_argument, NULL, E_OPTION_EXT_RAM},
      'e', "off|on", "Turn off/on the external memory region",
      epiphany_option_handler },
#if EMESH_SIM
#if HAVE_E_XML
  { {"e-hdf", required_argument, NULL, E_OPTION_XML_HDF},
      '\0', "FILE", "Epiphany XML hardware description file",
      epiphany_option_handler },
#endif
#if WITH_EMESH_NET
  /* coreid is determined from MPI rank */
#else
  { {"e-coreid", required_argument, NULL, E_OPTION_COREID},
      '\0', "COREID", "Set coreid. Default is 0x020.",
      epiphany_option_handler  },
#endif
  { {"e-cols", required_argument, NULL, E_OPTION_NUM_COLS},
      '\0', "n", "Number of core columns. Default is 1.",
      epiphany_option_handler  },
  { {"e-rows", required_argument, NULL, E_OPTION_NUM_ROWS},
      '\0', "n", "Number of core rows. DEFAULT is 1.",
      epiphany_option_handler  },
  { {"e-first-core", required_argument, NULL, E_OPTION_FIRST_CORE},
      '\0', "COREID", "Coreid of upper leftmost core",
      epiphany_option_handler  },
  { {"e-ext-ram-base", required_argument, NULL, E_OPTION_EXT_RAM_BASE},
      '\0', "address", "Base address of external RAM. Default is 0x8e000000.",
      epiphany_option_handler  },
  { {"e-ext-ram-size", required_argument, NULL, E_OPTION_EXT_RAM_SIZE},
      '\0', "MB", "Size of external RAM. Default is `32MB'.",
      epiphany_mem_size_option_handler  },
  { {"e-session-name", required_argument, NULL, E_OPTION_SESSION_NAME},
      '\0', "NAME", "Set the session name. Use this option when you want to run separate simulations concurrently without clashing, or if you want to connect clients to a one-core simulation.",
      epiphany_option_handler  },
  { {"e-external-fetch", no_argument, NULL, E_OPTION_EXTERNAL_FETCH},
      '\0', NULL, "Allow instruction fetch from off-core memory. Default is off.",
      epiphany_option_handler  },
  { {"e-core-mem", required_argument, NULL, E_OPTION_CORE_MEM},
      '\0', "SIZE", "Core memory size. Default is `64KB'.",
      epiphany_mem_size_option_handler  },
#endif
  { {NULL, no_argument, NULL, 0}, '\0', NULL, NULL, NULL, NULL }
};

static void
free_state (SIM_DESC sd)
{
#if WITH_EMESH_SIM
  if (STATE_ESIM (sd) != NULL)
    {
      es_fini (STATE_ESIM (sd));
      STATE_CPU(sd, 0) = sd->orig_cpu[0];
    }
#endif
  if (STATE_MODULES (sd) != NULL)
    sim_module_uninstall (sd);
  sim_cpu_free_all (sd);
  sim_state_free (sd);
}


#define SET_OR_FAIL(Param, Name)\
  do \
    {\
      if (valid)\
	{\
	  emesh_params.Param = (sizeof(emesh_params.Param) < 8 ? (unsigned) ul : ul);\
	}\
      else\
	{\
	  sim_io_eprintf(sd, "%s: Invalid parameter `%s'\n", Name, arg);\
	  return SIM_RC_FAIL;\
	}\
    }\
  while (0)

static SIM_RC
epiphany_mem_size_option_handler (SIM_DESC sd, sim_cpu *cpu, int opt, char *arg,
				  int is_command)
{
  char *endp;
  ulong64 ul = 0;
  int valid = 0;

  if (arg)
    {
      ul = strtoull (arg, &endp, 0);
      valid = ((isdigit (arg[0]) && endp != arg));

      switch (*endp)
	{
	case 'k': case 'K': ul <<= 10; break;
	case 'm': case 'M': ul <<= 20; break;
	case 'g': case 'G': ul <<= 30; break;
	case ' ': case '\0': case '\t':  break;
	default:
	  if (ul > 0)
	    sim_io_eprintf (sd, "Ignoring strange character at end of memory size: %c\n",
			    *endp);
	  break;
	}
    }

  switch ((EPIPHANY_OPTIONS) opt)
    {
    case E_OPTION_EXT_RAM_SIZE:
      SET_OR_FAIL(ext_ram_size, "e-ext-ram-size");
      break;
    case E_OPTION_CORE_MEM:
      SET_OR_FAIL (core_mem, "e-core-mem");
      break;
    default:
      sim_io_eprintf (sd, "Unknown option %d `%s'\n", opt, arg);
      return SIM_RC_FAIL;
    }

  /* Update options */
  if (STATE_OPEN_KIND (sd) == SIM_OPEN_DEBUG)
    return sim_esim_set_options(sd, cpu);
  else
    return SIM_RC_OK;
}

static SIM_RC
epiphany_option_handler (SIM_DESC sd, sim_cpu *cpu, int opt, char *arg,
			 int is_command)
{
  char *endp;
  ulong64 ul = 0;
  int valid = 0;

  if (arg)
    {
      ul = strtoull (arg, &endp, 0);
      valid = ((isdigit (arg[0]) && endp != arg));
    }

  switch ((EPIPHANY_OPTIONS) opt)
    {
    case E_OPTION_EXT_RAM:
      if (!arg || strcmp(arg,"on") == 0 )
	emesh_params.mesh_add_ext_ram = 1;
      else if(strcmp(arg,"off") == 0 )
	emesh_params.mesh_add_ext_ram = 0;
      else
	{
	  sim_io_eprintf(sd, "%s: Invalid parameter `%s'\n", "-e", arg);\
	  return SIM_RC_FAIL;
	}

      return SIM_RC_OK;
      break;
#if WITH_EMESH_SIM

#if HAVE_E_XML
    case E_OPTION_XML_HDF:
      emesh_params.xml_hdf_file = arg;
      break;
#endif
    case E_OPTION_COREID:
      SET_OR_FAIL(coreid, "e-coreid");
      break;
    case E_OPTION_NUM_COLS:
      SET_OR_FAIL(num_cols, "e-cols");
      break;
    case E_OPTION_NUM_ROWS:
      SET_OR_FAIL(num_rows, "e-rows");
      break;
    case E_OPTION_FIRST_CORE:
      SET_OR_FAIL(first_coreid, "e-first-core");
      break;
    case E_OPTION_EXT_RAM_BASE:
      SET_OR_FAIL(ext_ram_base, "e-ext-ram-base");
      break;
    case E_OPTION_SESSION_NAME:
      emesh_params.session_name = arg;
      break;
    case E_OPTION_EXTERNAL_FETCH:
      sd->external_fetch = true;
      break;
#endif
    default:
      sim_io_eprintf (sd, "Unknown option %d `%s'\n", opt, arg);
      return SIM_RC_FAIL;
    }
#ifdef WITH_EMESH_SIM
  /* Update options */

  if (STATE_OPEN_KIND (sd) == SIM_OPEN_DEBUG)
    return sim_esim_set_options(sd, cpu);
  else
    return SIM_RC_OK;

#endif
    return SIM_RC_OK;
}
#undef SET_OR_FAIL

#if WITH_EMESH_SIM
/* Custom sim cpu alloc for emesh sim */
SIM_RC
sim_esim_cpu_relocate (SIM_DESC sd, int extra_bytes)
{
  sim_cpu *new_cpu;

  /* Save pointer to originally allocated cpu struct for generic
   * sim_close (). We restore it in epiphany_sim_close ()  */
  sd->orig_cpu[0] = STATE_CPU(sd, 0);

  if (! (new_cpu = es_set_cpu_state(STATE_ESIM(sd), STATE_CPU(sd, 0),
			sizeof(sim_cpu) + extra_bytes)))
    {
      sim_io_eprintf (sd, "Could not set cpu state.\n");
      return SIM_RC_FAIL;
    }

  STATE_CPU (sd, 0) = new_cpu;

  return SIM_RC_OK;
}


/* Return SIM_RC_OK if user specified required params, SIM_RC_FAIL otherwise
 * @todo This does not work so well in debugger mode. If e.g. e-cols is set
 * and then e-hdf is set after that, it gets stuck.
 */
static SIM_RC sim_esim_have_required_params(SIM_DESC sd)
{
#define FAIL_IF(Expr, Desc)\
  if (Expr)\
    {\
      if (emesh_params.xml_hdf_file != NULL ||\
	  STATE_OPEN_KIND (sd) == SIM_OPEN_STANDALONE) \
	sim_io_eprintf(sd, "%s\n", Desc);\
      return SIM_RC_FAIL;\
    }

  /* Provide default values if none specified */
  if (emesh_params.num_rows == -1 && emesh_params.num_cols == -1 &&
      emesh_params.coreid == -1)
    {
      emesh_params.num_rows = 1;
      emesh_params.num_cols = 1;
      emesh_params.coreid = 0x020;
    }

#if WITH_EMESH_NET
  /* Coreid is determined by MPI RANK */
#else
  /* If there is only one core, we can determine coreid from first core, and
   * vice versa. */
  if (emesh_params.num_rows == 1 && emesh_params.num_cols == 1)
    {
      if (0 > emesh_params.coreid)
	emesh_params.coreid = emesh_params.first_coreid;

      if (0 > emesh_params.first_coreid)
	emesh_params.first_coreid = emesh_params.coreid;
    }

  FAIL_IF(0 > emesh_params.coreid      , "--e-coreid not set");
#endif

  /* Either use hardware definition file or other params */
  if (emesh_params.xml_hdf_file != NULL)
    {
      FAIL_IF(-1 != emesh_params.num_cols    ,
	      "Both --e-xml-file and --e-cols set");
      FAIL_IF(-1 != emesh_params.num_rows    ,
	      "Both --e-xml-file and --e-rows set");
      FAIL_IF(-1 != emesh_params.first_coreid,
	      "Both --e-xml-file and --e-first-core set");
      /** @todo Also check add_ext_ram */
    }
  else
    {
      FAIL_IF(0 > emesh_params.num_cols    , "--e-cols not set");
      FAIL_IF(0 > emesh_params.num_rows    , "--e-rows not set");
      FAIL_IF(0 > emesh_params.first_coreid, "--e-first-core not set");
    }
#undef FAIL_IF

  return SIM_RC_OK;
}

/* Only called from debugger */
static SIM_RC sim_esim_set_options(SIM_DESC sd, sim_cpu *cpu)
{
  if (sim_esim_have_required_params(sd) != SIM_RC_OK)
    return SIM_RC_OK;

  if (sim_esim_init(sd) != SIM_RC_OK)
    return SIM_RC_FAIL;

  return SIM_RC_OK;
}

#if HAVE_E_XML
static SIM_RC sim_esim_params_from_xml(SIM_DESC sd)
{
  e_xml_t xml;
  platform_definition_t* p;
  int i;

  xml = e_xml_new(emesh_params.xml_hdf_file);

#define FAIL_IF(Expr, Desc)\
  if ((Expr))\
    {\
      sim_io_eprintf(sd, "%s\n", (Desc));\
      goto err_out;\
    }

  if (e_xml_parse(xml))
    {
      sim_io_eprintf(sd, "Could not parse XML HDF file `%s'\n",
		     emesh_params.xml_hdf_file);
      goto err_out;
    }
  FAIL_IF((p = e_xml_get_platform(xml)) == NULL, "Internal error in e-xml.");
  FAIL_IF(p->num_chips != 1, "The simulator only supports one chip");

  emesh_params.num_rows = p->chips[0].num_rows;
  emesh_params.num_cols = p->chips[0].num_cols;
  emesh_params.first_coreid = (p->chips[0].yid << 6) + p->chips[0].xid;
  /** @todo */
  /* emesh_params.core_mem_size = p->chips[0].core_memory_size; */

  /* No external RAM unless specified in HDF file */
  emesh_params.mesh_add_ext_ram = 0;

  for (i=0; i < p->num_banks; i++)
    {
      /** @todo Will mem naming always be the same ? */
      if (strncmp(p->ext_mem[i].name, "EXTERNAL_DRAM", 13) == 0)
	{
	  /* Fail if there already was an ext ram bank */
	  FAIL_IF(emesh_params.mesh_add_ext_ram,
		  "The simulator only supports at most 1 memory bank");

	  emesh_params.mesh_add_ext_ram = 1;

	  emesh_params.ext_ram_base = p->ext_mem[i].base;
	  emesh_params.ext_ram_size = p->ext_mem[i].size;
	}
    }

#undef FAIL_IF

out:
  e_xml_delete(xml);
  return SIM_RC_OK;
err_out:
  e_xml_delete(xml);
  return SIM_RC_FAIL;
}
#endif /* HAVE_E_XML */

static SIM_RC
sim_esim_init(SIM_DESC sd)
{
  es_cluster_cfg cluster;
  struct emesh_params *p;
  uint64_t ext_ram_size, ext_ram_base, core_mem;

  if (es_initialized(STATE_ESIM(sd)) == ES_OK)
    return SIM_RC_OK;

  if (sim_esim_have_required_params(sd) != SIM_RC_OK)
    return SIM_RC_FAIL;

  p = &emesh_params;

  /* Default values */
  ext_ram_size = 32*1024*1024;
  ext_ram_base = 0x8e000000;
  core_mem    = 65536; /*!< @todo: derive from model */

#if HAVE_E_XML
  /* Parse XML file, if specified */
  if (emesh_params.xml_hdf_file != NULL)
    {
      if (sim_esim_params_from_xml(sd) != SIM_RC_OK)
	return SIM_RC_FAIL;
    }
#endif

  memset(&cluster, 0, sizeof(cluster));

  cluster.col_base = p->first_coreid & ((1 << 6) -1);
  cluster.row_base = p->first_coreid >> 6;
  cluster.cols = p->num_cols;
  cluster.rows = p->num_rows;
  cluster.core_mem_region = 1024*1024;

  if (p->mesh_add_ext_ram)
    {
      ext_ram_size = (0 <= p->ext_ram_size) ? p->ext_ram_size : ext_ram_size;
      ext_ram_base = (0 <  p->ext_ram_base) ? p->ext_ram_base : ext_ram_base;
    }
  else
    {
      ext_ram_size = 0;
      ext_ram_base = 0xffffffff;
    }

  core_mem = (0 <= p->core_mem) ? p->core_mem : core_mem;

  cluster.ext_ram_size = ext_ram_size;
  cluster.ext_ram_base = ext_ram_base;
  cluster.ext_ram_node = 0;
  cluster.core_phys_mem = core_mem;

  if (es_init(&STATE_ESIM(sd), cluster, p->coreid, p->session_name) != ES_OK)
    {
      return SIM_RC_FAIL;
    }

  if (sim_esim_cpu_relocate (sd, cgen_cpu_max_extra_bytes ()) != SIM_RC_OK)
    {
      return SIM_RC_FAIL;
    }

  /*! Set up lock and cond vars
   *  @todo Should be moved to esim
   */
  {
    SIM_CPU *current_cpu;
    pthread_mutexattr_t mutexattr;
    pthread_condattr_t condattr;

    current_cpu = STATE_CPU (sd, 0);

    pthread_mutexattr_init(&mutexattr);
    pthread_condattr_init(&condattr);

    pthread_mutexattr_setpshared(&mutexattr, PTHREAD_PROCESS_SHARED);
    pthread_condattr_setpshared(&condattr, PTHREAD_PROCESS_SHARED);

    pthread_mutex_init(&current_cpu->scr_lock, &mutexattr);
    pthread_cond_init(&current_cpu->scr_wakeup_cond, &condattr);
    pthread_cond_init(&current_cpu->scr_writeslot_cond, &condattr);

    pthread_mutex_init(&current_cpu->wand_lock, &mutexattr);

    current_cpu->scr_remote_write_reg = -1;
    current_cpu->scr_remote_write_val = 0xbaadbeef;

    pthread_condattr_destroy(&condattr);
    pthread_mutexattr_destroy(&mutexattr);
  }

  if (STATE_VERBOSE_P (sd))
    sim_io_eprintf(sd, "ESIM: Initialized successfully\n");

  return SIM_RC_OK;
}
#endif /* WITH_EMESH_SIM */

/* Create an instance of the simulator.  */

SIM_DESC
sim_open (SIM_OPEN_KIND kind,
	  host_callback *callback,
	  struct bfd *abfd,
	  char * const *argv)
{
  SIM_DESC sd = sim_state_alloc (kind, callback);
  char c;
  int i;

  /* The cpu data is kept in a separately allocated chunk of memory.  */
  if (sim_cpu_alloc_all (sd, 1, cgen_cpu_max_extra_bytes ()) != SIM_RC_OK)
    {
      free_state (sd);
      return 0;
    }

#if 0 /* FIXME: pc is in mach-specific struct */
  /* FIXME: watchpoints code shouldn't need this */
  {
    SIM_CPU *current_cpu = STATE_CPU (sd, 0);
    STATE_WATCHPOINTS (sd)->pc = &(PC);
    STATE_WATCHPOINTS (sd)->sizeof_pc = sizeof (PC);
  }
#endif

  if (sim_pre_argv_init (sd, argv[0]) != SIM_RC_OK)
    {
      free_state (sd);
      return 0;
    }

#if 0 /* FIXME: 'twould be nice if we could do this */
  /* These options override any module options.
     Obviously ambiguity should be avoided, however the caller may wish to
     augment the meaning of an option.  */
  if (extra_options != NULL)
    sim_add_option_table (sd, extra_options);
#endif


  sim_add_option_table (sd, NULL, options_epiphany);

  /* getopt will print the error message so we just have to exit if this fails.
     FIXME: Hmmm...  in the case of gdb we need getopt to call
     print_filtered.  */
  if (sim_parse_args (sd, argv) != SIM_RC_OK)
    {
      free_state (sd);
      return 0;
    }

#if WITH_EMESH_SIM
  for (i = 0; i < MAX_NR_PROCESSORS; i++)
    sd->orig_cpu[i] = NULL;

  if (STATE_OPEN_KIND (sd) == SIM_OPEN_STANDALONE)
    {
      if (sim_esim_init(sd) != SIM_RC_OK)
	return SIM_RC_FAIL;
    }
#endif

  /* Allocate core managed memory if none specified by user.  */

#if (WITH_HW)
  sim_hw_parse (sd, "/epiphany_mem");
  sim_hw_parse (sd, "/epiphany_dma@0");
  sim_hw_parse (sd, "/epiphany_dma@1");
  sim_hw_parse (sd, "/epiphany_timer");
  /** @todo Need to be able to map external mem */
#else
  if (sim_core_read_buffer (sd, NULL, read_map, &c, 0, 1) == 0)
    sim_do_commandf (sd, "memory region 0,0x%x", EPIPHANY_DEFAULT_MEM_SIZE);

  if (emesh_params.mesh_add_ext_ram)
    {
      if (sim_core_read_buffer (sd, NULL, read_map, &c,
				EPIPHANY_DEFAULT_EXT_MEM_BANK0_START, 1) == 0)
	sim_do_commandf (sd, "memory region 0x%x,0x%x",
			 EPIPHANY_DEFAULT_EXT_MEM_BANK0_START,
			 EPIPHANY_DEFAULT_EXT_MEM_BANK_SIZE);

      if (sim_core_read_buffer (sd, NULL, read_map, &c,
				EPIPHANY_DEFAULT_EXT_MEM_BANK1_START, 1) == 0)
	sim_do_commandf (sd, "memory region 0x%x,0x%x",
			 EPIPHANY_DEFAULT_EXT_MEM_BANK1_START,
			 EPIPHANY_DEFAULT_EXT_MEM_BANK_SIZE);

    }
#endif /* (WITH_HW) */

  /* check for/establish the reference program image */
  if (sim_analyze_program (sd,
			   (STATE_PROG_ARGV (sd) != NULL
			    ? *STATE_PROG_ARGV (sd)
			    : NULL),
			   abfd) != SIM_RC_OK)
    {
      free_state (sd);
      return 0;
    }

  /* Establish any remaining configuration options.  */
  if (sim_config (sd) != SIM_RC_OK)
    {
      free_state (sd);
      return 0;
    }

  if (sim_post_argv_init (sd) != SIM_RC_OK)
    {
      free_state (sd);
      return 0;
    }

  /* Open a copy of the cpu descriptor table.  */
  {
    CGEN_CPU_DESC cd = epiphany_cgen_cpu_open_1 (STATE_ARCHITECTURE (sd)->printable_name,
					     CGEN_ENDIAN_LITTLE);
    for (i = 0; i < MAX_NR_PROCESSORS; ++i)
      {
	SIM_CPU *cpu = STATE_CPU (sd, i);
	CPU_CPU_DESC (cpu) = cd;
	CPU_DISASSEMBLER (cpu) = sim_cgen_disassemble_insn;
      }
    epiphany_cgen_init_dis (cd);
  }

  /* Initialize various cgen things not done by common framework.
     Must be done after epiphany_cgen_cpu_open.  */
  cgen_init (sd);

  for (c = 0; c < MAX_NR_PROCESSORS; ++c)
    {
      /* Only needed for profiling, but the structure member is small.  */
      memset (CPU_EPIPHANY_PROFILE (STATE_CPU (sd, i)), 0,
	      sizeof (* CPU_EPIPHANY_PROFILE (STATE_CPU (sd, i))));
      /* Hook in callback for reporting these stats */
      PROFILE_INFO_CPU_CALLBACK (CPU_PROFILE_DATA (STATE_CPU (sd, i)))
	= epiphany_profile_info;
    }

  /* Store in a global so things like sparc32_dump_regs can be invoked
     from the gdb command line.  */
  current_state = sd;
  is_sim_opened = 1; /* To distinguish between HW and simulator target.  */

  {
    SIM_CPU *current_cpu;
    current_cpu = STATE_CPU (sd, 0);
    cgen_init_accurate_fpu (STATE_CPU (sd, 0), CGEN_CPU_FPU (current_cpu),
			    epiphany_fpu_error);
  }

  return sd;
}

void
epiphany_sim_close (SIM_DESC sd, int quitting)
{

  if (! sd->orig_cpu[0])
    return;

#if WITH_EMESH_SIM
  if (es_initialized (STATE_ESIM(sd)) == ES_OK)
    {
      if (STATE_VERBOSE_P (sd))
        sim_io_eprintf(sd, "ESIM: Waiting for other cores...");

      es_wait_exit(STATE_ESIM(sd));

      if (STATE_VERBOSE_P (sd))
        sim_io_eprintf(sd, " done.\n");

      es_fini (STATE_ESIM (sd));
    }

  /* Restore pointer to originally allocated cpu struct */
  STATE_CPU (sd, 0) = sd->orig_cpu[0];

  /* Fake it for generic sim_close () */
  {
    CGEN_CPU_DESC cd = epiphany_cgen_cpu_open_1 (STATE_ARCHITECTURE (sd)->printable_name,
						 CGEN_ENDIAN_LITTLE);
    SIM_CPU *cpu = STATE_CPU (sd, 0);
    CPU_CPU_DESC (cpu) = cd;
    CPU_DISASSEMBLER (cpu) = sim_cgen_disassemble_insn;
    epiphany_cgen_init_dis (cd);
    cgen_init (sd);
  }
#endif
}

static SIM_RC
setup_workgroup_cfg (SIM_DESC sd)
{
  asection *s;
  address_word addr;
  es_cluster_cfg cluster;
  e_group_config_t workgroup_cfg = { 0, };
  unsigned coreid;
  SIM_CPU *current_cpu = STATE_CPU (sd, 0);
  es_state *esim = STATE_ESIM (sd);
  bfd *prog_bfd = STATE_PROG_BFD (sd);
  bool found = false;

  if (!prog_bfd)
    return SIM_RC_OK;

  for (s = prog_bfd->sections; s; s = s->next)
    if (strcmp (bfd_get_section_name (prog_bfd, s), "workgroup_cfg") == 0)
      {
	found = true;
	break;
      }

  if (!found)
    return SIM_RC_OK;

  if (STATE_VERBOSE_P (sd))
    sim_io_eprintf(sd, "setting workgroup configuration\n");

  addr = bfd_get_section_vma (prog_bfd, s);

  es_get_cluster_cfg(esim, &cluster);
  coreid = es_get_coreid(esim);

  workgroup_cfg.objtype    = E_EPI_GROUP;
  workgroup_cfg.chiptype   = E_E1KG501;   /* TODO: Derive from model */
  workgroup_cfg.group_id   = cluster.row_base * 0x40 + cluster.col_base;
  workgroup_cfg.group_row  = cluster.row_base;
  workgroup_cfg.group_col  = cluster.col_base;
  workgroup_cfg.group_rows = cluster.rows;
  workgroup_cfg.group_cols = cluster.cols;
  workgroup_cfg.core_row   = coreid / 0x40 - cluster.row_base;
  workgroup_cfg.core_col   = coreid % 0x40 - cluster.col_base;

  if (sizeof(workgroup_cfg) !=
      sim_core_write_buffer (sd, current_cpu, write_map, &workgroup_cfg, addr,
			     sizeof(workgroup_cfg)))
    return SIM_RC_FAIL;

  return SIM_RC_OK;
}

static bool
find_sym (struct bfd *prog_bfd, char *name, unsigned_word *val)
{
  struct bfd_symbol **asymbols;
  long symsize;
  long symbol_count;
  long i;
  bool found = false;

  symsize = bfd_get_symtab_upper_bound (prog_bfd);
  if (symsize < 0)
    return false;
  asymbols = (asymbol **) xmalloc (symsize);
  symbol_count = bfd_canonicalize_symtab (prog_bfd, asymbols);
  if (symbol_count < 0)
    goto free;

  for (i = 0; i < symbol_count; i++)
    {
      if (!strcmp (asymbols[i]->name, name))
	{
	  *val = asymbols[i]->section->vma + asymbols[i]->value;
	  found = true;
	  goto free;
	}
    }

free:
  free (asymbols);
  return found;
}

static void
epiphany_user_init (SIM_DESC sd, SIM_CPU *cpu, struct bfd *abfd,
		    char * const *argv, char * const *env)
{
  asection *s;
  unsigned_word addr, initial_stack = 0, args_size;
  unsigned_word argcp, argvpp, envp, auxvp, argvp, strp;
  unsigned_word argv_flat;
  const unsigned_word null = 0;
  int argc;
  SIM_CPU *current_cpu = STATE_CPU (sd, 0);
  bfd *prog_bfd = STATE_PROG_BFD (sd);
  es_cluster_cfg cluster;

/* newlib/libgloss/epiphany/crt0.S  */
#define LOADER_BSS_CLEARED_FLAG 1
#define LOADER_ARGV_IN_SP_FLAG 4
  const unsigned_word flags = LOADER_BSS_CLEARED_FLAG | LOADER_ARGV_IN_SP_FLAG;
  int i;
  bool found = false;


  /* Set up stack like this:

     offset:
     0x00             <-- sp
     0x08 argc
     0x0c pointer to argv
     0x10 pointer to envp (null for now)
     0x14 pointer to auxv (null for now)
     0x18 argv[0]      <-- pointer to actual argv strings
     0x1c argv[1]
     ...  argv[argc-1]
          NULL         <-- argv terminating NULL ptr
          argv[0..N][0..M] <-- actual argv strings


     crt0 will take care of setting up regs:
     r0 = argc
     r1 = argv
     r2 = envp
     r3 = auxv  */


  assert (sizeof (unsigned_word) == 4);

  if (!prog_bfd)
    return;

  for (s = prog_bfd->sections; s; s = s->next)
    if (strcmp (bfd_get_section_name (prog_bfd, s), "loader_cfg") == 0)
      {
	found = true;
	break;
      }

  if (!found)
    return;

  if (STATE_VERBOSE_P (sd))
    sim_io_eprintf(sd, "setting loader flags\n");

  addr = bfd_get_section_vma (prog_bfd, s);

  sim_core_write_buffer (sd, current_cpu, write_map, &flags, addr,
			 sizeof(flags));

  es_get_cluster_cfg(STATE_ESIM (sd), &cluster);

  /* Figure out where to put the initial stack.
     If the "__stack" symbol points to a global address (above 1MB), place
     the initial stack there. Otherwise adjust it to available SRAM size.  */
  find_sym (prog_bfd, "__stack", &initial_stack);
  if (initial_stack < cluster.core_mem_region)
    {
      if (STATE_VERBOSE_P (sd) && initial_stack > cluster.core_phys_mem)
	{
	  sim_io_eprintf(sd,
			 "WARNING: truncating stack size to %#x\n",
			 initial_stack);
	}
      initial_stack = cluster.core_phys_mem;
    }

  /* Figure out how much storage the argv strings need.  */
  argc = countargv ((char **)argv);
  if (argc == -1)
    argc = 0;
  argv_flat = argc; /* NUL bytes  */
  for (i = 0; i < argc; i++)
    argv_flat += strlen (argv[i]);

#if 0
  /* Pushing the environment can eat up several KBs of SRAM.
     Ignore it for now, if we ever need it, create a memory slice inside the
     core's 1MB region above physical SRAM.  */
  envc = countargv ((char **)env);
  env_flat = envc; /* NUL bytes  */
  for (i = 0; i < envc; i++)
    env_flat += strlen (env[i]);
#endif

  args_size = argv_flat; /* size of argv strings  */
  args_size += 4;        /* argc  */
  args_size += 4;        /* argv pointer  */
  args_size += 4;        /* envp pointer  */
  args_size += 4;        /* auxv pointer  */
  args_size += 4 * argc; /* size of argv pointer vector  */
  args_size += 4;        /* null pointer terminating argv  */

  args_size = (args_size + 8) & ~7; /* round up for alignment */

  argcp  = initial_stack - args_size; /* Pointer to argc */
  argvpp = argcp  + 4; /* Address of pointer to argv pointer vector  */
  envp   = argvpp + 4; /* Address of pointer to envp vector  */
  auxvp  = envp   + 4; /* Address of pointer to auxv vector  */
  argvp  = auxvp  + 4; /* Address of argv pointer vector  */
  strp   = argvp  + 4 * (argc + 1); /* Address of argv strings  */

  /* Set actual stack pointer  */
  epiphanybf_h_all_registers_set (current_cpu, H_REG_SP, argcp - 8);

  /* Write argc */
  sim_core_write_buffer (sd, current_cpu, write_map, &argc, argcp, 4);

  /* Write pointer to argv pointer vector */
  sim_core_write_buffer (sd, current_cpu, write_map, &argvp, argvpp, 4);

  /* Write envp null pointer */
  sim_core_write_buffer (sd, current_cpu, write_map, &null, envp, 4);

  /* Write auxv null pointer */
  sim_core_write_buffer (sd, current_cpu, write_map, &null, auxvp, 4);

  /* Write argv pointers + argv strings */
  for (i = 0; i < argc; i++)
    {
      int l = strlen (argv[i]) + 1;

      sim_core_write_buffer (sd, current_cpu, write_map, argv[i], strp, l);
      sim_core_write_buffer (sd, current_cpu, write_map, &strp, argvp, 4);

      argvp += 4;
      strp += l;
    }

  /* Write argv terminating null pointer  */
  sim_core_write_buffer (sd, current_cpu, write_map, &null, argvp, 4);
}

SIM_RC
sim_create_inferior (SIM_DESC sd,
		     struct bfd *abfd,
		     char * const *argv,
		     char * const *envp)
{
  SIM_CPU *current_cpu = STATE_CPU (sd, 0);
  SIM_ADDR addr;

#if WITH_EMESH_SIM
  if (es_initialized(STATE_ESIM(sd)) != ES_OK ||
      !es_get_coreid(STATE_ESIM(sd)))
    {
      if (STATE_OPEN_KIND (sd) == SIM_OPEN_STANDALONE)
	sim_io_eprintf(sd,
		       "ESIM: Missing parameters. Call gdb with \"--help\"\n");
      else
	sim_io_eprintf(sd, "ESIM: Missing parameters. Say \"sim help\"\n");
      return SIM_RC_FAIL;
    }
#endif

  if (abfd != NULL)
    addr = bfd_get_start_address (abfd);
  else
    addr = 0;
  sim_pc_set (current_cpu, addr);

  /* Standalone mode (i.e. `run`) will take care of the argv for us in
     sim_open() -> sim_parse_args().  But in debug mode (i.e. 'target sim'
     with `gdb`), we need to handle it because the user can change the
     argv on the fly via gdb's 'run'.  */
  if (STATE_PROG_ARGV (sd) != argv)
    {
      freeargv (STATE_PROG_ARGV (sd));
      STATE_PROG_ARGV (sd) = dupargv ((char **)argv);
    }

#if WITH_EMESH_SIM

  if (STATE_ENVIRONMENT (sd) != OPERATING_ENVIRONMENT)
    {
      /* Operating environment is intended host connect throug esim client api
       * It's responsibility for host application to set workgroup_cfg */

      /* set up workgroup configuration according to mesh properties */
      if (setup_workgroup_cfg (sd) != SIM_RC_OK)
	return SIM_RC_FAIL;

    }

  /* Set coreid in cpu register. Do it via backdoor since it is (should be)
   * read only.
   */
  epiphanybf_h_all_registers_set_raw(STATE_CPU(sd, 0), H_REG_MESH_COREID,
				 es_get_coreid(STATE_ESIM(sd)));

  switch (STATE_ENVIRONMENT (sd))
    {
    case ALL_ENVIRONMENT:
      /* Fall through, default environment is USER */
    case USER_ENVIRONMENT:
      /* set up arguments */
      epiphany_user_init (sd, current_cpu, abfd, argv, envp);
      /* Start by setting caibit */
      epiphanybf_h_caibit_set (current_cpu, 1);
      break;
    case VIRTUAL_ENVIRONMENT:
      /* Start by triggering SYNC interrupt */
      epiphanybf_h_all_registers_set(current_cpu, H_REG_SCR_ILATST, 1);
      break;
    case OPERATING_ENVIRONMENT:
      /* Do nothing, this mode is for full system simulation. */
      break;
    default:
      sim_io_eprintf(sd, "ERROR: Unsupported environment mode\n");
      abort ();
    }

#endif

  return SIM_RC_OK;
}
