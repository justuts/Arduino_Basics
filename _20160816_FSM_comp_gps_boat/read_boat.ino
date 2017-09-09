String read_boat(){
 boatString = "";
 if(Serial2.available() > 0) 
 {
   boatString = Serial2.readStringUntil('\n');
 }
 if (boatString.length() > 0) 
 {
   return "\"" + boatString + "\""; 
 } 
 else 
 { 
  return "\"" + null_var + "\"";
 }
}
