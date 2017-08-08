#include <Wire.h>
int index;
uint8_t receive_data[9];
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  index = 0;
  Serial.begin(9600);
  //while(!Serial);
  Serial.println("start");

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("push request");
  Serial.println(Wire.requestFrom(8, 9));
  Serial.println("push request");
  index = 0;
  while(Wire.available()){
    Serial.println("get");
    receive_data[index] = Wire.read();
    Serial.println(receive_data[index]);
    index++;
    if(index > 9)
      break;
  }
  delay(1000);

}
