/*****************************************************************************
 *
 *  osuisp.2 - USB in-circuit programmer
 *
 *	Currently osuisp supports SPI programming of Atmel AVR micro controllers
 *	through the software written by Thomas Fischl (See other source files)
 *	as well as added support for JTAG 
 *
 *	This file was written specifically just to add JTAG support with  minimal
 *	alterations as possible to the Original Source.  More information can be 
 *	found at:
 *	http://eecs.oregonstate.edu/education/tekbots.html
 *
 *	Questions regarding the JTAG portion of the firmware can be sent to:
 *	tekbots@eecs.oregonstate.edu
 *
 *	For more information regarding the original firmware contact:
 *	Thomas Fischl <tfischl@gmx.de>
 *	http://www.fischl.de/usbasp/
 *
 *  License:
 *  The project is built with USBasp by Thomas Fischl, liscenced by the
 *  GNU General Public License (GPL).  A copy of the GPL can be found in
 *	the file "COPYING".
 * 
 ****************************************************************************/


#include "pins.h"


void JTAG_enable();

void JTAG_set_delay(uint8_t delay_time);

void JTAG_clock(unsigned char tms,unsigned char tdi,unsigned int n);

char JTAG_get_TDO();

void JTAG_trst(char trst);