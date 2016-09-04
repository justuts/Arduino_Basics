// Pin setup (MEGA 2560):
  //SD:
    //CS | SS = 53
    //DI | MOSI = 51
    //D0 | MISO = 50
    //CLK | SK = 52
  //I2C bus:
    // SCL = 21
    // SDA = 20
  //GPS Serial:
    // board Rx = 19
    // baord Tx = 18
  //Boat Serial:
    // board Rx = 17
    // board Tx = 16
//#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>

//compass setup
#define addr_Comp 0x1E //I2C Address for compass (HMC5883)  

//gps setup
static const uint32_t baud_GPS = 9600;
#define buff_Max 100

//sd setup
static const int chipSelect = 53;
//variables
 String inputString = "";
 String boatString = "";
 int Machine_State = 1;
 static const byte A_Hz = 10,
                   B_Hz = 10,
                   C_Hz = 50,
                   Out_Hz = 10;
                  
 unsigned long A_Count = 0,
               B_Count = 0,
               C_Count = 0,
               Out_Count = 0;
 
 static String null_var = "NA";
 
 static String tmp_Comp_Read = "NA", A_Read = "NA";
 static String tmp_GPS_Read = "NA", B_Read = "NA";
 static String tmp_Boat_Read = "NA", C_Read = "NA";

void setup() {
  Serial.begin(9600);
  Wire.begin();
  //set up compass
  Wire.beginTransmission(addr_Comp); //start talking
  Wire.write(0x02); // Set the Register
  Wire.write(0x00); // Tell the HMC5883 to Continuously Measure
  Wire.endTransmission();
  
  // Set up gps
   Serial1.begin(baud_GPS);
   inputString.reserve(buff_Max);
  // Set up boat
//   Serial2.begin(baud_boat);
//   boatString.reserve(buff_Max);

  // Set up card
   Serial.print(F("Initializing SD card..."));
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) 
  {
    Serial.println(F("Card failed, or not present"));
    // don't do anything more:
    return;
  } else {
  Serial.println(F("card initialized.")); }
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // A = compass, B = GPS, C = boat NMEA
  
  switch (Machine_State) {
    case 1:{ //check_A
      if ( millis() - A_Count > 1000/A_Hz ) {
        Machine_State = 5; // go to read_A
        //Serial.println(F("going to state 5"));
        break; } else {
          Machine_State = 2; // go to check_B
      //    Serial.println(F("going to state 2"));
          break; } }
      
     case 2:{
      if ( millis() - B_Count > 1000/B_Hz ) {
        Machine_State = 6;
      //  Serial.println(F("going to state 6"));
        break; } else {
          Machine_State = 3;
      //    Serial.println(F("going to state 3"));
          break; } }
          
     case 3:{
      if ( millis() - C_Count > 1000/C_Hz ) {
        Machine_State = 7;
    //    Serial.println(F("going to state 7"));
        break; } else {
          Machine_State = 4;
     //     Serial.println(F("going to state 4"));
          break; } }
     
     case 4:{
      if ( millis() - Out_Count > 1000/Out_Hz ) {
        Machine_State = 8;
   //     Serial.println(F("going to state 8"));
        break; } else {
          Machine_State = 1;
     //     Serial.println(F("going to state 1"));
          break; } }
          
     case 5: {
       tmp_Comp_Read = read_compass();
       if(tmp_Comp_Read != null_var) 
       {
       A_Read = tmp_Comp_Read;
       tmp_Comp_Read = null_var;
       }
       A_Count = millis();
       Machine_State = 2;
  //     Serial.println(F("going to state 2"));
       break; }
       
     case 6: {
       tmp_GPS_Read = read_gps();
       if(tmp_GPS_Read != null_var) 
       {
       B_Read = tmp_GPS_Read;
       tmp_GPS_Read = null_var;
       }
       B_Count = millis();
       Machine_State = 3;
   //    Serial.println(F("going to state 3"));
       break; }
       
     case 7: {
       tmp_Boat_Read = read_boat_test();
       if(tmp_Boat_Read != null_var) 
       {
       C_Read = tmp_Boat_Read;
       tmp_Boat_Read = null_var;
       }
       C_Count = millis();
       Machine_State = 4;
  //     Serial.println(F("going to state 4"));
       break; }
       
     case 8: {
       write_to_sd(A_Read,B_Read,C_Read);
       Out_Count = millis();
       A_Read = null_var;
       B_Read = null_var;
       C_Read = null_var;
       Machine_State = 1;
      // Serial.println("going to state 1");
       break; }
  }      
}


