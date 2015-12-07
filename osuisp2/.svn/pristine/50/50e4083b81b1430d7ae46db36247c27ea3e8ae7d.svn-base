
#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <util/delay.h>

#define COMMAND 1
#define DATA 2
#define WAIT 3
#define IDLE 4

#define CMD_SET_DDRA 0
#define CMD_SET_DDRB 1
#define CMD_SET_PORTA 2
#define CMD_SET_PORTB 3
#define CMD_READ_PINA 4
#define CMD_READ_PINB 5
#define CMD_READ_ADC 6

unsigned char state = 0;
unsigned char command = 0;

//ISR(USI_STRT_vect )
//{
//	PORTA = 0b00000001;
//	USICR = (1<<USIWM0) | (1<<USICS1) | (1<<USIOIE); // Disable start condition interrupt, enable tx complete interrupt
//	USISR = (1<<USIOIF); // Reset counter value
//}

unsigned char count;
unsigned char data[6];
unsigned char data_out = 0;



// This method is called on serial transfer complete
ISR(USI_OVF_vect)
{
	data[count] = USIDR; // Data Register - currently holds input data
	USIDR = data_out; // Set the output data to the data register
	
	USISR = 1<<USIOIF; // Clear the interrupt flag
	
	data_out = 0;
	
	count++;
	
	if (data[0] == 0xAA) // Read in an ADC value
	{
		if (count == 2) // ADC Setup
		{
			ADMUX = (1<<ADLAR) | data[1];
			ADCSRA = (1<<ADEN) | (1<<ADSC) | (1<<ADPS0); // Fast conversion
		}
		if (count == 4) // Respond with ADC value
		{
			data_out = ADCH;
		}
	}
	if (data[0] == 0x70) // Get/Set PORTA
	{
		if (count == 1)
		{
			data_out = PINA;
		}
		if (count == 2)
		{
			data_out = PORTA;
		}
		if (count == 3)
		{
			data_out = DDRA;
		}
		if (count == 5)
		{
			DDRA = (DDRA & ~data[2]) | (data[1] & data[2]);
			PORTA =(PORTA & ~data[4]) | (data[3] & data[4]);
		}
	}
	if (data[0] == 0x71) // Get/Set PORTB
	{
		if (count == 1)
		{
			data_out = PINB;
		}
		if (count == 2)
		{
			data_out = PORTB;
		}
		if (count == 3)
		{
			data_out = DDRB;
		}
		if (count == 5)
		{
			data[2] &= ~0b10000111; // Dont touch DDRB 0, 1, 2, 7
			data[4] &= ~0b10000111; // Dont touch PORTB 0, 1, 2, 7
			
			DDRB = (DDRB & ~data[2]) | (data[1] & data[2]);
			PORTB = (PORTB & ~data[4]) | (data[3] & data[4]);
		}
	}
	if (data[0] == 0x60) // Set Timer Values
	{
		if (count == 1)
		{
			data_out = TCNT1;
		}
		if (count == 5)
		{
			TCCR1A = data[1];
			TCCR1B = data[2];
			OCR1B = data[3];
			OCR1C = data[4];
		}
	}
	
	
	
	//PORTA = data[count-1];
	if (count == 5)
	{
		data_out = 0xA9; // First byte out of next packet
	}
	
	if (count == 6)
	{
		count = 0;
	}
	
	
	/*
	PORTA = 0b00000010;
	
	if (state==2)
		USIDR = data_out; // Send Next data, otherwise echo
	else
		USIDR = 0; // Otherwise, send zero
	
	if (state == 0)
	{
		command = data_in;
	}
	if (state == 1)
	{
		switch (command)
		{
			case CMD_SET_DDRA:
			{
				DDRA = data_in;
				data_out = PINA;
				break;
			}
			case CMD_SET_DDRB:
			{
				// Prevent changes in DDRB0, 1, 2, and 7
				DDRB = (data_in & 0b01111000) & (DDRB & 0b10000111);
				data_out = PINB;
				break;
			}
			case CMD_SET_PORTA:
			{
				PORTA = data_in;
				data_out = PINA;
				break;
			}
			case CMD_SET_PORTB:
			{
				// No changes to PB0,1,2
				PORTB = (PINB & 0b00000111) & (data_in & 0b11111000);
				data_out = PINB;
				break;
			}
			case CMD_READ_PINA:
			{
				data_out = PINA;
				break;
			}
			case CMD_READ_PINB:
			{
				data_out = PINB;
				break;
			}
			case CMD_READ_ADC:
			{	
				ADMUX = (1<<ADLAR) | data_in;
				ADCSR = (1<<ADEN) | (1<<ADSC) | (1<<ADPS0); // Fast conversion

				// Wait for conversion to complete
				//while((ADCSR & 0b00010000) == 0)
				//{
				//}
				data_out =0x67;
				
				break;
			}
			default:
			{
			}
		}
		return;
	}
	if (state == 2)
	{
	}
	if (state == 3)
	{
		state = 0;
		USICR = (1<<USIWM0) | (1<<USICS1) | (1<<USISIE); // Enable start condition interrupt
	}
	state++;
	*/
}

void SPI_SlaveInit()
{
	USICR = (1<<USIWM0) | (1<<USICS1) | (1<<USIOIE);

	//PORTB = (1<<PB2); // Pullup on serial clock (PB2)
	USISR = 1<<USIOIF; // Clear the interrupt flag, reset the counter
	
}

/*
unsigned char SPI_SlaveTransfer(unsigned char data)
{
	USIDR = data; // Load data into data register
	USISR = 1<<USIOIF;
	// Wait for shift to complete
	while ((USISR & (1<<USIOIF)) == 0)
	{
	}
	return USIDR;
}
*/

/*
out USIDR,r16
ldi r16,(1<<USIOIF)
out USISR,r16
SlaveSPITransfer_loop:
sbis USISR,USIOIF
rjmp SlaveSPITransfer_loop
in r16,USIDR
ret*/





int main (void) 
{
	DDRA = 0b00000011;
	DDRB = (1<<PB1) | (1<<PB3);
	SPI_SlaveInit();
	
	sei();
	
	USIDR = 0xA9;
	
	while(1)	//loop infinitely
	{
		//PORTA = SPI_SlaveTransfer(6);
	}
}
