/*
 * $Id: endian.c 1102 2008-02-27 03:38:31Z jiez $
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

#include "cmd.h"

static int
cmd_endian_run( chain_t *chain, char *params[] )
{
	if (cmd_params( params ) > 2)
		return -1;

	if (!params[1]) {
		if (big_endian)
			printf( _("Endianess for external files: big\n") );
		else
			printf( _("Endianess for external files: little\n") );
		return 1;
	}


	if (strcasecmp( params[1], "little" ) == 0) {
		big_endian = 0;
		return 1;
	}
	if (strcasecmp( params[1], "big" ) == 0) {
		big_endian = 1;
		return 1;
	}

	return -1;
}

static void
cmd_endian_help( void )
{
	printf( _(
		"Usage: %s\n"
		"Set or print endianess for external files.\n"
	), "endian [little|big]" );
}

cmd_t cmd_endian = {
	"endian",
	N_("set/print endianess"),
	cmd_endian_help,
	cmd_endian_run
};
