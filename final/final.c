// final.c 
// Chauncey Yan
// Fall2015

//16x2 LCD display 
//-----------------------------------------------------------------
//| 8 | 8 | . | 7 |   |   | * | * | * | * | * | * | * | * |   |   |
//|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
//| L | : | 2 | 4 | . | 2 | 5 | C |   | R | : | 2 | 5 | C |   |   |
//-----------------------------------------------------------------

// Push button assignment
// --- --- --- --- --- --- --- ---
// |7| |6| |5| |4| |3| |2| |1| |0|
// --- --- --- --- --- --- --- ---
// |0| -> Radio mode
// |1| -> toggle increments between 1 and 60 mins
// |2| -> set current time 
// |3| -> set alarm time 
// |4| -> toggle alarm set/non-set
// |5| -> toggle 12 / 24 hour mode
// |6| -> snooze mode
// |7| -> confirmation/dismiss alarm 

// Encoder assignment
//  _____    _____
// /     \  /     \
// | (L) |  | (R) |
// \_____/  \_____/
//
// L:Volume R:Time/Alarm/Fhz

// Wire layout
//      7Seg                Mega128 Board
// --------------        ------------------
//     pulldown          PORTA bit 0-7
//     sel0              PORTB bit 4
//     sel1              PORTB bit 5
//     sel2              PORTB bit 6
//     EN                PORTB bit VCC
//     EN_N              PORTB bit Gnd
//     PWM               PORTB bit 7
//     DEC7              COM_EN --> Pushbutton
//
// Pushbutton board         Mega128 board
// ----------------      ------------------
//     COM_EN            DEC7 --> 7Seg
//     COM_LVL           PORTE bit 4
//
// Bargraph board           Mega128 board
// --------------        ------------------
//     reglck            PORTB bit 0 (ss_n)
//     srclk             PORTB bit 1 (sclk)
//     sdin              PORTB bit 2 (mosi)
//     oe_n              PORTE bit 5
//     sd_out            not connected
//
// Encoder board           Mega128 board
// --------------        ------------------
//     SH/LD             PORTE bit 6 (high)
//     SCK               PORTB bit 1 (sclk) 
//     CKINH             PORTD bit 6 (gnd)
//     SOUT/SER_OUT      PORTB bit 3 (miso)
//     SIN/SER_IN        Not connected
//
//   AMP board             Mega128 board
// --------------        ------------------
// Alarm tone out        PORTD bit 7 (yellow)
// Volume control        PORTE bit 3 (green)
//
//     ADC                 Mega128 board
// --------------        ------------------
// analog data in        PORTF bit 0
// 
//   Local temp            Mega128 board
// --------------        -----------------
//     Sclk              PORTD bit 0
//     Sdata             PORTD bit 1
//
//   FM radio              Mega128 board
// --------------        ------------------
//     RST_N             PORTE bit 2 
//     SCLK              PORTD bit 0 
//     SDIO              PORTD bit 1 
//     GPO2/INT          PORTE bit 7 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "LCDDriver.h"
#include "kellen_music.c"
#include "lm73_functions.h"
#include "twi_master.h"
#include "uart_functions.c"
#include "si4734.h"

#define MAX_CHECKS 12           // # of checks before a switch is debounced
#define BASE 10                 // the base of the clock should be working
#define ALARM_LEN 1             // min of alarm going to be play
//#define SNOOZE_LEN 10         // seconds of snooze going to be wait

signed int gc = 0;              // globle counter
signed int lec = 0;             // left encoder counter
signed int old_lec = 0;         // old left encoder counter
signed int rec = 0;             // right encoder counter
signed int old_rec = 0;         // old right encoder counter
unsigned int radio_on = 0;      // volume mode
signed int vc = 20;             // volume counter
signed int old_vc = 1;          // volume counter old value
unsigned int vol = 0;           // volume mode
unsigned int rts = 0;           // global time counter seconds
unsigned int rtc = 1440;        // global time counter mins 
signed int rtc_t = 0;           // temporary rtc for set time mins
unsigned int atc = 1500;        // alarm mins 
signed int atc_t;               // temporary atc for set alarm mins
unsigned int hours = 0;         // display Hours
unsigned int hours_24 = 0;      // display 24 Hours
unsigned int ahours = 0;        // alarm Hours 24 hours
unsigned int mins = 0;          // display mins
unsigned int amins = 59;        // alarm mins
uint8_t alarm_wentoff = 0;
uint8_t alarm_start = 60;       // alarm start time
uint8_t snooze_wentoff = 0;
uint8_t snooze_start = 0;       // alarm snooze start time
uint8_t snooze_min = 0;         // alarm snooze start time
uint8_t snooze_second = 0;      // alarm snooze start time
uint8_t snooze_len = 1;
uint8_t sn = 0;                 // 0 - Beavs fight sone 1 - Tetris 
// 2 - Mario 3 - Unknown
uint8_t mode_t = 0;             // toggle mode switch
uint8_t mode = 0;               // mode flags
uint8_t tinc = 1;               // increament to seperate min and hour , and channel
uint8_t vinc = 2;               // increament to seperate volume
uint8_t barcode = 0;            // data print on the bar 
uint8_t debounced_state = 0;    // Debounced state of the switches
uint8_t state[MAX_CHECKS];      // Array that maintains bounce status
uint8_t id = 0;                 // Pointer into State
signed int adcd = 0;            // ADC data
uint16_t temp = 32;             // temporature value
uint16_t lm73_int;              // temporature value int
uint8_t lm73_dec;               // temporature value float
uint16_t nega_temp = 0;         // if negative temporature
uint8_t lm73_wr_buf[2];         // lm73 writing buffer
uint8_t lm73_rd_buf[2];         // lm73 reading buffer
char alarm_buf[32] = "Go Beavs! OSU Fight Fight Fight!";
char buf[16];                   // genaral purpose buffer
char loc_temp_buf[16];          // local temporature buffer
char remote_temp_buf[2];        // remote temporature buffer

enum radio_band{FM, AM, SW};
volatile enum radio_band current_radio_band;
volatile uint8_t STC_interrupt;  //flag bit to indicate tune or seek is done
uint16_t eeprom_fm_freq;
uint16_t eeprom_am_freq;
uint16_t eeprom_sw_freq;
uint8_t  eeprom_volume;
uint16_t current_fm_freq;
uint16_t old_fm_freq=8870;
uint16_t current_am_freq;
uint16_t current_wm_freq;
uint8_t current_volume;
uint8_t si4734_tune_status_buf[8];
uint8_t rssi;
uint16_t stations[5]={8870,9570,9910,9990,10630};
//decimal to 7-segment LED display encodings, logic "0" turns on segment
int dec_to_7seg[18] = {0b11000000, 0b11111001, 0b10100100, 0b10110000, // 0 1 2 3
    0b10011001, 0b10010010, 0b10000010, 0b11111000, // 4 5 6 7
    0b10000000, 0b10011000, 0b10001000, 0b10000011, // 8 9 A B
    0b11000110, 0b10100001, 0b10000110, 0b10001110, // C D E F
    0b10000011, 0b1000100};                         // ^ :

//holds data to be sent to the segments. logic zero turns segment on
int segment_data[5] = {0xff, 0xff, 0xff, 0xff, 0xff};   // turn off led not needed.


//*********************************************************************************
//                            chk_buttons
// Debounce the all 8 bit switchs at the same time by checking PINA input 
//*********************************************************************************

void DebounceSwitch(){
    uint8_t i,j;
    state[id++]=0xff - PINA;
    j=0xff;
    for(i=0; i<MAX_CHECKS-1;i++)j=j & state[i];
    debounced_state = j;
    if(id >= MAX_CHECKS)id=0;
}


//**********************************************************************************
//                                   7 seg display
//takes a 16-bit binary input value and places the appropriate equivalent 4 digit
//BCD segment code in the array segment_data for display.
//array is loaded at exit as:  |digit3|digit2|colon|digit1|digit0|
//**********************************************************************************

void breakDgt(uint16_t sum, int base_count, uint16_t check_bit) {
    uint16_t dgt;
    int o;
    for (o = 0; o < 4; o++){
        dgt = (sum >> (o * base_count)) & check_bit;
        segment_data[o] = dec_to_7seg[dgt];
    }
}

void segsum(uint16_t sum) {
    int u = 4;

    //break up decimal sum into 4 digit-segments
    switch (BASE) {
        case 10:
            //breakDgt(sum,10);
            segment_data[0] = dec_to_7seg[sum%10];
            segment_data[1] = dec_to_7seg[sum/10%10];
            segment_data[2] = 0xff; //dec_to_7seg[17];
            segment_data[3] = dec_to_7seg[sum/100%10];
            segment_data[4] = dec_to_7seg[sum/1000%10];
            break;
        case 16:
            breakDgt(sum,4,0x000f);    //check last 4
            break;
        case 8:
            breakDgt(sum,3,0x0007);    // check last 3
            break;
        case 2:
            breakDgt(sum,1,0x0001);    // check last 1
            break;
    }
    //blank out leading zero digits
    while (segment_data[u] == dec_to_7seg[0] || segment_data[u] == 0xff) {
        segment_data[u--] = 0xff;
        if ( u == -1) {
            segment_data[0] = dec_to_7seg[0];
            break;
        }
    }
}

//***********************************************************************************
//                                     clock
//
//***********************************************************************************
void hmclock(unsigned int tc){
    mins = tc % 60;
    hours_24 = tc / 60 % 24;                            // 24 hours
    hours = tc / 60 % 12;                               // 12 hours
}
void clock_dis(){

    segment_data[0] = dec_to_7seg[mins%BASE];           // 1st digit
    segment_data[1] = dec_to_7seg[mins/BASE];           // 2ed digit
    if (mode & (1<<5)){                                 // 24 hours mode
        segment_data[3] = dec_to_7seg[hours_24%BASE];    
        segment_data[4] = dec_to_7seg[hours_24/BASE];
    } else {                                            // 12 hours mode
        segment_data[3] = dec_to_7seg[hours%BASE];
        segment_data[4] = dec_to_7seg[hours/BASE];
    }
}


void alarm_check(){                                     // run once pre second
    if (mode & (1<<4)){        // initial value, use this to exe music once
        hmclock(rtc);                                   // update real time clock value hours and mins
        if (((ahours==hours_24)&&(amins==mins))||(snooze_wentoff==1)){   // use hours_24 for am pm
            alarm_wentoff=1;
            music_on();                                 // alarm tone on
            LCD_MovCursorLn1();
            if ( song == 0)
                LCD_PutStr(alarm_buf);                  // print Fight sone
            else if (song == 1)
                LCD_PutStr("Tetris Theme");             // print Tetris
            else if (song == 2)
                LCD_PutStr("Mario Theme");              // print Mario
            else if (song == 3)
                LCD_PutStr("Unknow");                   // print Unknow
            alarm_start = rtc;                          // set start second for alarm tone
        }
    }
    if ((rtc - alarm_start) == ALARM_LEN) {             // 1-58s for the alarm tone
        alarm_wentoff=0;
        snooze_wentoff = 0;
        music_off();                                    // alarm tone off
        song++;
        if (song == 4) song = 0;                        // roll back for the fisrt song
        LCD_MovCursorLn1();
        LCD_PutStr("Alarm off!");
        alarm_start = 0;                               // avoiding rerun this music_off and music_on
    } 
 
}

void snooze_func(){
    if ((alarm_wentoff == 1) && (snooze_min == 0)) {   // first time snooze is trigered
        snooze_wentoff = 1;
        music_off();                                // turn off the music
        LCD_MovCursorLn1();
        LCD_PutStr("Snooze mode: 1min");              // print snooze
        snooze_second = rts;                         // start count 10 second
        snooze_min = rtc;                         // start count 10 second
        //snprintf(buf,16,"%d.%-2dC ",(snooze_len-rtc+snooze_min),snooze_second);
    }

    if ((rts - snooze_second) == 0) {           // out of snooze mode
        if (( rtc - snooze_min) == snooze_len){
            song++;
            if (song == 4) song = 0;                        // roll back for the fisrt song
            snooze_min = 0;                               // reset snooze function
        }
    }
}



/***********************************************************************/
//                            lcd functions
// Alarm print out                           
/***********************************************************************/
void lcd_alarm(){
    LCD_MovCursorLn1();
    if (mode & (1<<4)){                                 // check if alarm is set
        LCD_PutStr("Alarm set ");
        itoa(ahours,buf,10);
        LCD_PutStr(buf);
        LCD_PutStr(":");
        itoa(amins,buf,10);
        LCD_PutStr(buf);
        LCD_PutStr("    ");
    } else                                              // not set
        LCD_PutStr("Alarm: Not set  ");
}

/***********************************************************************/
//                            spi input and output
//Initalizes the SPI port on the mega128. Does not do any further
//external device specific initalizations.  Sets up SPI to be:
//master mode, clock=clk/2, cycle half phase, low polarity, MSB first
//interrupts disabled, poll SPIF bit in SPSR to check xmit completion
/***********************************************************************/
void spi_init(void){
    DDRB  |= 0x07;                            // Turn on SS, MOSI, SCLK for output
    // Turn on bit 3 SER_out for input
    DDRE  |= 0xff;                            // Turn on CLK_INH, SH/LD for output

    SPCR  |= ( 1 << SPE ) | ( 1 << MSTR );    // Set up SPI mode
    SPSR  |= ( 1 << SPI2X );                  // Double speed operation
}

void bar_print(uint8_t led_num){
    SPDR = led_num;                           // print to bar graph
    while (bit_is_clear(SPSR,SPIF));          // wait for the data to be sent out
    PORTB |= 0x01;                            // strobe output data reg in HC595 - rising edge
    PORTB &= 0xFE;                            // Falling edge
}

void read_encoder(uint8_t miso){
    static uint8_t old_miso;

    // Pulse the HC165 with SH/LD 0 for load the data from knod then keep it high for serial sent back
    PORTE ^= (1<<6);                          // SH/LD = 0 CLK_INH = 0 
    PORTE = 0b01000000;                       // SH/LD = 1 CLK_INH = 0

    if (old_miso != miso){
        if ((old_miso & 0x03) == 0x03){
            switch(miso&0x03){
                case 0x02:
                    lec+=vinc;
                    break;
                case 0x01:
                    lec-=vinc;
                    break;
            }
        }
        if ((old_miso & 0x0C) == 0x0C){
            switch((miso&0x0C)>>2){
                case 0x02:
                    rec+=tinc;
                    break;
                case 0x01:
                    rec-=tinc;
                    break;
            }
        }
    }
    old_miso = miso;

}
//***********************************************************************************
//                             ADC and dimmer
//
//***********************************************************************************

void ADC_init (void){
    PORTF = 0x00;
    DDRF  &= ~(1<<0);
    ADCSR |= (1 << ADFR);          // Set ADC to Free-Running Mode
    ADCSR |= (1 << ADPS2);         // Set ADC prescaler to 16 - 500KHz
    //ADCSR |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 
    // Set ADC prescaler to 128 - 125KHz sample rate @ 16MHz

    ADMUX = 0;                     // Initial channel seletion
    ADMUX |= (1 << REFS0);         // Set ADC reference to AVCC
    ADMUX |= (1 << ADLAR);         // Left adjust ADC result to allow easy 8 bit reading

    // No MUX values needed to be changed to use ADC0

    ADCSR |= (1 << ADEN);          // Enable ADC
    ADCSR |= (1 << ADIE);          // Enable ADC Interrupt
    ADCSR |= (1 << ADSC);          // Start A2D Conversions
}

ISR(ADC_vect) {                    // auto dimming mode
    adcd = ADCH;                
    if (adcd < 1)                  // no negative
        adcd = 1;    
    else if (adcd > 255)           // no too bright value
        adcd = 255;
    OCR2 = adcd;                   // create the TCNT 2 PWM

}


//***********************************************************************************
//                             TWI tempurature
//
//***********************************************************************************
void localTemp(){;
    uint16_t lm73_temp;
    int i;

    twi_start_rd(LM73_ADDRESS,lm73_rd_buf,2); //read temperature data from LM73 (2 bytes)  (twi_mas    ter.h)
    _delay_ms(2);                             //wait for it to finish
    lm73_temp = lm73_rd_buf[0];               //save high temperature byte into lm73_temp
    lm73_temp = lm73_temp << 8;               //shift it into upper byte
    lm73_temp |= lm73_rd_buf[1];              //"OR" in the low temp byte to lm73_temp

    // check negative temp
    if (lm73_temp & (1<<15)){
        lm73_temp &= ~(1<<15);
        nega_temp = 1;
    } else nega_temp = 0;

    //lm73_temp_convert(lm73_temp,0x01);      // f_not_c

    lm73_temp = (lm73_temp >> 5);             // remove the last unused 5 bits, accuracy at 0.25 C.
    lm73_int = (lm73_temp >> 2);              // remove the last 2 bits, accuracy at 1 C.
    lm73_dec = (lm73_temp & 0x03) * 25;       // get 2 decimal float number

    snprintf(loc_temp_buf,16,"%d.%-2dC ",lm73_int,lm73_dec);
    //snprintf(loc_temp_buf,16,"%dC ",lm73_int);

    // negative number handler
    if (nega_temp == 1){
        for (i = 15; i >= 0; i--){
            loc_temp_buf[i] = loc_temp_buf[(i-1)];
        }
        loc_temp_buf[0] = '-';
    }
}

void radio_init(){

    //                           DDRE:  0 0 0 0 1 0 1 1
    //   (^ edge int from radio) bit 7--| | | | | | | |--bit 0 USART0 RX
    //(shift/load_n for 74HC165) bit 6----| | | | | |----bit 1 USART0 TX
    //                           bit 5------| | | |------bit 2 (new radio reset, active high)
    //                  (unused) bit 4--------| |--------bit 3 (TCNT3 PWM output for volume control)

    DDRE  |= 0x04; //Port E bit 2 is active high reset for radio
    DDRE  |= 0x40; //Port E bit 6 is shift/load_n for encoder 74HC165
    DDRE  |= 0x08; //Port E bit 3 is TCNT3 PWM output for volume
    PORTE |= 0x04; //radio reset is on at powerup (active high)
    PORTE |= 0x40; //pulse low to load switch values, else its in shift mode

    reset_radio();
    current_fm_freq = 8870;


   
}

//***********************************************************************************
//                             TCNT initial    
//
//***********************************************************************************
void tcnt0_init(void){                                      // real time clock
    //timer counter 0 setup, running off i/o clock
    TIMSK |= ( 1<<TOIE0 );                                  //enable interrupts
    TCCR0 |= ( 1<<CS00 ) | (1<<CS02);                       //normal mode, prescale by 128
}

// timer1 init --->>> music_init in kellen_music.c

void tcnt2_init(void){                                      // dimming
    //timer counter 2 setup, running off i/o clock
    TCCR2 |= ( 1<<CS20 );                                   //normal mode, no prescale 
    TCCR2 |= ( 1<<WGM20 ) | (1<<WGM21);                     //fast pwm mode
    TCCR2 |= ( 1<<COM20 ) | (1<<COM21);                     //Set OC2 on compare match
    TCCR2 &= ~( 1<<FOC2 );                                  //no forced compare 
    OCR2  = 0x00;                                           //initial the compare
}
void tcnt3_init(void){                                      // audio volume pwm
    //timer counter 3 setup, running off i/o clock
    TCCR3A |= ( 1<<COM3A1 ) | ( 1<<COM3A0 ) | ( 1<<WGM31 ); //fast pwm, set on match.
    TCCR3B |= ( 1<<CS30 ) | ( 1<<WGM32 ) | ( 1<<WGM33 );    //ICR3 for TOP, no prescale
    ICR3 = 0x0064;
}


//***********************************************************************************
//                             ISR for the timer
//
//***********************************************************************************
ISR(TIMER0_OVF_vect){
    // 16m/128 = 125khz
    // 1/125k * 256 = 2.048ms
    // 1/125k * 256 * 488 = 1s

    static uint16_t count_2ms = 0;
    static uint16_t curr = 0;
    count_2ms++;                                // increment count every 2.048ms

    // reduce the bar graph brightness
    //bar_print(0);   

    // Encoder and bar graph
    if (count_2ms % 2 == 0){
        //SPI MOSI to bar graph display
        bar_print(mode);

        // SPI MISO from Encoder 
        read_encoder(SPDR);

        // set time mode
        // semicolum alwas light up
        if (mode & (1<<2)){                        
            rtc_t = rtc + rec;                  // adding right encoder value to temp real time clock
            hmclock(rtc_t);                     // update hours and mins
            clock_dis();                        // display the clock
            segment_data[2] = dec_to_7seg[17];  // presist the semicolumn

            // check comfirmation
            if (mode & (1<<7)){    
                rtc = rtc_t;
            }
        }

        // set alarm time
        // checking comfirmation at the last
        else if (mode & (1<<3)){
            atc_t = atc + rec;                  // adding right encoder value to temo alarm time 
            hmclock(atc_t);                     // update hours and mins
            clock_dis();                        // display the clock
            segment_data[2] = dec_to_7seg[17];  // presist the semicolumn

            // check comfirmation
            if (mode & (1<<7)){                    
                atc = atc_t;
                ahours = atc / 60 % 24;         // update alarm hour 24 
                amins = atc % 60;               // update alarm min 
                mode |= (1<<4);                 // set alarm mode flag
                lcd_alarm();                    // display alarm on lcd
            }
        }



        // manualy clear snooze and confirm if necessary
        if (mode & (1<<6)) { // clear snooze if alarm is off
            // snooze function
            snooze_func();
            mode &= 0b00110011;                     // clear set time set alarm as well
        }
        if (mode & (1<<7)) {                          // clear confirm
            mode &= 0b00110011;                     // clear set time set alarm as well
        }
    }


    // real time clock
    if ((count_2ms % 488 == 0) ){                   // 1s
        rts++;                                      // seconds ++
        if (rts == 60){
            rtc++;                                  // mins ++
            rts = 0;                                // reset second
            // check if the real time match with alarm time
            alarm_check();
        }

        // make sure it is not in set time or set alarm mode
        if (!((mode & (1<<3)) || (mode & (1<<2)))){
            hmclock(rtc);                           // update real time clock
            clock_dis();                            // display the clock

            // seconds semicolumn
            if ((rts % 2) == 0){                    // flash every second
                segment_data[2] = dec_to_7seg[17];
            } else {
                segment_data[2] = 0xff;
            }
        }
    }

    // adding pm dot indicator 
    // (out of real time since it should show up on all settings)
    if ((hours_24 >= 12) && !(mode & (1<<5) && !(vol||radio_on))){    	// pm and not 24 hour mode
        segment_data[2] &= dec_to_7seg[16];
    } else {                                       	// explicitly turn off indicator 
        segment_data[2] &= ~(1<<1) | ~(1<<0);
    }

    // ararm tone speed for note duration(64th notes)
    if (count_2ms % 32 == 0){
        beat++;
    }
    static unsigned int i;

    if (count_2ms % 2 == 0){                        
		// radio mode
	    if (mode&(1<<0)){
            if (old_rec != rec){
                radio_on = 1;
                

                if (mode & (1<<1)){
                    i += abs(rec)/60%5;
                    if (i==5)
                        i = 0;
                    current_fm_freq = stations[i];

                } else 
                    current_fm_freq = ((unsigned long)old_fm_freq + rec - 8790)%2000+8790;

                segsum(current_fm_freq/10);
                segment_data[1] &= ~(1<<7);                // decimal point
                old_rec = rec;

                while(twi_busy()){} //spin while TWI is busy
                fm_tune_freq();     //tune to frequency
                curr = count_2ms;    
            } else {
                old_fm_freq = current_fm_freq;
                rec = 0;

                if ((radio_on==1)&&(count_2ms-curr<=976)){
                    segsum(current_fm_freq/10);
                    segment_data[1] &= ~(1<<7);                // decimal point
                    //if (count_2ms-curr == 0){ // 0.125s
                    //    while(twi_busy()){} //spin while TWI is busy
                    //    fm_tune_freq();     //tune to frequency
                    //}
                    if (count_2ms-curr == 488){
                        LCD_MovCursorLn1();
                        snprintf(buf,16,"%3d.%-1d",current_fm_freq/100,current_fm_freq/10%10);
                        LCD_PutStr(buf);                                                  
                        //LCD_PutStr("         ");                                                  
                        
                    }
                } else {
                    radio_on = 0;
                }
            }
        }

        // volume control
        if (lec != old_lec){
            vol = 1;
            if ((old_vc + lec) < 0) 
                lec = 0-old_vc;                     // set range 0 - 100
            else if ((old_vc + lec) > 100) 
                lec = 100-old_vc; 
            vc = old_vc + lec;                      // update volume counter
            segsum(vc);                             // display vc
            OCR3A = 100 - vc;                       // create PWM with TCNT3
            old_lec = lec;
            curr = count_2ms;
        }
        else {        
            old_vc = vc;                // save old vc value for next adding
            lec = 0;                    // reset light encoder reading
            if ((vol==1)&&(count_2ms-curr<=976)){
                segsum(vc);
            }
            else {
                vol = 0; 
            }

        }

    }

    // lcd update rate 1s for temp
    if (count_2ms % 488 == 0){
        LCD_MovCursorLn2();
        LCD_PutStr("L:");
        LCD_PutStr(loc_temp_buf);
        LCD_PutStr("R:");
        LCD_PutChar(remote_temp_buf[0]);
        LCD_PutChar(remote_temp_buf[1]);
        LCD_PutChar('C');
        
        //retrive the receive strength and display on the bargraph display
        //while(twi_busy()){}                //spin while TWI is busy
        //fm_rsq_status();                   //get status of radio tuning operation
        //rssi = si4734_tune_status_buf[4];
        ////redefine rssi to be a thermometer code
        //if(rssi<= 8) {rssi = 0x00;} else
        //    if(rssi<=16) {rssi = 0x01;} else
        //        if(rssi<=24) {rssi = 0x03;} else
        //            if(rssi<=32) {rssi = 0x07;} else
        //                if(rssi<=40) {rssi = 0x0F;} else
        //                    if(rssi<=48) {rssi = 0x1F;} else
        //                        if(rssi<=56) {rssi = 0x3F;} else
        //                            if(rssi<=64) {rssi = 0x7F;} else
        //                                if(rssi>=64) {rssi = 0xFF;}
        //LCD_MovCursorLn1();
        //LCD_PutStr(itoa(rssi,buf,5));  
    }

}

//ISR timer 1 is in kellen_music.c

//***********************************************************************************
//                                    Toggle interpurator
//                                     mode_t -> mode flags
//***********************************************************************************
void set_mode(){
    switch (mode_t){
        case 1:                         // toggle radio mode 
            mode &= 0b00110011;         // clear all mode but alarm set, 12/24, 1/60
            mode ^= (1<<0);             // toggle

            if (mode & (1<<0)){
                if (mode&(1<<1))
                    tinc = 60;
                else
                    tinc = 20;
            } else
                tinc = 1; 

            if (mode & (1<<0)) {
                while(twi_busy()){} //spin while TWI is busy
                fm_pwr_up();        //power up radio
                while(twi_busy()){} //spin while TWI is busy
                fm_tune_freq();     //tune to frequency
            } else { 
                while(twi_busy()){} //spin while TWI is busy
                radio_pwr_dwn();        //power down radio
            }

            old_fm_freq = current_fm_freq;
            rec = 0;
            old_rec = 1;

            break;
        case 2:                         // 1 min or 60 mins ?
            mode ^= (1<<1);             // toggle inc between 1 and 60 mins
            if (mode & (1<<1)){
                tinc = 60;
                vinc = 10;
            }
            else{         
                if (mode & (1<<0))
                    tinc = 20;
                else
                    tinc = 1;
                vinc = 2;
            }
            break;
        case 4:                         // set time
            mode &= 0b00110110;         // clear set alarm
            mode ^= (1<<2);             // toggle, for cancelling
            rec = 0;                    // reset right encoder reading
            break;
        case 8:                         // set alarm
            mode &= 0b00111010;         // clear set time
            mode ^= (1<<3);             // toggle, for cancelling
            if (!(mode & (1<<3)))       // unset alarm if double cancel setting
                mode &= ~(1<<4);        // unset alarm flag
            lcd_alarm();                // update lcd 
            rec = 0;                    // reset right encoder reading
            break;
        case 16:                        // alarm indicator, toggle set or unset
            mode ^= (1<<4);             // toggle
            lcd_alarm();
            alarm_wentoff=0;
            snooze_wentoff = 0;
            music_off();
            break;						
        case 32:                        // 24 - 12 indicator
            mode ^= (1<<5);             // toggle
            break;
        case 64:                        // snooze function indicator
            mode |= (1<<6);             // clear manually in timer 0
            break;
        case 128:                       // confirm & dismiss alarm
            mode |= (1<<7);             // clear manually in timer 0
            break;
        default:                        // multiple buttons input detected
            mode &= 0b00110010;         // clear all mode but alarm set, 12/24, 1/60
            break;
    }
}
//***********************************************************************************
//                                    Main
// 
//***********************************************************************************
int main(){
    // run time initial 
    uint8_t counter = 0; 

    //set port bits 4-7 B as outputs
    DDRB = 0xf0; // output
    DDRD = 0xff; // output

    // ADC init
    ADC_init();

    // time counter init
    tcnt0_init();
    music_init(0);
    tcnt2_init();
    tcnt3_init();

    // initial Volume 20
    OCR3A = 100 - vc;

    // SPI interupt initial
    spi_init();

    // initialize TWI
    init_twi();
    // load lm73_wr_buf[0] with temperature pointer address
    lm73_wr_buf[0] = LM73_PTR_TEMP;   
    // start the TWI write process (twi_master.h)
    twi_start_wr(LM73_ADDRESS,lm73_wr_buf,2);   
    _delay_ms(2);

    // initialize LCD
    LCD_Init();
    LCD_Clr();
    LCD_CursorBlinkOff();
    LCD_PutStr("Teklarm 2.0!!!");

    // uart transmition 
    uart_init();

    // enable global interrupt
    sei();

    // turn on radio
    radio_int_init();
    radio_init();
    //music_on();
    // main while loop
    while(1){

        PORTA = 0xff;
        DDRA = 0x00;                        // make PORTA an input with pullups

        PORTB |= 0b01110000;                // enable tristate buffer for pushbutton switches

        _delay_ms(1);                       // make sure button get the time to react

        // Debounceing buttons
        DebounceSwitch();                   // now check each button
        if (debounced_state){               // check if any inputs
            if (mode_t != debounced_state){ // make sure no duplicate input
                mode_t = debounced_state;   // toggle switch
                set_mode();                 // decode button input
                debounced_state = 0;        // reset debouced_state
            }

        } else mode_t = 0;                  // no toggle input

        localTemp();

        // remote tempurature uart rx and tx
        uart_putc('s');
        for ( counter = 0; counter < 2; counter++){
            remote_temp_buf[counter] = uart_getc();
            uart_putc('Y');
        }


        // select the digit to display and select the input from decoder
        DDRA = 0xff;                        // make PORTA an output

        //bound a counter (0-4) to keep track of digit to display
        for (counter = 0; counter < 5; counter++){
            PORTB = counter << 4;           // send PORTB the digit to display
            PORTA = segment_data[counter];  // send 7 segment code to LED segments

            _delay_ms(1);                   // display the each digit for 1ms 
        }

    }//while
}//main
