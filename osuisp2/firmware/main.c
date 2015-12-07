/*
 * USBasp - USB in-circuit programmer for Atmel AVR controllers
 *
 * Thomas Fischl <tfischl@gmx.de>
 *
 * License........: GNU GPL v2 (see Readme.txt)
 * Target.........: ATMega88 at 12 MHz
 * Creation Date..: 2005-02-20
 * Last change....: 2009-02-28
 *
 * PC2 SCK speed option.
 * GND  -> slow (8khz SCK),
 * open -> software set speed (default is 375kHz SCK)
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "clock.h"
#include "states.h"
#include "usbdrv.h"

#include "spi.h"
#include "jtag.h"
#include "xsvfexec\xsvfexec.h"

// Define three reports:
// Report ID = 1: 8 bytes of data
// Report ID = 2: 16 bytes of data
// Report ID = 3: 250 bytes of data
PROGMEM char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = {    // USB report descriptor
	0x06, 0x00, 0xff,     // Usage Page (Vendor Defined)                     
	0x09, 0x01,           // Usage (Vendor Defined)                          
	0xa1, 0x01,           // Collection (Vendor Defined)

	
	0x85, 0x01, 		  // Report Id (1)
	0x09, 0x00,           //   Usage (Undefined)                        
	0x75, 0x08,           //   Report Size (8)                               
	0x95, 8, 			  //   Report Count (8)       
	0x15, 0x00,           //   Logical Minimum (0)                        
	0x26, 0xff, 0x00,     //   Logical Maximum (255)   
    0xb2, 0x02, 0x01,     //   FEATURE (Data,Var,Abs,Buf)	
	

	0x85, 0x02, 		  // Report Id (2)
	0x09, 0x00,           //   Usage (Undefined)                        
	0x75, 0x08,           //   Report Size (8)                               
	0x95, 16, 		      //   Report Count (16)       
	0x15, 0x00,           //   Logical Minimum (0)                        
	0x26, 0xff, 0x00,     //   Logical Maximum (255)   
    0xb2, 0x02, 0x01,     //   FEATURE (Data,Var,Abs,Buf)	
	

	0x85, 0x03, 		  // Report Id (3)
	0x09, 0x00,           //   Usage (Undefined)                        
	0x75, 0x08,           //   Report Size (8)                               
	0x95, 250, 			  //   Report Count (250)       
	0x15, 0x00,           //   Logical Minimum (0)                        
	0x26, 0xff, 0x00,     //   Logical Maximum (255)   
    0xb2, 0x02, 0x01,     //   FEATURE (Data,Var,Abs,Buf)
          
	0xc0                  // End Collection     						     
};


/**JTAG variables*/
static uint16_t length;
static uint16_t bitCount;

/** Current byte index of a usb data transfer */
static uchar    currentAddress;
/** Number of bytes remaining on current usb transfer */
static uchar    bytesRemaining;

/** Structure for holding the data sent to the firmware from the host */
typedef struct receive
{
	uchar reportID;			/// first byte received will be the report ID
	uchar reportSize;		/// Number of meaningful data bytes in the data field
	uchar command;			/// The command requested to be performed
	uchar data[248];		/// Data used to execute the command
} receive_t;
receive_t receiveBuffer;

// This structure formats the reply return information into 
// a friendlier format.  The total length of this structure
// should be at least 17 bytes, and can be more (but the 
// extra bytes won't be used unless the report structure is
// modified)
// This structure can be used with report ID 1 and 2, but
// report ID 3 should use the usbReadFunction to transmit
// data back to the host
typedef struct reply
{
    uchar reportID; // First byte in reply is reportID, as per specification
	uchar reportSize; // The number of meaningful bytes in the following data field
	uchar data[15];
} reply_t;
static reply_t replyBuffer;

/** The executeCommand function is called when an incomming transfer is complete */
void executeCommand();

/** Current programming state */
static uchar prog_state = PROG_STATE_IDLE;
static unsigned int prog_pagesize; /** AVR-ISP page size */
static unsigned long prog_address; /** AVR-ISP current address */
static uchar prog_nbytes; /** Number of byes left to program */
static uchar prog_pagecounter; /** Mumber of bytes until the next page */
static uchar dataBytes; /** Number of data bytes sent/received */

/* ------------------------------------------------------------------------- */

/** SPI Functions for communication */
void Connect();
void SendSPI();

/** AVR-ISP SPI functions */
void ReadMemory();
void EnableProgramming();
void WriteMemory(); 
void SetLongAddress();

/** JTAG State Machine */
void JtagStateMachineInit();
void JtagStateMachineCommand();
void JtagStateMachineClose();

/** Slow JTAG (urJTAG) communication */
void JtagSetFrequency();
void JtagClock();
void JtagGetTDO();
void JtagTrst();
void JtagSendTDI();
void JtagGetBigTDO();


/** The host computer uses this function to send 
	data to this device.  The data is stored in
	an array, and operations are carried out when
	the transfer is complete. */
uchar   usbFunctionWrite(uchar *data, uchar len)
{
	uchar i = 0;

    if(len > bytesRemaining)
        len = bytesRemaining;
    
	
	for (; i<len; i++)
	{
		((uchar*)&receiveBuffer)[currentAddress+i] = data[i];
	}
	
	currentAddress += len;
    bytesRemaining -= len;
	if (bytesRemaining==0)
	{
		// Process results here
		executeCommand();
		return 1;
	}
    return 0;
}

/* ------------------------------------------------------------------------- */

/** This function is called before any usb data
	is transfered to or from the device.  This allows
	the proper variables to be initialized for the
	impending transfer in or out of data. */
usbMsgLen_t usbFunctionSetup(uchar data[8])
{
	usbRequest_t    *rq = (void *)data;

    if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS)
	{    /* HID class request */
	
		if(rq->bRequest == USBRQ_HID_GET_REPORT) // Host requests data from us!
		{
			replyBuffer.reportID = data[2];
			switch (replyBuffer.reportID) // switch (Report ID)
			{
				case 1:
					bytesRemaining = 9;
					break;
				case 2:
					bytesRemaining = 17;
					break;
				case 3:
					bytesRemaining = 251;
					break;
				default:
					return 0;
			}
			
			currentAddress = 0;
			
			return USB_NO_MSG; // Use the usbFunctionRead
        }
		else if(rq->bRequest == USBRQ_HID_SET_REPORT) // Host sends data
		{	
			// In the usbFunctionWrite function which will get called after
			// this point, the reply buffer structure will be filled out
			// including the reportSize.  In the event that the reply buffer
			// is not filled out, setting the report size to zero will
			// tell the receiving application (host program) that there is
			// no meaningful data.  Otherwise, the size will remain that
			// which was sent for the previous request.
			replyBuffer.reportSize = 0;
		 
			// The number of bytes which will need to be read in using
			// the usbFunctionWrite function.
			bytesRemaining = data[6];
			currentAddress = 0;
			
			// After this, the usbFunctionWrite function will be called
			// and the receive buffer will be filled with (bytesRemaining)
			// number of bytes from the host.  This data will be parsed
			// and used to set up and execute a command.
			return USB_NO_MSG;
        }
    }
	else
	{
        /* ignore vendor type requests, we don't use any */
    }
    return 0;
}



/** The incoming command is fully copied to the receive
	buffer, procede to execute the command */
void executeCommand()
{
	switch(receiveBuffer.command)
	{
	
/** Jtag State machine (Fast) */
		case JTAG_STATE_MACHINE_INIT:
			JtagStateMachineInit();
			break;
			
		case JTAG_STATE_MACHINE_COMMAND:
			JtagStateMachineCommand();
			break;
			
		case JTAG_STATE_MACHINE_CLOSE:
			JtagStateMachineClose();
			break;
			
			
/** Disconnect Everything (disable all interfaces) */
		case DISCONNECT_ALL:
			DisableProgramming();
			prog_state = PROG_STATE_IDLE;
			break;	
	
/** SPI Programming */
		case SPI_CONNECT:
			Connect();
			break;
			
		case SPI_TRANSMIT:
			SendSPI();
			break;
			
		case SPI_READMEMORY:
			ReadMemory();
			break;
		
		case SPI_ENABLEPROG:
			EnableProgramming();
			break;
			
		case SPI_WRITEMEMORY:
			WriteMemory();
			break;

			
/** Bit-Bang JTAG: INCREDIBLY slow, good for hungry people.
 * You will have enough time to make a bowl
 * of ramen noodles if you choose to program
 * a cpld with this jtag method */
		case JTAG_CONNECT:
			EnableJTAG();
			break;
			
		case JTAG_SET_FREQ:
			JtagSetFrequency();
			break;
		
		case JTAG_CLOCK:
			JtagClock();
			break;
			
		case JTAG_GET_TDO:
			JtagGetTDO();
			break;
			
		case JTAG_SET_TRST:
			JtagTrst();
			break;
			
		case JTAG_SEND_TDI:
			JtagSendTDI();
			break;

		case JTAG_GET_BIGTDO:
			JtagGetBigTDO();
			break;

		default:
			replyBuffer.reportSize = 0;
			break;
	}
	return;
}


// JTAG State Machine
void JtagStateMachineInit()
{
	XsvfInit();
	replyBuffer.data[0] = 0; // Success
	replyBuffer.reportSize = 1;
	return;
}

void JtagStateMachineCommand()
{
	unsigned char i = 0;
	replyBuffer.reportSize = 1;

	while (i<receiveBuffer.reportSize)
	{
		unsigned char dataLength = receiveBuffer.data[i];
		replyBuffer.data[0] = XsvfExec(&(receiveBuffer.data[i+1]), dataLength);
		if (replyBuffer.data[0]!=0)
		{
			return; // Error!
		}
		i += dataLength+1;
	}
	return;
}

void JtagStateMachineClose()
{
	XsvfClose();
	return;
}



// SPI
void Connect()
{
	replyBuffer.reportSize = 1;
	/** Set the clock index.  The return value will
		be the actual clock index set */
	replyBuffer.data[0] = SPI_Connect(receiveBuffer.data[0], receiveBuffer.data[1]);
}

void SendSPI()
{
	uchar i;
	replyBuffer.reportSize = receiveBuffer.reportSize-1;
	uchar delay = receiveBuffer.data[0];
	
	/** The maximum size of the reply buffer is 15 elements */
	if (replyBuffer.reportSize > 15) replyBuffer.reportSize = 15;
	
	/** Transmit and receive data */
	for (i=0; i<replyBuffer.reportSize; i++)
	{
		replyBuffer.data[i] = SPI_Transmit(receiveBuffer.data[i+1]);
		clockWait(delay); // (optional) Allow for processing of the last command
	}
}

void ReadMemory()
{	
	prog_address = *((unsigned long*) &receiveBuffer.data[0]);
	prog_nbytes = receiveBuffer.data[4]; // The number of bytes to read
	uchar memType = receiveBuffer.data[5];
	
	if (memType == MEM_FLASH)
	{
		prog_state = PROG_STATE_READFLASH;
	}
	else if (memType == MEM_EEPROM)
	{
		prog_state = PROG_STATE_READEEPROM;
	}
	
	replyBuffer.reportSize = prog_nbytes;
}

void EnableProgramming()
{
	replyBuffer.reportSize = 1;
	replyBuffer.data[0] = SPI_EnterProgrammingMode();
}

void WriteMemory()
{
	uchar i;
	
	// Setup Variables
	prog_address = *((unsigned long*) &receiveBuffer.data[0]); // First 4 bytes are the address
	prog_pagesize = (receiveBuffer.data[5] << 8) | receiveBuffer.data[4];
	prog_nbytes   = receiveBuffer.data[6];
	uchar memType = receiveBuffer.data[7];
	uchar prog_blockflags = receiveBuffer.data[8];
	
	if (memType == MEM_FLASH)
	{
		if (prog_blockflags & PROG_BLOCKFLAG_FIRST)
		{
			prog_pagecounter = prog_pagesize;
		}
		
		for (i = 0; i < prog_nbytes; i++) 
		{
			// Flash 
			if (prog_pagesize == 0) 
			{
				// not paged 
				SPI_WriteFlash(prog_address, receiveBuffer.data[i+9], 1);
			} 
			else 
			{
				// paged 
				SPI_WriteFlash(prog_address, receiveBuffer.data[i+9], 0);
				prog_pagecounter--;
				if (prog_pagecounter == 0) 
				{
					SPI_FlushPage(prog_address, receiveBuffer.data[i+9]);
					prog_pagecounter = prog_pagesize;
				}
			}
			prog_address++;
		}
		
		if ((prog_blockflags & PROG_BLOCKFLAG_LAST) && 
			(prog_pagecounter!= prog_pagesize)) 
		{
			// last block and page flush pending, so flush it now 
			SPI_FlushPage(prog_address-1, receiveBuffer.data[i+8]);
		}
	}
	else if (memType == MEM_EEPROM)
	{
		uchar i;
		for (i = 0; i < prog_nbytes; i++)
		{
			SPI_WriteEEPROM(prog_address, receiveBuffer.data[i+9]);
			prog_address++;
		}
	}
	
	replyBuffer.reportSize = 1;
	replyBuffer.data[0] = prog_nbytes; // Set to the number of succesfully programmed bytes
}







// Slow Jtag
void JtagSetFrequency()
{
	JTAG_set_delay (receiveBuffer.data[0]);
	return;
}

void JtagClock()
{
	unsigned int temp;
	temp = receiveBuffer.data[2] +(((unsigned int)receiveBuffer.data[3])<<8);
	JTAG_clock(receiveBuffer.data[0],receiveBuffer.data[1],temp);
	return;
}

void JtagGetTDO()
{
	replyBuffer.data[0]=JTAG_get_TDO();
	replyBuffer.reportSize = 1;
}

void JtagTrst()
{
	JTAG_trst(receiveBuffer.data[0]);
	return;
}

/** Send bits to the device, disregard any replies from the device */
void JtagSendTDI()
{
	length=*((unsigned int *)&receiveBuffer.data[0]);
	
	unsigned int i;
	unsigned char byteIndex;
	unsigned char bitIndex;
	// Length is the number of bits to send
	for (i = 0; i<length; i++)
	{
		byteIndex = i/8 + 2; // The data starts 2 bytes into the data array
		bitIndex = 7 - (i % 8);
		
		// Clock out the bit located at the location bitIndex in byte byteIndex of the data array
		JTAG_clock(0, (receiveBuffer.data[byteIndex] >> bitIndex) & 0x01, 1);
	}
	return;
}

/** Set up sending bits to the device through the read function,
	where the replies from the device will be passed back to the
	host computer */
void JtagGetBigTDO()
{
	/** Prepare variables for the usbFunctionRead below 
		There's already a bunch of data in the receive
		buffer, which will be sent to the device as data
		is read from the device 
	*/
	prog_state = PROG_STATE_JTAG_SEND_TDO;
	length=*((uint16_t *)&receiveBuffer.data[0]);
	bitCount = 0;
	replyBuffer.reportSize = (length+7)/8;
	return;
}




/** Data is requested and sent back to the host computer here.
    The prog_state variable will determine which data to send back */
uchar usbFunctionRead(uchar *data, uchar len) 
{
	uchar i = 0;
	
	if(len > bytesRemaining)
        len = bytesRemaining;
	
	if (currentAddress == 0)
	{
		dataBytes = 0;
		data[0] = replyBuffer.reportID;
		i = 1;
		if (len > 1)
		{	
			i = 2;
			data[1] = replyBuffer.reportSize;
		}
	}
	if (currentAddress == 1)
	{
		i = 2;
		data[1] = replyBuffer.reportSize;
	}


	// Fill in the rest of the data request depending on the current state of the programmer:
	if ((prog_state == PROG_STATE_READFLASH) || (prog_state == PROG_STATE_READEEPROM))
	{
		// If in Flash or EEPROM read state:
		for (; i < len; i++) 
		{
			if (dataBytes < prog_nbytes) // Meaningful data bytes
			{
				if (prog_state == PROG_STATE_READFLASH) 
				{
					data[i] = SPI_ReadFlash(prog_address);
				} 
				else 
				{
					data[i] = SPI_ReadEEPROM(prog_address);
				}
				prog_address++;
			}
			else // Fill the rest of the buffer with zeros
			{
				data[i] = 0;
			}
			dataBytes++;
		}
	}
	else if (prog_state == PROG_STATE_JTAG_SEND_TDO)
	{
		uchar j;
		uchar bitIndex;
		for(; i < len; i++)
		{
			data[i] = 0;
			for(j = 0; j < 8; j++)
			{		
				bitIndex = 7 - j;
				
				if (bitCount < length)
				{
					data[i] |= (JTAG_get_TDO()) << bitIndex; // Data gets read from device
					JTAG_clock (0, (receiveBuffer.data[dataBytes+2] >> bitIndex) & 0x01, 1); //data actually gets clocked into jtag device - joey
				}
				bitCount++;
			}
			dataBytes++;
		}
	}
	else
	{
		// Otherwise, pass back whatever is in the reply buffer
		for (; i < len; i++) 
		{
			if (dataBytes < replyBuffer.reportSize)
			{
				data[i] = replyBuffer.data[dataBytes];
			}
			else
			{
				data[i] = 0;
			}
			dataBytes++;
		}
	}
	
	currentAddress += len;
    bytesRemaining -= len;

	if (len < 8 || bytesRemaining == 0) 
	{
		prog_state = PROG_STATE_IDLE;
	}
	
    return len;
}


int main(void)
{
	uchar   i;
	
	// Initial Setup
	
	DisableProgramming();
	
	/* all inputs except PC0, PC1, PC3 */
	DDRC = 0b00001011;
	InitSlowClockJumper();

	// Clock Setup
	clockInit();
	
	
	/* Even if you don't use the watchdog, turn it off here. On newer devices,
     * the status of the watchdog (on/off, period) is PRESERVED OVER RESET! */
    wdt_enable(WDTO_1S);
    
    usbInit();
    usbDeviceDisconnect();  /* enforce re-enumeration, do this while interrupts are disabled! */
    i = 0;
    while(--i) /* fake USB disconnect for > 250 ms */
	{             
        wdt_reset();
        _delay_ms(1);
    }
    usbDeviceConnect();
    sei();
	
	INDICATOR_LED_ON();
	
    for(;;)
	{
        wdt_reset();
        usbPoll();
    }
    return 0;
}


