

#include "Tiny26Interface.h"

#include "usb.h"

// Constructor
USBDevice::USBDevice()
{
    dev = NULL;
}
// Destructor: Disconnect and close
USBDevice::~USBDevice()
{
    Disconnect();
}

int USBDevice::Connect()
{
    //dev = UsbOpenDevice();
    if (UsbOpenDevice(&dev, 0x16c0, "beaversource.oregonstate.edu/projects/osuisp2", 0x05df, "OSUisp2"))
    {
        return -2;
    }
    if (dev==NULL)
        return -3;

    // Set clock speed
    /*reportOut.reportID = 1;
    reportOut.reportSize = 1;
    reportOut.command = 10;
    reportOut.data[0] = 5; // Clock Speed Index (higher for faster serial clock)
    if (!HidD_SetFeature(dev, (void*)&reportOut, sizeof(ReportOut_t)))
    {
        Disconnect();
        return -1;
    }
    reportIn.reportID = 1;
    if (!HidD_GetFeature(dev, (void*)&reportIn, sizeof(ReportIn_t)))
    {
        Disconnect();
        return -1;
    }
    if (reportIn.reportSize!=1 || reportIn.data[0] !=0)
    {
        Disconnect();
        return -1;
    }*/

    // Connect with the slowest clock option and do not maintain target device reset state
    uchar dataToSend[2] = {8, 0}; // Clock option = 8, maintainReset = false
    if (UsbSendData(dev, 1, dataToSend, 2, NULL, 0)!=1)
    {
        Disconnect();
        return -4;
    }

    // Initialize ISP
    /*reportOut.reportID = 1;
    reportOut.reportSize = 0;
    reportOut.command = 13;
    if (!HidD_SetFeature(dev, (void*)&reportOut, sizeof(ReportOut_t)))
    {
        Disconnect();
        return -1;
    }
    reportIn.reportID = 1;
    if (!HidD_GetFeature(dev, (void*)&reportIn, sizeof(ReportIn_t)))
    {
        Disconnect();
        return -1;
    }
    if (reportIn.reportSize!=1 || reportIn.data[0] !=0)
    {
        Disconnect();
        return -1;
    }*/

    // Wait for device to start up
    Sleep(100);

    uchar testData [7] = {1, 0, 0, 0, 0, 0, 0};
    uchar reply[6];
    if (UsbSendData(dev, 3, testData, 7, reply, 6)!=6)
    {
        Disconnect();
        return -5;
    }

    /*
    // Send some test data
    reportOut.reportID = 1;
    reportOut.reportSize = 6;
    reportOut.command = 12;

    reportOut.data[0] = 0;
    reportOut.data[1] = 0;
    reportOut.data[2] = 0;
    reportOut.data[3] = 0;
    reportOut.data[4] = 0;
    reportOut.data[5] = 0;

    if (!HidD_SetFeature(dev, (void*)&reportOut, sizeof(ReportOut_t)))
    {
        Disconnect();
        return -1;
    }

    reportIn.reportID = 1;
    if (!HidD_GetFeature(dev, (void*)&reportIn, sizeof(ReportIn_t)))
    {
        Disconnect();
        return -1;
    }
    */

    if (reply[0] !=0xA9)
    {
        Disconnect();
        return -6;
    }
    return 0;

}

int USBDevice::Disconnect()
{
    // Disconnect from the target device
    if (dev!=NULL)
    {
        // Issue disconnect command, ignore errors
        UsbSendData(dev, 2, NULL, 0, NULL, 0);
        UsbCloseDevice(dev);
    }

    dev = NULL;
    return 0;
}

int USBDevice::GetSetPortA (Port &port)
{
    return GetSetPort(port, 0x70); // 0x70 for PORTA
    //unsigned char buffer [5];
    //int ret = Send(0x70, port.DDR, port.DDR_Mask, port.PORT, port.PORT_Mask, 0, buffer);
    //port.PIN = buffer[1];
    //port.PORT = buffer[2];
    //port.DDR = buffer[3];
    //return ret;
}
int USBDevice::GetSetPortB (Port &port)
{
    return GetSetPort(port, 0x71); // 0x71 for PORTB
}
int USBDevice::GetSetPort (Port &port, unsigned char command)
{
    unsigned char buffer [5];
    int ret = Send(command, port.DDR, port.DDR_Mask, port.PORT, port.PORT_Mask, 0, buffer);
    port.PIN = buffer[1];
    port.PORT = buffer[2];
    port.DDR = buffer[3];
    return ret;
}



int USBDevice::Get_PINA_PORTA_DDRA(OUT uchar &PINA, OUT uchar &PORTA, OUT uchar &DDRA)
{
    unsigned char buffer[5];
    int ret = Send(0x70, 0, 0, 0, 0, 0, buffer);
    PINA = buffer[1];
    PORTA = buffer[2];
    DDRA = buffer[3];
    return ret;
}

int USBDevice::Get_PINB_PORTB_DDRB(OUT uchar &PINB, OUT uchar &PORTB, OUT uchar &DDRB)
{
    unsigned char buffer[5];
    int ret = Send(0x71, 0, 0, 0, 0, 0, buffer);
    PINB = buffer[1];
    PORTB = buffer[2];
    DDRB = buffer[3];
    return ret;
}

int USBDevice::Get_ADC(uchar adcNumber, OUT uchar &adcValue)
{
    unsigned char buffer[5];
    int ret = Send(0xAA, adcNumber, 0, 0, 0, 0, buffer);
    adcValue = buffer[4];
    return ret;
}

int USBDevice::Set_Timers(uchar TCCR1A, uchar TCCR1B, uchar OCR1B, uchar OCR1C, OUT uchar &TCNT1)
{
    unsigned char buffer[5];
    int ret = Send(0x60, TCCR1A, TCCR1B, OCR1B, OCR1C, 0, buffer);
    TCNT1 = buffer[1];
    return ret;
}

int USBDevice::Set_DDRA_PORTA(uchar DDRA, uchar DDRA_Mask, uchar PORTA, uchar PORTA_Mask)
{
    return Send (0x70, DDRA, DDRA_Mask, PORTA, PORTA_Mask, 0, NULL);
}

int USBDevice::Set_DDRB_PORTB(uchar DDRB, uchar DDRB_Mask, uchar PORTB, uchar PORTB_Mask)
{
    return Send (0x71, DDRB, DDRB_Mask, PORTB, PORTB_Mask, 0, NULL);
}

int USBDevice::Send(uchar command, uchar data1, uchar data2, uchar data3, uchar data4, uchar data5, uchar outBuffer[5])
{
    if (dev==NULL)
        return -1;

    uchar delay = 1; /// Delay = 1 * 320us
    uchar dataToSend[7] = {delay, command, data1, data2, data3, data4, data5};
    uchar replyBuffer[6];
    if (UsbSendData(dev, 3, dataToSend, 7, replyBuffer, 6)!=6)
    {
        Disconnect();
        return -2;
    }

    if (replyBuffer[0] != 0xA9)
    {
        // Incorrect reply: first should alwasy be 0xA9 (set in Tiny26 Receive Method)
        Disconnect();
        return -1;
    }

    if (outBuffer!=NULL)
    {
        for(int i=0; i<5; i++)
        {
            outBuffer[i] = replyBuffer[i+1];
        }
    }

    return 0;


/*
    reportOut.reportID = 1;
    reportOut.reportSize = 6;
    reportOut.command = 12;

    reportOut.data[0] = command;
    reportOut.data[1] = data1;
    reportOut.data[2] = data2;
    reportOut.data[3] = data3;
    reportOut.data[4] = data4;
    reportOut.data[5] = data5;

    if (!HidD_SetFeature(dev, (void*)&reportOut, sizeof(ReportOut_t)))
    {
        Disconnect();
        return -1;
    }

    reportIn.reportID = 1;
    if (!HidD_GetFeature(dev, (void*)&reportIn, sizeof(ReportIn_t)))
    {
        Disconnect();
        return -1;
    }

    if (outBuffer!=NULL)
    {
        int i =0;
        for (i=0; i<5; i++)
        {
            outBuffer[i] = reportIn.data[i+1]; // First data chunk isn't useful here (should always be 0xA9)
        }
    }

    */
}














