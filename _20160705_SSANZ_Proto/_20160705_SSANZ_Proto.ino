// Pin setup:
  //SD:
    //CS = 10
    //DI = 11
    //D0 = 12
    //CLK = 13
  //I2C bus:
    // SCL = A5
    // SDA = A4
  //GPS Serial:
    // Rx = 2
    // Tx = 3
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>

//compass setup
#define addr_Comp 0x1E //I2C Address for compass (HMC5883)

//gps setup
static const int RxPin_GPS = 2, TxPin_GPS = 3;
static const uint32_t baud_GPS = 9600;
TinyGPSPlus GPS;
SoftwareSerial port_GPS(RxPin_GPS,TxPin_GPS);

//sd setup
static const int chipSelect = 10;

void setup(){
  
  Serial.begin(9600);
  Wire.begin();
  // Set up I2C components
  Wire.beginTransmission(addr_Comp); //start talking
  Wire.write(0x02); // Set the Register
  Wire.write(0x00); // Tell the HMC5883 to Continuously Measure
  Wire.endTransmission();
  
  // Set up soft serial components
  port_GPS.begin(baud_GPS);
  
  // Set up SD reader
  Serial.print("Initializing SD card...");
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) 
  {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  } else {
  Serial.println("card initialized."); }
}

void loop(){
  
  Serial.println("entered loop");
  int x_Comp,y_Comp,z_Comp; //triple axis data
  String output_Comp,output_GPS,output_csv;

  //Tell the HMC what regist to begin writing data into
  Wire.beginTransmission(addr_Comp);
  Wire.write(0x03); //start with register 3.
  Wire.endTransmission();
  Serial.println("spoke to compass");
  
 
 //Read compass data.. 2 bytes for each axis.. 6 total bytes
 //Should divide by gain to get teslas
  Wire.requestFrom(addr_Comp, 6);
  if(6<=Wire.available()){
    x_Comp = Wire.read()<<8; //MSB  x 
    x_Comp |= Wire.read(); //LSB  x
    z_Comp = Wire.read()<<8; //MSB  z
    z_Comp |= Wire.read(); //LSB z
    y_Comp = Wire.read()<<8; //MSB y
    y_Comp |= Wire.read(); //LSB y
  }
  Serial.println("heard back from compass");
  output_Comp = String(x_Comp) + "," +
                String(y_Comp) + "," +
                String(z_Comp);
  Serial.println(output_Comp);
  output_GPS = read_GPS(); //lat, lon, course, speed, date, timeUTC
  Serial.println("read gps");
  Serial.println(output_GPS);
  output_csv = output_Comp + "," +
               output_GPS;
  
  Serial.println(output_csv);
  Serial.println("writing to card");
  File dataFile = SD.open("SSANZ_Data.txt", FILE_WRITE);
  
  if (dataFile) {
    dataFile.println(output_csv);
    dataFile.close();
    Serial.println(output_csv);
  }
  delay(500);
}

String read_GPS ()
{
  unsigned long lat_GPS,lng_GPS,course_GPS,speed_GPS,date_GPS,time_GPS;
  int startmilli = millis();
  
  while( (port_GPS.available() > 0) )//&& (millis()-startmilli < 80) )
  {
  if(GPS.encode(port_GPS.read())==1)
  break;
  } 
    if(GPS.time.isUpdated())
    {
      if(GPS.location.isValid())
      {
        lat_GPS = GPS.location.lat();
        lng_GPS = GPS.location.lng();
      }
      if(GPS.speed.isValid())
      {
        speed_GPS = GPS.speed.value();
      } 
      if(GPS.course.isValid())
      {
        course_GPS = GPS.course.value();
      }
      if(GPS.time.isValid())
      {
        date_GPS = GPS.date.value();
        time_GPS = GPS.time.value();
      }
    }
    return(String(lat_GPS) + "," +
           String(lng_GPS) + "," +
           String(course_GPS) + "," +
           String(speed_GPS) + "," +
           String(date_GPS) + "," +
           String(time_GPS) );
  }
  
  
  
  
