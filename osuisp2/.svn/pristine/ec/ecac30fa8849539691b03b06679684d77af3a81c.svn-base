
#include "pins.h"

void DisableProgramming ()
{
	spiHWdisable();
	JTAG_OUTPUT_OFF();
	SPI_OUTPUT_OFF();
	
	DDRB &= ~(PIN(PB2) | PIN(PB3) | PIN(PB4) | PIN (PB5));
	PORTB &= ~(PIN(PB2) | PIN(PB3) | PIN(PB4) | PIN (PB5));
	
	DDRD &= ~(PIN(PD4) | PIN(PD5) | PIN(PD6) | PIN(PD7));
	PORTD &= ~(PIN(PD4) | PIN(PD5) | PIN(PD6) | PIN(PD7));
}

void EnableSPI()
{
	DisableProgramming();
	SPI_OUTPUT_ON();
	DDRB |= PIN(PB2) | PIN(PB3) | PIN(PB5);
}

void EnableJTAG()
{
	DisableProgramming();
	JTAG_OUTPUT_ON();
	DDRD |= PIN(PD4) | PIN(PD5) | PIN(PD6);
	PORTD |= PIN(PD7); // Pull up on PORTD
}