#include <Wire.h>
#include <Arduino.h>
#include <HydroCtl.h>

/*
#define pin_pump1 6
#define pin_pump2 7
#define pin_solenoid 5
#define pin_temp 0 
#define pin_hum 1
*/
int receive_data[9];
int pin_pump1 = 6;
void setup() {
  // put your setup code here, to run once:
  //master  としてI2C
  
  Wire.begin();
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  Wire.requestFrom(8, 9);
  
  int inputchar;
  inputchar = Serial.read(); //シリアルから1文字読み込む

  switch(inputchar){
    case 'u':
      //update
      //受け取った9バイトから水温、EC値、水量のHigh or Lowを解析
      //Wire.read（）は1バイトずつしか受け取れない！！！
      Serial.print("update");
      break;
    case 'q':
      //exit
      break;
    case '1':
      //pump on
      turnOnPump((int)pin_pump1);
      Serial.print("turn on pump1"); 
      break;
    case '2':

      turnOnPump((int)pin_pump2);
      Serial.print("turn on pump2"); 
      break;
    case '3':

      turnOffPump((int)pin_pump1);
      Serial.print("turn off pump1"); 
      break;
    case '4':

      turnOffPump((int)pin_pump2);
      Serial.print("turn off pump2"); 
      break;
    case '5':

      turnOnSolenoid((int)pin_solenoid);
      Serial.print("turn on solenoid"); 
      break;
    case '6':

      turnOffSolenoid((int)pin_solenoid);
      Serial.print("turn off solenoid"); 
      break;
    case '7':

      getTemp((int)pin_temp);
      Serial.print("get temp"); 
      break;
    case '8':

      getHum((int)pin_hum):
      Serial.print("get hum"); 
      break;
    default:
      Serial.print(inputchar); 
  }

  delay(500);

}


