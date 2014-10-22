// lab2_skel.c 
// R. Traylor
// 9.12.08

//  HARDWARE SETUP:
//  PORTA is connected to the segments of the LED display. and to the pushbuttons.
//  PORTA.0 corresponds to segment a, PORTA.1 corresponds to segement b, etc.
//  PORTB bits 4-6 go to a,b,c inputs of the 74HC138.
//  PORTB bit 7 goes to the PWM transistor base.

#define F_CPU 16000000 // cpu speed in hertz 
#define TRUE 1
#define FALSE 0
#include <avr/io.h>
#include <util/delay.h>



#define Y7 0b01110000
#define DC 0b10001111

uint8_t digit_data[5] = {
	0b00000000,//0
	0b00010000,//1
	0b00100000,//:
	0b00110000,//2
	0b01000000 //3
};


//holds data to be sent to the segments. logic zero turns segment on
uint8_t segment_data[5] = { 
		0b11000000, 
		0b11111001, 
		0b10100100, //0 1 2
		0b10110000, 
		0b10110000, 
};

//decimal to 7-segment LED display encodings, logic "0" turns on segment
uint8_t dec_to_7seg[12] = {
		0b11000000, 
		0b11111001, 
		0b10100100, //0 1 2
		0b10110000, 
		0b10011001, 
		0b10010010, 
		0b10000010, // 3 4 5 6
		0b11111000, 
		0b10000000, 
		0b10011000 
}; // 7 8 9

int8_t debounce_switch() {
		static uint16_t state = 0; //holds present state
			state = (state << 1) | (! bit_is_clear(PINA, 0)) | 0xE000;
				if (state == 0xF000)
							return 1;
					return 0;
}
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
}//******************************************************************************

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
uint8_t main()
{
int i, count = 4;
//set port bits 4-7 B as outputs
DDRB = 0xf0;
DDRC = 0xff;
PORTC = 0x00;
PORTB = 0x00;
DDRA = 0xff;

while(1){
	//  for(i=0;i<10000;i++)
	//	  segsum(count);//insert loop delay for debounce
	DDRA = 0x00;
	PINA = 0xff;//make PORTA an input port with pullups 
	PORTB |= Y7;//enable tristate buffer for pushbutton switches
	_delay_ms(2);	
	if(debounce_switch()){
			count++;	
			count = count % 10; //1023; //bound the count to 0 - 1023
		}	

	//for(i=0;i<8;i++)
	//  chk_button(i)//now check each button and increment the count as needed
	//segsum(count);//break up the disp_value to 4, BCD digits in the array: call (segsum)
	for(i=4;i>=0;i--){//bound a counter (0-4) to keep track of digit to display 
		DDRA = 0xff;//make PORTA an output
		PORTA = segment_data[count];//send 7 segment code to LED segments
		PORTB &= DC;
		PORTB |= digit_data[i];//update digit to display
		_delay_ms(2);
	}
}//while
return 0;
}//main
