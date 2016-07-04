#include <SoftwareSerial.h>
// software serial #1: TX = digital pin 10, RX = digital pin 11
SoftwareSerial portOne(10,11);
SoftwareSerial portTwo(8,9);

void setup()
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   // Start each software serial port
  portOne.begin(9600);
  portTwo.begin(9600);
}

String sentance;
void loop()
{
  digitalWrite(13,HIGH);
  delay(1000);
  // By default, the last intialized port is listening.
  // when you want to listen on a port, explicitly select it:
  portOne.listen();
  Serial.println("Data from port one:");
  // while there is data coming in, read it
  // and send to the hardware serial port:
  while (portOne.available() > 0) 
  {
    char inChar = portOne.read();
    
    if(inChar == '\n')
    {
      parseCommandtest(sentance);
      sentance = "";
    } else {
    sentance += inChar; }
    Serial.write(inChar);
  }

  // blank line to separate data from the two ports:
  Serial.println();

  // Now listen on the second port
  portTwo.listen();
  // while there is data coming in, read it
  // and send to the hardware serial port:
  Serial.println("Data from port two:");
  while (portTwo.available() > 0) {
    
    char inChar = portTwo.read();
    
    if(inChar == '\n')
    {
      parseCommandtest(sentance);
      sentance = "";
    } else {
    sentance += inChar; }
    Serial.write(inChar);
  }

  // blank line to separate data from the two ports:
  Serial.println();
}


void parseCommand(String sent, String code)
{
  if(sent.lastIndexOf("$") == -1)
  {}
  else
  { String clipped = sent.substring(sent.lastIndexOf("$"));
    if (clipped.substring(0,5) == code)
    {Serial.println(clipped);}
  }
}

void parseCommandtest(String sent)
{
  if(sent.lastIndexOf("$") == -1)
  {}
  else
  { String clipped = sent.substring(sent.lastIndexOf("$"));
    if (clipped.substring(0,5) == "$GPRM")
    {Serial.println(clipped);}
  }
}

