void BME280_check(){  
Temperature=bme.readTemperature(); //*C
Temperature=Temperature-11;

Pressure=bme.readPressure() / 100.0F;  //hPA
Altitude=bme.readAltitude(SEALEVELPRESSURE_HPA);  //m
Humidity=bme.readHumidity(); //%



}
