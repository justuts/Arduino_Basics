int incomingByte = 0;   // for incoming serial data
int pin = 8;
void setup() {
  

        Serial.begin(4800);     // opens serial port, sets data rate to 9600 bps
        Serial.println("ready");
}

void loop() {

    pinMode(pin, OUTPUT);           // set pin to input
digitalWrite(pin, HIGH);
        // send data only when you receive data:
        if(Serial.available()==0) {Serial.println("Nothing");}
        else{
        if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();

                // say what you got:
                if(!incomingByte == '\n')
                {Serial.println(incomingByte);} else
                {}}
        }
}
