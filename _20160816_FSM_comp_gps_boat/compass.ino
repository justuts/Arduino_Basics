
String read_compass(){
  
  int x_Comp,y_Comp,z_Comp;
  String output_Comp;
  uint8_t reg_read;
  
  Wire.beginTransmission(addr_Comp);
  Wire.write(0x02); //start with register 3.
  Wire.endTransmission();
  
  Wire.beginTransmission(addr_Comp);
  Wire.write(0x03); //start with register 3.
  Wire.endTransmission();
  
 //Read compass data.. 2 bytes for each axis.. 6 total bytes
 //Should divide by gain to get teslas
 
  Wire.requestFrom(addr_Comp, 6);
  if(6<=Wire.available()){
    x_Comp = Wire.read()<<8; //MSB  x 
    x_Comp |= Wire.read(); //LSB  x
    z_Comp = Wire.read()<<8; //MSB  z
    z_Comp |= Wire.read(); //LSB z
    y_Comp = Wire.read()<<8; //MSB y
    y_Comp |= Wire.read(); //LSB y

    output_Comp = "\"" + String(x_Comp) + "," +
                  String(y_Comp) + "," +
                  String(z_Comp) + "\"";
    return output_Comp;
  } else {return null_var;}
}
  
  
  
