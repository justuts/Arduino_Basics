


// the setup function runs once when you press reset or power the board

int RedPins[] = {13, 12, 7};
int GreenPin = 6;
int SwitchPin = 2;
int flashdel = 100;
int RedPinsCount = (sizeof(RedPins) / sizeof(RedPins[1]));
int SwitchState = 0;

void setup() {
  Serial.begin(9600);
  for ( int p = 0; p < sizeof(RedPins) - 1; p++) {
    pinMode(RedPins[p], OUTPUT);
  }

  pinMode(GreenPin, OUTPUT);
  pinMode(SwitchPin, INPUT);
}

// the loop function runs over and over again forever
void loop() {

  if (buttonPressed() == 1) {
    delay(500);
    Serial.println(1);
    lightsOn();
    }  
  }

boolean buttonPressed() {

  long time = millis();
  int debounce = 30;
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

void lightsOn () {

  SwitchState = 1;
  digitalWrite(GreenPin, HIGH);
  // build the sequence to flash leds
  int flashsqLen = (RedPinsCount * 2) - 2;
  int flashsq[flashsqLen];
  for ( int i = 0; i < RedPinsCount; i++) {
    flashsq[i] = RedPins[i];
  }
  int tick = 0;
  for ( int i = RedPinsCount - 2; i > 0; i--) {
    flashsq[RedPinsCount + tick] = RedPins[i];
    tick = tick++;
  }
  // then run through the sequence
  while (1 == 1) {
  if(SwitchState == 0) { break; }
  for (int f = 0; f < flashsqLen; f++) {
    if (buttonPressed() == 1 ) {
      lightsOff();
      delay(100);
      break;
    }
    digitalWrite(flashsq[f], HIGH);
    delay(flashdel);
    digitalWrite(flashsq[f], LOW);
  } }
}

void lightsOff () {
  SwitchState = 0;
  digitalWrite(GreenPin, LOW);
  for (int p = 0; p < RedPinsCount; p++) {
    digitalWrite(RedPins[p], LOW);
  }
  delay(500);
}
