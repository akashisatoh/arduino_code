/* FreqCount - Example with serial output
   http://www.pjrc.com/teensy/td_libs_FreqCount.html

   This example code is in the public domain.
*/
#include "FreqCount.h"

void setup() {
  Serial.begin(57600);
  FreqCount.begin(1000);

  for (int i = 0; i < 50; i++) {
    while (!FreqCount.available()) {}
    unsigned long count = FreqCount.read();
    Serial.print(i);
    Serial.print("\t");
    Serial.println(count);
  }
}

void loop() {

}

void serialEvent() {
  Serial.println();

  if (Serial.available()) {
    for (int i = 0; i < 50; i++) {
      while (!FreqCount.available()) {}
      unsigned long count = FreqCount.read();
      Serial.print(i);
      Serial.print("\t");
      Serial.println(count);
    }
  }

  while(Serial.available()){
    Serial.read();
  }
}

