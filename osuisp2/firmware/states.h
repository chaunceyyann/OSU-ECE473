/** 
 * @file states.h
 * @brief This file contains definitions for state variable values and bit fields
 * @author Ben Porter
 */

#ifndef USBASP_H_
#define USBASP_H_

/** Disconnect all interfaces */
#define DISCONNECT_ALL  	2

/** SPI Function Codes */
#define SPI_CONNECT     	1
#define SPI_TRANSMIT    	3
#define SPI_READMEMORY   	4
#define SPI_ENABLEPROG  	5
#define SPI_WRITEMEMORY  	6

/**JTAG Function Codes (for urJTAG interface) */
#define JTAG_CONNECT 		11
#define JTAG_SET_FREQ		12
#define JTAG_CLOCK			13
#define JTAG_GET_TDO		14
#define JTAG_SET_TRST		15
#define JTAG_SEND_TDI		16
#define JTAG_SEND_REC		17
#define JTAG_GET_BIGTDO		18

/** Jtag State Machine Codes */
#define JTAG_STATE_MACHINE_INIT 	92
#define JTAG_STATE_MACHINE_COMMAND 	93
#define JTAG_STATE_MACHINE_CLOSE 	94


/** Jtag Programming State Codes */
#define PROG_STATE_JTAG_SEND_TDO 	12

/** SPI Programming State Codes */
#define PROG_STATE_IDLE         	0
#define PROG_STATE_READFLASH    	2
#define PROG_STATE_READEEPROM   	3

/** SPI Block mode flags */
#define PROG_BLOCKFLAG_FIRST   		0x01
#define PROG_BLOCKFLAG_LAST     	0x02

/** SPI Memory type flags */
#define MEM_EEPROM 					0x04
#define MEM_FLASH 					0x08


#endif
