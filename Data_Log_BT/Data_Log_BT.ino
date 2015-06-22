
int RedPin = 12;
int SwitchPin = 13;
int PotPin = A0;
float logHz = 0.5;


boolean buttonPressed() {

  long time = millis();
  int debounce = 50;
  boolean previous = digitalRead(SwitchPin);
  boolean lastRead = 0;

  while (millis() - time < debounce) {
    lastRead = digitalRead(SwitchPin);
    if (lastRead != previous) {
      time = millis();
      previous = lastRead ;
    }
  }

  return (lastRead);
}

void doLog() {
  
    digitalWrite(RedPin, HIGH);
    delay(500);
    
    while( !buttonPressed() ){
      
      Serial.print( millis() );
      Serial.print(",");
      Serial.println( analogRead(PotPin) );
      if(buttonPressed()) {break;}
      delay(1000 / logHz); }
   
    digitalWrite(RedPin, LOW);
    delay(500); }  

void setup() {
  Serial.begin(9600);
  
  pinMode(RedPin, OUTPUT);
  pinMode(SwitchPin, INPUT);
}

void loop() {
  
  if( buttonPressed() )
  
  doLog ();
  
}
