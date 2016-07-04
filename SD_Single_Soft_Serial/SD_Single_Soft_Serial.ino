/*
  SD card datalogger

 This example shows how to log data from three analog sensors
 to an SD card using the SD library.

 The circuit:
 * analog sensors on analog ins 0, 1, and 2
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 10

 created  24 Nov 2010
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

const int chipSelect = 10;
SoftwareSerial portOne(8,7);

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // Start each software serial port
  portOne.begin(9600);
  
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

String sentance;
String portOneString;

void loop()
{
 delay(1000);
 portOne.listen();
 Serial.print("PortOne,");
 
 portOneString = "NA";
 int startTime = millis();
  while(portOneString == "NA")
    {  
     if (millis()-startTime > 1000){break;}
     while(portOne.available() > 0)
    {
     char inChar = portOne.read(); 
     if(inChar == '\n')
     {
       portOneString = parseCommand(sentance);
       sentance = "";
     }
     else 
     {
       sentance += inChar; 
     }
    }
   }
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("data_file.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(portOneString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(portOneString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}

String parseCommand(String sent)
{
  if(sent.lastIndexOf("$") == -1)
  {return("NA");}
  else
  { String clipped = sent.substring(sent.lastIndexOf("$"));
    if (clipped.substring(0,5) == "$GPRM")
    {return(clipped);} else {return("NA");}
  }
}








