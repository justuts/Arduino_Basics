void write_to_sd(String a,String b,String c){
  
  Serial.print(a);
  Serial.print(',');
  Serial.print(b);
  Serial.print(',');
  Serial.println(c);
  File dataFile = SD.open("dat.txt", FILE_WRITE); //short filename needs < 8.3 format
  
  if (dataFile) {
  dataFile.print(a);
  dataFile.print(',');
  dataFile.print(b);
  dataFile.print(',');
  dataFile.println(c);
    dataFile.close();
    Serial.println(F("Wrote to Card"));
    } else {Serial.println(F("no Card"));}
}
