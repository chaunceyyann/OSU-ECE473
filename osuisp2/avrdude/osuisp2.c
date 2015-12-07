/*
 * avrdude - A Downloader/Uploader for AVR device programmers
 * Copyright (C) 2006  Thomas Fischl
 * Copyright 2007 Joerg Wunsch <j@uriah.heep.sax.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* $Id: osuisp2.c 1 2010-07-13 18:33:23Z porterbe $ */

/**
 * @file osuisp2.c
 * @brief Interface to the OSUisp2 programmer.
 *
 * Adapted from USBasp code written by Thomas Fischl,
 * Modified to use a generic HID interface class for
 * USB communication to avoid driver installation.
 * The OSUisp2 programmer will work on Windows based
 * machines without any external drivers.  For other
 * operating systems, libusb can be used.
 *
 * @author Ben Porter
 * @date Summer 2010
 *
 * @note See http://beaversource.oregonstate.edu/projects/osuisp2
 * TODO: Finish code documentation, fix tab format (2 space tabs),
 * TEST, TEST, TEST!!!
 */

#include "ac_cfg.h"
#include "osuisp2.h"

#ifdef WIN32
#define OSUISP2_OK_TO_BUILD
#else
#ifdef HAVE_LIBUSB
#define OSUISP2_OK_TO_BUILD
#endif
#endif

/** Compile guard to prevent build of osuisp2 without usb communication abilities **/
#ifdef OSUISP2_OK_TO_BUILD

#define PDATA(pgm) ((struct pdata *)(pgm->cookie))



/**************************** USB COMMUNICATION CODE *****************************/
/*********************************************************************************/
//{*******************************************************************************/


/* Original code was from hiddata.c, in the hid-data example for V-USB
 * Original Author: Christian Starkjohann
 * Adapted By: Ben Porter
 * Original Creation Date: 2008-04-11
 * Adaptation Date: Summer 2010
 * Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2, GNU GPL v3
 */


/* ######################################################################## */
#if defined(WIN32) /* ## WIN32 HID USB COMMUNICATION VERSION ############## */
/* ######################################################################## */

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
        /* attempt opening for R/W -- we don't care about devices which can't be accessed */
        handle = CreateFile(deviceDetails->DevicePath, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, openFlag, NULL);
        if(handle == INVALID_HANDLE_VALUE){
            //DEBUG_PRINT(("opening failed: %d\n", (int)GetLastError()));
            /* errorCode = USBOPEN_ERR_ACCESS; opening will always fail for mouse -- ignore */
            continue;
        }
        deviceAttributes.Size = sizeof(deviceAttributes);
        HidD_GetAttributes(handle, &deviceAttributes);
        //DEBUG_PRINT(("device attributes: vid=%d pid=%d\n", deviceAttributes.VendorID, deviceAttributes.ProductID));
        if(deviceAttributes.VendorID != vendor || deviceAttributes.ProductID != product)
            continue;   /* ignore this device */
        errorCode = USBOPEN_ERR_NOTFOUND;
        if(vendorName != NULL && productName != NULL){
            char    buffer[512];
            if(!HidD_GetManufacturerString(handle, buffer, sizeof(buffer))){
                //DEBUG_PRINT(("error obtaining vendor name\n"));
                errorCode = USBOPEN_ERR_IO;
                continue;
            }
            convertUniToAscii(buffer);
            //DEBUG_PRINT(("vendorName = \"%s\"\n", buffer));
            if(strcmp(vendorName, buffer) != 0)
                continue;
            if(!HidD_GetProductString(handle, buffer, sizeof(buffer))){
                //DEBUG_PRINT(("error obtaining product name\n"));
                errorCode = USBOPEN_ERR_IO;
                continue;
            }
            convertUniToAscii(buffer);
            //DEBUG_PRINT(("productName = \"%s\"\n", buffer));
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
        errorCode = 0;
    }
    return errorCode;
}

void usbhidCloseDevice(usbDevice_t *device)
{
    CloseHandle((HANDLE)device);
}

int usbhidSetReport(usbDevice_t *device, char *buffer, int len)
{
	BOOLEAN rval;

    rval = HidD_SetFeature((HANDLE)device, buffer, len);
    return rval == 0 ? USBOPEN_ERR_IO : 0;
}

int usbhidGetReport(usbDevice_t *device, char *buffer, int len)
{
	BOOLEAN rval = 0;

//    buffer[0] = reportNumber;
    rval = HidD_GetFeature((HANDLE)device, buffer, len);
    return rval == 0 ? USBOPEN_ERR_IO : 0;
}


/* ------------------------------------------------------------------------ */
/* ######################################################################## */
#else /* defined WIN32 #### Linux/LibUSB Implementation ################### */
/* ######################################################################## */

static int usbhidGetStringAscii(usb_dev_handle *dev, int index, char *buf, int buflen)
{
	char    buffer[256];
	int     rval, i;

    if((rval = usb_get_string_simple(dev, index, buf, buflen)) >= 0) /* use libusb version if it works */
        return rval;
    if((rval = usb_control_msg(dev, USB_ENDPOINT_IN, USB_REQ_GET_DESCRIPTOR, (USB_DT_STRING << 8) + index, 0x0409, buffer, sizeof(buffer), 5000)) < 0)
        return rval;
    if(buffer[1] != USB_DT_STRING){
        *buf = 0;
        return 0;
    }
    if((unsigned char)buffer[0] < rval)
        rval = (unsigned char)buffer[0];
    rval /= 2;
    /* lossy conversion to ISO Latin1: */
    for(i=1;i<rval;i++){
        if(i > buflen)              /* destination buffer overflow */
            break;
        buf[i-1] = buffer[2 * i];
        if(buffer[2 * i + 1] != 0)  /* outside of ISO Latin1 range */
            buf[i-1] = '?';
    }
    buf[i-1] = 0;
    return i-1;
}

int usbhidOpenDevice(usbDevice_t **device, int vendor, char *vendorName, int product, char *productName)
{
    printf("Opening device...\n");
	struct usb_bus      *bus;
	struct usb_device   *dev;
	usb_dev_handle      *handle = NULL;
	int                 errorCode = USBOPEN_ERR_NOTFOUND;
	static int          didUsbInit = 0;

    if(!didUsbInit){
        usb_init();
        didUsbInit = 1;
    }
    printf("Busses = %d\n", usb_find_busses());
    printf("Devices = %d\n", usb_find_devices());
    for(bus=usb_get_busses(); bus; bus=bus->next){
        printf("bus...\n");
        for(dev=bus->devices; dev; dev=dev->next){
            printf("dev...\n");
            if(dev->descriptor.idVendor == vendor && dev->descriptor.idProduct == product){
		printf("Device with matching ID's found!\n");
                char    string[256];
                int     len;
                handle = usb_open(dev); /* we need to open the device in order to query strings */
                if(!handle){
                    errorCode = USBOPEN_ERR_ACCESS;
                    fprintf(stderr, "Warning: cannot open USB device: %s\n", usb_strerror());
                    continue;
                }
                if(vendorName == NULL && productName == NULL){  /* name does not matter */
                    break;
                }
                /* now check whether the names match: */
                len = usbhidGetStringAscii(handle, dev->descriptor.iManufacturer, string, sizeof(string));
                if(len < 0){
                    errorCode = USBOPEN_ERR_IO;
                    fprintf(stderr, "Warning: cannot query manufacturer for device: %s\n", usb_strerror());
                }else{
                    errorCode = USBOPEN_ERR_NOTFOUND;
                    /* fprintf(stderr, "seen device from vendor ->%s<-\n", string); */
                    if(strcmp(string, vendorName) == 0){
                        len = usbhidGetStringAscii(handle, dev->descriptor.iProduct, string, sizeof(string));
                        if(len < 0){
                            errorCode = USBOPEN_ERR_IO;
                            fprintf(stderr, "Warning: cannot query product for device: %s\n", usb_strerror());
                        }else{
                            errorCode = USBOPEN_ERR_NOTFOUND;
                            /* fprintf(stderr, "seen product ->%s<-\n", string); */
                            if(strcmp(string, productName) == 0)
                                break;
                        }
                    }
                }
                usb_close(handle);
                handle = NULL;
            }
        }
        if(handle)
            break;
    }
    if(handle != NULL){
        errorCode = 0;
        *device = (void *)handle;
    }
    return errorCode;
}

void usbhidCloseDevice(usbDevice_t *device)
{
    if(device != NULL)
        usb_close((void *)device);
}

int usbhidSetReport(usbDevice_t *device, char *buffer, int len)
{
	int bytesSent;

    bytesSent = usb_control_msg((void *)device, USB_TYPE_CLASS | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, USBRQ_HID_SET_REPORT, USB_HID_REPORT_TYPE_FEATURE << 8 | (buffer[0] & 0xff), 0, buffer, len, 5000);
    if(bytesSent != len){
        if(bytesSent < 0)
            fprintf(stderr, "Error sending message: %s\n", usb_strerror());
        return USBOPEN_ERR_IO;
    }
    return 0;
}

int usbhidGetReport(usbDevice_t *device, char *buffer, int len)
{
	int bytesReceived, maxLen = len;
    char reportNumber = buffer[0]; // Report number is the first character
    bytesReceived = usb_control_msg((void *)device, USB_TYPE_CLASS | USB_RECIP_DEVICE | USB_ENDPOINT_IN, USBRQ_HID_GET_REPORT, USB_HID_REPORT_TYPE_FEATURE << 8 | reportNumber, 0, buffer, maxLen, 5000);
    if(bytesReceived < 0)
	{
        fprintf(stderr, "Error sending message: %s\n", usb_strerror());
        return USBOPEN_ERR_IO;
    }
    //len = bytesReceived;

    return 0;
}

/* ######################################################################## */
#endif /* defined WIN32 ################################################### */
/* ######################################################################## */


//}*******************************************************************************/
/*********************************************************************************/
/*********************************************************************************/


/**
 * Setup private data for the programmer
 * This must be called before any other function
 * @param pgm Programmer for which to setup data
 */
static void osuisp2_setup(PROGRAMMER * pgm)
{
  if ((pgm->cookie = malloc(sizeof(struct pdata))) == 0)
  {
    fprintf(stderr,
	    "%s: osusip2_setup(): Out of memory allocating private data\n",
	    progname);
    exit(1);
  }
  memset(pgm->cookie, 0, sizeof(struct pdata));
}

/**
 * Free private data for the programmer
 * Call this only when the programmer is no longer needed
 * @param pgm Programmer to free
 */
static void osuisp2_teardown(PROGRAMMER * pgm)
{
  free(pgm->cookie);
}

/*! Send and Receive data over USB
 * @param device Handle to USB OSUisp2 device
 * @param command to send to the device
 * @param array of data to send
 * @param length of data to send
 * @param buffer to hold response
 * @param lengh of data expected
 * @return length of data received, or < 0 on error
 */
int SendData(usbDevice_t *dev, uchar command, uchar * dataToSend, int length, uchar * outBuffer, int outBufferLength)
{
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
    //printf("Send size is too large for a single transmission!\n");
    return -1; // Error, size too great for a single transmission
  }

  if (outBufferLength > 249)
  {
    //printf("Reply size is too large for a single transmission!\n");
    return -1;
  }

  // Copy the data to the transmit buffer
  int i;
  for (i=0; i<reportOut.reportSize; i++)
  {
    reportOut.data[i] = dataToSend[i];
  }

  // Send out the data
  if (usbhidSetReport(dev, (char*)&reportOut, sizeof(ReportOut_t)) != 0)
  {
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
  else if (outBufferLength <= 249)
  {
    reportIn.reportID = 3;
  }

  if (usbhidGetReport(dev, (char*)&reportIn, sizeof(ReportIn_t)) != 0)
  {
    printf("Receiving data failed!\n");
    return -1;
  }

  if (outBuffer!=NULL)
  {
    for (i=0; i<reportIn.reportSize; i++)
    {
        outBuffer[i] = reportIn.data[i];
    }
  }

  return reportIn.reportSize; // The return code should be held in this value
}

/** Connect ISP to the target device
 * Clock speed is related to the clockOption
 * @param Usb device pointer
 * @param Frequency Index
 * @return Set Frequency value
 */
int ProgIspConnect(usbDevice_t *dev, char clockOption)
{
  uchar data[2] = {clockOption, 1};
  uchar response[1];
  SendData(dev, SPI_PROG_CONNECT, data, 2, response, 1);
  return response[0];
}

/** Tranceive 4 bytes to/from the target
 * @param dev Handle to USB OSUisp2 device
 * @param bytesIn Four bytes to send to the target
 * @param bytesOut Four bytes to receive from the target
 */
int ProgIspTransmit(usbDevice_t *dev, uchar * bytesIn, uchar * bytesOut)
{
  uchar dataToSend[5] = {0, bytesIn[0], bytesIn[1], bytesIn[2], bytesIn[3]};
  int ret = SendData(dev, SPI_PROG_TRANSMIT, dataToSend, 5, bytesOut, 4);
  return ret;
}

/** Read a chunk of memory starting at the specified address
 * @param dev Handle to USB OSUisp2 device
 * @param The type of memory to read (MEM_EEPROM or MEM_FLASH)
 * @param Address at which to begin reading data
 * @param Pointer to an allocated array of at least size (length)
 * @param Number of bytes to read (maximum 249)
 * @return The number of bytes read
 */
int ProgIspReadMemory(usbDevice_t *dev, uchar memoryType, unsigned int address, uchar * bytesOut, int length)
{
    //printf("Reading Memory\n");
    uchar send[6] = {0xFF & address,
                     0xFF & (address >> 8),
                     0xFF & (address >> 16),
                     0xFF & (address >> 24),
                     0xFF & length ,
                     memoryType};
    return SendData(dev, SPI_PROG_READMEMORY, send, 6, bytesOut, length);
}

/** Enable ISP programming
 @param dev USB handle to the OSUisp2 programmer
 @return zero if successful, nonzero if failure
 */
int ProgIspEnableProgramming(usbDevice_t *dev)
{
//  uchar t[2] = {0, 0};
  uchar receive[1];
  SendData (dev, SPI_PROG_ENABLEPROG, NULL, 0, receive, 1);
  return receive[0];
}

/** Write to memory
 @param dev USB handle to the OSUisp2 programmer
 @param MEM_FLASH or MEM_EEPROM
 @param address at which to begin writing memory
 @param page size for writing  (unused for EEPROM writes)
 @param data array to be written
 @param number of bytes to write
 @param flags
 */
int ProgIspWriteMemory(usbDevice_t *dev, uchar memoryType, int address, int pageSize, uchar * data, uchar bytes, uchar flags)
{
    int size = bytes;

    size+=9;
    unsigned char * send;
    send = (unsigned char*)malloc(size);
    if (send==0)
    {
        //printf("Malloc failed!\n\n\n");
        return -1;
    }
    send[0] = 0xFF & address;
    send[1] = 0xFF & (address>>8);
    send[2] = 0xFF & (address>>16);
    send[3] = 0xFF & (address>>24);

    send[4] = 0xFF & pageSize;
    send[5] = 0xFF & (pageSize >> 8);

    send[6] = bytes;
    send[7] = memoryType;
    send[8] = flags;

    int i;
    for (i=0; i<bytes; i++)
    {
        send[i+9] = data[i];
    }

    uchar bytesWritten;
    SendData (dev, SPI_PROG_WRITEMEMORY, send, bytes+9, &bytesWritten, 1);

    free ((void *)send);
    return bytesWritten;
}

/**
 * Open the OSUisp2 USB Device handle
 * @param pgm Programmer to open the usb device handle.
 * @param port unused
 * @return 0 on success, terminates program on failure (might be a better way to do this...)
*/
static int osuisp2_open(PROGRAMMER * pgm, char * port)
{
  int retValue = usbhidOpenDevice(
    &PDATA(pgm)->usbhandle,
    OSUISP2_VENDOR_ID,
    OSUISP2_VENDOR_NAME,
    OSUISP2_PRODUCT_ID,
    OSUISP2_PRODUCT_NAME);

  if (retValue!=0)
  {
    // Device not found
    fprintf(
      stderr,
      "%s: error: Could not find USB programmer '%s'.  Is the programmer plugged in?",
      progname, OSUISP2_PRODUCT_NAME);

    exit(1); // Is this the best way to indicate an opening error?
  }
  return 0;
}

/**
 * Disconnect the device from the target,
 * then disconnect the device and close the
 * handle.
 * @param pgm Programmer to close
 */
static void osuisp2_close(PROGRAMMER * pgm)
{
  // Disconnect from target device
  SendData(PDATA(pgm)->usbhandle, SPI_PROG_DISCONNECT, NULL, 0, NULL, 1);

  // Close the USB handle
  usbhidCloseDevice(PDATA(pgm)->usbhandle);
}

/**
 * Initialize the programmer by determining a clock speed
 * and connecting to the target device
 * @param pgm Programmer to initialize
 * @param p avr part to be connected (unused?)
 */
static int osuisp2_initialize(PROGRAMMER * pgm, AVRPART * p)
{
    /* set sck period */
    pgm->set_sck_period(pgm, pgm->bitclock);

    /* Issue connect to target command */
    ProgIspConnect(PDATA(pgm)->usbhandle, PDATA(pgm)->clockOption);

    /* wait, so device is ready to receive commands */
    usleep(100000);

    return pgm->program_enable(pgm, p);
}

static void osuisp2_disable(PROGRAMMER * pgm)
{
  /* Intentionally empty */
  return;
}

static void osuisp2_enable(PROGRAMMER * pgm)
{
  /* Intentionally empty */
  return;
}

static void osuisp2_display(PROGRAMMER * pgm, const char * p)
{
  /* Intentionally empty */
  return;
}

/**
 * Transmit and receive four bytes through the device to the target
 * @param pgm programmer for tranceiving
 * @param command four bytes to send
 * @param reply four byte reply from target
 * @return 0 on success, < 0 on failure
 */
static int osuisp2_cmd(PROGRAMMER * pgm, unsigned char command[4], unsigned char reply[4])
{
  int num_bytes = ProgIspTransmit (PDATA(pgm)->usbhandle, command, reply);

  if(num_bytes != 4)
  {
    fprintf(stderr, "%s: error: unexpected response size was %d\n",
    progname, num_bytes);
    return -1;
  }

  return 0;
}

/**
 * AVRDUDE calls this to enable target programming.
 * @return 0 on success, non-zero otherwise
 */
static int osuisp2_program_enable(PROGRAMMER * pgm, AVRPART * p)
{
  int response = ProgIspEnableProgramming (PDATA(pgm)->usbhandle);

  if (response!=0)
  {
    fprintf(stderr, "%s: error: program enable: target doesn't answer, code %d\n", progname, response);
    return -1;
  }

  return 0;
}

/**
 * AVRDUDE calls this to send the chip erase command
 * @return 0n on success, non-zero otherwise
 */
static int osuisp2_chip_erase(PROGRAMMER * pgm, AVRPART * p)
{
  unsigned char command[4];
  unsigned char reply[4];

  if (p->op[AVR_OP_CHIP_ERASE] == NULL)
  {
    fprintf(stderr, "chip erase instruction not defined for part \"%s\"\n", p->desc);
    return -1;
  }

  memset(command, 0, sizeof(command));

  avr_set_bits(p->op[AVR_OP_CHIP_ERASE], command);
  pgm->cmd(pgm, command, reply);
  usleep(p->chip_erase_delay);
  pgm->initialize(pgm, p);

  return 0;
}

/**
 * Compute a block size for serial transfer depending on serial clock frequency
 * The block size must be smaller for lower frequencies, because each block
 * transfer will take longer - and the maximum transfer time per block must be
 * less than the usb timeout.
 */
int GetBlockSize (PROGRAMMER * pgm)
{
    double frequency = 0;

    switch (PDATA(pgm)->clockOption)
    {
        case 1:
            frequency = 1500000;
            break;
        case 2:
            frequency = 750000;
            break;
        case 3:
            frequency = 375000;
            break;
        case 4:
            frequency = 185000;
            break;
        case 5:
            frequency = 93750;
            break;

        default:
        {
            unsigned long period_us = (PDATA(pgm)->clockOption-5)*20;
            frequency = (int)(1000000.0f / period_us);
            break;
        }

    }

    // Set the block size such that the raw data transfer
    // to the device over ISP is no longer than 250 ms
    // The usb communication will time out after 5 seconds,
    // so 250 ms + whatever time the usb requires (a few ms)
    // will be less than the usb timeout
    double blocksize_d = frequency * 0.0125; // (max_time / 8 bits) = 0.0125

    if (blocksize_d > ISP_PROG_MAX_SIZE) // Max block size of 240
        blocksize_d = ISP_PROG_MAX_SIZE;

    if (blocksize_d < 6) // Minimum block size of 6
        blocksize_d = 6;

    return (int)blocksize_d;
}

/**
 * AVRDUDE calls this to perform a paged load (read from target)
 * of flash or eeprom memory.
 * @return number of bytes read, or < 0 on failure
 */
static int osuisp2_paged_load(PROGRAMMER * pgm, AVRPART * p, AVRMEM * m,
                             int page_size, int n_bytes)
{
    int n;
    int address = 0;
    int wbytes = n_bytes;
    int blocksize;
    unsigned char * buffer = m->buf;

    uchar memoryType;

    if (strcmp(m->desc, "flash") == 0)
    {
        memoryType = MEM_FLASH;
    }
    else if (strcmp(m->desc, "eeprom") == 0)
    {
        memoryType = MEM_EEPROM;
    }
    else
    {
        return -2;
    }

    // Obtain a reasonable block size
    blocksize = GetBlockSize (pgm);

    while (wbytes)
    {
        if (wbytes <= blocksize)
        {
            blocksize = wbytes;
        }

        wbytes -= blocksize;


        n = ProgIspReadMemory(PDATA(pgm)->usbhandle, memoryType, address, buffer, blocksize);

        if (n != blocksize)
        {
            fprintf(stderr, "%s: error: wrong reading bytes %x\n",
            progname, n);
            exit(1);
        }

        buffer += blocksize;
        address += blocksize;

        report_progress (address, n_bytes, NULL);
    }

    return n_bytes;
}

/**
 * AVRDUDE calls this to write a page of data to the target.
 * @return number of bytes written, or < 0 on failure
 */
static int osuisp2_paged_write(PROGRAMMER * pgm, AVRPART * p, AVRMEM * m,
                              int page_size, int n_bytes)
{
    int n;
    int address = 0;
    int wbytes = n_bytes;
    int blocksize;
    unsigned char * buffer = m->buf;
    unsigned char blockflags = OSUISP2_BLOCKFLAG_FIRST;
    uchar memoryType;

    if (strcmp(m->desc, "flash") == 0)
    {
        memoryType = MEM_FLASH;
    }
    else if (strcmp(m->desc, "eeprom") == 0)
    {
        memoryType = MEM_FLASH;
    }
    else
    {
        return -2;
    }

    /* set blocksize depending on sck frequency */
    blocksize = GetBlockSize (pgm);

    while (wbytes)
    {
        if (wbytes <= blocksize)
        {
            blocksize = wbytes;
            blockflags |= OSUISP2_BLOCKFLAG_LAST;
        }
        wbytes -= blocksize;

        n = ProgIspWriteMemory(PDATA(pgm)->usbhandle, memoryType, address, page_size, buffer, blocksize, blockflags);

        blockflags = 0;

        if (n != blocksize)
        {
            fprintf(stderr, "%s: error: wrong count at writing %d\n",
            progname, n);
            exit(1);
        }

        buffer += blocksize;
        address += blocksize;

        report_progress (address, n_bytes, NULL);
    }

    return n_bytes;
}

/**
 * Called to set the serial clock period to sckperiod
 * For the OSUisp2 programmer, there are 5 hardware SPI
 * modes from 93.75 Khz to 1.5Mhz.  Slower clock speeds
 * are obtained through software SPI emulation.  The
 * algorithm below determines whether to use a HW SPI
 * mode (clockOption 1-5), or calculates a delay value
 * for the software SPI mode (6-255).
 * The software SPI delay period can be calculated as
 * (clockOption - 5) * 20 uS
 */
static int osuisp2_set_sck_period(PROGRAMMER *pgm, double sckperiod)
{
    unsigned long frequency = (int)(1.0/sckperiod);
    if (frequency > 50000)
    {
        PDATA(pgm)->clockOption = 5; // 93,750 Khz
        if (frequency > 93750)
            PDATA(pgm)->clockOption = 4; //18,750 Khz
        if (frequency > 185000)
            PDATA(pgm)->clockOption = 3; // 375,000 Khz
        if (frequency > 375000)
            PDATA(pgm)->clockOption = 2; // 750,000 Khz
        if (frequency > 750000)
            PDATA(pgm)->clockOption = 1; // 1,500,000 Khz

    }
    else
    {
        // 6 is delay 20 us,
        // 7 is 40 us,
        // 8 is 60 us, and so forth
        PDATA(pgm)->clockOption = (int)(sckperiod*50001) + 5;
    }

    return 0;
}

/**
 * AVRDUDE calls this to setup function pointers
 */
void osuisp2_initpgm(PROGRAMMER * pgm)
{
  strcpy(pgm->type, "OSUisp2");

  /*
   * mandatory functions
   */

  pgm->initialize     = osuisp2_initialize;
  pgm->display        = osuisp2_display;
  pgm->enable         = osuisp2_enable;
  pgm->disable        = osuisp2_disable;
  pgm->program_enable = osuisp2_program_enable;
  pgm->chip_erase     = osuisp2_chip_erase;
  pgm->cmd            = osuisp2_cmd;
  pgm->open           = osuisp2_open;
  pgm->close          = osuisp2_close;
  pgm->read_byte      = avr_read_byte_default;
  pgm->write_byte     = avr_write_byte_default;

  /*
   * optional functions
   */

  pgm->paged_write = osuisp2_paged_write;
  pgm->paged_load = osuisp2_paged_load;
  pgm->setup          = osuisp2_setup;
  pgm->teardown       = osuisp2_teardown;
  pgm->set_sck_period	= osuisp2_set_sck_period;

}

#else /* OSUISP2_OK_TO_BUILD */

static int osuisp2_nousb_open (struct programmer_t *pgm, char * name)
{
  fprintf(stderr, "%s: error: libusb not available, please install libusb and configure/compile again.\n",
	  progname);
  exit(1);
}

void osuisp2_initpgm(PROGRAMMER * pgm)
{
  strcpy(pgm->type, "OSUisp2");
  pgm->open = osuisp2_nousb_open;
}

#endif /* OSUISP2_OK_TO_BUILD */

