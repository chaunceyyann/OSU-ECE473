// lab4.c 
// Chauncey Yan
// Fall2015

// Wire layout
// 	    7Seg			    Mega128 Board
// --------------        ------------------
//     pulldown		 PORTA bit 0-7
//     sel0              PORTB bit 4
//     sel1              PORTB bit 5
//     sel2              PORTB bit 6
//     EN                PORTB bit VCC
//     EN_N              PORTB bit Gnd
//     PWM               PORTB bit 7
//     DEC7              COM_EN --> Pushbutton
//
// Pushbutton board         Mega128 board
// ----------------      ------------------
//     COM_EN            DEC7 --> 7Seg
//     COM_LVL           PORTE bit 4
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
//     SH/LD             PORTE bit 7 (high)
//     SCK               PORTB bit 1 (sclk) 
//     CKINH             PORTE bit 6 (gnd)
//     SOUT/SER_OUT      PORTB bit 3 (miso)
//     SIN/SER_IN      	 Not connected
//
//   AMP board           Mega128 board
// --------------        ------------------
// Alarm tone out        PORTD bit 7 (yellow)
// Volume control        PORTE bit 3 (green)
//
//   	ADC              Mega128 board
// --------------        ------------------
// analog data in        PORTF bit 0

// Push button assignment
// --- --- --- --- --- --- --- ---
// |7| |6| |5| |4| |3| |2| |1| |0|
// --- --- --- --- --- --- --- ---
// |0| -> change volume
// |1| -> toggle increments between 1 and 60 mins
// |2| -> set current time 
// |3| -> set alarm time (double push unset) 
// |4| -> toggle alarm 
// |5| -> toggle 12 / 24 hour mode
// |6| -> snooze mode
// |7| -> confirmation


// Encoder assignment
// left encoder for tune up the volume for alarm clock and radio
// right encoder for set time set alarm

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "LCDDriver.h"
#include "kellen_music.c"

#define MAX_CHECKS 12 				// # checks before a switch is debounced
#define BASE 10  					// the base of the clock should be working
#define ALARM_LEN 16  				// seconds of alarm going to be play
#define SNOOZE_LEN 10  				// seconds of snooze going to be wait

signed int gc = 0;					// globle counter
signed int lec = 0;					// left encoder counter
signed int old_lec = 0;				// old left encoder counter
signed int rec = 0;					// right encoder counter
signed int vc = 20;					// volume counter
signed int old_vc = 1;				// volume counter old value
unsigned int rts = 0; 				// global time counter seconds
unsigned int rtc = 1440; 			// global time counter mins 
signed int rtc_t = 0;				// temporary rtc for set time mins
unsigned int atc = 1500;			// alarm mins 
signed int atc_t;			 		// temporary atc for set alarm mins
unsigned int hours = 0; 			// display Hours
unsigned int hours_24 = 0; 			// display 24 Hours
unsigned int ahours = 0; 			// alarm Hours 24 hours
unsigned int mins = 0;				// display mins
unsigned int amins = 60;			// alarm mins
uint8_t alarm_start = 60;			// alarm start time
uint8_t snooze_start = 0;			// alarm snooze start time
uint8_t sn = 0;						// 0 - Beavs fight sone 1 - Tetris 
// 2 - Mario 3 - Unknown
uint8_t mode_t = 0;					// toggle mode switch
uint8_t mode = 1;					// mode flags
uint8_t inc = 1;					// increament to seperate min and hour 
uint8_t barcode = 0;				// data print on the bar 
uint8_t debounced_state = 0; 		// Debounced state of the switches
uint8_t state[MAX_CHECKS]; 			// Array that maintains bounce status
uint8_t id = 0; 					// Pointer into State
signed int adcd = 0;				// ADC data
uint16_t temp = 32;					// temporature value
int encoder_data[4] = {0x00, 0x01, 0x03, 0x02};	// reorder encoder data
char alarm_buf[32] = "Go Beavs! OSU Fight Fight Fight!";
char buf[16];						// genaral purpose buffer

//decimal to 7-segment LED display encodings, logic "0" turns on segment
int dec_to_7seg[18] = {0b11000000, 0b11111001, 0b10100100, 0b10110000, // 0 1 2 3
				       0b10011001, 0b10010010, 0b10000010, 0b11111000, // 4 5 6 7
					   0b10000000, 0b10011000, 0b10001000, 0b10000011, // 8 9 A B
 					   0b11000110, 0b10100001, 0b10000110, 0b10001110, // C D E F
					   0b10000011, 0b1000100}; 						   // ^ :

//holds data to be sent to the segments. logic zero turns segment on
int segment_data[5] = {0xff, 0xff, 0xff, 0xff, 0xff}; 	// turn off led not needed.


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
			segment_data[2] = 0xff; //dec_to_7seg[17];
			segment_data[3] = dec_to_7seg[sum/100%10];
			segment_data[4] = dec_to_7seg[sum/1000%10];
			break;
		case 16:
			breakDgt(sum,4,0x000f);	//check last 4
			break;
		case 8:
			breakDgt(sum,3,0x0007);	// check last 3
			break;
		case 2:
			breakDgt(sum,1,0x0001);	// check last 1
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
}

//***********************************************************************************
// 									clock
//
//***********************************************************************************
void hmclock(unsigned int tc){							// hour and mins from mins count
	mins = tc % 60;                                     // 
	hours_24 = tc / 60 % 24;							// 24 hours
	hours = tc / 60 % 12;								// 12 hours
}

void clock_dis(){
	segment_data[0] = dec_to_7seg[mins%BASE];			// 1st digit
	segment_data[1] = dec_to_7seg[mins/BASE];			// 2ed digit
	if (mode & (1<<4)){	 		   						// 24 hours mode
		segment_data[3] = dec_to_7seg[hours_24%BASE];	
		segment_data[4] = dec_to_7seg[hours_24/BASE];
	} else {											// 12 hours mode
		segment_data[3] = dec_to_7seg[hours%BASE];
		segment_data[4] = dec_to_7seg[hours/BASE];
	}
}


void alarm_check(){										// run once pre second
	uint8_t i;
	if ((alarm_start == 60) && (mode & (1<<3))){		// initial value, use this to exe music once
		hmclock(rtc);									// update real time clock value hours and mins
		if ((ahours == hours_24) && (amins == mins)){	// use hours_24 for am pm
			music_on();									// alarm tone on
			LCD_Clr();
			if ( song == 0)
				LCD_PutStr(alarm_buf);					// print Fight sone
			else if (song == 1)
				LCD_PutStr("Tetris Theme");				// print Tetris
			else if (song == 2)
				LCD_PutStr("Mario Theme");				// print Mario
			else if (song == 3)
				LCD_PutStr("Unknow");					// print Unknow
			alarm_start = rts;							// set start second for alarm tone
		}
	}
	if ((rts - alarm_start) >= ALARM_LEN) { 			// 1-58s for the alarm tone
		music_off();									// alarm tone off
		LCD_Clr();
		LCD_PutStr("Alarm off!");
		alarm_start = 61;								// avoiding rerun this music_off and music_on
	} 
	if (((rts-alarm_start)<ALARM_LEN)&&(song==0)) {		// roll over buffer chars
		LCD_Clr();
		for (i=0;i<16;i++){								// give 16 chars to buf
			buf[i] = alarm_buf[i+(rts-alarm_start)];
		}
		LCD_PutStr(buf);
	}
	if (rts == 59){									    // last second in this min
		alarm_start = 60;								// reset alarm
	}
}

void snooze_func(){
	if ((alarm_start != 61) && (alarm_start !=60)) {	// alarm is on
		if ((mode & (1<<6)) && (snooze_start == 0)) {	// first time snooze is trigered
			music_off();								// turn off the music
			LCD_Clr();
			LCD_PutStr("Snooze mode 10s");				// print snooze
			snooze_start = rts;							// start count 10 second
			alarm_start = 61;							// stop alarm tone end check
		}
	}
	if ((rts - snooze_start) == SNOOZE_LEN) {			// out of snooze mode
		alarm_start = 60;								// resume music. 
		// Not working for long snoozing 
		song++;
		if (song == 4) song = 0;						// roll back for the fisrt song
		snooze_start = 0;								// reset snooze function
	}
}

/***********************************************************************/
//                            lcd functions
// Alarm print out                           
/***********************************************************************/
void lcd_alarm(){
	LCD_Clr();
	if (mode & (1<<3)){							// check if alarm is set
		LCD_PutStr("Alarm set ");
		itoa(ahours,buf,10);
		LCD_PutStr(buf);
		LCD_PutStr(":");
		itoa(amins,buf,10);
		LCD_PutStr(buf);
	} else										// not set
		LCD_PutStr("Alarm: Not set");
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

	// Pulse the HC165 with SH/LD 0 for load the data from knod then keep it high for serial sent back
	PORTE ^= (1<<7); 			      		// SH/LD = 0 CLK_INH = 0 
	PORTE |= 0b10000000; 			     	// SH/LD = 1 CLK_INH = 0

	if (old_miso != miso){
		if ((old_miso & 0x03) == 0x03){
			switch(miso&0x03){
				case 0x02:
					lec+=inc;
					break;
				case 0x01:
					lec-=inc;
					break;
			}
		}
		if ((old_miso & 0x0C) == 0x0C){
			switch((miso&0x0C)>>2){
				case 0x02:
					rec+=inc;
					break;
				case 0x01:
					rec-=inc;
					break;
			}
		}
	}
	old_miso = miso;

}
//***********************************************************************************
// 							ADC and dimmer
//
//***********************************************************************************

void ADC_init (void){
	PORTF = 0x00;
	DDRF  &= ~(1<<0);
	ADCSR |= (1 << ADFR);  		// Set ADC to Free-Running Mode
	ADCSR |= (1 << ADPS2); 		// Set ADC prescaler to 16 - 500KHz
	//ADCSR |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 
	// Set ADC prescaler to 128 - 125KHz sample rate @ 16MHz

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
	if (adcd < 1)			   	// no negative
		adcd = 1;	
	else if (adcd > 255)	   	// no too bright value
		adcd = 255;
	OCR2 = adcd;			   	// create the TCNT 2 PWM

}

//***********************************************************************************
// 							TCNT initial	
//
//***********************************************************************************
void tcnt0_init(void){								// real time clock
	//timer counter 0 setup, running off i/o clock
	TIMSK |= ( 1<<TOIE0 );             				// enable interrupts
	TCCR0 |= ( 1<<CS00 ) | (1<<CS02);  				// normal mode, prescale by 128
}

// timer1 init --->>> music_init in kellen_music.c

void tcnt2_init(void){								// LCD dimming fast PWM
	//timer counter 2 setup, running off i/o clock
	TCCR2 |= ( 1<<CS20 );  							// no prescale 
	TCCR2 |= ( 1<<WGM20 ) | (1<<WGM21);	  			// fast pwm mode
	TCCR2 |= ( 1<<COM20 ) | (1<<COM21);				// Set OC2 on compare match
	TCCR2 &= ~( 1<<FOC2 );  						// no forced compare 
	OCR2  = 0x00;									// initial the compare
}
void tcnt3_init(void){								// audio volume pwm
	//timer counter 3 setup, running off i/o clock
	TCCR3A |= ( 1<<COM3A1 ) | ( 1<<COM3A0 ) | ( 1<<WGM31 );	// fast pwm, set on match.
	TCCR3B |= ( 1<<CS30 ) | ( 1<<WGM32 ) | ( 1<<WGM33 );  	// ICR3 for TOP, no prescale
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

	bar_print(0);								// reduce the bar graph brightness

	// Encoder and bar graph
	if (count_2ms % 2 == 0){
		//SPI MOSI to bar graph display
		bar_print(mode);

		// SPI MISO from Encoder 
		read_encoder(SPDR);

		// set time mode
		// semicolum always light up
		if (mode & (1<<2)){						
			rtc_t = rtc + rec;					// adding right encoder value to temp real time clock
			hmclock(rtc_t);						// update hours and mins
			clock_dis();						// display the clock
			segment_data[2] = dec_to_7seg[17];	// presist the semicolumn

			// check comfirmation
			if (mode & (1<<7)){	
				rtc = rtc_t;
			}
		}

		// set alarm time
		// checking comfirmation at the last
		else if (mode & (1<<3)){
			atc_t = atc + rec;					// adding right encoder value to temo alarm time 
			hmclock(atc_t);						// update hours and mins
			clock_dis();							// display the clock
			segment_data[2] = dec_to_7seg[17];	// presist the semicolumn

			// check comfirmation
			if (mode & (1<<7)){					
				atc = atc_t;
				ahours = atc / 60 % 24;				// update alarm hour 24 
				amins = atc % 60;					// update alarm min 
				mode |= (1<<4);						// set alarm mode flag
				lcd_alarm();						// display alarm on lcd
			}
		}


		// snooze function
		snooze_func();

		// manualy clear snooze and confirm if necessary
		if ((mode & (1<<6)) && (snooze_start == 0))			// clear snooze if alarm is off
			mode &= 0b00110011;								// clear set time set alarm as well
		if (mode & (1<<7))									// clear confirm
			mode &= 0b00110011;								// clear set time set alarm as well
	}


	// real time clock
	if ((count_2ms % 488 == 0) ){					// 1s
		rts++;										// seconds ++
		if (rts == 60){
			rtc++;									// mins ++
			rts = 0;									// reset second
		}
		// check if the real time match with alarm time
		alarm_check();

		// make sure it is not in set time or set alarm mode
		if (!((mode & (1<<0)) && (mode & (1<<1)))){
			if (!((mode & (1<<3)) || (mode & (1<<2)))){
				hmclock(rtc);							// update real time clock
				clock_dis();							// display the clock

				// seconds semicolumn
				if ((rts % 2) == 0){					// flash every second
					segment_data[2] = dec_to_7seg[17];
				} else {
					segment_data[2] = 0xff;
				}
			}
		}
	}

	// adding pm dot indicator 
	// (out of real time since it should show up on all settings)
	if ((hours_24 >= 12) && !(mode & (1<<5))){	// pm and not 24 hour mode
		segment_data[2] &= dec_to_7seg[16];
	} else {										// explicitly turn off indicator 
		segment_data[2] &= ~(1<<1) | ~(1<<0);
	}

	// ararm tone speed for note duration(64th notes)
	if (count_2ms % 32 == 0){
		beat++;
	}

	if (count_2ms % 2 == 0){						// volume control
		if (((mode & (1<<0)) && (mode & (1<<1)))){	// mode 0 & 1
			if ((old_vc + lec) < 0) lec = 0-old_vc;	// set range 0 - 100
			else if ((old_vc + lec) > 50) lec = 50-old_vc; 
			vc = old_vc + lec;						// update volume counter
			segsum(vc);								// display vc
			OCR3A = 100 - vc;							// create PWM with TCNT3
			if (count_2ms % 488 == 0){				// strobe lcd in half a second
				if (old_lec != lec){
					LCD_Clr();
					LCD_PutStr("Volume: ");
					LCD_PutStr(itoa(vc,buf,10));			// lcd display volume
				}
				old_lec = lec;
			}
			if (mode_t & 0xFC){						// hit any button beside 0 1
				mode &= ~0x02;							// exit volume control mode
				LCD_Clr();
				LCD_PutStr("Volume: ");
				LCD_PutStr(itoa(vc,buf,10));			// lcd display volume
			}
		}
	}
}

//ISR timer 1 is in kellen_music.c

//***********************************************************************************
//									Toggle interpurator
// 									mode_t -> mode flags
//***********************************************************************************
void set_mode(){
	switch (mode_t){
		case 1:							// increament 1 min 
			inc = 1;
			mode &= 0b11111100;			// clear the other inc
			mode |= (1<<0);
			break;
		case 2:							// 60 mins -> 1 hour
			inc = 60;
			mode &= 0b11111100;			// clear the other inc
			mode |= (1<<1);
			break;
		case 4:							// set time
			mode &= 0b00110111;			// clear set alarm
			mode ^= (1<<2);				// toggle, for cancelling
			rec = 0;						// reset right encoder reading
			break;
		case 8:							// set alarm
			mode &= 0b00111011;			// clear set time
			mode ^= (1<<3);				// toggle, for cancelling
			if (!(mode & (1<<3)))			// unset alarm if double cancel setting
				mode &= ~(1<<4);			// unset alarm flag
			lcd_alarm();					// update lcd 
			rec = 0;						// reset right encoder reading
			break;
		case 16:						// alarm indicator, button broke
			break;						
		case 32:						// 24 - 12 indicator
			mode ^= (1<<5);				// toggle
			break;
		case 64:						// snooze function indicator
			mode |= (1<<6);				// clear manually in timer 0
			break;
		case 128:						// confirm
			mode |= (1<<7);				// clear manually in timer 0
			break;
		default:						// multiple button input detected
			mode &= 0b00110011;			// clear set time set alarm
			mode |= (1<<0) | (1<<1);		// entering volume control
			lec = 0;						// reset light encoder reading
			old_vc = vc;					// save old vc value for next adding
			break;
	}
}
//***********************************************************************************
//									Main
// 
//***********************************************************************************
int main(){
	// run time initial 
	uint8_t counter = 0; 

	//set port bits 4-7 B as outputs
	DDRB = 0xf0; // output
	DDRD = 0xff; // output

	// SPI interupt initial
	spi_init();

	LCD_Init();
	LCD_Clr();
	LCD_CursorBlinkOff();
	LCD_PutStr("Teklarm2.0");
	LCD_MovCursorLn2();
	LCD_PutStr("Local: ");
	LCD_PutDec16(temp);
	LCD_PutDec16(adcd);

	// current time init
	//time_init();

	// ADC init
	ADC_init();

	// time counter init
	tcnt0_init();
	music_init(sn);
	tcnt2_init();
	tcnt3_init();

	// initial Volume mute
	OCR3A = 0x0064;

	// enable global interrupt
	sei();

	// main while loop
	while(1){
		_delay_ms(2);								// insert loop delay for debounce

		PORTA = 0xff;
		DDRA = 0x00;								// make PORTA an input with pullups

		PORTB |= 0b01110000;						// enable tristate buffer for pushbutton switches

		_delay_ms(1);								// make sure button get the time to react

		// Debounceing buttons
		DebounceSwitch();							// now check each button
		if (debounced_state){ 						// check if any inputs
			if (mode_t != debounced_state){			// make sure no duplicate input
				mode_t = debounced_state;			// toggle switch
				set_mode();							// decode button input
				debounced_state = 0;				// reset debouced_state
			}

		} else mode_t = 0;							// no toggle input


		// testing 
		//segsum(mode);								// display on 7 seg

		// select the digit to display and select the input from decoder
		DDRA = 0xff;								// make PORTA an output

		//bound a counter (0-4) to keep track of digit to display
		for (counter = 0; counter < 5; counter++){
			PORTB = counter << 4;					// send PORTB the digit to display
			PORTA = segment_data[counter];			// send 7 segment code to LED segments

			//fix for the last digit over bright issue
			if (counter != 4)
				_delay_ms(2);

		}
	}//while
}//main
