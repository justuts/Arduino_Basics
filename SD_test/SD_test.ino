// Pin setup:
  //SD:
    //CS = 10
    //DI = 11
    //D0 = 12
    //CLK = 13
    
    ///////CODE DOESNT CURRENTLY WORK!!!!!/////////
    
#include <SPI.h>
#include <SD.h>

//sd setup
static const int chipSelect = 10;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
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

void loop() {
  String output_csv = "bringmemywine";
  
  File dataFile = SD.open("SSANZ_Data.txt", FILE_WRITE);
  
  if (dataFile) {
    dataFile.println(output_csv);
    dataFile.close();
    Serial.println(output_csv);
  }
  
  delay(500);
  // put your main code here, to run repeatedly:

}
