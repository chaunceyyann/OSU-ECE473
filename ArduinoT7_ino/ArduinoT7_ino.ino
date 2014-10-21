 

//  Tutorial 7: 7 Segment LED
//
// Define the LED digit patters, from 0 – 9
// Note that these patterns are for common anode displays
// 0 = LED on, 1 = LED off:
//                                     Digital pin: 2,3,4,5,6,7,8,9
aver
saver
/                                                          a,b,c,d,e,f,g,Dp

byte seven_seg_digits[10][8] = { { 0,0,0,0,0,0,1,1 },  // = 0
                               { 1,0,0,1,1,1,1,0 },  // = 1.
                               { 0,0,1,0,0,1,0,1 },  // = 2
                               { 0,0,0,0,1,1,0,0 },  // = 3
                               { 1,0,0,1,1,0,0,1 },  // = 4
                               { 0,1,0,0,1,0,0,0 },  // = 5
                               { 0,1,0,0,0,0,0,1 },  // = 6
                               { 0,0,0,1,1,1,1,0 },  // = 7
                               { 0,0,0,0,0,0,0,1 },  // = 8
                               { 0,0,0,1,1,0,0,0 }   // = 9
                               };

void setup() {              
  pinMode(2, OUTPUT); 
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void sevenSegWrite(byte digit) {

  byte pin = 2;
  for (byte segCount = 0; segCount < 8; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}

 

void loop() {

  for (byte count = 0; count < 10; ++count) {
   delay(1000);
   sevenSegWrite(count);
  }

}
