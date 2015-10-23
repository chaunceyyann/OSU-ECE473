//heartint.c
//setup TCNT1 in pwm mode, TCNT3 in normal mode 
//set OC1A (PB5) as pwm output 
//pwm frequency:  (16,000,000)/(1 * (61440 + 1)) = 260hz
//
//Timer TCNT3 is set to interrupt the processor at a rate of 30 times a second.
//When the interrupt occurs, the ISR for TCNTR3 changes the duty cycle of timer 
//TCNT1 to affect the brightness of the LED connected to pin PORTB bit 5.
//
//to download: 
//wget http://www.ece.orst.edu/~traylor/ece473/inclass_exercises/timers_and_counters/heartint_skeleton.c
//

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define TRUE  1
#define FALSE 0

//Traverse the array up then down with control statements or double the size of
//the array and make the control easier.  Values from 0x0100 thru 0xEF00 work 
//well for setting the brightness level.

uint16_t brightness[10] = { 0x0100,0x1600,0x2B00,0x4000,0x5500,0x6A00,0x7F00,0x9400,0xA900,0xBE00} ;

ISR(TIMER3_OVF_vect) {
	static uint8_t timer_tick=0, status=0, i=0;

	timer_tick++;
	if (timer_tick == 10 ) {
		timer_tick = 0;
		status = 1 - status;
	}
	switch(status){
		case 0:
			OCR1A = brightness[timer_tick];
			break;
		case 1:
			OCR1A = brightness[9-timer_tick];
			break;
	}
}


int main() {
	DDRB = 0xff;                           //set port B bit five to output
	//setup timer counter 1 as the pwm source

	TCCR1A |= (1<<COM1A1) | (1<<COM1A0) | (1<<WGM11);//fast pwm, set on match, clear@bottom, 
	//(inverting mode) ICR1 holds TOP

	TCCR1B |= (1<<WGM13) | (1<< WGM12) | (1<<CS10);//use ICR1 as source for TOP, use clk/1

	TCCR1C = 0x00;                            //no forced compare 

	ICR1 = 0xF000;                            //clear at 0xF000                               

	
	//setup timer counter 3 as the interrupt source, 30 interrupts/sec
	// (16,000,000)/(8 * 2^16) = 30 cycles/sec
	
	TCCR3A = 0x00;                            //normal mode

	TCCR3B = (1<<CS31);                             //use clk/8  (15hz)  

	TCCR3C = 0x00;                            //no forced compare 

	ETIMSK = (1<<TOIE3);                         //enable timer 3 interrupt on TOV

	sei();                                //set GIE to enable interrupts
	while(1) { } //do forever

}  // main
