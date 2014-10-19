// lab2.c 
// Chauncey Yan
// 10.16.14

//  HARDWARE SETUP:
//  PORTA is connected to the segments of the LED display. and to the pushbuttons.
//  PORTA.0 corresponds to segment a, PORTA.1 corresponds to segement b, etc.
//  PORTB bits 4-6 go to a,b,c inputs of the 74HC138.
//  PORTB bit 7 goes to the PWM transistor base.

#define TRUE 1
#define FALSE 0
#include <avr/io.h>
#include <util/delay.h>
//#define F_CPU 16000000 // cpu speed in hertz 

//holds data to be sent to the segments. logic zero turns segment on
uint8_t segment_data[5]; 

//decimal to 7-segment LED display encodings, logic "0" turns on segment
//uint8_t dec_to_7seg[12] 
int dec_to_7seg[12] = {0b11000000, 0b11111001, 0b10100100, 0b10110000, // 0 1 2 3
					   0b10011001, 0b10010010, 0b10000010, 0b11111000, // 4 5 6 7
					   0b10000000, 0b10011000, 0b10000011, 0b1000100}; // 9 0 ^ :



//******************************************************************************
//                            chk_buttons                                      
//Checks the state of the button number passed to it. It shifts in ones till   
//the button is pushed. Function returns a 1 only once per debounced button    
//push so a debounce and toggle function can be implemented at the same time.  
//Adapted to check all buttons from Ganssel's "Guide to Debouncing"            
//Expects active low pushbuttons on PINA port.  Debounce time is determined by 
//external loop delay times 12. 
//
uint8_t chk_buttons(uint8_t button) {
	static uint16_t state = 0; //holds present state
	state = (state << 1) | (! bit_is_clear(PIND,0));
	if ( state == 0x8000 ) return 1;
	return 0;
}
//******************************************************************************

//***********************************************************************************
//                                   segment_sum                                    
//takes a 16-bit binary input value and places the appropriate equivalent 4 digit 
//BCD segment code in the array segment_data for display.                       
//array is loaded at exit as:  |digit3|digit2|colon|digit1|digit0|
void segsum(uint16_t sum) {
  //determine how many digits there are 
  //break up decimal sum into 4 digit-segments
  //blank out leading zero digits 
  //now move data to right place for misplaced colon position
}//segment_sum
//***********************************************************************************


//***********************************************************************************

void ledDigit (int n, int pos){
	//pos 0 1 3 4 
	if ( pos != -1 ){
		DDRA = 0xff; // output
		PORTB = pos << 4; // selet the digit
		PORTA = dec_to_7seg[n];
	}
	_delay_ms(20);
}

void ledNumber (int n, int f){ // f = format
	int digit[4],i,k;
	digit[0] = n%f;
	digit[1] = n/f%f;
	digit[2] = n/f/f%f;
	digit[3] = n/f/f/f%f;
	for (i = 0; i<4; i++){
		k=i%4;
		if (k >= 2) k++;
		ledDigit(digit[i%4],k);
	}
}

int main(){
//set port bits 4-7 B as outputs
	DDRB = 0xff; // output
	DDRA = 0x00; // input
	DDRC = 0xff; // output
	PORTC = 0x00;
	int bit = 0;
while(1){
	DDRA = 0x00; // input
	PORTB = 0b01110000;
	_delay_ms(10);
	//DDRA = 0xff;
	DDRA = 0xff;
	PORTB = 0b00010000;
	PORTA = bit_is_clear(PINA,1);
	_delay_ms(200);
	//ledDigit()
	//ledDigit(bit_is_clear(PIND,0),0);
	//ledDigit(bit_is_clear(PIND,1),1);
	//ledDigit(bit_is_clear(PIND,2),3);
	//ledDigit(bit_is_clear(PIND,3),4);
	//PORTB = 0x10;
	//if (chk_buttons(1))
	//PORTB = 0x20;
	//PORTA = dec_to_7seg[10];
	//_delay_ms(1000);
  //insert loop delay for debounce
  //make PORTA an input port with pullups 
  //enable tristate buffer for pushbutton switches
  //now check each button and increment the count as needed
  //bound the count to 0 - 1023
  //break up the disp_value to 4, BCD digits in the array: call (segsum)
  //bound a counter (0-4) to keep track of digit to display 
  //make PORTA an output
  //send 7 segment code to LED segments
  //send PORTB the digit to display
  //update digit to display
  }//while
}//main
