void INA219_check(){


  shuntvoltage = ina219.getShuntVoltage_mV();
//  busvoltage = ina219.getBusVoltage_V();
//  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW()*100;
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  Power=busvoltage*(current_mA/1000);
  
  int voltageformap=busvoltage*100;
  mapvoltage=map(voltageformap,370, 420,0,100);
  
//EEPROM DATA CONVERSION
//  EVolt=busvoltage*10;
//  ECurr=current_mA*10;
//  EPOW=power_mW*10;

  

  
}
