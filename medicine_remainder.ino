
//Medicine remainder using arduino Uno
//Reminds to take medicine at 9:30am,12pm,8pm.
#include<LiquidCrystal.h>
#include<Wire.h>
#include<RTClib.h>
#include<EEPROM.h>
int pushVal=0;
 int val1;
 int val2;
 int addr=0;
 RTC_DS3231 rtc;
 const int rs=12,en=11,d4=5,d5=4,d6=3,d7=2; //LCD pins
 LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
 #define getWellsoon 0
 #define HELP_SCREEN 188
 #define TIME_SCREEN 2    //bool
 int pushPressed=0;   //flag to keep track of push button state
 const int ledPin=LED_BUILTIN;    //Buzzer and LED pin
 int ledState=LOW;
 int Signal=0;
 int buzz=13;
 int push1state,push2state,push3state,stopinState=0;
 int push1Flag,push2Flag,push3Flag=0;   //push button flags
 int push1pin=9;
 int push2pin=8;
 int push3pin=7;
 int stopPin=6;
 int screens=0;    //Screen to display
 int maxScreen=2;  //Maximum number of screens required
 bool isScreenChanged=true;
 long previousMillis=0;
 long interval=500;   //buzzing interval
 unsigned long currentMillis;
 long previousMillisLCD=0;  //for LCD screen update
 long intervalLCD=2000;   //Screen cycling interval
 unsigned long currentMillisLCD;  //Set remainder change time
 int buzz9amHH=9;  //HH-hours
 int buzz9amMM=00;   //MM-Minutes
 int buzz9amSS=00;   //SS-Seconds
 int buzz12pmHH=12;
 int buzz12pmMM=00;
 int buzz12pmSS=00;
 int buzz8pmHH=20;
 int buzz8pmMM=00;
 int buzz8pmSS=00;
 int nowHr,nowMin,nowSec;   //to show current mm,hh,ss
void GetWellSoonMessage() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Stay Healthy:)");
  lcd.setCursor(0,1);
  lcd.print("Get Well Soon :)");
}

void helpScreen() {     //function to display 1st screen in LCD
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Press Buttons");
 lcd.setCursor(0,1);
 lcd.print("for remainder...!");
 }

 void timeScreen(){   //function to display date and time in LCD screen
  DateTime now=rtc.now();    //take rtc time and print in display
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Time:");
  lcd.setCursor(6,0);
  lcd.print(nowHr=now.hour(),DEC);
  lcd.print(":");
  lcd.print(nowMin=now.minute(),DEC);
  lcd.print(":");
  lcd.print(nowSec=now.second(),DEC);
  lcd.setCursor(0,1);
  lcd.print("Date:");
  lcd.print(now.day(),DEC);
  lcd.print("/");
  lcd.print(now.month(),DEC);
  lcd.print("/");
  lcd.print(now.year(),DEC);
 }
 void setup(){
  Serial.begin(9600);   //start serial debugging
  if(!rtc.begin())      //check if RTC is connected
  {
    Serial.println("Couldn't find RTC");
    while(1);
  }
  if(rtc.lostPower())    
  {
    Serial.println("RTC lost power,lets set the time!");
  }
 // rtc.adjust(DateTime(F(_DATE_),F(_TIME_))); is used to set the current date and time
 rtc.adjust(DateTime(2019,11,20,17,10,23));  //Manually we can set the date and and time and it can be changed
 lcd.begin(16,2);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Welcome To");    //print a message to start up  the process of device
 lcd.setCursor(0,1);
 lcd.print("Circuit Digest");
 delay(1000);
 pinMode(push1pin,INPUT);   //define push button pins type
 pinMode(push2pin,INPUT);
 pinMode(push3pin,INPUT);
 pinMode(stopPin,INPUT);
 pinMode(ledPin,OUTPUT);
 delay(200);
 Serial.println(EEPROM.read(addr));
 val2=EEPROM.read(addr);     //read previously saved value of push button to start from where it was left previously
 switch(val2)
 {
  case 1:
  Serial.println("Set for 1/day");
  push1state=1;
  push2state=0;
  push3state=0;
  pushVal=1;
  break; 
  case 2:
  push1state=0;
  push2state=1;
  push3state=0;
  pushVal=2;
  break;
  case 3:
  push1state=0;
  push2state=0;
  push3state=1;
  pushVal=3;
  break;
 }}
 void loop()
 {
  push1();  //call to set once/day
  push2();  //twice/day
  push3();  //thrice/day
  if(pushVal==1)
  {
    at9am();
  }
  else if(pushVal==2)
  {
    at9am();
    at3pm();
  }
  else if (pushVal==3)
  {
    at9am();
    at12pm;
    at3pm;
  }
  currentMillisLCD=millis();     //start millis for LCD screen switching at defined interval of time
  push1state=digitalRead(push1pin);    //start reading all push button pins
  push2state=digitalRead(push2pin);
  push3state=digitalRead(push3pin);
  stopinState=digitalRead(stopPin);
  stopPins(); //call to stop buzzing
  changeScreen();     //screen cycle function
  }
 void push1(){
  if(push1state==1){
    push1state=0;
    push2state=0;
    push3state=0;
    //pushPressed=true;
    EEPROM.write(addr,1);
    Serial.print("Push1 Written:");
    Serial.println(EEPROM.read(addr));      //for debugging
    pushVal=1;      //save the state of push button-1
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Remainder set");
    lcd.setCursor(0,1);
    lcd.print("for Once/day!");
    delay(1200);
    lcd.clear();
  }
  }
   void push2() {
   if(push2state==1){
    push2state=0;
    push1state=0;
    push3state=0;
    //pushPressed=true;
    EEPROM.write(addr,2);
    Serial.print("Push2 Written:");
    Serial.println(EEPROM.read(addr));
    pushVal=2;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Remainder set");
    lcd.setCursor(0,1);
    lcd.print("for Twice/day!");
    delay(1200);
    lcd.clear();
  }
  }
  void push3(){
  if(push3state==1){
    push3state=0;
    push1state=0;
    push2state=0;
    //pushPressed=true;
    EEPROM.write(addr,3);
    Serial.print("Push3 Written:");
    Serial.println(EEPROM.read(addr));
    pushVal=3;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Remainder set");
    lcd.setCursor(0,1);
    lcd.print("for Thrice/day!");
    delay(1200);
    lcd.clear();
    }
  }
  void stopPins(){        //function to stop buzzing when user puhes stop push button
    if(stopinState==1){
      //stopinState=0;
      //pushPressed=1;
      pushPressed=1;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Take Medicine");
      lcd.setCursor(0,1);
      lcd.print("with Warm Water");
      delay(1200);
      lcd.clear();
    }
  }
  void startBuzz(){
      if(pushPressed==0){
        Serial.println("pushPressed is false in blink");
        unsigned long currentMillis=millis();
        if(currentMillis-previousMillis>=interval){
          previousMillis=currentMillis;     //save the time you blinked the LED
          Serial.println("Start Buzzing");
          if(ledState==LOW){       //if LED is off turn it on and vice-versa
            ledState=HIGH;
           }
           else{
            ledState=LOW;
           }
           digitalWrite(ledPin,ledState);
        }
      }
      else if(pushPressed==1){
        Serial.println("pushpressed is true");
        ledState=LOW;
        digitalWrite(ledPin,ledState);
      }
    }
  
  void at9am(){
    DateTime now=rtc.now();
    if(int(now.hour())>=buzz9amHH){
      if(int(now.minute())>=buzz9amMM){
        if(int(now.second())>buzz9amSS){
          /////////////////////////////////
          startBuzz();
          /////////////////////////////////
        }
      }
    }
  }void at12pm(){
    DateTime now=rtc.now();
    if(int(now.hour())>=buzz12pmHH){
      if(int(now.minute())>=buzz12pmMM){
        if(int(now.second())>buzz12pmSS){
          /////////////////////////////////
          startBuzz();
          /////////////////////////////////
        }
      }
    }
  }void at3pm(){
    DateTime now=rtc.now();
    if(int(now.hour())>=buzz8pmHH){
      if(int(now.minute())>=buzz8pmMM){
        if(int(now.second())>buzz8pmSS){
          /////////////////////////////////
          startBuzz();
          /////////////////////////////////
        }
      }
    }
  }//Screen Cycling
  void changeScreen(){
    if(currentMillisLCD-previousMillisLCD>intervalLCD){
      previousMillisLCD=currentMillisLCD;
      screens++;
      if(screens>maxScreen){
        screens=0;
      }
      isScreenChanged=true;
    }
    if(isScreenChanged){
      isScreenChanged=false;
      switch(screens)
      {
        case getWellsoon:
        GetWellSoonMessage();
        break;
        case HELP_SCREEN:
        helpScreen();
        break;
        case TIME_SCREEN:
        timeScreen();
        break;
        default:
        break;
        
      }
    }
  }
   
  
 
