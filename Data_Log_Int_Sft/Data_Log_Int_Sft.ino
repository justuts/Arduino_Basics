// DS3232 I2C square-wave generator

#include<Time.h>
#include <Wire.h>
#include <DS3232RTC.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RxPin1 = 4, TxPin1 = 3;
static const uint32_t GPS1baud = 9600;

int sqwvpin = 2;// mut be on pin 2 with itrupt = 0
int irupt = 0;
time_t nowTime;
long StartOfSecond = 0;
boolean getTimeFlag = 0;
int MilliTime = 0;

char c;
TinyGPSPlus gps;

SoftwareSerial portOne(RxPin1, TxPin1);

void setup()
{
  pinMode(sqwvpin, INPUT);
  Wire.begin();
  Serial.begin(9600);
  
  RTC.squareWave(SQWAVE_1_HZ);
  attachInterrupt(irupt, isr_func, RISING);
  
  portOne.begin(GPS1baud);
}

void loop()
{

 if(getTimeFlag == 1)
{ nowTime = RTC.get();
  StartOfSecond = millis();
  getTimeFlag = 0; 
}
 delay(87);   
 //nowTime = RTC.get();
 MilliTime = millis() - StartOfSecond;
 if(MilliTime > 999) return;
 
     Serial.print(hour(nowTime));     
     printDigits(minute(nowTime));
     printDigits(second(nowTime));
     printMilliDigits(MilliTime);
     Serial.print(",");
     GPS1data();
     Serial.println();
   }

void printDigits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    Serial.print(':');
    if(digits < 10)
        Serial.print('0');
    Serial.print(digits);
}

void printMilliDigits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    Serial.print(':');
    if(digits < 100)
    {
       if(digits < 10){
       Serial.print("00");
    } else { Serial.print('0'); }
    }   
    Serial.print(digits);
}

void isr_func() 
{
  getTimeFlag = 1;
}

void rawdata ()
{
  while(portOne.available()>0)
  if(gps.encode(portOne.read())==1)
  Serial.print("Data Coded");
 
}


void GPS1data ()
{
  int startmilli = millis();
  while( (portOne.available() > 0) )//&& (millis()-startmilli < 80) )
  {
  if(gps.encode(portOne.read())==1)
  break;
  } 
  
    if(gps.location.isValid())
    {
      Serial.print(gps.location.lat(),6);
      Serial.print(",");
      Serial.print(gps.location.lng(),6);
    } else {Serial.print("NA,NA");}
    Serial.print(",");
    if(gps.speed.isValid())
    {
      Serial.print(gps.speed.value());
    } else Serial.print("NA");
    Serial.print(",");
    if(gps.course.isValid())
    {
      Serial.print(gps.course.value());
    } else Serial.print("NA");
    return;
//   else {
//  Serial.print("NA,NA,X,NA");
//  return; }
  
}
