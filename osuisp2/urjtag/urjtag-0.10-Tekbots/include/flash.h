/*
 * $Id: flash.h 1444 2009-02-27 19:36:50Z arniml $
 *
 * Copyright (C) 2003 ETC s.r.o.
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
 * Written by Marcel Telka <marcel@telka.sk>, 2003.
 *
 */

#ifndef FLASH_H
#define FLASH_H

#include <stdio.h>
#include <stdint.h>

#include <bus_driver.h>

/* Following moved here from brux/cfi.h */

#include <flash/cfi.h>

typedef struct {
	int width;		/* 1 for 8 bits, 2 for 16 bits, 4 for 32 bits, etc. */
	cfi_query_structure_t cfi;
} cfi_chip_t;

typedef struct {
	bus_t *bus;
	uint32_t address;
	int bus_width;		/* in cfi_chips, e.g. 4 for 32 bits */
	cfi_chip_t **cfi_chips;
} cfi_array_t;

void cfi_array_free( cfi_array_t *cfi_array );
int cfi_detect( bus_t *bus, uint32_t adr, cfi_array_t **cfi_array );

/* End of brux/cfi.h */

typedef struct {
	unsigned int bus_width;		/* 1 for 8 bits, 2 for 16 bits, 4 for 32 bits, etc. */
	const char *name;
	const char *description;
	int (*autodetect)( cfi_array_t *cfi_array );
	void (*print_info)( cfi_array_t *cfi_array );
	int (*erase_block)( cfi_array_t *cfi_array, uint32_t adr );
	int (*unlock_block)( cfi_array_t *cfi_array, uint32_t adr );
	int (*program)( cfi_array_t *cfi_array, uint32_t adr, uint32_t *buffer, int count );
	void (*readarray)( cfi_array_t *cfi_array );
} flash_driver_t;

#define	FLASH_ERROR_NOERROR			0
#define	FLASH_ERROR_INVALID_COMMAND_SEQUENCE	1
#define	FLASH_ERROR_LOW_VPEN			2
#define	FLASH_ERROR_BLOCK_LOCKED		3
#define	FLASH_ERROR_UNKNOWN			99

void detectflash( bus_t *bus, uint32_t adr );

void flashmem( bus_t *bus, FILE *f, uint32_t addr, int );
void flashmsbin( bus_t *bus, FILE *f, int );

/* end of original brux/flash.h */

extern flash_driver_t *flash_drivers[];

#endif /* FLASH_H */

