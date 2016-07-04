
void setup() {
  Serial.begin(4800);
}

String sentance;

void loop() {
  while (Serial.available()) {
    char inChar = Serial.read();
    
    if(inChar == '\n')
    { Serial.print("testing,");
     Serial.println(sentance);
    //  parseCommand(sentance);
    //  Serial.println(sentance);
      sentance = "";
    } else {
    sentance += inChar; }
     }
}

void parseCommand(String sent)
{
  if(sent.lastIndexOf("$") == -1)
  {}
  else
  { String clipped = sent.substring(sent.lastIndexOf("$"));
    if (clipped.substring(0,3) == "$II")
    {Serial.println(clipped);}
  }
}

void testparseCommand(String sent)
{
  String clipped = sent.substring(sent.lastIndexOf("$"),5);
 Serial.println(clipped); 
}
    
