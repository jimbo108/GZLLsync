#include <RFduinoGZLL.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include "I2Cdev.h"

device_t role = HOST;

File sanityFile;
File timestampFile;

int SCLpin = 0;
int SDApin = 1;
int SDpin = 6;

int timestamp;

void sanityPrint()
{
  sanityFile = SD.open("sanity.txt", FILE_WRITE);
  sanityFile.print("Print successful.");
  sanityFile.close();
}

void timestampPrint()
{
  timestampFile = SD.open("tshost.txt", FILE_WRITE);
  timestampFile.print("TIMESTAMP: ");
  timestampFile.print(timestamp);
  timestampFile.close();
}

void setup() 
{
  
  RFduinoGZLL.begin(role);
  Wire.beginOnPins(SCLpin, SDApin);
  SD.begin(SDpin);
  delay(1000);
  sanityPrint();
}

void loop() 
{
}

void RFduinoGZLL_onReceive(device_t device, int rssi, char *data, int len)
{
  timestamp = micros();
  RFduinoGZLL.sendToDevice(device, "OK");
  timestampPrint();
}
