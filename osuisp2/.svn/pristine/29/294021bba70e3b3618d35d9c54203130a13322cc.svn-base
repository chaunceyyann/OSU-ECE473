


#ifndef PINS_H
#define PINS_H


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <util/delay.h>


#define PIN(x)            (1 << (x))
#define SETPIN(addr,x)    (addr |= PIN(x))
#define CLEARPIN(addr,x)  (addr &= ~PIN(x))

/** Slow Clock Jumper */
#define InitSlowClockJumper() CLEARPIN(DDRC, PC2); SETPIN(PORTC, PC2)
#define SlowClockSet() (!((PINC & PIN(PC2)) >> PC2))


/** URJTAG */

//#define JTAG_OUT PORTD
//#define JTAG_IN	 PIND
//#define JTAG_DDR DDRD
//#define TCK 5
//#define TMS 4
//#define TDI 6
//#define TDO 7

/** TDO: Test data from target.  PD7 */
#define GET_TDO() ((PIND & PIN(PD7)) >> PD7)

/** TDI: Test data to target PD6*/
#define SET_TDI() SETPIN(PORTD, PD6)
#define CLR_TDI() CLEARPIN(PORTD, PD6)

/** JTAG State Control PD4 */
#define SET_TMS() SETPIN(PORTD, PD4)
#define CLR_TMS() CLEARPIN(PORTD, PD4)

/** JTAG Clock Control PD5 */
#define SET_TCK() SETPIN (PORTD, PD5)
#define CLR_TCK() CLEARPIN (PORTD, PD5)


/** ISP  */

//#define	ISP_OUT   PORTB
//#define ISP_IN    PINB
//#define ISP_DDR   DDRB
//#define ISP_RST   PB2
//#define MOSI  PB3
//#define ISP_MISO  PB4
//#define ISP_SCK   PB5

#define SET_RST() SETPIN(PORTB, PB2)
#define CLR_RST() CLEARPIN(PORTB, PB2)

#define SET_SCK() SETPIN(PORTB, PB5)
#define CLR_SCK() CLEARPIN(PORTB, PB5)

#define SET_MOSI() SETPIN(PORTB, PB3)
#define CLR_MOSI() CLEARPIN(PORTB, PB3)

#define GET_MISO() ((PINB & PIN(PB4)) >> PB4)

/**Disable the SPI hardware */
#define spiHWdisable() SPCR &= ~(1<<SPE)

/** Enable the SPI hardware */
#define spiHWenable() SPCR |= (1<<SPE)



/** STATE MACHINE JTAG */
//#define JTAG_PORT_INIT		DDRD
//#define JTAG_PORT_WRITE		PORTD
//#define JTAG_PORT_READ		PIND
//#define	TCK			5
//#define TMS			4
//#define TDI			6
//#define TDO			7
//#define SET_TMS()		SETPIN(JTAG_PORT_WRITE, TMS)
//#define CLR_TMS()		CLEARPIN(JTAG_PORT_WRITE, TMS)
//#define SET_TDI()		SETPIN(JTAG_PORT_WRITE, TDI)
//#define CLR_TDI()		CLEARPIN(JTAG_PORT_WRITE, TDI)
//#define SET_TCK()		SETPIN(JTAG_PORT_WRITE, TCK)
//#define CLR_TCK()		CLEARPIN(JTAG_PORT_WRITE, TCK)
//#define GET_TDO()   	(JTAG_PORT_READ & PIN(TDO))


#define INDICATOR_LED_ON() CLEARPIN(PORTC, PC0)
#define INDICATOR_LED_OFF() SETPIN(PORTC, PC0)

/** Enable jtag output */
#define JTAG_OUTPUT_ON()		CLEARPIN(PORTC, PC1)

/** Disable jtag output */
#define JTAG_OUTPUT_OFF()		SETPIN(PORTC, PC1)

/** Enable/Disable SPI interface */
#define SPI_OUTPUT_ON() 	{ CLEARPIN(PORTC, PC3); CLEARPIN(PORTC, PC1); }
#define SPI_OUTPUT_OFF()	{ SETPIN  (PORTC, PC3); SETPIN  (PORTC, PC1); }

/** Set all programming ports to input (off) */
void DisableProgramming();

void EnableSPI();

void EnableJTAG();






/*! \brief Set TMS high and toggle TCK. */
#define SET_TMS_TCK()   { SET_TMS(); CLR_TCK(); SET_TCK(); }

/*! \brief Set TMS low and toggle TCK. */
#define CLR_TMS_TCK()   { CLR_TMS(); CLR_TCK(); SET_TCK(); }




#endif

