#include <RFduinoGZLL.h>
#include <SD.h>
#include <Wire.h>

device_t role = DEVICE0;

File sanityFile;
File timestampFile;

int SCLpin = 0;
int SDApin = 1;
int SDpin = 6;

int timestampBegin;
int timestampEnd;

void sanityPrint()
{
  sanityFile = SD.open("sanity.txt", FILE_WRITE);
  sanityFile.print("Print successful.");
  sanityFile.close();
}

void timestampPrint()
{
  timestampFile = SD.open("tsfile.txt", FILE_WRITE);
  timestampFile.print("TIMESTAMP BEGIN: ");
  timestampFile.print(timestampBegin);
  timestampFile.print("\n");
  timestampFile.print("TIMESTAMP END: ");
  timestampFile.print(timestampEnd);
  timestampFile.close();
}

void startRountrip()
{
  timestampBegin = micros();
  // Data is irrelevant
  RFduinoGZLL.sendToHost(1);
  
}


void setup() 
{
  RFduinoGZLL.begin(role);
  Wire.beginOnPins(SCLpin, SDApin);
  SD.begin(SDpin);
  sanityPrint();
  startRountrip(); 
}

void loop() 
{
}
void RFduinoGZLL_onReceive(device_t device, int rssi, char *data, int len)
{
  timestampEnd = micros();
  timestampPrint();
}


