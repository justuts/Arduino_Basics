#include <Time.h>
#include <DS3232RTC.h>
#include <Wire.h>  

int RedPin = 12;
int SwitchPin = 13;
int PotPin = A0;
float logHz = 0.5;


boolean buttonPressed() {

  long time = millis();
  int debounce = 50;
  boolean previous = digitalRead(SwitchPin);
  boolean lastRead = 0;

  while (millis() - time < debounce) {
    lastRead = digitalRead(SwitchPin);
    if (lastRead != previous) {
      time = millis();
      previous = lastRead ;
    }
  }

  return (lastRead);
}

void printDigits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    Serial.print(':');
    if(digits < 10)
        Serial.print('0');
    Serial.print(digits);
}

void doLog() {
  
    digitalWrite(RedPin, HIGH);
    delay(500);
    
    while( !buttonPressed() ){
      
      time_t myTime;
      myTime = RTC.get();
      
        Serial.print(hour(myTime));     
      printDigits(minute(myTime));
      printDigits(second(myTime));
      
      Serial.print(",");
      Serial.println( analogRead(PotPin) );
      if(buttonPressed()) {break;}
      delay(1000 / logHz); }
   
    digitalWrite(RedPin, LOW);
    delay(500); }  

void setup() {
  Serial.begin(9600);
  
  pinMode(RedPin, OUTPUT);
  pinMode(SwitchPin, INPUT);
}

void loop() {
  
  if( buttonPressed() ){
  //setTime(22,35,20,21,06,2015);
  //RTC.set(now());
  doLog ();}
  
}
