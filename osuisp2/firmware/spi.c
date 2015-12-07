/*
 * isp.c - part of USBasp
 *
 * Autor..........: Thomas Fischl <tfischl@gmx.de>
 * Description....: Provides functions for communication/programming
 *                  over ISP interface
 * Licence........: GNU GPL v2 (see Readme.txt)
 * Creation Date..: 2005-02-23
 * Last change....: 2009-02-28
 */
 
#include <avr/io.h>
#include "spi.h"
#include "clock.h"

uchar sw_delay_time = 0;

uchar SPI_SetSCKOption(uchar option) 
{
	if (SlowClockSet()) /** Check slow clock switch (jumper on board) */
	{
		option = SLOWEST_CLOCK;
	}
	if (option == 0) /// 0 is an invalid option, use default clock
	{
		option = DEFAULT_CLOCK;
	}
		
	SPSR = 0;

	// Software
	if (option > 5)
	{
		sw_delay_time = option-5;
	}
	else // 1 through 5 are hardware SPI
	{
		sw_delay_time = 0; // Means we're using hardware
		switch (option) 
		{
			case 1: /// 1500 Khz
				SPSR = (1 << SPI2X); /// <-- Double speed, fall through to set SPCR
				
			case 2: /// 750 Khz
				SPCR = (1 << MSTR) | (1 << SPR0);
				break;
			
			case 3: /// 357 Khz
				SPSR = (1 << SPI2X); /// <-- Double speed, fall through to set SPCR
			
			case 4: /// 187.5 Khz
				SPCR = (1 << MSTR) | (1 << SPR1);
				break;
				
			case 5: /// 93.75 Khz
				SPCR = (1 << MSTR) | (1 << SPR1) | (1 << SPR0);
				break;
		}
	}
	
	return option;
}

/** 
 @brief Enable SPI hardware and reset the connected device.
 This function leaves the target in reset mode.
 Use SET_RST() to un-reset the target device.
 @param clockOption Clock option for spi clock speed
 @param maintainReset True to maintain target reset state
 @return actual set clock option: this may differ from
 the option passed in if the passed in value is invalid
 or if the slow clock jumper is connected */
uchar SPI_Connect(uchar clockOption, uchar maintainReset) 
{
	clockOption = SPI_SetSCKOption(clockOption);

	/** Turn on the SPI pins */
	EnableSPI();

	/** Reset the device, and maintain reset */
	SET_RST();
	CLR_RST();
	clockWait(1);
	SET_RST();
	
	/** Put the device back into reset mode if required */
	if (maintainReset)
	{
		clockWait(1);
		CLR_RST();
	}
	
	/** Enable the SPI Hardware (if needed) */
	if (sw_delay_time == 0)
		spiHWenable();
	
	return clockOption;
}


uchar SPI_Transmit(uchar send_byte) 
{
	if (sw_delay_time == 0)
	{
		SPDR = send_byte;
		while(!(SPSR & (1<<SPIF)));
		return SPDR;
	}
	else
	{
		return SPI_Transmit_sw(send_byte);
	}
}

uchar SPI_Transmit_sw(uchar send_byte) 
{
	uchar rec_byte = 0;
	uchar i;
	for (i = 0; i < 8; i++) 
	{
		// Transmit MSB first
		if ((send_byte & 0x80) != 0) 
		{
			SET_MOSI(); // Set MOSI high
		} 
		else 
		{
			CLR_MOSI(); // Set MOSI low
		}
		
		// Shift 2nd msb to msb
		send_byte = send_byte << 1;

		// Get data from MISO pin
		rec_byte = rec_byte << 1;
		if (GET_MISO()) 
		{
			rec_byte++;
		}

		// Pulse clock
		SET_SCK();
		ten_us_delay(sw_delay_time);
		CLR_SCK();
		ten_us_delay(sw_delay_time);
	}

	return rec_byte;
}

uchar SPI_EnterProgrammingMode() 
{
	uchar check;
	uchar count = 3; // Try to connect 3 times

	for (; count > 0; count--)
	{
		SPI_Transmit(0xAC);
		SPI_Transmit(0x53);
		check = SPI_Transmit(0);
		SPI_Transmit(0);

		if (check == 0x53) 
		{
			return 0; // Success! We're connected an in programming mode!
		}
		
		// If the connect command failed,
		// the communication may be out of sync.
		// Pulse reset (as per the datasheet) and
		// try again.
		SET_RST(); // Device into normal operation
		clockWait(1);
		CLR_RST(); // Device back into reset mode
		clockWait(63); // Wait 20 ms before sending another program enable command

	}

	return 1; /* error: device dosn't answer */
}

uchar SPI_ReadFlash(unsigned long address) 
{
	SPI_Transmit(0x20 | ((address & 1) << 3));
	SPI_Transmit(address >> 9);
	SPI_Transmit(address >> 1);
	return SPI_Transmit(0);
}

uchar SPI_WriteFlash(unsigned long address, uchar data, uchar pollmode) 
{

	// We're not guarenteed that there was a chip erase, so we can't 
	// skip programming of 0xFF...
	/* 0xFF is value after chip erase, so skip programming
	 if (data == 0xFF) {
	 return 0;
	 }
	 */

	SPI_Transmit(0x40 | ((address & 1) << 3));
	SPI_Transmit(address >> 9);
	SPI_Transmit(address >> 1);
	SPI_Transmit(data);

	if (pollmode == 0)
		return 0;

	if (data == 0x7F) 
	{
		clockWait(15); // wait 4,8 ms
		return 0;
	} 
	else 
	{
		// Poll flash for (30 * 320 uS)
		uchar counter = 30;
		TIMER1 = 0;
		while (counter != 0) 
		{
			if (SPI_ReadFlash(address) != 0x7F) 
			{
				return 0;
			};
			
			if (TIMER1 > CLOCK_T_320us) 
			{
				TIMER1 = 0;
				counter--;
			}
			
		}
		return 1; /* error */
	}

}

uchar SPI_FlushPage(unsigned long address, uchar pollvalue) 
{
	SPI_Transmit(0x4C);
	SPI_Transmit(address >> 9);
	SPI_Transmit(address >> 1);
	SPI_Transmit(0);

	if (pollvalue == 0xFF) {
		clockWait(15);
		return 0;
	} else {

		/* polling flash */
		uchar counter = 30;
		TIMER1 = 0;

		while (counter != 0) 
		{
			if (SPI_ReadFlash(address) != 0xFF) 
			{
				return 0;
			}
			
			if (TIMER1 > CLOCK_T_320us) 
			{
				TIMER1 = 0;
				counter--;
			}
		}
		return 1; /* error */
	}
}

uchar SPI_ReadEEPROM(unsigned int address) 
{
	SPI_Transmit(0xA0);
	SPI_Transmit(address >> 8);
	SPI_Transmit(address);
	return SPI_Transmit(0);
}

uchar SPI_WriteEEPROM(unsigned int address, uchar data) 
{

	SPI_Transmit(0xC0);
	SPI_Transmit(address >> 8);
	SPI_Transmit(address);
	SPI_Transmit(data);
	clockWait(30); // Wait 9.6ms for write to complete
	return 0;
}
