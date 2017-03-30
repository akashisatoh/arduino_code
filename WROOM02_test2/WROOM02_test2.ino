#include <SoftwareSerial.h>
SoftwareSerial mySerial(11,10); // RX, TX
void setup()
{
  Serial.begin(9600);
  while (!Serial) {
  ; // wait for serial port to connect. Needed for Leonardo only
  }
  mySerial.begin(9600);
}
void loop()
{ 
  char c;
  if(mySerial.available()){
    Serial.write(mySerial.read());
  }
  if (Serial.available()){
    mySerial.write(Serial.read());
  }
}
