


// the setup function runs once when you press reset or power the board

int RedPins[] = {13,12,7};
int GreenPin = 2;
int flashdel = 100;

void setup() {
  Serial.begin(9600);
  for ( int p = 0; p < sizeof(RedPins) - 1; p++){
        pinMode(RedPins[p], OUTPUT); }
        
  pinMode(GreenPin, OUTPUT); 
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(GreenPin, HIGH);  
  
  int RedPinsCount = (sizeof(RedPins)/sizeof(RedPins[1]));
  
  int flashsqLen = (RedPinsCount*2) - 2;
  
      // Serial.print(flashsqLen);
       
  int flashsq[ flashsqLen ];
  
    for ( int i = 0; i < RedPinsCount; i++) { flashsq[i] = RedPins[i]; }
  
       int tick = 0;
    for ( int i = RedPinsCount-2; i > 0; i--) { 
      flashsq[RedPinsCount + tick] = RedPins[i];
   
      tick = tick++;}
      
  for (int f = 0; f < flashsqLen; f++){
   
    digitalWrite(flashsq[f], HIGH);
    delay(flashdel);
    digitalWrite(flashsq[f], LOW); }
}
