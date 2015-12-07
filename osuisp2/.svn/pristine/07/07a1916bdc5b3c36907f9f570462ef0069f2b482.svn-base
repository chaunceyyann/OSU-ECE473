/*
 * $Id: usbasp.c 1030 2008-02-16 16:25:51Z akerlunj $
 *
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * Originally By Jace Akerlund
 * Modified by Ben Porter
 *
 */

 
/** USB identifiers */
#define	OSUISP2_VENDOR_ID   0x16C0  /* VOTI */
#define	OSUISP2_PRODUCT_ID   0x05DF  /* Obdev's free shared PID */
#define OSUISP2_VENDOR_NAME "beaversource.oregonstate.edu/projects/osuisp2"
#define OSUISP2_PRODUCT_NAME "OSUisp2"
 
#include <windows.h>
#include <setupapi.h>
#include <ddk\hidsdi.h>
#include <ddk\hidpi.h>
#include <ddk\hidusage.h>

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "generic.h"
#include "generic_usbconn.h"

#include "usbconn.h"

#include "sysdep.h"
#include "cable.h"
#include "chain.h"
#include "jtag.h"

#define USE_TRANSFER

#define SEND 0
#define RECIEVE 1


#define FUNC_DISCONNECT 2//Puts device back into idle mode

//USBASP command defines
/*
#define FUNC_JTAG_CONNECT 	10 //Puts device into JTAG mode
#define FUNC_JTAG_SET_FREQ	11
#define FUNC_JTAG_CLOCK		12
#define FUNC_JTAG_GET_TDO	13
#define FUNC_JTAG_SET_TRST	14
#define FUNC_JTAG_SEND_TDI	15
#define FUNC_JTAG_SEND_REC	16
#define FUNC_JTAG_GET_BIGTDO	17
*/

//USBASP command defines
#define FUNC_JTAG_CONNECT 	11 //Puts device into JTAG mode
#define FUNC_JTAG_SET_FREQ	12
#define FUNC_JTAG_CLOCK		13
#define FUNC_JTAG_GET_TDO	14
#define FUNC_JTAG_SET_TRST	15
#define FUNC_JTAG_SEND_TDI	16
#define FUNC_JTAG_SEND_REC	17
#define FUNC_JTAG_GET_BIGTDO	18

#define MAX_FREQUENCY 1000000
#define DATA_CHUNK_LENGTH 1024

#ifdef HAVE_LIBUSB


#include <usb.h>

#define USBDEV_VENDOR 0x16C0
#define USBDEV_PRODUCT 0x05DF

typedef unsigned char uchar;
typedef struct usbDevice    usbDevice_t;

static usbDevice_t *usb_handle;
static int transmit_chunk(char, char *, char *, int);

// BEGIN NEW CODE
typedef struct ReportOut
{
    unsigned char reportID;
    unsigned char reportSize;
    unsigned char command;
    unsigned char data [248];
} ReportOut_t;
ReportOut_t reportOut;


typedef struct ReportIn
{
    unsigned char reportID;
    unsigned char reportSize;
    unsigned char data [249];
} ReportIn_t;
ReportIn_t reportIn;


/** Send and Receive data over USB
 * @param device
 * @param command to send to the device
 * @param array of data to send
 * @param length of data to send
 * @param buffer to hold response (8 characters)
 * @param lengh of data expected
 * @return length of data received
 */
int SendData(usbDevice_t *dev, uchar command, uchar * dataToSend, int length, uchar * outBuffer, int outBufferLength)
{
    //printf("SendData called: Dev = %d, command = %d\n", dev, command);
    if (dev==NULL)
        return -1; // Error, device not opened

    ReportOut_t reportOut;
    ReportIn_t reportIn;

    reportOut.reportSize = length;
    reportOut.command = command;

    if (reportOut.reportSize <= 6)
    {
        reportOut.reportID = 1;
    }
    else if (reportOut.reportSize <= 14)
    {
        reportOut.reportID = 2;
    }
    else if (reportOut.reportSize <=248)
    {
        reportOut.reportID = 3;
    }
    else
    {
        printf("Send size is too large for a single transmission!\n");
        return -1; // Error, size too great for a single transmission
    }

    if (outBufferLength > 250)
    {
        printf("Reply size is too large for a single transmission!\n");
        return -1;
    }

    // Copy the data to the transmit buffer
    int i;
    for (i=0; i<reportOut.reportSize; i++)
    {
        reportOut.data[i] = dataToSend[i];
    }


    // Send out the data
    if (!HidD_SetFeature(dev, (void*)&reportOut, sizeof(ReportOut_t)))
    {
        //Disconnect();
        printf("Sending data failed!\n");
        return -1;
    }

    // Receive the data
    if (outBufferLength <= 7)
    {
        reportIn.reportID = 1; // Up to 7 bytes of data to receive, plus 1 size byte
    }
    else if (outBufferLength <= 15)
    {
        reportIn.reportID = 2;
    }
    else if (outBufferLength <=249)
    {
        reportIn.reportID = 3;
    }

    if (!HidD_GetFeature(dev, (void*)&reportIn, sizeof(ReportIn_t)))
    {
        //Disconnect();
        printf("Receiving data failed!\n");
        return -1;
    }

    if (outBuffer!=NULL)
    {
        //outBuffer[0] = reportIn.reportSize;
        for (i=0; i<reportIn.reportSize; i++)
        {
            outBuffer[i] = reportIn.data[i];
        }
    }

    return reportIn.reportSize; // The return code should be held in this value
}

#define USBOPEN_SUCCESS         0   /* no error */
#define USBOPEN_ERR_ACCESS      1   /* not enough permissions to open device */
#define USBOPEN_ERR_IO          2   /* I/O error */
#define USBOPEN_ERR_NOTFOUND    3   /* device not found */

#ifdef DEBUG
#define DEBUG_PRINT(arg)    printf arg
#else
#define DEBUG_PRINT(arg)
#endif
static void convertUniToAscii(char *buffer)
{
unsigned short  *uni = (void *)buffer;
char            *ascii = buffer;

    while(*uni != 0){
        if(*uni >= 256){
            *ascii++ = '?';
        }else{
            *ascii++ = *uni++;
        }
    }
    *ascii++ = 0;
}

/*
 * Try to open USB device with given VID, PID, vendor and product name
 * Parts of this function were taken from an example code by OBJECTIVE
 * DEVELOPMENT Software GmbH (www.obdev.at) to meet conditions for
 * shared VID/PID
 */
int usbhidOpenDevice(usbDevice_t **device, int vendor, char *vendorName, int product, char *productName)
{
    GUID                                hidGuid;        /* GUID for HID driver */
    HDEVINFO                            deviceInfoList;
    SP_DEVICE_INTERFACE_DATA            deviceInfo;
    SP_DEVICE_INTERFACE_DETAIL_DATA     *deviceDetails = NULL;
    DWORD                               size;
    int                                 i, openFlag = 0;  /* may be FILE_FLAG_OVERLAPPED */
    int                                 errorCode = USBOPEN_ERR_NOTFOUND;
    HANDLE                              handle = INVALID_HANDLE_VALUE;
    HIDD_ATTRIBUTES                     deviceAttributes;

    HidD_GetHidGuid(&hidGuid);
    deviceInfoList = SetupDiGetClassDevs(&hidGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
    deviceInfo.cbSize = sizeof(deviceInfo);
    for(i=0;;i++){
        if(handle != INVALID_HANDLE_VALUE){
            CloseHandle(handle);
            handle = INVALID_HANDLE_VALUE;
        }
        if(!SetupDiEnumDeviceInterfaces(deviceInfoList, 0, &hidGuid, i, &deviceInfo))
            break;  /* no more entries */
        /* first do a dummy call just to determine the actual size required */
        SetupDiGetDeviceInterfaceDetail(deviceInfoList, &deviceInfo, NULL, 0, &size, NULL);
        if(deviceDetails != NULL)
            free(deviceDetails);
        deviceDetails = malloc(size);
        deviceDetails->cbSize = sizeof(*deviceDetails);
        /* this call is for real: */
        SetupDiGetDeviceInterfaceDetail(deviceInfoList, &deviceInfo, deviceDetails, size, &size, NULL);
        DEBUG_PRINT(("checking HID path \"%s\"\n", deviceDetails->DevicePath));
#if 0
        /* If we want to access a mouse our keyboard, we can only use feature
         * requests as the device is locked by Windows. It must be opened
         * with ACCESS_TYPE_NONE.
         */
        handle = CreateFile(deviceDetails->DevicePath, ACCESS_TYPE_NONE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, openFlag, NULL);
#endif
        /* attempt opening for R/W -- we don't care about devices which can't be accessed */
        handle = CreateFile(deviceDetails->DevicePath, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, openFlag, NULL);
        if(handle == INVALID_HANDLE_VALUE){
            DEBUG_PRINT(("opening failed: %d\n", (int)GetLastError()));
            /* errorCode = USBOPEN_ERR_ACCESS; opening will always fail for mouse -- ignore */
            continue;
        }
        deviceAttributes.Size = sizeof(deviceAttributes);
        HidD_GetAttributes(handle, &deviceAttributes);
        DEBUG_PRINT(("device attributes: vid=%d pid=%d\n", deviceAttributes.VendorID, deviceAttributes.ProductID));
        if(deviceAttributes.VendorID != vendor || deviceAttributes.ProductID != product)
            continue;   /* ignore this device */
        errorCode = USBOPEN_ERR_NOTFOUND;
        if(vendorName != NULL && productName != NULL){
            char    buffer[512];
            if(!HidD_GetManufacturerString(handle, buffer, sizeof(buffer))){
                DEBUG_PRINT(("error obtaining vendor name\n"));
                errorCode = USBOPEN_ERR_IO;
                continue;
            }
            convertUniToAscii(buffer);
            DEBUG_PRINT(("vendorName = \"%s\"\n", buffer));
            if(strcmp(vendorName, buffer) != 0)
                continue;
            if(!HidD_GetProductString(handle, buffer, sizeof(buffer))){
                DEBUG_PRINT(("error obtaining product name\n"));
                errorCode = USBOPEN_ERR_IO;
                continue;
            }
            convertUniToAscii(buffer);
            DEBUG_PRINT(("productName = \"%s\"\n", buffer));
            if(strcmp(productName, buffer) != 0)
                continue;
        }
        break;  /* we have found the device we are looking for! */
    }
    SetupDiDestroyDeviceInfoList(deviceInfoList);
    if(deviceDetails != NULL)
        free(deviceDetails);
    if(handle != INVALID_HANDLE_VALUE){
        *device = (usbDevice_t *)handle;
        //printf("Opened device handle = %d\n", *device);
        errorCode = 0;
    }
    return errorCode;
}

void usbhidCloseDevice(usbDevice_t *device)
{
    CloseHandle((HANDLE)device);
}


static int connect(char *params[], cable_t *cable)
{
	printf("Initializing %s Programmer\n",_(OSUISP2_PRODUCT_NAME));
	
	int retValue = usbhidOpenDevice(&usb_handle, OSUISP2_VENDOR_ID, _(OSUISP2_VENDOR_NAME), OSUISP2_PRODUCT_ID, _(OSUISP2_PRODUCT_NAME));
	if(retValue!=0)
	{
		printf(_("Couldn't connect to programmer... Is the %s plugged in?\n"), _(OSUISP2_PRODUCT_NAME));
		return 1;
	}

	// Might be a good idea to put the usb handle into the cable link somehow...
	cable->link.usb = NULL;
//	free(cable->params);
//	cable->params = cable_params;
	cable->chain = NULL;
	return 0;
}

void disconnect(cable_t *cable)
{
	cable_done(cable);
	chain_disconnect( cable->chain );
}

static void this_cable_free(cable_t *cable)
{
	CloseHandle(usb_handle);

	usb_handle=NULL;

	// Free any generic params stuck into the params list
	free( cable->params );
	
	// Are we really responsible for freeing the cable?
	free( cable );	
}

static int init(cable_t *cable)
{
	//printf(_("Cable Init"));

	int result = SendData(usb_handle, FUNC_JTAG_CONNECT, NULL, 0, NULL, 0);
	
	return (result==-1?1:0);
}

static void done(cable_t *cable)
{
	//printf(_("Done\n"));
}

void set_frequency(cable_t *cable, uint32_t new_frequency)
{
	printf( _("set_frequency [MAX_FREQUENCY=%d, new_frequency=%d\n"), MAX_FREQUENCY, new_frequency);
	
	//need check to ensure max frequency isn't hit, need to find what max frequency is as well
	unsigned int us_delaytime = MAX_FREQUENCY / new_frequency;
	uchar data[2];
	data[0]=(uchar)us_delaytime;
	data[1]=(uchar)(us_delaytime>>8);

	SendData(usb_handle, FUNC_JTAG_SET_FREQ, data, 2, NULL, 0);
	
	cable->frequency = (new_frequency>MAX_FREQUENCY)?MAX_FREQUENCY:new_frequency;
}

static void clock(cable_t *cable, int tms, int tdi, int n)
{
	unsigned char data[4];
	tms = tms ? 1 : 0;
	tdi = tdi ? 1 : 0;
	data[0]=tms;
	data[1]=tdi;
	data[2]=(unsigned char)n;
	data[3]=(unsigned char)(n>>8);
	SendData(usb_handle, FUNC_JTAG_CLOCK, data, 4, NULL, 0);
}

static int get_tdo(cable_t *cable)
{
	
	unsigned char temp;
	SendData(usb_handle, FUNC_JTAG_GET_TDO, NULL, 0, &temp, 1);
	return temp;
}

#ifdef USE_TRANSFER

int transfer(cable_t *cable, int bits, char *bitIn, char *bitOut)
{
	//printf("\n\njoey_transfer(cable=%x, bits=%d, bitIn=%x, bitOut=%x)\n", cable, bits, bitIn, bitOut);

	// bitIn is transfer data TO THE DEVICE
	// bitOut is data received FROM THE DEVICE

	int i;

	if(bits<1)
		return bits;
	
	//if there are more than DATA_CHUNK_LENGTH bits, we are breaking packets into DATA_CHUNK_LENGTH bit chunks due to memory limitations
	//on the mega and possibly due to size limitations in the transmit function
	
	if (bits<=DATA_CHUNK_LENGTH) {
		//printf("bits<=%d, sending one chunk\n", DATA_CHUNK_LENGTH);
		transmit_chunk(bitOut?1:0, bitIn, bitOut, bits);
	}
	else 
	{
		for(i=0;i<(bits/DATA_CHUNK_LENGTH);i++) 
		{
			transmit_chunk(bitOut?1:0, bitIn+DATA_CHUNK_LENGTH*i, bitOut+DATA_CHUNK_LENGTH*i, DATA_CHUNK_LENGTH);
		}
		
		int tailOffset = DATA_CHUNK_LENGTH*(bits/DATA_CHUNK_LENGTH);
		int tailLength = bits%DATA_CHUNK_LENGTH;
		tailLength += (tailLength%8)?1:0; //round up
		
		if (!(bits%DATA_CHUNK_LENGTH==0))
			transmit_chunk(bitOut?1:0, bitIn+tailOffset, bitOut+tailOffset, tailLength);
	}
		
	return bits;
}

// Convert an array of characters each either zero or one to an array containing the binary equal
// output is stored in the same array as the input.
// EXAMPLE:
// input: char [] in = {0, 1, 1, 0, 0, 0, 1, 1};
// output: char [] out = {99, 1, 1, 0, 0, 0, 1, 1};
// BYTE INDICES: 76543210 (MSB first)
// Gives the index of a given bit within a byte.
// Equivelant to 7 - (x-BYTE_INDEX(x)*8)
#define BIT_INDEX(x) (7 - ((x) % 8))

// Gives the index of the byte which will hold bit x
#define BYTE_INDEX(x) ((x)/8)

// length is the size of the char [], same as number of meaningful bits represented by the char []
void Compress (int length, unsigned char * data)
{
    if (length <= 0 || data == 0)
    {
        return;
    }

    int i;

    for (i=0; (i+8)<length; i+=8)
    {
        data[BYTE_INDEX(i)] =
            (data[i+7]?0x01:0) |
            (data[i+6]?0x02:0) |
            (data[i+5]?0x04:0) |
            (data[i+4]?0x08:0) |
            (data[i+3]?0x10:0) |
            (data[i+2]?0x20:0) |
            (data[i+1]?0x40:0) |
            (data[i+0]?0x80:0);
    }

    unsigned char lastByte = 0;
    for (; i<length; i++)
    {
        lastByte |= data[i] ? (1<<BIT_INDEX(i)) : 0;
    }

    data[BYTE_INDEX(length-1)] = lastByte; // Set the last byte
}

// Undoes Compress
void Decompress (unsigned int length, unsigned char * data)
{
    unsigned int i = length-1;
    unsigned int MAX_UINT = (unsigned int)(-1);

    for(; i<MAX_UINT; i--)
    {
        data[i] = (data[BYTE_INDEX(i)] >> BIT_INDEX(i)) & 1;
    }
}

/*
 * 
 * name: transmit_chunk
 * @param receive wether to recieve data back from programmer
 * @param bitIn pointer to bit array to be transmitted (each bit is stored in a char)
 * @param bitOut pointer to bit array to store recieved information (each bit is stored in a char)
 * @param bits length of buffer 
 * @return bytes transfered
 */
static int transmit_chunk(char receive, char * bitIn, char * bitOut, int bits) 
{
	//printf("transmit_chunk(receive=%d, bitOut=%x, bitIn=%x, bits=%d)\n", receive, bitOut, bitIn, bits);

	int bytes = (bits+7)/8; //length of buffer once converted to byte array (squeezed/compressed)
	int dataLength = bytes + 2; // Tack on 2 bytes for the length, measured in bits
	
	Compress(bits, bitIn); // Squeeze all the bits together
	
	uchar * dataToSend = (uchar*)malloc(sizeof(uchar) * (dataLength));
	dataToSend[0]=(uchar)(bits);
	dataToSend[1]=(uchar)(bits>>8);
	
	int i;
	for (i= 0; i<bytes; i++)
	{
		dataToSend[i+2] = bitIn[i];
	}
	
	if(receive) 
	{
		//printf("Transfer and Receive\n");
		int retVal = SendData(usb_handle, FUNC_JTAG_GET_BIGTDO, dataToSend, dataLength, bitOut, bytes);
		
		// Expand out the bits sent to us from the device
		Decompress(bits, bitOut);
	}
	else
	{
		// Send the chunk of data out to be written to the device.  There's no response data we care about.
		//printf("Transfer Only: %d\n", dataLength);
		int retVal = SendData(usb_handle, FUNC_JTAG_SEND_TDI, dataToSend, dataLength, NULL, 0);
	}
	
	free (dataToSend);
	
	// Expand the bit array sent in (undo the compression we did earlier)
	Decompress(bits, bitIn);
	return 1;
}

#endif

static int set_signal(cable_t *cable, int trst)
{
	//~ printf("set_signal\n");
	uchar data[1];
	
	data[0]=(trst?1:0);

	SendData(usb_handle, FUNC_JTAG_SET_TRST, data, 1, NULL, 0);
	return 1;
}

#ifdef USE_GET_TRST
int get_signal(cable_t *cable)
{
	//~ printf("get_signal\n");
}
#endif

#ifdef USE_FLUSH
void flush(cable_t *cable, cable_fluch_amount_t how_much)
{
	//~ printf("flush\n");
}
#endif

static void usbcable_help(const char *cablename)
{
	printf( _(
		"Usage: cable %s\n"
		"\n"
		),
		cablename
		);
}

cable_driver_t usbasp_cable_driver = {
	"USBASP",
	N_("Oregon State University TekBots Universal Programmer"),
	connect,
	disconnect,
	this_cable_free,
	init,
	done,
	set_frequency,
	clock,
	get_tdo,
#ifdef USE_TRANSFER
	transfer,
#else
	generic_transfer,
#endif
	set_signal,
#ifdef USE_GET_TRST
	get_signal,
#else
	generic_get_signal,
#endif
#ifdef USE_FLUSH
	flush,
#else
	generic_flush_using_transfer,
#endif
	usbcable_help
};

usbconn_cable_t usbconn_cable_usbasp = {
		N_("usbasp"),						/* cable name */
		NULL,								/* string pattern, not used */
		N_("libusb"),						/* usbconn driver */ 
		USBDEV_VENDOR,								/* VID */
		USBDEV_PRODUCT								/* PID */
};

#else

static int
connect(char *params[], cable_t *cable)
{
	printf(_("Error: Cable connection failed, LibUSB not found"));
	return 1;
}


cable_driver_t usbasp_cable_driver = {
	_("USBASP"),
	N_("Oregon State University TekBots Universal Programmer"),
	connect,
	connect,
	connect,
	connect,
	connect,
	connect,
	connect,
	connect,
	connect,
	connect,
	connect,
	connect,
	usbcable_help
};

static void
usbcable_help(const char *cablename)
{
	printf( _(
		"Usage: cable %s\n"
		"LibUSB not found, please recompile with LibUSB\n"
		"\n"
		),
		cablename
		);
}

#endif
