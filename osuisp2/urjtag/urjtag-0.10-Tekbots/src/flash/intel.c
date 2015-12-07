/*
 * $Id: intel.c 1459 2009-03-18 21:48:38Z arniml $
 *
 * Copyright (C) 2002 ETC s.r.o.
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
 * Written by Marcel Telka <marcel@telka.sk>, 2002.
 * Changed by August Hörandl, 2003
 *
 * Documentation:
 * [1] Advanced Micro Devices, "Common Flash Memory Interface Specification Release 2.0",
 *     December 1, 2001
 * [2] Intel Corporation, "Intel PXA250 and PXA210 Application Processors
 *     Developer's Manual", February 2002, Order Number: 278522-001
 * [3] Intel Corporation, "Common Flash Interface (CFI) and Command Sets
 *     Application Note 646", April 2000, Order Number: 292204-004
 * [4] Advanced Micro Devices, "Common Flash Memory Interface Publication 100 Vendor & Device
 *     ID Code Assignments", December 1, 2001, Volume Number: 96.1
 * [5] Micron Technology, Inc. "Q-Flash Memory MT28F123J3, MT28F640J3, MT28F320J3",
 *     MT28F640J3.fm - Rev. N 3/05 EN
 *
 */

#include "sysdep.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <flash/cfi.h>
#include <flash/intel.h>
#include <flash/mic.h>

#include <jtag.h>
#include <flash.h>
#include <bus.h>

static int intel_flash_erase_block( cfi_array_t *cfi_array, uint32_t adr );
static int intel_flash_unlock_block( cfi_array_t *cfi_array, uint32_t adr );
static int intel_flash_program_single( cfi_array_t *cfi_array, uint32_t adr, uint32_t data );
static int intel_flash_program_buffer( cfi_array_t *cfi_array, uint32_t adr, uint32_t *buffer, int count );
static int intel_flash_program( cfi_array_t *cfi_array, uint32_t adr, uint32_t *buffer, int count );
static int intel_flash_erase_block32( cfi_array_t *cfi_array, uint32_t adr );
static int intel_flash_unlock_block32( cfi_array_t *cfi_array, uint32_t adr );
static int intel_flash_program32_single( cfi_array_t *cfi_array, uint32_t adr, uint32_t data );
static int intel_flash_program32( cfi_array_t *cfi_array, uint32_t adr, uint32_t *buffer, int count );

/* autodetect, we can handle this chip */
static int 
intel_flash_autodetect32( cfi_array_t *cfi_array )
{
	bus_area_t area;

	if (bus_area( cfi_array->bus, cfi_array->address, &area ) != URJTAG_STATUS_OK)
		return 0;

	return ((cfi_array->cfi_chips[0]->cfi.identification_string.pri_id_code == CFI_VENDOR_MITSUBISHI_SCS)
		 || (cfi_array->cfi_chips[0]->cfi.identification_string.pri_id_code == CFI_VENDOR_MITSUBISHI_ECS)
		 || (cfi_array->cfi_chips[0]->cfi.identification_string.pri_id_code == CFI_VENDOR_INTEL_ECS)
		 || (cfi_array->cfi_chips[0]->cfi.identification_string.pri_id_code == CFI_VENDOR_INTEL_SCS))
		 && (area.width == 32);
}

static int 
intel_flash_autodetect( cfi_array_t *cfi_array )
{
	bus_area_t area;

	if (bus_area( cfi_array->bus, cfi_array->address, &area ) != URJTAG_STATUS_OK)
		return 0;

	return ((cfi_array->cfi_chips[0]->cfi.identification_string.pri_id_code == CFI_VENDOR_MITSUBISHI_SCS)
		 || (cfi_array->cfi_chips[0]->cfi.identification_string.pri_id_code == CFI_VENDOR_MITSUBISHI_ECS)
		 || (cfi_array->cfi_chips[0]->cfi.identification_string.pri_id_code == CFI_VENDOR_INTEL_ECS)
		 || (cfi_array->cfi_chips[0]->cfi.identification_string.pri_id_code == CFI_VENDOR_INTEL_SCS))
		 && (area.width == 16);
}

static int 
intel_flash_autodetect8( cfi_array_t *cfi_array )
{
	bus_area_t area;

	if (bus_area( cfi_array->bus, cfi_array->address, &area ) != URJTAG_STATUS_OK)
		return 0;

	return ((cfi_array->cfi_chips[0]->cfi.identification_string.pri_id_code == CFI_VENDOR_MITSUBISHI_SCS)
		 || (cfi_array->cfi_chips[0]->cfi.identification_string.pri_id_code == CFI_VENDOR_MITSUBISHI_ECS)
		 || (cfi_array->cfi_chips[0]->cfi.identification_string.pri_id_code == CFI_VENDOR_INTEL_ECS)
		 || (cfi_array->cfi_chips[0]->cfi.identification_string.pri_id_code == CFI_VENDOR_INTEL_SCS))
		 && (area.width == 8);
}

static void
_intel_flash_print_info( cfi_array_t *cfi_array, int o )
{
	uint32_t mid, cid;
	bus_t *bus = cfi_array->bus;

	mid = (bus_read( bus, cfi_array->address + (0x00 << o) ) & 0xFF);
	switch (mid) {
		case STD_MIC_INTEL:
			printf( _("Manufacturer: %s\n"), STD_MICN_INTEL );
			break;
		case STD_MIC_MITSUBISHI:
			printf( _("Manufacturer: %s\n"), STD_MICN_MITSUBISHI );
			break;
		case STD_MIC_MICRON_TECHNOLOGY:
			printf( _("Manufacturer: %s\n"), STD_MICN_MICRON_TECHNOLOGY );
			break;
		default:
			printf( _("Unknown manufacturer (0x%04X)!\n"), mid);
			break;
	}

	printf( _("Chip: ") );
	cid = (bus_read( bus, cfi_array->address + (0x01 << o) ) & 0xFFFF);
	switch (cid) {
		case 0x0016:
			printf( "28F320J3A\n" );
			break;
		case 0x0017:
			printf( "28F640J3A\n" );
			break;
		case 0x0018:
			printf( "28F128J3A\n" );
			break;
		case 0x001D:
			printf( "28F256J3A\n" );
			break;
		case 0x8801:
			printf( "28F640K3\n" );
			break;
		case 0x8802:
			printf( "28F128K3\n" );
			break;
		case 0x8803:
			printf( "28F256K3\n" );
			break;
		case 0x8805:
			printf( "28F640K18\n" );
			break;
		case 0x8806:
			printf( "28F128K18\n" );
			break;
		case 0x8807:
			printf( "28F256K18\n" );
			break;
		case 0x880B:
			printf( "GE28F640L18T\n" );
			break;
		case 0x880C:
			printf( "GE28F128L18T\n" );
			break;
		case 0x880D:
			printf( "GE28F256L18T\n" );
			break;
		case 0x880E:
			printf( "GE28F640L18B\n" );
			break;
		case 0x880F:
			printf( "GE28F128L18B\n" );
			break;
		case 0x8810:
			printf( "GE28F256L18B\n" );
			break;
		default:
			printf( _("Unknown (0x%02X)!\n"), cid );
			break;
	}

	/* Read Array */
	bus_write( bus, cfi_array->address + (0 << o), 0x00FF00FF );
}

static void
intel_flash_print_info( cfi_array_t *cfi_array )
{
	int o = 1;
	bus_t *bus = cfi_array->bus;

	/* Intel Primary Algorithm Extended Query Table - see Table 5. in [3] */
	/* TODO */

	/* Clear Status Register */
	bus_write( bus, cfi_array->address + (0 << o), 0x0050 );

	/* Read Identifier Command */
	bus_write( bus, cfi_array->address + (0 << 0), 0x0090 );

	_intel_flash_print_info( cfi_array, o );
}

static void
intel_flash_print_info32( cfi_array_t *cfi_array )
{
	int o = 2;
	bus_t *bus = cfi_array->bus;
	/* Intel Primary Algorithm Extended Query Table - see Table 5. in [3] */
	/* TODO */

	/* Clear Status Register */
	bus_write( bus, cfi_array->address + (0 << o), 0x00500050 );

	/* Read Identifier Command */
	bus_write( bus, cfi_array->address + (0 << 0), 0x00900090 );

	_intel_flash_print_info( cfi_array, o );
}

static int
intel_flash_erase_block( cfi_array_t *cfi_array, uint32_t adr )
{
	uint16_t sr;
	bus_t *bus = cfi_array->bus;

	bus_write( bus, cfi_array->address, CFI_INTEL_CMD_CLEAR_STATUS_REGISTER );
	bus_write( bus, adr, CFI_INTEL_CMD_BLOCK_ERASE );
	bus_write( bus, adr, CFI_INTEL_CMD_CONFIRM );

	while (!((sr = bus_read( bus, cfi_array->address ) & 0xFE) & CFI_INTEL_SR_READY)) ; 		/* TODO: add timeout */

	switch (sr & ~CFI_INTEL_SR_READY) {
		case 0:
			return 0;
		case CFI_INTEL_SR_ERASE_ERROR | CFI_INTEL_SR_PROGRAM_ERROR:
			printf( _("flash: invalid command seq\n") );
			return FLASH_ERROR_INVALID_COMMAND_SEQUENCE;
		case CFI_INTEL_SR_ERASE_ERROR | CFI_INTEL_SR_VPEN_ERROR:
			printf( _("flash: low vpen\n") );
			return FLASH_ERROR_LOW_VPEN;
		case CFI_INTEL_SR_ERASE_ERROR | CFI_INTEL_SR_BLOCK_LOCKED:
			printf( _("flash: block locked\n") );
			return FLASH_ERROR_BLOCK_LOCKED;
		default:
			break;
	}

	return FLASH_ERROR_UNKNOWN;
}

static int
intel_flash_unlock_block( cfi_array_t *cfi_array, uint32_t adr )
{
	uint16_t sr;
	bus_t *bus = cfi_array->bus;

	bus_write( bus, cfi_array->address, CFI_INTEL_CMD_CLEAR_STATUS_REGISTER );
	bus_write( bus, adr, CFI_INTEL_CMD_LOCK_SETUP );
	bus_write( bus, adr, CFI_INTEL_CMD_UNLOCK_BLOCK );

	while (!((sr = bus_read( bus, cfi_array->address ) & 0xFE) & CFI_INTEL_SR_READY)) ; 		/* TODO: add timeout */

	if (sr != CFI_INTEL_SR_READY) {
		printf( _("flash: unknown error while unblocking\n") );
		return FLASH_ERROR_UNKNOWN;
	} else
		return 0;
}

static int
intel_flash_program_single( cfi_array_t *cfi_array, uint32_t adr, uint32_t data )
{
	uint16_t sr;
	bus_t *bus = cfi_array->bus;

	bus_write( bus, cfi_array->address, CFI_INTEL_CMD_CLEAR_STATUS_REGISTER );
	bus_write( bus, adr, CFI_INTEL_CMD_PROGRAM1 );
	bus_write( bus, adr, data );

	while (!((sr = bus_read( bus, cfi_array->address ) & 0xFE) & CFI_INTEL_SR_READY)) ; 		/* TODO: add timeout */

	if (sr != CFI_INTEL_SR_READY) {
		printf( _("flash: unknown error while programming\n") );
		return FLASH_ERROR_UNKNOWN;
	} else
		return 0;
}

static int
intel_flash_program_buffer( cfi_array_t *cfi_array, uint32_t adr, uint32_t *buffer, int count )
{
	/* NOTE: Write-to-buffer programming operation according to [5], Figure 9 */
	uint16_t sr;
	bus_t *bus = cfi_array->bus;
	cfi_chip_t *cfi_chip = cfi_array->cfi_chips[0];
	int wb_bytes = cfi_chip->cfi.device_geometry.max_bytes_write;
	int chip_width = cfi_chip->width;
	int offset = 0;

	while (count > 0) {
		int wcount, idx;
		uint32_t block_adr = adr;

		/* determine length of next multi-byte write */
		wcount = wb_bytes - (adr % wb_bytes);
		wcount /= chip_width;
		if (wcount > count)
			wcount = count;

		/* issue command WRITE_TO_BUFFER */
		bus_write( bus, cfi_array->address, CFI_INTEL_CMD_CLEAR_STATUS_REGISTER );
		bus_write( bus, adr, CFI_INTEL_CMD_WRITE_TO_BUFFER );
		/* poll XSR7 == 1 */
		while (!((sr = bus_read( bus, cfi_array->address ) & 0xFE) & CFI_INTEL_SR_READY)) ; 		/* TODO: add timeout */

		/* write count value (number of upcoming writes - 1) */
		bus_write( bus, adr, wcount-1 );

		/* write payload to buffer */
		for (idx = 0; idx < wcount; idx++) {
			bus_write( bus, adr, buffer[offset + idx] );
			adr += cfi_array->bus_width;
		}
		offset += wcount;

		/* issue command WRITE_CONFIRM */
		bus_write( bus, block_adr, CFI_INTEL_CMD_WRITE_CONFIRM );

		count -= wcount;
	}

	/* poll SR7 == 1 */
	while (!((sr = bus_read( bus, cfi_array->address ) & 0xFE) & CFI_INTEL_SR_READY)) ; 		/* TODO: add timeout */
	if (sr != CFI_INTEL_SR_READY) {
		printf( _("flash: unknown error while programming\n") );
		return FLASH_ERROR_UNKNOWN;
	}

	return 0;
}

static int
intel_flash_program( cfi_array_t *cfi_array, uint32_t adr, uint32_t *buffer, int count )
{
	cfi_query_structure_t *cfi = &(cfi_array->cfi_chips[0]->cfi);
	int max_bytes_write = cfi->device_geometry.max_bytes_write;

#ifndef FLASH_MULTI_BYTE
	max_bytes_write = 0;
#endif

	/* multi-byte writes supported? */
	if (max_bytes_write > 1)
		return intel_flash_program_buffer( cfi_array, adr, buffer, count );

	else {
		/* unroll buffer to single writes */
		int idx;

		for (idx = 0; idx < count; idx++) {
			int status = intel_flash_program_single( cfi_array, adr, buffer[idx] );
			if (status)
				return status;
			adr += cfi_array->bus_width;
		}
	}

	return 0;
}

static int
intel_flash_erase_block32( cfi_array_t *cfi_array, uint32_t adr )
{
	uint32_t sr;
	bus_t *bus = cfi_array->bus;

	bus_write( bus, cfi_array->address, (CFI_INTEL_CMD_CLEAR_STATUS_REGISTER << 16) | CFI_INTEL_CMD_CLEAR_STATUS_REGISTER );
	bus_write( bus, adr, (CFI_INTEL_CMD_BLOCK_ERASE << 16) | CFI_INTEL_CMD_BLOCK_ERASE );
	bus_write( bus, adr, (CFI_INTEL_CMD_CONFIRM << 16) | CFI_INTEL_CMD_CONFIRM );

	while (((sr = bus_read( bus, cfi_array->address ) & 0x00FE00FE) & ((CFI_INTEL_SR_READY << 16) | CFI_INTEL_SR_READY)) != ((CFI_INTEL_SR_READY << 16) | CFI_INTEL_SR_READY)) ; 		/* TODO: add timeout */

	if (sr != ((CFI_INTEL_SR_READY << 16) | CFI_INTEL_SR_READY)) {
		printf( "\nsr = 0x%08X\n", sr );
		return FLASH_ERROR_UNKNOWN;
	} else
		return 0;
}

static int
intel_flash_unlock_block32( cfi_array_t *cfi_array, uint32_t adr )
{
	uint32_t sr;
	bus_t *bus = cfi_array->bus;

	bus_write( bus, cfi_array->address, (CFI_INTEL_CMD_CLEAR_STATUS_REGISTER << 16) | CFI_INTEL_CMD_CLEAR_STATUS_REGISTER );
	bus_write( bus, adr, (CFI_INTEL_CMD_LOCK_SETUP << 16) | CFI_INTEL_CMD_LOCK_SETUP );
	bus_write( bus, adr, (CFI_INTEL_CMD_UNLOCK_BLOCK << 16) | CFI_INTEL_CMD_UNLOCK_BLOCK );

	while (((sr = bus_read( bus, cfi_array->address ) & 0x00FE00FE) & ((CFI_INTEL_SR_READY << 16) | CFI_INTEL_SR_READY)) != ((CFI_INTEL_SR_READY << 16) | CFI_INTEL_SR_READY)) ; 		/* TODO: add timeout */

	if (sr != ((CFI_INTEL_SR_READY << 16) | CFI_INTEL_SR_READY)) {
		printf( "\nsr = 0x%08X\n", sr );
		return FLASH_ERROR_UNKNOWN;
	} else
		return 0;
}

static int
intel_flash_program32_single( cfi_array_t *cfi_array, uint32_t adr, uint32_t data )
{
	uint32_t sr;
	bus_t *bus = cfi_array->bus;

	bus_write( bus, cfi_array->address, (CFI_INTEL_CMD_CLEAR_STATUS_REGISTER << 16) | CFI_INTEL_CMD_CLEAR_STATUS_REGISTER );
	bus_write( bus, adr, (CFI_INTEL_CMD_PROGRAM1 << 16) | CFI_INTEL_CMD_PROGRAM1 );
	bus_write( bus, adr, data );

	while (((sr = bus_read( bus, cfi_array->address ) & 0x00FE00FE) & ((CFI_INTEL_SR_READY << 16) | CFI_INTEL_SR_READY)) != ((CFI_INTEL_SR_READY << 16) | CFI_INTEL_SR_READY)) ; 		/* TODO: add timeout */

	if (sr != ((CFI_INTEL_SR_READY << 16) | CFI_INTEL_SR_READY)) {
		printf( "\nsr = 0x%08X\n", sr );
		return FLASH_ERROR_UNKNOWN;
	} else
		return 0;
}

static int
intel_flash_program32( cfi_array_t *cfi_array, uint32_t adr, uint32_t *buffer, int count )
{
	/* Single byte programming is forced for 32 bit (2x16) flash configuration.
	   a) lack of testing capbilities for 2x16 multi-byte write operation
	   b) no implementation of intel_flash_program32_buffer() available
	   Closing these issues will enable multi-byte for 2x16 as well. */
	int idx;

	/* unroll buffer to single writes */
	for (idx = 0; idx < count; idx++) {
		int status = intel_flash_program32_single( cfi_array, adr, buffer[idx] );
		if (status)
			return status;
		adr += cfi_array->bus_width;
	}

	return 0;
}

static void
intel_flash_readarray32( cfi_array_t *cfi_array )
{
	/* Read Array */
	bus_write( cfi_array->bus, cfi_array->address, 0x00FF00FF );
}

static void
intel_flash_readarray( cfi_array_t *cfi_array )
{
	/* Read Array */
	bus_write( cfi_array->bus, cfi_array->address, 0x00FF00FF );
}

flash_driver_t intel_32_flash_driver = {
	4, /* buswidth */
	N_("Intel Standard Command Set"),
	N_("supported: 28Fxxxx, 2 x 16 bit"),
	intel_flash_autodetect32,
	intel_flash_print_info32,
	intel_flash_erase_block32,
	intel_flash_unlock_block32,
	intel_flash_program32,
	intel_flash_readarray32,
};

flash_driver_t intel_16_flash_driver = {
	2, /* buswidth */
	N_("Intel Standard Command Set"),
	N_("supported: 28Fxxxx, 1 x 16 bit"),
	intel_flash_autodetect,
	intel_flash_print_info,
	intel_flash_erase_block,
	intel_flash_unlock_block,
	intel_flash_program,
	intel_flash_readarray,
};

flash_driver_t intel_8_flash_driver = {
	1, /* buswidth */
	N_("Intel Standard Command Set"),
	N_("supported: 28Fxxxx, 1 x 8 bit"),
	intel_flash_autodetect8,
	intel_flash_print_info,
	intel_flash_erase_block,
	intel_flash_unlock_block,
	intel_flash_program,
	intel_flash_readarray,
};
