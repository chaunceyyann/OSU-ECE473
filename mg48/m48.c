// mega48 remote temp
// Chauncey Yan
// Fall2014

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "twi_master.h"
#include "lm73_functions.h"
#include "uart_functions.c"

#define F_CPU 8000000UL

uint8_t lm73_wr_buf[2];
uint8_t lm73_rd_buf[2];
char remote_temp_buf[2];

void remoteTemp () {
  uint16_t lm73_temp;
  twi_start_rd(LM73_ADDRESS,lm73_rd_buf,2); //read temperature data from LM73 (2 bytes)  (twi_mas        ter.h)
  _delay_ms(2);                             //wait for it to finish
  lm73_temp = lm73_rd_buf[0];               //save high temperature byte into lm73_temp
  lm73_temp = lm73_temp << 8;               //shift it into upper byte
  lm73_temp |= lm73_rd_buf[1];              //"OR" in the low temp byte to lm73_temp
  lm73_temp = (lm73_temp >> 7);				// move it to whole digits
  itoa((int)lm73_temp,remote_temp_buf,10);   //convert to string in array with itoa() from avr-libc
}


int main(){
  int i;
  // initialize TWI
  init_twi();
  lm73_wr_buf[0] = LM73_PTR_TEMP;             //load lm73_wr_buf[0] with temperature pointer address
  twi_start_wr(LM73_ADDRESS,lm73_wr_buf,1);   //start the TWI write process (twi_master.h)
  _delay_ms(2);
  
  uart_init();

  sei();

  while (1){
    remoteTemp();
	if (uart_getc() == 's'){
	  for (i = 0; i<2; i++){
	    uart_putc(remote_temp_buf[i]);
	    while (uart_getc() != 'Y'){}
	  }
	}
  }
}
