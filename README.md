#473Lab
======

To put all you have learned together to create a stereo FM alarm clock radio with inside/outside temperature indications.

#####Author: Chauncey Yan
#####Date: Fall2015

```c
//Push button assignment
// --- --- --- --- --- --- --- ---
// |7| |6| |5| |4| |3| |2| |1| |0|
// --- --- --- --- --- --- --- ---
// |0| -> change volume
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
// L:Volume R:Time/Alarm

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
//     SH/LD             PORTE bit 7 (high)
//     SCK               PORTB bit 1 (sclk)
//     CKINH             PORTE bit 6 (gnd)
//     SOUT/SER_OUT      PORTB bit 3 (miso)
//     SIN/SER_IN        Not connected
//
//   AMP board             Mega128 board
// --------------        ------------------
// Alarm tone out        PORTD bit 7 (yellow)
// Volume control        PORTE bit 3 (green)
//
//       ADC               Mega128 board
// --------------        ------------------
// analog data in        PORTF bit 0
```
