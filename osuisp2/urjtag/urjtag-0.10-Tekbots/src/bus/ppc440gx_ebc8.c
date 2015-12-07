/*
 * Copyright (C) 2002, 2003 ETC s.r.o.
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
 * Written by Marcel Telka <marcel@telka.sk>, 2002, 2003.
 */

#include "sysdep.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "part.h"
#include "bus.h"
#include "chain.h"
#include "bssignal.h"
#include "jtag.h"
#include "buses.h"
#include "generic_bus.h"

#define PPC440GX_ADDR_LINES 32
#define PPC440GX_DATA_LINES  8

typedef struct {
	signal_t *a[PPC440GX_ADDR_LINES];
	signal_t *d[PPC440GX_DATA_LINES];
	signal_t *ncs;
	signal_t *nwe;
	signal_t *noe;
} bus_params_t;

#define	A	((bus_params_t *) bus->params)->a
#define	D	((bus_params_t *) bus->params)->d
#define	nCS	((bus_params_t *) bus->params)->ncs
#define	nWE	((bus_params_t *) bus->params)->nwe
#define	nOE	((bus_params_t *) bus->params)->noe


/**
 * bus->driver->(*new_bus)
 *
 */
static bus_t *
ppc440gx_ebc8_bus_new( chain_t *chain, const bus_driver_t *driver, char *cmd_params[] )
{
	bus_t *bus;
	part_t *part;
	char buff[10];
	int i;
	int failed = 0;

	bus = calloc( 1, sizeof (bus_t) );
	if (!bus)
		return NULL;

	bus->driver = driver;
	bus->params = calloc( 1, sizeof (bus_params_t) );
	if (!bus->params) {
		free( bus );
		return NULL;
	}

	CHAIN = chain;
	PART = part = chain->parts->parts[chain->active_part];

	for (i = 0; i < PPC440GX_ADDR_LINES; i++) {
		sprintf( buff, "EBCADR%d", i );
		failed |= generic_bus_attach_sig( part, &(A[i]), buff );
	}

	for (i = 0; i < PPC440GX_DATA_LINES; i++) {
		sprintf( buff, "EBCDATA%d", i );
		failed |= generic_bus_attach_sig( part, &(D[i]), buff );
	}

	failed |= generic_bus_attach_sig( part, &(nCS), "EBCCS0_N" );

	failed |= generic_bus_attach_sig( part, &(nWE), "EBCWE_N"  );

	failed |= generic_bus_attach_sig( part, &(nOE), "EBCOE_N"  );

	if (failed) {
		free( bus->params );
		free( bus );
		return NULL;
	}

	return bus;
}

/**
 * bus->driver->(*printinfo)
 *
 */
static void
ppc440gx_ebc8_bus_printinfo( bus_t *bus )
{
	int i;

	for (i = 0; i < CHAIN->parts->len; i++)
		if (PART == CHAIN->parts->parts[i])
			break;
	printf( _("IBM PowerPC 440GX 8-bit compatible bus driver via BSR (JTAG part No. %d)\n"), i );
}

/**
 * bus->driver->(*area)
 *
 */
static int
ppc440gx_ebc8_bus_area( bus_t *bus, uint32_t adr, bus_area_t *area )
{
	area->description = NULL;
	area->start = UINT32_C(0x00000000);
	area->length = UINT64_C(0x100000000); /* ??????????? */
	area->width = PPC440GX_DATA_LINES;

	return URJTAG_STATUS_OK;
}

static void
setup_address( bus_t *bus, uint32_t a )
{
	int i;
	part_t *p = PART;

	for (i = 0; i < PPC440GX_ADDR_LINES; i++)
		part_set_signal( p, A[i], 1, (a >> (PPC440GX_ADDR_LINES-1-i)) & 1 );
}

static void
set_data_in( bus_t *bus )
{
	int i;
	part_t *p = PART;
	bus_area_t area;

	ppc440gx_ebc8_bus_area( bus, 0, &area );

	for (i = 0; i < area.width; i++)
		part_set_signal( p, D[i], 0, 0 );
}

static void
setup_data( bus_t *bus, uint32_t d )
{
	int i;
	part_t *p = PART;
	bus_area_t area;

	ppc440gx_ebc8_bus_area( bus, 0, &area );

	for (i = 0; i < area.width; i++)
		part_set_signal( p, D[PPC440GX_DATA_LINES-1-i], 1, (d >> i) & 1 );
}

/**
 * bus->driver->(*read_start)
 *
 */
static void
ppc440gx_ebc8_bus_read_start( bus_t *bus, uint32_t adr )
{
	part_t *p = PART;
	chain_t *chain = CHAIN;

	part_set_signal( p, nCS, 1, 0 );
	part_set_signal( p, nWE, 1, 1 );
	part_set_signal( p, nOE, 1, 0 );

	setup_address( bus, adr );
	set_data_in( bus );

	chain_shift_data_registers( chain, 0 );
}

/**
 * bus->driver->(*read_next)
 *
 */
static uint32_t
ppc440gx_ebc8_bus_read_next( bus_t *bus, uint32_t adr )
{
	part_t *p = PART;
	chain_t *chain = CHAIN;
	int i;
	uint32_t d = 0;
	bus_area_t area;

	ppc440gx_ebc8_bus_area( bus, adr, &area );

	setup_address( bus, adr );
	chain_shift_data_registers( chain, 1 );

	for (i = 0; i < area.width; i++)
		d |= (uint32_t) (part_get_signal( p, D[PPC440GX_DATA_LINES-1-i] ) << i);

	return d;
}

/**
 * bus->driver->(*read_end)
 *
 */
static uint32_t
ppc440gx_ebc8_bus_read_end( bus_t *bus )
{
	part_t *p = PART;
	chain_t *chain = CHAIN;
	int i;
	uint32_t d = 0;
	bus_area_t area;

	ppc440gx_ebc8_bus_area( bus, 0, &area );

	part_set_signal( p, nCS, 1, 1 );
	part_set_signal( p, nOE, 1, 1 );
	chain_shift_data_registers( chain, 1 );

	for (i = 0; i < area.width; i++)
		d |= (uint32_t) (part_get_signal( p, D[PPC440GX_DATA_LINES-1-i] ) << i);

	return d;
}

/**
 * bus->driver->(*write)
 *
 */
static void
ppc440gx_ebc8_bus_write( bus_t *bus, uint32_t adr, uint32_t data )
{
	part_t *p = PART;
	chain_t *chain = CHAIN;

	part_set_signal( p, nCS, 1, 0 );
	part_set_signal( p, nWE, 1, 1 );
	part_set_signal( p, nOE, 1, 1 );

	setup_address( bus, adr );
	setup_data( bus, data );

	chain_shift_data_registers( chain, 0 );

	part_set_signal( p, nWE, 1, 0 );
	chain_shift_data_registers( chain, 0 );
	part_set_signal( p, nWE, 1, 1 );
	part_set_signal( p, nCS, 1, 1 );
	chain_shift_data_registers( chain, 0 );
}

const bus_driver_t ppc440gx_ebc8_bus = {
	"ppc440gx_ebc8",
	N_("IBM PowerPC 440GX 8-bit EBC compatible bus driver via BSR"),
	ppc440gx_ebc8_bus_new,
	generic_bus_free,
	ppc440gx_ebc8_bus_printinfo,
	generic_bus_prepare_extest,
	ppc440gx_ebc8_bus_area,
	ppc440gx_ebc8_bus_read_start,
	ppc440gx_ebc8_bus_read_next,
	ppc440gx_ebc8_bus_read_end,
	generic_bus_read,
	ppc440gx_ebc8_bus_write,
	generic_bus_no_init
};
