/**
 @file clock.c
 @author Thomas Fischl <tfischl@gmx.de>
 @author Ben Porter
 @brief Implementation file for timing functions
 
 License: GNU GPL v2
 @date 7-3-2010
*/

#include <inttypes.h>
#include <avr/io.h>
#include "clock.h"


void clockWait(uint8_t time) 
{
	for (; time>0; time--) 
	{
		TIMER1 = 0;
		while (TIMER1 < CLOCK_T_320us);
	}
}

void ten_us_delay(uint8_t time)
{
	TIMER2 = 2; // Compensate for assignment and function call time
	for(; time > 0; time--)
	{
		while (TIMER2<120);
		TIMER2 = 2; // Compensate (somewhat) for the clock cycles used for the while loop and assignment
	}
}


void short_delay(uint8_t time) 
{
	TIMER2 = 1;
	while (TIMER2<time);
}
