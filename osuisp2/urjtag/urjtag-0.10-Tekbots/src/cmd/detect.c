/*
 * $Id: detect.c 1366 2008-09-26 22:14:08Z arniml $
 *
 * Copyright (C) 2003 ETC s.r.o.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * Written by Marcel Telka <marcel@telka.sk>, 2003.
 *
 */

#include "sysdep.h"

#include <stdio.h>
#include <string.h>

#include "jtag.h"
#include "chain.h"
#include "bus.h"

#include "cmd.h"

static int
cmd_detect_run( chain_t *chain, char *params[] )
{
	int i;
	bus_t * abus;
	
	if (cmd_params( params ) != 1)
		return -1;

	if (!cmd_test_cable( chain ))
		return 1;

	buses_free();
	parts_free( chain->parts );
	chain->parts = NULL;
	detect_parts( chain, jtag_get_data_dir() );
	if (!chain->parts)
		return 1;
	if (!chain->parts->len) {
		parts_free( chain->parts );
		chain->parts = NULL;
		return 1;
	}
	parts_set_instruction( chain->parts, "SAMPLE/PRELOAD" );
	chain_shift_instructions( chain );
	chain_shift_data_registers( chain, 1 );
	parts_set_instruction( chain->parts, "BYPASS" );
	chain_shift_instructions( chain );
	
	// Initialize all the buses
	for (i = 0; i < buses.len; i++)
	{
		abus = buses.buses[i];
		if(abus->driver->init)
		{
			if(abus->driver->init(abus) != URJTAG_STATUS_OK)
				return -1;
		}
	}

	return 1;
}

static void
cmd_detect_help( void )
{
	printf( _(
		"Usage: %s\n"
		"Detect parts on the JTAG chain.\n"
		"\n"
		"Output from this command is a list of the detected parts.\n"
		"If no parts are detected other commands may not work properly.\n"
	), "detect" );
}

cmd_t cmd_detect = {
	"detect",
	N_("detect parts on the JTAG chain"),
	cmd_detect_help,
	cmd_detect_run
};
