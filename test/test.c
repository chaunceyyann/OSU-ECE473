#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCDDriver.h"
#include "kellen_music.c"
#include "lm73_functions.h"
#include "twi_master.h"
#include "uart_functions.c"

#define MAX_CHECKS 12           // # of checks before a switch is debounced
#define BASE 10                 // the base of the clock should be working
#define ALARM_LEN 32            // seconds of alarm going to be play
#define SNOOZE_LEN 10           // seconds of snooze going to be wait

//In any bus mode, before sending a command or reading
//a response, the user must first read the status byte to
//ensure that the device is ready (CTS bit is high).

static uint16_t gc = 0;
uint8_t mode_step = 1;
uint8_t mode = 1;
uint8_t debounced_state = 0; // Debounced state of the switches
uint8_t old_deState = 0;     // old Debounced state of the switches
uint8_t release = 1;
uint8_t state[MAX_CHECKS]; // Array that maintains bounce status
uint8_t id = 0; // Pointer into State
enum states {INIT};
char * str;
int dec_to_7seg[18] = {0b11000000, 0b11111001, 0b10100100, 0b10110000, // 0 1 2 3
		       0b10011001, 0b10010010, 0b10000010, 0b11111000, // 4 5 6 7
		       0b10000000, 0b10011000, 0b10001000, 0b10000011, // 8 9 A B
		       0b11000110, 0b10100001, 0b10000110, 0b10001110, // C D E F
		       0b10000011, 0b1000100}; // ^ :

//holds data to be sent to the segments. logic zero turns segment on
int segment_data[5] = {0b11000000, 0xff, 0xff, 0xff, 0xff}; // turn off led not needed.


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
}

/***********************************************************************/
//                            spi input and output
//Initalizes the SPI port on the mega128. Does not do any further
//external device specific initalizations.  Sets up SPI to be:
//master mode, clock=clk/2, cycle half phase, low polarity, MSB first
//interrupts disabled, poll SPIF bit in SPSR to check xmit completion
/***********************************************************************/
void spi_init(void){
    DDRB  |= 0x07;                            // Turn on SS, MOSI, SCLK for output
    // Turn on bit 3 SER_out for input
    DDRE  |= 0xff;                            // Turn on CLK_INH, SH/LD for output

    SPCR  |= ( 1 << SPE ) | ( 1 << MSTR );    // Set up SPI mode
    SPSR  |= ( 1 << SPI2X );                  // Double speed operation
}

void bar_print(uint8_t led_num){
    SPDR = led_num;                           // print to bar graph
    while (bit_is_clear(SPSR,SPIF));          // wait for the data to be sent out
    PORTB |= 0x01;                            // strobe output data reg in HC595 - rising edge
    PORTB &= 0xFE;                            // Falling edge
}

void read_encoder(uint8_t miso){
    static uint8_t old_miso;

    // Pulse the HC165 with SH/LD 0 for load the data from knod then keep it high for serial sent back
    PORTE ^= (1<<7);                          // SH/LD = 0 CLK_INH = 0 
    PORTE = 0b10000000;                       // SH/LD = 1 CLK_INH = 0

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
                    gc+=mode_step;
                    break;
                case 0x01:
                    gc-=mode_step;
                    break;
            }
        }
    }
    old_miso = miso;

}
//***********************************************************************************
//                             TCNT initial    
//
//***********************************************************************************
void tcnt0_init(void){                                      // real time clock
    //timer counter 0 setup, running off i/o clock
    TIMSK |= ( 1<<TOIE0 );                                  //enable interrupts
    TCCR0 |= ( 1<<CS00 ) | (1<<CS02);                       //normal mode, prescale by 128
}

// timer1 init --->>> music_init in kellen_music.c

void tcnt2_init(void){                                      // dimming
    //timer counter 2 setup, running off i/o clock
    TCCR2 |= ( 1<<CS20 );                                   //normal mode, no prescale 
    TCCR2 |= ( 1<<WGM20 ) | (1<<WGM21);                     //fast pwm mode
    TCCR2 |= ( 1<<COM20 ) | (1<<COM21);                     //Set OC2 on compare match
    TCCR2 &= ~( 1<<FOC2 );                                  //no forced compare 
    OCR2  = 0x00;                                           //initial the compare
}
void tcnt3_init(void){                                      // audio volume pwm
    //timer counter 3 setup, running off i/o clock
    TCCR3A |= ( 1<<COM3A1 ) | ( 1<<COM3A0 ) | ( 1<<WGM31 ); //fast pwm, set on match.
    TCCR3B |= ( 1<<CS30 ) | ( 1<<WGM32 ) | ( 1<<WGM33 );    //ICR3 for TOP, no prescale
    ICR3 = 0x0064;
}


//***********************************************************************************
//                             ISR for the timer
//
//***********************************************************************************
ISR(TIMER0_OVF_vect){
    // 16m/128 = 125khz
    // 1/125k * 256 = 2.048ms
    // 1/125k * 256 * 488 = 1s

    static uint16_t count_2ms = 0;
    count_2ms++;                                // increment count every 2.048ms

    // reduce the bar graph brightness
    //bar_print(0);   

    // Encoder and bar graph
    if (count_2ms % 2 == 0){
        //SPI MOSI to bar graph display
        bar_print(mode);

        // SPI MISO from Encoder 
        read_encoder(SPDR);

    }
    if (count_2ms == 0xff) count_2ms = 0x00;
}

int main(){
	// run time initial 
	int counter = 0;

	//set port bits 4-7 B as outputs
	DDRB = 0xf0; // output
    DDRD = 0xff;
	DDRF = 0xff; // output
	PORTF = 0x00;
	
	// SPI interupt initial
	spi_init();

	LCD_Init();
	LCD_Clr();
	LCD_CursorBlinkOff();
	LCD_PutStr("Welcome to Alarm!!!");
	LCD_MovCursorLn2();
	//LCD_PutDec16(temp);

	tcnt0_init();
	sei();
	// main while loop
	while(1){
  	_delay_ms(2);				        // insert loop delay for debounce

	PORTA = 0xff;
  	DDRA = 0x00;				        // make PORTA an input with pullups

  	PORTB |= 0b01110000;			        // enable tristate buffer for pushbutton switches

  	_delay_ms(1);				       	// make sure button get the time to react

	// Debounceing buttons
	DebounceSwitch();				// now check each button and increment the count as needed
	if (old_deState & debounced_state)
		release = 0;
	else 
		release = 1;
	old_deState = debounced_state;
	if (debounced_state && (release == 1)){ 	// change the mode according to the button pushed
		release = 0;
		mode = debounced_state ^ mode; 		// store the mode  
		debounced_state = 0;			// reset debouced_state
	}

	switch (mode){
		case 1:
                       mode_step = 1;
		       break;
		case 2:
		       mode_step = 2;
		       break;
		case 4:
		       mode_step = 4;
		       break;
		default :
		       mode_step = 0;
	}

	// display the global counter
	if (gc==1024)gc++;
	gc=gc%1024;					// roll over 
	segsum(gc);					// display on 7 seg

	// select the digit to display and select the input from decoder
	DDRA = 0xff;					//make PORTA an output

	//bound a counter (0-4) to keep track of digit to display
	for (counter = 0; counter < 5; counter++){
		PORTB = counter << 4;			//send PORTB the digit to display
		PORTA = segment_data[counter];		//send 7 segment code to LED segments

  		//fix for the last digit over bright issue
		if (counter != 4)
			_delay_ms(2);

	}
  }//while
}//main
