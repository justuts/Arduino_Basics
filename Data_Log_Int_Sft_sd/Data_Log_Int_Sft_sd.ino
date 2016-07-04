// DS3232 I2C square-wave generator

#include<Time.h>
#include <Wire.h>
#include <DS3232RTC.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

static const int RxPin1 = 4, TxPin1 = 3;
static const uint32_t GPS1baud = 9600;
const int chipSelect = 10; // set sd CS to pin 10

int sqwvpin = 2;// mut be on pin 2 with itrupt = 0
int irupt = 0;
time_t nowTime;
long StartOfSecond = 0;
boolean getTimeFlag = 0;
int MilliTime = 0;

String acString;
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
  
  Serial.print("Initializing SD card...");
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void loop()
{

 if(getTimeFlag == 1)
{ nowTime = RTC.get();
  StartOfSecond = millis();
  getTimeFlag = 0; 
}
 delay(40);   
 MilliTime = millis() - StartOfSecond;
 if(MilliTime > 999) return;
 
 acString =
     String( hour(nowTime) +
     printDigits(minute(nowTime)) +
     printDigits(second(nowTime)) + 
     printMilliDigits(MilliTime) +
     "," +
     GPS1data() );
  
   File dataFile = SD.open("ACM_test.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(acString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(acString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }    
  
}

String printDigits(int digits)
{
  String rtnstring;
    // utility function for digital clock display: prints preceding colon and leading 0
    if( digits < 10)
   
     { rtnstring = ":0";
      rtnstring += digits;}
    
    else
   // {
     {rtnstring = ":";
      rtnstring += digits;}
 //   }

    return(rtnstring);
}

String printMilliDigits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
  String rtnstring;
    if(digits < 100)
    {
       if(digits < 10){
       rtnstring = ":00";
    } else { rtnstring = ":0"; }
    } else { rtnstring = ":"; }   
  rtnstring += digits;
  return(rtnstring);
}

void isr_func() 
{
  getTimeFlag = 1;
}

String GPS1data ()
{
  int startmilli = millis();
  while( (portOne.available() > 0) )//&& (millis()-startmilli < 80) )
  {
  if(gps.encode(portOne.read())==1)
  break;
  } 
    String rtnstring;
    if(gps.location.isValid())
    {
      rtnstring += String(gps.location.lat(),6);
      rtnstring += (",");
      rtnstring += String (gps.location.lng(),6);
    } else {rtnstring += String("NA,NA");}
    rtnstring += (",");
    if(gps.speed.isValid())
    {
      rtnstring += String(gps.speed.value());
    } else rtnstring += ("NA");
    rtnstring += (",");
    if(gps.course.isValid())
    {
      rtnstring += String(gps.course.value());
    } else rtnstring += ("NA");
    return(rtnstring);
//   else {
//  Serial.print("NA,NA,X,NA");
//  return; }
  
}
