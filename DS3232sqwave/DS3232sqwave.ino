// DS3232 I2C square-wave generator

#include<Time.h>
#include <Wire.h>
#include <DS3232RTC.h>

int sqwvpin = 2;// mut be on pin 2 with itrupt = 0
int irupt = 0;

void setup()
{
  pinMode(sqwvpin, INPUT);
  Wire.begin();
  Serial.begin(9600);
  
  RTC.squareWave(SQWAVE_1_HZ);
attachInterrupt(irupt, isr_func, RISING);
}


void loop()
{  
 delay(250);   
 time_t myTime;
    myTime = RTC.get();
    
     Serial.print(hour(myTime));     
     printDigits(minute(myTime));
     printDigits(second(myTime));
     Serial.print(",");
   
    if(digitalRead(sqwvpin) == HIGH){
      Serial.println("HIGH");} else {
        Serial.println("LOW");} 
}



void printDigits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    Serial.print(':');
    if(digits < 10)
        Serial.print('0');
    Serial.print(digits);
}

void isr_func() {
 
//counter = counter+1; 
 Serial.println("Hello World");
  
}
