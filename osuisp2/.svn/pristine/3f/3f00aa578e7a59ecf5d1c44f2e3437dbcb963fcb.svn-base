
/**
 @note To compile this file in a wxWidgets project in CodeBlocks,
 ensure that the compiler variable is set to CPP and not CC.
*/

#include "usb.h"

int UsbSendData(usbDevice_t *dev, uchar command, uchar * dataToSend, int length, uchar * outBuffer, int outBufferLength)
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
//        printf("Send size is too large for a single transmission!\n");
        return -1; // Error, size too great for a single transmission
    }

    if (outBufferLength > 250)
    {
//        printf("Reply size is too large for a single transmission!\n");
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
//        printf("Sending data failed!\n");
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
 //       printf("Receiving data failed!\n");
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

/** Helper function for UsbOpenDevice **/
static void convertUniToAscii(char *buffer)
{
    unsigned short  *uni = (unsigned short*)buffer;
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

int UsbOpenDevice(usbDevice_t **device, int vendor, char *vendorName, int product, char *productName)
{
    GUID                                hidGuid;        /// GUID for HID driver
    HDEVINFO                            deviceInfoList;
    SP_DEVICE_INTERFACE_DATA            deviceInfo;
    SP_DEVICE_INTERFACE_DETAIL_DATA     *deviceDetails = NULL;
    DWORD                               size;
    int                                 i, openFlag = 0;  /// may be FILE_FLAG_OVERLAPPED
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
            break;  /// no more entries
        /// first do a dummy call just to determine the actual size required
        SetupDiGetDeviceInterfaceDetail(deviceInfoList, &deviceInfo, NULL, 0, &size, NULL);
        if(deviceDetails != NULL)
            free(deviceDetails);
        deviceDetails = (SP_DEVICE_INTERFACE_DETAIL_DATA*)malloc(size);
        deviceDetails->cbSize = sizeof(*deviceDetails);
        /// this call is for real:
        SetupDiGetDeviceInterfaceDetail(deviceInfoList, &deviceInfo, deviceDetails, size, &size, NULL);
#if 0
        /// If we want to access a mouse our keyboard, we can only use feature
        // requests as the device is locked by Windows. It must be opened
        // with ACCESS_TYPE_NONE.
        //
        handle = CreateFile(deviceDetails->DevicePath, ACCESS_TYPE_NONE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, openFlag, NULL);
#endif
        /// attempt opening for R/W -- we don't care about devices which can't be accessed
        handle = CreateFile(deviceDetails->DevicePath, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, openFlag, NULL);
        if(handle == INVALID_HANDLE_VALUE){
            /// errorCode = USBOPEN_ERR_ACCESS; opening will always fail for mouse -- ignore
            continue;
        }
        deviceAttributes.Size = sizeof(deviceAttributes);
        HidD_GetAttributes(handle, &deviceAttributes);
        if(deviceAttributes.VendorID != vendor || deviceAttributes.ProductID != product)
            continue;   /// ignore this device
        errorCode = USBOPEN_ERR_NOTFOUND;
        if(vendorName != NULL && productName != NULL){
            char    buffer[512];
            if(!HidD_GetManufacturerString(handle, buffer, sizeof(buffer))){
                errorCode = USBOPEN_ERR_IO;
                continue;
            }
            convertUniToAscii(buffer);
            if(strcmp(vendorName, buffer) != 0)
                continue;
            if(!HidD_GetProductString(handle, buffer, sizeof(buffer))){
                errorCode = USBOPEN_ERR_IO;
                continue;
            }
            convertUniToAscii(buffer);
            if(strcmp(productName, buffer) != 0)
                continue;
        }
        break;  // we have found the device we are looking for!
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

void UsbCloseDevice(usbDevice_t * dev)
{
    if (dev!=NULL)
    {
        CloseHandle(dev);
        dev = NULL;
    }
}



