// lab3.c 
// Chauncey Yan
// 11.02.14
// Lab3:
// Try another way to use push buttons as a user interface.
// Using interrupts with counter/timer 0
// Learn how to use SPI I/O.

// Wire layout
// 	    7Seg			    Mega128 Board
// --------------        ------------------
//     pulldown          PORTA bit 0-7
//	   sel0				 PORTB bit 4
//	   sel1				 PORTB bit 5
//	   sel2				 PORTB bit 6
//	   EN    			 PORTB bit VCC
//	   EN_N   			 PORTB bit Gnd
//	   PWM				 PORTB bit 7
//	   DEC7				 COM_EN --> Pushbutton
//
// Pushbutton board         Mega128 board
// ----------------      ------------------
//     COM_EN			 DEC7 --> 7Seg
//     COM_LVL			 PORTE bit 4
//
// Bargraph board           Mega128 board
// --------------        ------------------
//     reglck            PORTB bit 0 (ss_n)
//     srclk             PORTB bit 1 (sclk)
//     sdin              PORTB bit 2 (mosi)
//     oe_n              PORTE bit 5
//     sd_out            not connected
//
// Encoder board           Mega128 board
// --------------        ------------------
//     SH/LD             PORTE bit 7
//     SCK               PORTB bit 1 
//     CKINH             PORTE bit 6 
//     SOUT/SER_OUT      PORTB bit 3
//     SIN/SER_IN      	 Not connected

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <time.h>
//#include "hd44780.h"
#include "kellen_music.c"

#define MAX_CHECKS 12 				// # checks before a switch is debounced
#define BASE 10  					// the base of the clock should be working

signed int gc = 0;					// globle counter
signed int lec = 0;					// left encoder counter
signed int rec = 0;					// right encoder counter
signed int vc = 1;					// volume counter
unsigned int rtc = 0; 			// global time counter 
unsigned int hours = 0; 			// Hours
unsigned int mins = 0;				// mins
uint8_t mode_step = 1;				// mode adder 
uint8_t debounced_state = 0; 		// Debounced state of the switches
uint8_t state[MAX_CHECKS]; 			// Array that maintains bounce status
uint8_t id = 0; 					// Pointer into State
signed int adcd = 0;					// ADC data
int encoder_data[4] = {0x00, 0x01, 0x03, 0x02};
uint16_t britness_s = 0x0100;
uint16_t britness_e = 0xBE00;

//decimal to 7-segment LED display encodings, logic "0" turns on segment
int dec_to_7seg[18] = {0b11000000, 0b11111001, 0b10100100, 0b10110000, // 0 1 2 3
					   0b10011001, 0b10010010, 0b10000010, 0b11111000, // 4 5 6 7
					   0b10000000, 0b10011000, 0b10001000, 0b10000011, // 8 9 A B
					   0b11000110, 0b10100001, 0b10000110, 0b10001110, // C D E F
					   0b10000011, 0b1000100}; 						   // ^ :

//holds data to be sent to the segments. logic zero turns segment on
int segment_data[5] = {0b11000000, 0xff, 0xff, 0xff, 0xff}; 	// turn off led not needed.


//*********************************************************************************
//                            chk_buttons
// Debounce the all 8 bit switchs at the same time by checking PINA input 
//*********************************************************************************

void DebounceSwitch(){
	uint8_t i,j;
	state[id++]=0xff - PINA;
    j=0xff;
    for(i=0; i<MAX_CHECKS-1;i++)j=j & state[i];
	debounced_state = j;
    if(id >= MAX_CHECKS)id=0;
}


//**********************************************************************************
//                                   7 seg display
//takes a 16-bit binary input value and places the appropriate equivalent 4 digit
//BCD segment code in the array segment_data for display.
//array is loaded at exit as:  |digit3|digit2|colon|digit1|digit0|
//**********************************************************************************

void breakDgt(uint16_t sum, int base_count, uint16_t check_bit) {
	uint16_t dgt;
	int o;
	for (o = 0; o < 4; o++){
		dgt = (sum >> (o * base_count)) & check_bit;
		segment_data[o] = dec_to_7seg[dgt];
	}
}

void segsum(uint16_t sum) {
	int u = 4;

  	//break up decimal sum into 4 digit-segments
	switch (BASE) {
	case 10:
		//breakDgt(sum,10);
		segment_data[0] = dec_to_7seg[sum%10];
		segment_data[1] = dec_to_7seg[sum/10%10];
		segment_data[2] = dec_to_7seg[sum/100%10];
		segment_data[3] = dec_to_7seg[sum/1000%10];
		break;
	case 16:
		breakDgt(sum,4,0x000f);
		break;
	case 8:
		breakDgt(sum,3,0x0007);
		break;
	case 2:
		breakDgt(sum,1,0x0001);
		break;
	}
  	//blank out leading zero digits
	while (segment_data[u] == dec_to_7seg[0] || segment_data[u] == 0xff) {
		segment_data[u--] = 0xff;
		if ( u == -1) {
			segment_data[0] = dec_to_7seg[0];
			break;
		}
	}
  	//now move data to right place for misplaced colon position
	segment_data[4] = segment_data[3];
	segment_data[3] = segment_data[2];
	segment_data[2] = 0xff; //dec_to_7seg[17];
}

//***********************************************************************************
// 									clock
//
//***********************************************************************************
void time_init(void){
	time_t timer;
 	struct tm y2k;
 	double seconds;

  	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
 	y2k.tm_year = 114; y2k.tm_mon = 11; y2k.tm_mday = 1;

  	time(&timer);  /* get current time; same as: timer = time(NULL)  */

  	seconds = difftime(timer,mktime(&y2k));
	segsum(seconds);
}
void aclock_dis(unsigned int tc){

	mins = (tc / 60) % 60;

	hours = tc / 3600 % 24;

	segment_data[0] = dec_to_7seg[mins%BASE];
	segment_data[1] = dec_to_7seg[mins/BASE];
	segment_data[3] = dec_to_7seg[hours%BASE];
	segment_data[4] = dec_to_7seg[hours/BASE];

	if ((tc % 2) == 0){
		segment_data[2] = dec_to_7seg[17];
	} else {
		segment_data[2] = 0xff;
	}
}


/***********************************************************************/
//                            spi input and output
//Initalizes the SPI port on the mega128. Does not do any further
//external device specific initalizations.  Sets up SPI to be:
//master mode, clock=clk/2, cycle half phase, low polarity, MSB first
//interrupts disabled, poll SPIF bit in SPSR to check xmit completion
/***********************************************************************/
void spi_init(void){
  	DDRB  |= 0x07;         					  	// Turn on SS, MOSI, SCLK for output
												// Turn on bit 3 SER_out for input
  	DDRE  |= 0xff;        					  	// Turn on CLK_INH, SH/LD for output

	SPCR  |= ( 1 << SPE ) | ( 1 << MSTR );		// Set up SPI mode
  	SPSR  |= ( 1 << SPI2X );              		// Double speed operation
 }

void bar_print(uint8_t led_num){
	SPDR = led_num;								// print to bar graph
	while (bit_is_clear(SPSR,SPIF));			// wait for the data to be sent out
	PORTB |= 0x01;								// strobe output data reg in HC595 - rising edge
	PORTB &= 0xFE;								// Falling edge
}

void read_encoder(uint8_t miso){
	static uint8_t old_miso;
	static int s = 0;

	// Pulse the HC165 with SH/LD 0 for load the data from knod then keep it high for serial sent back
	PORTE ^= (1<<7); 						// SH/LD = 0 CLK_INH = 0 
  	PORTE = 0b10000000; 					// SH/LD = 1 CLK_INH = 0

	switch (s) {
		case 0:
			if ( encoder_data[(miso & 0x03)] - encoder_data[(old_miso & 0x03)] == -1) lec-=mode_step; 	
			if ( encoder_data[(miso & 0x03)] - encoder_data[(old_miso & 0x03)] == 1) lec+=mode_step; 	
			s = 1;
			break;
		case 1:
			if ( encoder_data[((miso & 0x0C) >> 2)] - encoder_data[((old_miso & 0x0C) >> 2)] == -1) vc-=mode_step; 	
			if ( encoder_data[((miso & 0x0C) >> 2)] - encoder_data[((old_miso & 0x0C) >> 2)] == 1) vc+=mode_step; 	
			s = 0;
			break;
	}
	old_miso = miso;

}
//***********************************************************************************
// 							ADC and dimmer
//
//***********************************************************************************

void ADC_init (void){
	PORTF = 0x00;
	DDRF  = 0x00;
	ADCSR |= (1 << ADFR);  		// Set ADC to Free-Running Mode
	ADCSR |= (1 << ADPS2); 		// Set ADC prescaler to 16 - 500KHz
	//ADCSR |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescaler to 128 - 125KHz sample rate @ 16MHz

	ADMUX = 0; 					// Initial channel seletion
	ADMUX |= (1 << REFS0); 		// Set ADC reference to AVCC
	ADMUX |= (1 << ADLAR); 		// Left adjust ADC result to allow easy 8 bit reading

	// No MUX values needed to be changed to use ADC0

	ADCSR |= (1 << ADEN);  		// Enable ADC
	ADCSR |= (1 << ADIE);  		// Enable ADC Interrupt
	ADCSR |= (1 << ADSC);  		// Start A2D Conversions
}

ISR(ADC_vect) {					// auto dimming mode
	adcd = ADCH;
	adcd -= 50;
	if (adcd < 1)
		adcd = 1;
	else if (adcd > 200)
		adcd = 170;
	OCR2 = adcd;
}

//***********************************************************************************
// 							TCNT initial	
//
//***********************************************************************************
void tcnt0_init(void){								// real time clock
	//timer counter 0 setup, running off i/o clock
	TIMSK |= ( 1<<TOIE0 );             				//enable interrupts
	TCCR0 |= ( 1<<CS00 ) | (1<<CS02);  				//normal mode, prescale by 128
}

// timer1 init --->>> music_init in kellen_music.c

void tcnt2_init(void){							// dimming
	//timer counter 2 setup, running off i/o clock
	TCCR2 |= ( 1<<CS20 );  						//normal mode, no prescale 
	TCCR2 |= ( 1<<WGM20 ) | (1<<WGM21);  		//fast pwm mode
	TCCR2 |= ( 1<<COM20 ) | (1<<COM21);  		//Set OC2 on compare match
	TCCR2 &= ~( 1<<FOC2 );  					//no forced compare 
	OCR2  = 0x00;								//initial the compare
}
void tcnt3_init(void){							// audio volume pwm
	//timer counter 3 setup, running off i/o clock
	TCCR3A |= ( 1<<COM3A1 ) | ( 1<<COM3A0 ) | ( 1<<WGM31 );	//fast pwm, set on match.
	TCCR3B |= ( 1<<CS30 ) | ( 1<<WGM32 ) | ( 1<<WGM33 );  	//ICR3 for TOP, no prescale
	ICR3 = 0x0064;
}


//***********************************************************************************
// 							ISR for the timer
//
//***********************************************************************************
ISR(TIMER0_OVF_vect){
	// 16m/128 = 125khz
	// 1/125k * 256 = 2.048ms
	// 1/125k * 256 * 488 = 1s
	
	static uint16_t count_2ms = 0;
	count_2ms++; 								// increment count every 2.048ms

	if ( count_2ms % 256 == 0 ){
		// for note duration(64th notes)
		beat++;
	}

  	bar_print(mode_step);					// SPI MOSI to bar graph display 
	
	read_encoder(SPDR);						// SPI MISO from Encoder 
	if (vc < 0)
		vc = 0;
	if (vc > 100)
		vc = 100;

	// Volume
	OCR3A = 0x0064 - vc;

	//segsum(vc);
	if (( count_2ms % 488 ) == 0 ){				// prescale the count again by mod 
		aclock_dis(rtc++);
	}
	if ( count_2ms == 0xffff ) count_2ms = 0;  	// count_2ms to 1st positon
}

//ISR timer 1 is in kellen_music.c

//ISR(TIMER2_COMP_vect){
	// change duty cycle according to ADCH input
//	OCR2 = 2;
//}



//***********************************************************************************
//									Main
// 
//***********************************************************************************
int main(){
	// run time initial 
	uint8_t counter = 0, i;

	//set port bits 4-7 B as outputs
	DDRB = 0xf0; // output
	DDRD = 0xff; // output
	
	// current time init
	//time_init();

	// ADC init
	ADC_init();

	// SPI interupt initial
	spi_init();

	// time counter init
	tcnt0_init();
	music_init();
	tcnt2_init();
	//tcnt3_init();

	// Volume
	OCR3A = 0x0005; 	// minimum

	sei();
	
	// main while loop
	while(1){
  	_delay_ms(2);								// insert loop delay for debounce

	PORTA = 0xff;
  	DDRA = 0x00;								// make PORTA an input with pullups

  	PORTB |= 0b01110000;						// enable tristate buffer for pushbutton switches

  	_delay_ms(1);								// make sure button get the time to react
	
	// Debounceing buttons
	DebounceSwitch();							// now check each button and increment the count as needed
	if (debounced_state){ 						// change the mode according to the button pushed
		mode_step = debounced_state; 			// store the mode step 
		for (i = 0; i<8; i++){ 					// checking the additional input
			if ( debounced_state & (1 << i) ){ 	// detect where is one of the buttons
				debounced_state ^= (1 << i);	// invert that buttons input 
				break;
			}
		}
		if (debounced_state) 					// check if it still has buttons pressed
			mode_step = 0;						// set mode step as 0 if two or more buttons
		debounced_state = 0;					// reset debouced_state
	}
	if (gc == 0){
		gc = 1;
		music_on();
	}
//	switch (mode_step){
//		case 1:
//			break;
//		case 2:
//			break;
//		case 4:
//			break;
//		case 8:
//			break;
//		case 32:
//			break;
//		case 64:
//			break;
//		case 128:
//			break;
//		default:
//			break;
//	}
	// display the global counter
	//segsum(adcd);									// display on 7 seg

	// select the digit to display and select the input from decoder
	DDRA = 0xff;								//make PORTA an output

	//bound a counter (0-4) to keep track of digit to display
	for (counter = 0; counter < 5; counter++){
		PORTB = counter << 4;					//send PORTB the digit to display
		PORTA = segment_data[counter];			//send 7 segment code to LED segments

  		//fix for the last digit over bright issue
		if (counter != 4)
			_delay_ms(2);

	}
  }//while
}//main
