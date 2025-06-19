/**********************************************************************
 * DESCRIPTION:
 * This code is for GERHANASAT DEMONSTRATION
 * 
 * SENSORS USED
 * 
 * 1)MPU6050
 * I2C ADDRESS: 0x68
 * 
 * 2)INA219
 * I2C ADDRESS: 0x40
 * 
 * 3)EEPROM
 * I2C ADDRESS: 0x50
 * 
 * 4)BME280
 * I2C ADDRESS: 0x76
 * 
 * 5)SPARKFUN I2C GPS
 * I2C ADDRESS: 0x10
 * 
 * SPARKFUN IMU (unused but connected)
 * I2C ADDRESSES: 0x1C & 0x6b
 * 
 * 
 * 
 * AUTHOR   : MOHD IZMIR BIN YAMIN
 * COMPANY  : IZMIR TECHNOLOGY INDUSTRIES SDN. BHD.
 * DATE     : 12TH SEPTEMBER 2022
 * 
 * CODE VERSION: REVISION 5
 * CODE UPDATE : 12.34AM, 12/9/2022
 * 
**********************************************************************/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
//#include "Wire.h"

#include <Adafruit_GPS.h>
Adafruit_GPS GPS(&Wire);// Connect to the GPS on the hardware I2C port
#define GPSECHO false
uint32_t timer = millis();
//unsigned long startMillis;  //some global variables available anywhere in the program
//unsigned long currentMillis;


#include <MPU6050_light.h>
MPU6050 mpu(Wire);
// unsigned long timer = 0;
#define EEPROM_I2C_ADDRESS 0x50
#define SEALEVELPRESSURE_HPA (1013.25)

#include <Adafruit_INA219.h>
Adafruit_INA219 ina219;
Adafruit_BME280 bme;
char inByte='c';

int Temperature, Pressure, Humidity, Altitude, mapvoltage;
int X_Accel,Y_Accel,Z_Accel, shuntvoltage,  loadvoltage, Pitch, Roll, Yaw;
float Power, busvoltage, current_mA,power_mW;

//I2C ADDRESSES OF CONNECTED ITEMS

//0x10 --> I2C SPARKFUN GPS /but using Adafruit GPS code of I2C Parsing from example
//0x1c --> IMU SPARKFUN /can't be used unfortunately
//0x40 --> INA219 VOLTAGE & CURRENT SENSOR
//0x50 --> EERPOM
//0x68 --> MPU6050
//0x6b --> IMU SPARKFUN /can't be used unfortunately
//0x76 --> BME280 HUMIDITY, PRESSURE AND ALTITUDE SENSOR

//------------EEPROM---------------
int maxaddress=16384-1;           //24C128   -> 131072 bit  -> 16384 byte
int address = 0;
unsigned int value = 0;
unsigned int check_value = 0;
//---------------------------------

float LAT=1;//2.688281;
float LON=1;//101.844496;
int masa=0;
//int ETemp, EPres, EHum, EAlt, ERoll, EPitch, EYaw, EX_Acc,EY_Acc,EZ_Acc,EVolt,ECurr,EPOW,ELAT,ELON;
//----------------------------------LORA------------------------------------------

#include <SPI.h>
#include <LoRa_STM32.h>
#define SS PA4
#define RST PB0
#define DI0 PA1
#define TX_P 15
#define BAND 435E6


void setup() {
  Serial.begin(9600);
  Wire.begin();
  Serial.println("Initialize checking of BME280, MPU6050 and EEPROM CAT24C128");
//------------SPARKFUN I2C GPS--------------  
  GPS.begin(0x10);  // The I2C address to use is 0x10
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
  GPS.sendCommand(PGCMD_ANTENNA);
  GPS.println(PMTK_Q_RELEASE);
  
//------------MPU6050--------------
  mpu.begin();
  delay(3000);
  mpu.calcOffsets();// gyro and accelero
  
//------------INA219---------------
  uint32_t currentFrequency;
ina219.begin();
//ina219.setCalibration_16V_400mA();

//------------EEPROM---------------
  //Wire.begin();
  //randomSeed(analogRead(0));
  
//------------BME280---------------
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
//----------------------------------LORA------------------------------------------

LoRa.setTxPower(17, PA_OUTPUT_PA_BOOST_PIN);
  LoRa.setSignalBandwidth(31.25E3); 
  LoRa.setSpreadingFactor(12);
  LoRa.setCodingRate4(5);
if (!LoRa.begin(BAND)) { // or 915E6, the MHz speed of yout module
    //Serial.println("Starting LoRa failed!");
    while (1);
    
    }
}

void loop() {

int TEMPERATURE=Temperature;
int PRESSURE=Pressure;
int HUMIDITY=Humidity;
int ALTITUDE=Altitude;
//currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
int MASA=0;//currentMillis/1000;
int ROLL=Roll*100;
int PITCH=Pitch*100;
int YAW=Yaw*100;
int X_ACCEL=X_Accel*100;
int Y_ACCEL=Y_Accel*100;
int Z_ACCEL=Z_Accel*100;
int VOLTAGE=busvoltage*100;
int CURRENT=current_mA*100;
int POWER=Power*100;
int MAPVOLTAGE=mapvoltage;
int LATITUDE=LAT*1000000;
int LONGITUDE=LON*1000000;
  
    if (Serial.available() > 0) {
        // get incoming byte:
        inByte = Serial.read();
        //Serial.print(inByte);
          }        
          if(inByte=='a'){//writing Yaw data to EEPROM

   BME280_check();   //run code to check BME280
   MPU6050_check();  //run code to check MPU6050  
   INA219_check();
   GPS_check();
   Serial.print(Temperature);
   Serial.print(",");
   Serial.print(Pressure);
   Serial.print(",");
   Serial.print(Humidity);
   Serial.print(",");
   Serial.print(Altitude);
   Serial.print(",");
   Serial.print(Roll);
   Serial.print(",");
   Serial.print(Pitch);
   Serial.print(",");
   Serial.print(Yaw);
   Serial.print(",");
   Serial.print(X_Accel);
   Serial.print(",");
   Serial.print(Y_Accel);
   Serial.print(",");
   Serial.print(Z_Accel);
   Serial.print(",");
   Serial.print(busvoltage);
   Serial.print(",");
   Serial.print(current_mA);
   Serial.print(",");
   Serial.print(Power);
   Serial.print(",");
      Serial.print(mapvoltage);
   //Serial.print(",");
     //  Serial.print("120"); //RSSI
   Serial.print(",");
      Serial.print(LAT);
   Serial.print(",");
   Serial.print(LON);
   Serial.print(",");

// Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
// Serial.print(",");
//  Serial.print(GPS.longitude, 4); Serial.print(GPS.lon);
//  Serial.print(",");
   Serial.print("EEPROM Write,");
      EEPROM_Write_check();


   //delay(100);
   
          }else if(inByte=='c'){//Getting data as usual
    
   BME280_check();   //run code to check BME280
   MPU6050_check();  //run code to check MPU6050  
   //INA219_check();
   GPS_check();

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  Power=busvoltage*(current_mA/1000);
  
  int voltageformap=busvoltage*100;
  mapvoltage=map(voltageformap,370, 420,0,100);
  
   Serial.print(Temperature);
   Serial.print(",");
   Serial.print(Pressure);
   Serial.print(",");
   Serial.print(Humidity);
   Serial.print(",");
   Serial.print(Altitude);
   Serial.print(",");
   Serial.print(Roll);
   Serial.print(",");
   Serial.print(Pitch);
   Serial.print(",");
   Serial.print(Yaw);
   Serial.print(",");
   Serial.print(X_Accel);
   Serial.print(",");
   Serial.print(Y_Accel);
   Serial.print(",");
   Serial.print(Z_Accel);
   Serial.print(",");
   Serial.print(busvoltage);
   Serial.print(",");
   Serial.print(current_mA);
   Serial.print(",");
   Serial.print(Power);
   Serial.print(",");
      Serial.print(mapvoltage);
   //Serial.print(",");
   // Serial.print("120"); //RSSI
   Serial.print(",");
      //Serial.print(LAT);
   //Serial.print(",");
   //Serial.print(LON);
   //Serial.print(",");


    Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
 Serial.print(",");
  Serial.print(GPS.longitude, 4); Serial.print(GPS.lon);
  Serial.print(",");
   Serial.print("EEPROM Ready,");
//   Serial.print("Bus voltage is:");
//   Serial.print(busvoltage);


  int myArray[]={MASA, TEMPERATURE, PRESSURE, HUMIDITY, ALTITUDE, ROLL, PITCH, YAW, X_ACCEL, Y_ACCEL, Z_ACCEL, VOLTAGE, CURRENT, POWER, MAPVOLTAGE, LATITUDE, LONGITUDE};

  LoRa.beginPacket();  
//  LoRa.print(myArray[0]);  //MASA
//  LoRa.print (",");
  LoRa.print(myArray[1]);  //TEMPERATURE
  LoRa.print (",");
  LoRa.print(myArray[2]);  //PRESSURE
  LoRa.print (",");
  LoRa.print(myArray[3]);  //HUMIDITY
  LoRa.print (",");
  LoRa.print(myArray[4]);  //ALTITUDE
  LoRa.print (",");
  LoRa.print(myArray[5]);  //ROLL
  LoRa.print (",");
  LoRa.print(myArray[6]);  //PITCH
  LoRa.print (",");
  LoRa.print(myArray[7]);  //YAW
  LoRa.print (",");
  LoRa.print(myArray[8]);  //X_ACCEL
  LoRa.print (",");
  LoRa.print(myArray[9]);  //Y_ACCEL
  LoRa.print (",");
  LoRa.print (myArray[10]);  //Z_ACCEL
  LoRa.print (",");
  LoRa.print (myArray[11]);  //VOLTAGE
  LoRa.print (",");
  LoRa.print(myArray[12]);  //CURRENT
  LoRa.print (",");
  LoRa.print(myArray[13]);  //POWER
  LoRa.print (",");
  LoRa.print (myArray[14]);  //MAPVOLTAGE
  LoRa.print (",");
  LoRa.print (myArray[15]);  //LONGITUDE
  LoRa.print (",");
  LoRa.print (GPS.lat);  //LONGITUDE
  LoRa.print (",");
  LoRa.print (myArray[16]);  //LONGITUDE
  LoRa.print (",");
  LoRa.print (GPS.lon);  //LONGITUDE
  LoRa.print (",");
  LoRa.print ("EEPROM READY");
  LoRa.endPacket();
  
   

   //delay(50);
    }else if(inByte=='b'){
      
      EEPROM_Read_check();
      
      }
          
   
}
