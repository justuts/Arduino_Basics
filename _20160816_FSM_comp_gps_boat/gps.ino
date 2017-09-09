String read_gps(){
 inputString = "";
 if(Serial1.available() > 0) 
 {
   inputString = Serial1.readStringUntil('\n');
 }
 if (inputString.length() > 0 & inputString[0] == '$' &
     inputString[1] == 'G' & inputString[2] == 'P' &
     inputString[3] == 'R' & inputString[4] == 'M' &
     inputString[5] == 'C') 
 {
   return "\"" + inputString + "\""; 
 } else { return "\"" + null_var + "\"";}
}
