



#ifndef _TINY26INTERFACE_H
#define _TINY26INTERFACE_H

#include "usb.h"

/*
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
*/

/*
typedef unsigned char uchar;
*/
struct Port
{
    unsigned char PORT;
    unsigned char PORT_Mask;
    unsigned char PIN;
    unsigned char DDR;
    unsigned char DDR_Mask;
};

class USBDevice
{
    public:

    // Constructor
    USBDevice();
    // Destructor
    ~USBDevice();
    int Connect();
    int Disconnect();

    int GetSetPortA (Port &port);
    int GetSetPortB (Port &port);
    int GetSetPort (Port &port, unsigned char command);

    int Get_PINA_PORTA_DDRA(OUT uchar &PINA, OUT uchar &PORTA, OUT uchar &DDRA);
    int Get_PINB_PORTB_DDRB(OUT uchar &PINB, OUT uchar &PORTB, OUT uchar &DDRB);
    int Get_ADC(uchar adcNumber, OUT uchar &adcValue);
    int Set_DDRA_PORTA(uchar DDRA, uchar DDRA_Mask, uchar PORTA, uchar PORTA_Mask);
    int Set_DDRB_PORTB(uchar DDRB, uchar DDRB_Mask, uchar PORTB, uchar PORTB_Mask);
    int Set_Timers(uchar TCCR1A, uchar TCCR1B, uchar OCR1B, uchar OCR1C, OUT uchar &TCNT1);



    int Send(uchar command, uchar data1, uchar data2, uchar data3, uchar data4, uchar data5, uchar * outBuffer);

    private:

    usbDevice_t * dev;
    ReportOut_t reportOut;
    ReportIn_t reportIn;

};

#endif


