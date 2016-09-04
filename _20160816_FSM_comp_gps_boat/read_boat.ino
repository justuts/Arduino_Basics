String read_boat(){
 boatString = "";
 if(Serial.available() > 0) 
 {
   boatString = Serial.readStringUntil('\n');
 }
 if (boatString.length() > 0) 
 {
   return "\"" + boatString + "\""; 
 } 
 else 
 { 
 return null_var;
 }
}
