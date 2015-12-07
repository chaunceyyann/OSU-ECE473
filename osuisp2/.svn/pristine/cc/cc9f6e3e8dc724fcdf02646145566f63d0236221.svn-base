/*
 * isp.h - part of USBasp
 *
 * Autor..........: Thomas Fischl <tfischl@gmx.de>
 * Description....: Provides functions for communication/programming
 *                  over ISP interface
 * Licence........: GNU GPL v2 (see Readme.txt)
 * Creation Date..: 2005-02-23
 * Last change....: 2009-02-28
 */

#ifndef __isp_h_included__
#define	__isp_h_included__

#ifndef uchar
#define	uchar	unsigned char
#endif

#include "pins.h"

#define SLOWEST_CLOCK 200 // About 5000 Hz
#define DEFAULT_CLOCK 10 // 100 Khz (should work with 1Mhz devices without a problem)

uchar SPI_Connect(uchar clockOption, uchar maintainReset);

uchar SPI_Transmit(uchar send_byte);
uchar SPI_Transmit_sw(uchar send_byte);

uchar SPI_EnterProgrammingMode();

/* read byte from eeprom at given address */
uchar SPI_ReadEEPROM(unsigned int address);

/* write byte to flash at given address */
uchar SPI_WriteFlash(unsigned long address, uchar data, uchar pollmode);

uchar SPI_FlushPage(unsigned long address, uchar pollvalue);

/* read byte from flash at given address */
uchar SPI_ReadFlash(unsigned long address);

/* write byte to eeprom at given address */
uchar SPI_WriteEEPROM(unsigned int address, uchar data);

/* set SCK speed. call before ispConnect! */
uchar SPI_SetSCKOption(uchar sckoption);

#endif /* __isp_h_included__ */
