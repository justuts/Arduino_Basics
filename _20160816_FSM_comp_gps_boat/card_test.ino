void write_to_sd_test(String a,String b,String c)
{
  Serial.print(a);
  Serial.print(',');
  Serial.print(b);
  Serial.print(',');
  Serial.println(c);
  Serial.println("wrote to card");
}
