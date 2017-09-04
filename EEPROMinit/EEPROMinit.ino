#include <EEPROM.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  int date = 0;
  byte* p = (byte*)&date;

  for(int i=0; i<sizeof(int); i++){
    EEPROM.write(i, *p);
    p++;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("write");
}
