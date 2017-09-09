void write_to_sd_test(String a,String b,String c,String d)
{
  Serial.print(a);
  Serial.print(',');
  Serial.print(b);
  Serial.print(',');
  Serial.println(c);
  Serial.print(',');
  Serial.println(d);
  Serial.println("wrote to card test");
}
