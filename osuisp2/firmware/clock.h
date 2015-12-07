/**
 @file clock.h
 @author Thomas Fischl <tfischl@gmx.de>
 @author Ben Porter
 @brief Header file for timing functions
 
 License: GNU GPL v2
 @date 7-3-2010
*/

#ifndef _CLOCK_H
#define	_CLOCK_H

/** Timer1 will operate with a 64 prescaler */
#define TIMER1 TCNT0

/** Timer2 will operate with a 1 prescaler */
#define TIMER2 TCNT2

/** Number of Timer1 ticks to equal 320 micro seconds */
#define CLOCK_T_320us 60

/** Slow clock operates at 12Mhz/64 (5.33 uS per tick) */
#define slowClockInit() (TCCR0B = (1 << CS01) | (1 << CS00))

/** Fast clock operates at 12Mhz (83.33 nS per tick) */
#define fastClockInit() (TCCR2B = (1 << CS20))

/** Init both the slow and fast clock */
#define clockInit() {slowClockInit(); fastClockInit();}

/** Wait for 320 uS multiplied by time
 * This delay is fairly accurate
 * @param time number of 320uS periods to wait
 */
void clockWait(uint8_t time);

/** Wait for a multiple of 10 uS
 * @param number of delays
 */
void ten_us_delay(uint8_t time);

/** Wait for a multiple of 83.33 nS 
 * NOTE: short delays are more inaccurate
 * since the relative overhead is increased
 * @param time number of 83.33ns periods to wait 
 */
void short_delay(uint8_t time);

#endif
