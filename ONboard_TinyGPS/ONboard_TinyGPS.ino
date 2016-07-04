
#include <TinyGPS++.h>

// The TinyGPS++ object
TinyGPSPlus MUX_NMEA;

/*
   (Counting starts with the field immediately following the sentence name, 
   i.e. $GPGSA.  For more information on NMEA sentences, consult your
   GPS module's documentation and/or http://aprs.gids.nl/nmea/.)
*/

TinyGPSCustom boat_speed(MUX_NMEA, "IIVHW", 5); // $VHW sentence, 5th element
TinyGPSCustom wind_speed(MUX_NMEA, "IIMWV", 3);
TinyGPSCustom wind_angle(MUX_NMEA, "IIVWR", 1);// apparent angle from bow
TinyGPSCustom tack(MUX_NMEA, "IIVWR",2);// returns R for stb, L for port

void setup() 
{

  Serial.begin(4800);
  
  Serial.println("Ready");
  Serial.println();
}

void loop() 
{
  // Every time anything is updated, print everything.
  if (boat_speed.isUpdated()||wind_speed.isUpdated()||wind_angle.isUpdated()||tack.isUpdated())
  {
    Serial.print("STW: ");
    Serial.println(boat_speed.value());
    Serial.print("AWS: ");
    Serial.println(wind_speed.value());
    Serial.print("AWA: ");
    Serial.println(wind_angle.value());
    Serial.print("AWT: ");
    if (tack.value() == "R") 
    {
      Serial.println("STB");
    }
    else
    {
      if (tack.value() == "L")
      { Serial.println("PRT"); }
      else Serial.println(tack.value());
    } 
   Serial.println();
   Serial.println(); 
  }
  while (Serial.available() > 0)
    MUX_NMEA.encode(Serial.read());
}
