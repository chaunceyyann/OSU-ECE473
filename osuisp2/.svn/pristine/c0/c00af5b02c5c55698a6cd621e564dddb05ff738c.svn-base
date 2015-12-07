
#include "usbhid.h"


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

int HidD_SetFeature(usbDevice_t *device, char *buffer, int len)
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

int HidD_GetFeature(usbDevice_t *device, char *buffer, int len)
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


/*! Send and Receive data over USB
 * @param device
 * @param command to send to the device
 * @param array of data to send
 * @param length of data to send
 * @param buffer to hold response
 * @param lengh of data expected
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
        return -1; // Error, size too great for a single transmission
    }

    if (outBufferLength > 250)
    {
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
        return -1; // Error: Couldn't transmit data
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
        return -1; // Error: Couldn't retrieve data
    }

    if (outBuffer!=NULL)
    {
        for (i=0; i<reportIn.reportSize; i++)
        {
            outBuffer[i] = reportIn.data[i];
        }
    }

    return reportIn.reportSize; // Return the number of bytes received
}

usbDevice_t  *openDevice(void)
{
    usbDevice_t     *dev = NULL;
    unsigned char   rawVid[2] = {USB_CFG_VENDOR_ID}, rawPid[2] = {USB_CFG_DEVICE_ID};
    char            vendorName[] = {USB_CFG_VENDOR_NAME, 0}, productName[] = {USB_CFG_DEVICE_NAME, 0};
    int             vid = rawVid[0] + 256 * rawVid[1];
    int             pid = rawPid[0] + 256 * rawPid[1];
    int             err;

    if((err = usbhidOpenDevice(&dev, vid, vendorName, pid, productName)) != 0){
        printf("error finding %s: %d\n", productName, err);
        return NULL;
    }

    return dev;
}
