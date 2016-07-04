#include <Wire.h> //I2C Arduino Library
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define addr 0x1E //I2C Address for The HMC5883

static const int RxPin_GPS = 2, TxPin_GPS = 3;
static const uint32_t baud_GPS = 9600;

TinyGPSPlus GPS;
SoftwareSerial port_GPS(RxPin_GPS,TxPin_GPS);

void setup(){
  
  Serial.begin(9600);
  Wire.begin();
  // Set up compass
  Wire.beginTransmission(addr); //start talking
  Wire.write(0x02); // Set the Register
  Wire.write(0x00); // Tell the HMC5883 to Continuously Measure
  Wire.endTransmission();
  
  // Set up soft serials
  port_GPS.begin(baud_GPS);
}


void loop(){
  
  int x,y,z; //triple axis data

  //Tell the HMC what regist to begin writing data into
  Wire.beginTransmission(addr);
  Wire.write(0x03); //start with register 3.
  Wire.endTransmission();
  
 
 //Read the data.. 2 bytes for each axis.. 6 total bytes
  Wire.requestFrom(addr, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8; //MSB  x 
    x |= Wire.read(); //LSB  x
    z = Wire.read()<<8; //MSB  z
    z |= Wire.read(); //LSB z
    y = Wire.read()<<8; //MSB y
    y |= Wire.read(); //LSB y
  }
  
  // Show Values -- note these should be divided by gain to get field stregth
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.print(z);
  Serial.print(",");
  read_GPS();
  Serial.println();
  
  delay(500);
}

void read_GPS ()
{
  int startmilli = millis();
  while( (port_GPS.available() > 0) )//&& (millis()-startmilli < 80) )
  {
  if(GPS.encode(port_GPS.read())==1)
  break;
  } 
  
    if(GPS.location.isValid())
    {
      Serial.print(GPS.location.lat(),6);
      Serial.print(",");
      Serial.print(GPS.location.lng(),6);
    } else {Serial.print("NA,NA");}
    Serial.print(",");
    if(GPS.speed.isValid())
    {
      Serial.print(GPS.speed.value());
    } else Serial.print("NA");
    Serial.print(",");
    if(GPS.course.isValid())
    {
      Serial.print(GPS.course.value());
    } else Serial.print("NA");
    Serial.print(",");
    if(GPS.time.isValid())
    {
      Serial.print(GPS.date.value());
      Serial.print("-");
      Serial.print(GPS.time.value());
    }
    return;
  }
