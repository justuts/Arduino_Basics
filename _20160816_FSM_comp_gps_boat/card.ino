void write_to_sd(String a,String b,String c,String d){
  
  String timeStamp = String(millis());
  
  Serial.print("\"" + timeStamp + "\"");
  Serial.print(',');
  Serial.print(a);
  Serial.print(',');
  Serial.print(b);
  Serial.print(',');
  Serial.print(c);
  Serial.print(',');
  Serial.println(d);
  
  File dataFile = SD.open("DAT.txt", FILE_WRITE); //short filename needs < 8.3 format
  
  if (dataFile) {
  
  dataFile.print("\"" + timeStamp + "\"");
  dataFile.print(',');
  dataFile.print(a);
  dataFile.print(',');
  dataFile.print(b);
  dataFile.print(',');
  dataFile.print(c);
  dataFile.print(',');
  dataFile.println(d);
    dataFile.close();
    Serial.println(F("Wrote to Card"));
    } else {Serial.println(F("no Card"));}
}
