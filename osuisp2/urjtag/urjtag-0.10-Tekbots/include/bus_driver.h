/*
 * $Id: bus_driver.h 1292 2008-07-02 00:32:52Z jiez $
 *
 * Bus driver interface
 * Copyright (C) 2002, 2003 ETC s.r.o.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the ETC s.r.o. nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Written by Marcel Telka <marcel@telka.sk>, 2002, 2003.
 *
 */

#ifndef BRUX_BUS_H
#define	BRUX_BUS_H

#include <stdint.h>

#include "chain.h"

typedef struct {
	const char *description;
	uint32_t start;
	uint64_t length;
	unsigned int width;
} bus_area_t;

typedef struct bus bus_t;
typedef struct bus_driver bus_driver_t;

struct bus_driver {
	const char *name;
	const char *description;
	bus_t *(*new_bus)( chain_t *chain, const bus_driver_t *driver, char *cmd_params[] );
	void (*free_bus)( bus_t *bus );
	void (*printinfo)( bus_t *bus );
	void (*prepare)( bus_t *bus );
	int (*area)( bus_t *bus, uint32_t adr, bus_area_t *area );
	void (*read_start)( bus_t *bus, uint32_t adr );
	uint32_t (*read_next)( bus_t *bus, uint32_t adr );
	uint32_t (*read_end)( bus_t *bus );
	uint32_t (*read)( bus_t *bus, uint32_t adr );
	void (*write)( bus_t *bus, uint32_t adr, uint32_t data );
	int (*init) (bus_t *bus);
};

struct bus {
	chain_t *chain;
	part_t *part;
	void *params;
	int initialized;
	const bus_driver_t *driver;
};

extern bus_t *bus;

#define CHAIN			bus->chain
#define PART			bus->part
#define INITIALIZED		bus->initialized

#define	bus_printinfo(bus)	bus->driver->printinfo(bus)
#define	bus_prepare(bus)	bus->driver->prepare(bus)
#define	bus_area(bus,adr,a)	bus->driver->area(bus,adr,a)
#define	bus_read_start(bus,adr)	bus->driver->read_start(bus,adr)
#define	bus_read_next(bus,adr)	bus->driver->read_next(bus,adr)
#define	bus_read_end(bus)	bus->driver->read_end(bus)
#define	bus_read(bus,adr)	bus->driver->read(bus,adr)
#define	bus_write(bus,adr,data)	bus->driver->write(bus,adr,data)
#define	bus_free(bus)		bus->driver->free_bus(bus)
#define	bus_init(bus)		bus->driver->init(bus)

#endif /* BRUX_BUS_H */
