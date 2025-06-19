//------------------------------KEY CODE---------------------------------------------------




void EEPROM_Write_check(){ 
  
int test1=90;
int test2=80;

   writeEEPROM(EEPROM_I2C_ADDRESS, address, inByte);
   //Serial.print(address); Serial.print(","); Serial.print(ETemp); Serial.print(", ");
   address++;
   writeEEPROM(EEPROM_I2C_ADDRESS, address, test1);
     // Serial.print(address); Serial.print(","); Serial.print(EPres); Serial.print(", ");
      address++;
   writeEEPROM(EEPROM_I2C_ADDRESS, address, test2);
     // Serial.print(address); Serial.print(","); Serial.print(EHum); Serial.print(", ");
      address++;
   writeEEPROM(EEPROM_I2C_ADDRESS, address, 96);
     // Serial.print(address); Serial.print(","); Serial.print(EAlt); Serial.print(", ");
      address++;
   writeEEPROM(EEPROM_I2C_ADDRESS, address, 115);
     // Serial.print(address); Serial.print(","); Serial.print(ERoll); Serial.print(", ");
      address++;
   writeEEPROM(EEPROM_I2C_ADDRESS, address, 46);
     // Serial.print(address); Serial.print(","); Serial.print(EPitch); Serial.print(", ");
      address++;
//   writeEEPROM(EEPROM_I2C_ADDRESS, address, EYaw);
//      address++;
//   writeEEPROM(EEPROM_I2C_ADDRESS, address, EX_Acc);
//      address++;
//   writeEEPROM(EEPROM_I2C_ADDRESS, address, EY_Acc);
//      address++;
//   writeEEPROM(EEPROM_I2C_ADDRESS, address, EZ_Acc);
//      address++;
//   writeEEPROM(EEPROM_I2C_ADDRESS, address, Ebvolt);
//      address++;
//   writeEEPROM(EEPROM_I2C_ADDRESS, address, Ecurr);
//      address++;
//   writeEEPROM(EEPROM_I2C_ADDRESS, address, ELAT);
//         address++;
//   writeEEPROM(EEPROM_I2C_ADDRESS, address, ELON);
//         address++;
   delay(100);
  
  
  
  
  }


//------------------------------------------------------------------------------------------

void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data ) 
{
  if (maxaddress <= 255) 
   {
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress));
    Wire.write(data);
    Wire.endTransmission();
   }
   
  if(maxaddress >= 511) 
   {
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8));   // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.write(data);
    Wire.endTransmission();
   }
   
  delay(5);
}
