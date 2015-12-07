
#include <stdio.h>

/** USB Device identification parameters */
#define USB_CFG_VENDOR_ID       0xc0, 0x16
#define USB_CFG_DEVICE_ID       0xdf, 0x05
#define USB_CFG_VENDOR_NAME     'b', 'e', 'a', 'v', 'e', 'r', 's', 'o', 'u', 'r', 'c', 'e', '.', 'o', 'r', 'e', 'g', 'o', 'n', 's', 't', 'a', 't', 'e', '.', 'e', 'd', 'u', '/', 'p', 'r', 'o', 'j', 'e', 'c', 't', 's', '/', 'o', 's', 'u', 'i', 's', 'p', '2'
#define USB_CFG_DEVICE_NAME     'O', 'S', 'U', 'i', 's', 'p', '2'

/** Typedef usbDevice_t for use with Windows or Linux/Mac */
typedef struct usbDevice    usbDevice_t;

typedef struct ReportOut
{
    unsigned char reportID;
    unsigned char reportSize;
    unsigned char command;
    unsigned char data [248];
} ReportOut_t;


typedef struct ReportIn
{
    unsigned char reportID;
    unsigned char reportSize;
    unsigned char data [249];
} ReportIn_t;


usbDevice_t *openDevice(void);

/** Convenience typedef for unsigned 8 bit value
 * Might consider using uint8_t in the future...
 */
typedef unsigned char uchar;

/** USB Error Codes */
#define USBOPEN_SUCCESS         0   /* no error */
#define USBOPEN_ERR_ACCESS      1   /* not enough permissions to open device */
#define USBOPEN_ERR_IO          2   /* I/O error */
#define USBOPEN_ERR_NOTFOUND    3   /* device not found */

#if defined(WIN32)
    /** Windows includes for hid interface */
    #include <windows.h>
    #include <setupapi.h>
    #include <ddk\hidsdi.h>
    #include <ddk\hidpi.h>
#else
    /** libusb specific items **/
    #include <string.h>
    #include <usb.h>
    #define usbDevice   usb_dev_handle  /* use libusb's device structure */
    #define USBRQ_HID_GET_REPORT    0x01
    #define USBRQ_HID_SET_REPORT    0x09
    #define USB_HID_REPORT_TYPE_FEATURE 3
#endif

int usbhidOpenDevice(usbDevice_t **device, int vendor, char *vendorName, int product, char *productName);

void usbhidCloseDevice(usbDevice_t *device);

/*! Send and Receive data over USB
 * @param device
 * @param command to send to the device
 * @param array of data to send
 * @param length of data to send
 * @param buffer to hold response (8 characters)
 * @param lengh of data expected
 */
int SendData(usbDevice_t *dev, uchar command, uchar * dataToSend, int length, uchar * outBuffer, int outBufferLength);
