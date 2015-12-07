


#ifndef _USB_H
#define _USB_H


#include <windows.h>
#include <setupapi.h>
#include <ddk\hidsdi.h>
#include <ddk\hidpi.h>
#include <ddk\hidusage.h>

#define USBOPEN_SUCCESS         0   /* no error */
#define USBOPEN_ERR_ACCESS      1   /* not enough permissions to open device */
#define USBOPEN_ERR_IO          2   /* I/O error */
#define USBOPEN_ERR_NOTFOUND    3   /* device not found */

/// Windows usb device type
typedef struct usbDevice usbDevice_t;

#ifndef uchar
typedef unsigned char uchar;
#endif



/** Output Report Structure **/
typedef struct ReportOut
{
    unsigned char reportID;
    unsigned char reportSize;
    unsigned char command;
    unsigned char data [248];
} ReportOut_t;

/** Input Report Structure **/
typedef struct ReportIn
{
    unsigned char reportID;
    unsigned char reportSize;
    unsigned char data [249];
} ReportIn_t;

/** Send and Receive data over USB (Windows)
 * @param device
 * @param command to send to the device
 * @param array of data to send
 * @param length of data to send
 * @param buffer to hold response (8 characters)
 * @param lengh of data expected
 * @return length of data received
 */
int UsbSendData(usbDevice_t *dev, uchar command, uchar * dataToSend, int length, uchar * outBuffer, int outBufferLength);

int UsbOpenDevice(usbDevice_t **device, int vendor, char *vendorName, int product, char *productName);

void UsbCloseDevice (usbDevice_t * dev);


#endif

