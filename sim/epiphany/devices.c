/* epiphany device support
   Copyright (C) 1997, 1998, 2007, 2008, 2011 Free Software Foundation, Inc.
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

#ifdef HAVE_DV_SOCKSER
#include "dv-sockser.h"
#endif

/* Stubbed out devices for future enhancement.  */

device epiphany_devices;

int
device_io_read_buffer (device *me, void *source, int space,
		       address_word addr, unsigned nr_bytes,
		       SIM_DESC sd, SIM_CPU *cpu, sim_cia cia)
{
  return -1;
}

int
device_io_write_buffer (device *me, const void *source, int space,
			address_word addr, unsigned nr_bytes,
			SIM_DESC sd, SIM_CPU *cpu, sim_cia cia)
{
  return -1;
}

void
device_error (device *me, const char *message, ...)
{
  return;
}
