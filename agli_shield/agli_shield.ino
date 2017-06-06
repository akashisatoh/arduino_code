#include <Wire.h>
#include <Arduino.h>
#include "HydroCtl.h"


#define pin_pump1 6
#define pin_pump2 7
#define pin_solenoid 5
#define pin_temp 0 
#define pin_hum 1
#define pin_ill 24

uint8_t receive_data[9];
HydroCtlClass ctl = HydroCtlClass(pin_pump1, pin_pump2, pin_solenoid, pin_temp, pin_hum, pin_ill);

void setup() {
  // put your setup code here, to run once:
  //master  ※I2C
  Wire.begin();
  Serial.begin(9600);
  while(!Serial);
  Serial.print("start");
}

void loop() {
  // put your main code here, to run repeatedly:
  int index = 0;
  Wire.requestFrom(8, 9);
  while(Wire.available()){
    receive_data[index] = Wire.read();
    Serial.println(receive_data[index]);
    index++;
    if(index > 9)
      break;
  }
  uint32_t tmp[4];
  for(int i=0; i<4; i++){
    tmp[i] = receive_data[i+4];
    String str = String(tmp[i], BIN);
    Serial.println(str);
  }

  uint32_t ec;
  ec = ctl.getEcValue(receive_data);
  Serial.write("ec:");
  Serial.println(ec);
  String str = String(ec, BIN);
  Serial.println(str);
  
  uint8_t inputchar;
  while((inputchar = Serial.read()) == 255){
    
  }

  switch(inputchar){
    case 'u':
      //update
      //蜿励￠蜿悶▲縺�9繝舌う繝医°繧画ｰｴ貂ｩ縲・C蛟､縲∵ｰｴ驥上�ｮHigh or Low繧定ｧ｣譫�
      //Wire.read�ｼ茨ｼ峨�ｯ1繝舌う繝医★縺､縺励°蜿励￠蜿悶ｌ縺ｪ縺�ｼ�ｼ�ｼ�
      Serial.write("update");
      break;
    case 'q':
      //exit
      break;
    case '1':
      //pump on
      ctl.turnOnPump((int)pin_pump1);
      Serial.write("ctl.turn on pump1");
      Serial.write("\n");
      break;
    case '2':
      ctl.turnOnPump((int)pin_pump2);
      Serial.write("ctl.turn on pump2");
      Serial.write("\n");
      break;
    case '3':
      ctl.turnOffPump((int)pin_pump1);
      Serial.write("ctl.turn off pump1");
      Serial.write("\n");
      break;
    case '4':
      ctl.turnOffPump((int)pin_pump2);
      Serial.write("ctl.turn off pump2");
      Serial.write("\n");
      break;
    case '5':
      ctl.turnOnSolenoid();
      Serial.write("ctl.turn on solenoid");
      Serial.write("\n");
      break;
    case '6':
      ctl.turnOffSolenoid();
      Serial.write("ctl.turn off solenoid");
      Serial.write("\n"); 
      break;
    case '7':
      //I2C
      float temp;
      temp = ctl.getTemp();
      Serial.write("get temp");
      Serial.write("\n");
      break;
    case '8':
      //I2C
      float hum;
      hum = ctl.getHum();
      Serial.write("get hum:");
      Serial.write(hum);
      Serial.write("\n");
      break;
    case '9':
      float ill;
      ill = ctl.getIll();
      Serial.write("get ill:");
      Serial.write(ill);
      Serial.write("\n");
      break;
    case 'a' :
      bool height;
      //height = ctl.isFull();
      Serial.write("water is empty?:");
      Serial.write("");
      break;
    default:
      Serial.write(inputchar);
      Serial.write("\n");
  }
  
  delay(500);
  
  

}



