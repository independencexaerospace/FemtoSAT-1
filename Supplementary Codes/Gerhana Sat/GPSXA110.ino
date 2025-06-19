


void GPS_check() // run over and over again
{
  // read data from the GPS in the 'main loop'
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
  if (GPSECHO)
    if (c) Serial.print(c);
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    //Serial.println(GPS.lastNMEA()); // this also sets the newNMEAreceived() flag to false
    if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
      return; // we can fail to parse a sentence in which case we should just wait for another
  }

    //if (GPS.fix) {
      LAT=GPS.latitude,4;
      LON=GPS.longitude,4;
     //Serial.print("Location: ");
     //Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
     //Serial.print(", ");
     //Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
    //}
    //Serial.print("GPS-page");
  }
