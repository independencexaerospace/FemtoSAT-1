void MPU6050_check(){

  mpu.update();
Roll=mpu.getAngleX()*100;
Pitch=mpu.getAngleY()*100;
Yaw=mpu.getAngleZ()*100;

X_Accel=mpu.getAccX()*100;
Y_Accel=mpu.getAccY()*100;
Z_Accel=mpu.getAccZ()*100;

//EEPROM DATA CONVERSION

//ERoll=Roll*10;
//EPitch=Pitch*10;
//EYaw=Yaw*10;
//EX_Acc=X_Accel*10;
//EY_Acc=Y_Accel*10;
//EZ_Acc=Z_Accel*10;
}
