/*
 * avrdude - A Downloader/Uploader for AVR device programmers
 * Copyright (C) 2006  Thomas Fischl
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* $Id: usbasp.h 815 2009-02-28 13:10:47Z fischl $ */
#ifndef _OSUISP2_H
#define _OSUISP2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <unistd.h>
#include <malloc.h>

#include "avrpart.h"
#include "avrdude.h"
#include "avr.h"
#include "pgm.h"

/** USB device handle type */
typedef struct usbDevice    usbDevice_t;

/** Structure for holding USB data to send */
typedef struct ReportOut
{
    unsigned char reportID;
    unsigned char reportSize;
    unsigned char command;
    unsigned char data [248];
} ReportOut_t;

/** Structure for holding USB received data */
typedef struct ReportIn
{
    unsigned char reportID;
    unsigned char reportSize;
    unsigned char data [249];
} ReportIn_t;

/** Convenience typedef for unsigned 8 bit value
 * Might consider using uint8_t in the future...
 */
typedef unsigned char uchar;


/** Private data for the OSUisp2 programmer */
struct pdata
{
  usbDevice_t *usbhandle;
  int sckfreq_hz;
  int clockOption;
};


/** USB Error Codes */
#define USBOPEN_SUCCESS         0   /* no error */
#define USBOPEN_ERR_ACCESS      1   /* not enough permissions to open device */
#define USBOPEN_ERR_IO          2   /* I/O error */
#define USBOPEN_ERR_NOTFOUND    3   /* device not found */

#if defined(WIN32)
  // Windows hid usb items
  #include <windows.h>
  #include <setupapi.h>
  #include <ddk\hidsdi.h>
  #include <ddk\hidpi.h>
#else
  // libusb specific items
  #include <string.h>
  #include <usb.h>
  #define usbDevice   usb_dev_handle  /* use libusb's device structure */
  #define USBRQ_HID_GET_REPORT    0x01
  #define USBRQ_HID_SET_REPORT    0x09
  #define USB_HID_REPORT_TYPE_FEATURE 3
#endif

/** USB identifiers */
#define	OSUISP2_VENDOR_ID   0x16C0  /* VOTI */
#define	OSUISP2_PRODUCT_ID   0x05DF  /* Obdev's free shared PID */
#define OSUISP2_VENDOR_NAME "beaversource.oregonstate.edu/projects/osuisp2"
#define OSUISP2_PRODUCT_NAME "OSUisp2"

/** SPI Programming Command Identifiers */
#define SPI_PROG_CONNECT    1
#define SPI_PROG_DISCONNECT 2
#define SPI_PROG_TRANSMIT   3
#define SPI_PROG_READMEMORY  4
#define SPI_PROG_ENABLEPROG 5
#define SPI_PROG_WRITEMEMORY 6

/** Block mode flags */
#define OSUISP2_BLOCKFLAG_FIRST    0x01
#define OSUISP2_BLOCKFLAG_LAST     0x02

/** Memory type flags */
#define MEM_EEPROM 0x04
#define MEM_FLASH 0x08

/** Send/Receive Block Size Maximum */
#define ISP_PROG_MAX_SIZE 235

#ifdef __cplusplus
extern "C" {
#endif

void osuisp2_initpgm (PROGRAMMER * pgm);

#ifdef __cplusplus
}
#endif

#endif /* usbasp_h */
