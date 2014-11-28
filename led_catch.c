
int led_yellow=5;
int led_blue=4;
int led_green=3;
int led_red=2;
int speedup=40;
int slowdown=10;
int dVal=200;
int ledcatch=0;
int lastime=2; // for how many times of delayvalue for each light

int r, rr=0; //random number and previous random number

void setup(){
  pinMode(12,INPUT);
  pinMode(led_yellow,OUTPUT);
  pinMode(led_blue,OUTPUT);
  pinMode(led_green,OUTPUT);
  pinMode(led_red,OUTPUT);
  Serial.begin(9600);
  ledinit();
}

int checkInput(){
  if (digitalRead(12)==0){
    return 1;
  } else {
    return 0;
  }
}

void ledinit(){
  randomSeed(analogRead(0));
  ledcatch=random(0,4);
  for (int i = 0; i < 3; i++){
    lightled(ledcatch);
    delay(200);
  }
}
void lightled(int n){
  switch (n) {
    case 0:
      digitalWrite(led_red,HIGH);
      delay(dVal);
      digitalWrite(led_red,LOW);
      break;
    case 1:
      digitalWrite(led_green,HIGH);
      delay(dVal);
      digitalWrite(led_green,LOW);
      break;
    case 2:
      digitalWrite(led_blue,HIGH);
      delay(dVal);
      digitalWrite(led_blue,LOW);
      break;
    case 3:
      digitalWrite(led_yellow,HIGH);
      delay(dVal);
      digitalWrite(led_yellow,LOW);
      break;
    default: 
      // if nothing else matches, do the default
      digitalWrite(led_red,LOW);
      digitalWrite(led_green,LOW);
      digitalWrite(led_blue,LOW);
      digitalWrite(led_yellow,LOW);
  }
}
int color_arr[4]={0,0,0,0};
int ccount(int c, int cc) {
  if (cc == c){
    color_arr[c]++;
  } else {
    color_arr[c]=0;
  }
  if (color_arr[c] == lastime) {
    color_arr[c]=0;
    return 0;
  } else {
    return 1;
  }
}
    
void loop (){
  randomSeed(analogRead(0));
  r=random(0,4)%4;
  if (ccount(r,rr)==1){
    if (r==0) {
        lightled(0);
    } else if (r==1) {
      lightled(1);
    } else if (r==2) {
      lightled(2);
    } else if (r==3) {
      lightled(3);
    }
    if (checkInput()==1){
       if (r==ledcatch){
         for (int i=0; i < 4; i++){
         digitalWrite(led_red,HIGH);
         digitalWrite(led_green,HIGH);
         digitalWrite(led_blue,HIGH);
         digitalWrite(led_yellow,HIGH);
         delay(200);
         digitalWrite(led_red,LOW);
         digitalWrite(led_green,LOW);
         digitalWrite(led_blue,LOW);
         digitalWrite(led_yellow,LOW);
         delay(200);
         }
         if (dVal>speedup){
           dVal-=speedup;
         }
         delay(500);
         ledinit();
       } else {
         digitalWrite(led_red,HIGH);
         digitalWrite(led_green,HIGH);
         digitalWrite(led_blue,HIGH);
         digitalWrite(led_yellow,HIGH);
         delay(1000);
         digitalWrite(led_red,LOW);
         digitalWrite(led_green,LOW);
         digitalWrite(led_blue,LOW);
         digitalWrite(led_yellow,LOW);
         dVal+=slowdown;
       }
    }
  }
  lastime=400/dVal;
  Serial.println(lastime);
  rr=r;
}
