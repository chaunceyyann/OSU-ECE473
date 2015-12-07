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
 
#include <avr/io.h>
#include "clock.h"
#include "jtag.h"


static uint8_t jtagDelayTime;
#define delay() short_delay(jtagDelayTime)


void JTAG_set_delay(uint8_t time)
{ 
	jtagDelayTime = time;
}

void JTAG_clock(unsigned char tms, unsigned char tdi, unsigned int n)
{
	CLR_TMS();
	CLR_TDI();
	for (; n>0; n--) 
	{
		CLR_TCK();
		if (tms) SET_TMS();
		if (tdi) SET_TDI();
		delay();
		SET_TCK();
		delay();
	}
}

char JTAG_get_TDO()
{
	CLR_TCK();
	delay();
	return GET_TDO();
}

void JTAG_trst(char trst)
{
	if(trst) JTAG_clock(1,0,6);
}
