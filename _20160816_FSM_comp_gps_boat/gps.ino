String read_gps(){
 inputString = "";
 if(Serial1.available() > 0) 
 {
   inputString = Serial1.readStringUntil('\n');
 }
 if (inputString.length() > 0) 
 {
   return "\"" + inputString + "\""; 
 } else { return null_var;}
}
