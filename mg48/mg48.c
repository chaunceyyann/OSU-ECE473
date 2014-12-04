#include <avr/io.h>
#include <util/delay.h>
#include "lm73_functions.h"
#include "twi_master.h"

uint8_t lm73_wr_buf[2];
uint8_t lm73_rd_buf[2];
char remote_temp_buf[16];
char remote_temp_buf2[16] = {1,0,1,0,1,1,1,0};



void remoteTemp () {
  uint16_t lm73_temp;
  twi_start_rd(LM73_ADDRESS,lm73_rd_buf,2); //read temperature data from LM73 (2 bytes)  (twi_mas        ter.h)
  _delay_ms(2);    //wait for it to finish
  lm73_temp = lm73_rd_buf[0];//save high temperature byte into lm73_temp
  lm73_temp = lm73_temp << 8; //shift it into upper byte
  lm73_temp |= lm73_rd_buf[1]; //"OR" in the low temp byte to lm73_temp
  lm73_temp = (lm73_temp >> 5);
  lm73_temp ^= (1 << 6);
  itoa((int)lm73_temp,remote_temp_buf,2); //convert to string in array with itoa() from avr-libc
  //lm73_temp_convert(temp_digits,lm73_temp,0x01);
  //string2lcd(temp_digits); //send the string to LCD (lcd_functions)
}



int main(){
  int i;
  DDRD = 0xff;

  // initialize TWI
  init_twi();
  lm73_wr_buf[0] = LM73_PTR_TEMP;      //load lm73_wr_buf[0] with temperature pointer address
  twi_start_wr(LM73_ADDRESS,lm73_wr_buf,2);   //start the TWI write process (twi_master.h)
  _delay_ms(2);

  while (1){
  remoteTemp();
	for (i = 0; i < 16; i++){
	  if (remote_temp_buf[i] == 1){
		PORTD = 0xff;
		_delay_ms(10);
	  }
	  PORTD = 0x00;
	  _delay_ms(10);
	}
	_delay_ms(100);
  }
}
