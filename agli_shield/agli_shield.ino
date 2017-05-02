#include "HydroCtl.h"
<<<<<<< HEAD

void setup() {
  // put your setup code here, to run once:
=======
#include <Wire.h>

#define pin_pump1 //ポンプ1
#define pin_pump2 //ポンプ2
#define pin_solenoid //電磁弁1
#define pin_temp //温度計用ピン
#define pin_hum //光量用ピン

uint8_t receive_data[9];

void setup() {
  // put your setup code here, to run once:
  //master  としてI2C
  Wire.begin();
  Serial.begin(9600);
>>>>>>> 910da94810bce1295abaeb255ebac161306750eb

}

void loop() {
  // put your main code here, to run repeatedly:
<<<<<<< HEAD

=======
  Wire.requestFrom(8, 9);
  
  int inputchar;
  inputchar = Serial.read(); //シリアルから1文字読み込む

  switch(inputchar){
    case 'u':
      //update
      //受け取った9バイトから水温、EC値、水量のHigh or Lowを解析
      //Wire.read（）は1バイトずつしか受け取れない！！！
      break;
    case 'q':
      //exit
      break;
    case '1':
      //pump on
      turnOnPump(pin_pump1);
      Serial.print("turn on pump1"); 
      break;
    case '2':
      turnOnPump(pin_pump2);
      Serial.print("turn on pump2"); 
      break;
    case '3':
      turnOffPump(pin_pump1);
      Serial.print("turn off pump1"); 
      break;
    case '4':
      turnOffPump(pin_pump2);
      Serial.print("turn off pump2"); 
      break;
    case '5':
      turnOnSolenoid(pin_solenoid);
      Serial.print("turn on solenoid"); 
      break;
    case '6':
      turnOffSolenoid(pin_solenoid);
      Serial.print("turn off solenoid"); 
      break;
    case '7':
      getTemp(pin_temp);
      Serial.print("get temp"); 
      break;
    case '8':
      getHum(pin_hum):
      Serial.print("get hum"); 
      break;
    default:
      Serial.print(inputchar); 
  }

  delay(500);
>>>>>>> 910da94810bce1295abaeb255ebac161306750eb
}


