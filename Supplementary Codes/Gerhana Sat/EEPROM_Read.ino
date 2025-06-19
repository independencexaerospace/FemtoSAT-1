//------------------------------KEY CODE---------------------------------------------------

void EEPROM_Read_check(){ 
  
    for (address=0 ; address<=500 ; address++)
  {

   Serial.print(address); Serial.print(","); //Serial.print(value); Serial.print(", ");
  
   check_value = readEEPROM(EEPROM_I2C_ADDRESS, address); 
   Serial.print(check_value);
   Serial.print(",");
   delay(10);
  }
  inByte='c';
  
  
  
  }


//------------------------------------------------------------------------------------------

byte readEEPROM(int deviceaddress, unsigned int eeaddress ) 
{
  byte rdata = 0xFF;
  
  if(maxaddress <= 255) 
   {
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress));
    Wire.endTransmission();
   }

  if(maxaddress >= 511) 
   {
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8));   // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.endTransmission();
   }

   Wire.requestFrom(deviceaddress,1);

   if (Wire.available()) rdata = Wire.read();
 
   return rdata;
}
