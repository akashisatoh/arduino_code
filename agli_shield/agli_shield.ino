#include <Wire.h>
#include <Arduino.h>
#include "HydroCtl.h"


#define pin_pump1 6
#define pin_pump2 7
#define pin_solenoid 5
#define pin_temp 0 
#define pin_hum 1

int receive_data[9];
HydroCtlClass ctl = HydroCtlClass(pin_pump1, pin_pump2, pin_solenoid, pin_temp, pin_hum);

void setup() {
  // put your setup code here, to run once:
  //master  としてI2C
  //Wire.begin();
  Serial.begin(9600);
  while(!Serial);
  Serial.print("start");
}

void loop() {
  // put your main code here, to run repeatedly:

  //Wire.requestFrom(8, 9);
  
  uint8_t inputchar;
  while((inputchar = Serial.read()) == 255){
    
  }

  switch(inputchar){
    case 'u':
      //update
      //受け取った9バイトから水温、EC値、水量のHigh or Lowを解析
      //Wire.read（）は1バイトずつしか受け取れない！！！
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
      ctl.turnOnSolenoid((int)pin_solenoid);
      Serial.write("ctl.turn on solenoid");
      Serial.write("\n");
      break;
    case '6':
      ctl.turnOffSolenoid((int)pin_solenoid);
      Serial.write("ctl.turn off solenoid");
      Serial.write("\n"); 
      break;
    case '7':
      ctl.getTemp((int)pin_temp);
      Serial.write("get temp");
      Serial.write("\n");
      break;
    case '8':
      ctl.getHum((int)pin_hum);
      Serial.write("get hum");
      Serial.write("\n");
      break;
    default:
      Serial.write(inputchar);
      Serial.write("\n");
  }
  
  delay(500);
  
  

}


