/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
#include <SoftwareSerial.h>

#define N 128

SoftwareSerial mySerial(10, 11); // RX, TX
char str[N];
uint8_t len;

void setup()
{
  // codes for UNO
  #ifdef __AVR_ATmega328P__
  Serial.begin(115200);
  #endif
  
  // codes for LEONARDO
  #ifdef __AVR_ATmega32U4__
  Serial.begin(9600);
  #endif
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
}

void loop() // run over and over
{
  // codes for UNO
  #ifdef __AVR_ATmega328P__
  if (mySerial.available()){
    len = mySerial.readBytes(str, N);
    Serial.write(str, len);
  }
  if (Serial.available()) {
    len = Serial.readBytes(str, N);
    mySerial.write(str, len);
  }
  #endif
  
  // codes for LEONARDO
  #ifdef __AVR_ATmega32U4__
  if (mySerial.available()){
    len = mySerial.readBytes(str, N);
    Serial.print("<< ");
    Serial.write(str, len);
    Serial.println();
  }
  if (Serial.available()) {
    len = Serial.readBytes(str, N);
    mySerial.write(str, len);
    Serial.print(">> ");
    Serial.write(str, len);
    //Serial.println();
  }
  #endif

}

