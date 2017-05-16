#include <Arduino.h>
#include "HydroCtl.h"
#include <Wire.h>


HydroCtlClass::HydroCtlClass(int pump1, int pump2, int sole, int temp, int hum, int ill){
    freq = 0;
    waterTemp = 0;
    waterLevel = 0;
    pin_pump1 = pump1;
    pin_pump2 = pump2;
    pin_solenoid = sole;
    pin_temp = temp;
    pin_hum = hum;
    pin_ill = ill;
    pinMode(pin_pump1, OUTPUT);
    pinMode(pin_pump2, OUTPUT);
    pinMode(pin_solenoid, OUTPUT);
}

static void     HydroCtlClass::begin(void){
  
}

static int8_t   HydroCtlClass::turnOnPump(int  pumpId){
  //繝昴Φ繝励ｒ蜍輔°縺吝多莉､
  digitalWrite(pumpId, HIGH);
}
static int8_t   HydroCtlClass::turnOffPump(int  pumpId){
  //繝昴Φ繝励ｒ豁｢繧√ｋ蜻ｽ莉､
  digitalWrite(pumpId, LOW);
}
static int8_t   HydroCtlClass::turnOnSolenoid(){
  //髮ｻ逎∝ｼ�
  digitalWrite(pin_solenoid, HIGH);
}
 int8_t   HydroCtlClass::turnOffSolenoid(){
  //髮ｻ逎∝ｼ�
  digitalWrite(pin_solenoid, LOW);
}

 uint32_t HydroCtlClass::getEcValue(uint8_t data[]){
  //EC蛟､繧貞叙蠕�
  //I2C

  //縺ｾ縺壹�ｯ蜻ｨ豕｢謨ｰ繧貞叙蠕�
  uint32_t tmp[4];
  uint32_t ecValue;
  
  for(int i=0; i<4; i++){
    tmp[i] = data[i+4];
  }
  
  ecValue = 0;
  ecValue = tmp[0] << 24 | tmp[1] << 16 | tmp[2] << 8 | tmp[3]; ;
  return ecValue;
}

 float    HydroCtlClass::getWaterTemp(uint8_t data[]){
  //豌ｴ貂ｩ繧貞叙蠕�
  //I2C
}

void HydroCtlClass::getSensorValues(uint8_t data[]){
  //蟄ｫ�ｼ郁｣ｽ蜩∫沿縺ｧ縺ｯ蟄撰ｼ牙渕逶､縺紀2C騾壻ｿ｡縺励※繝�繝ｼ繧ｿ繧貞叙蠕�
  //縺昴�ｮ蠕悟�､繧偵◎繧後◇繧悟叙蠕励☆繧�
}

int HydroCtlClass::waterEmpty(){
  //豌ｴ縺悟�･縺｣縺ｦ縺�繧九°縺ｩ縺�縺九ｒ蜿門ｾ�
  //I2C
}

static float    HydroCtlClass::getTemp(){
  //豌玲ｸｩ繧貞叙蠕�
  //I2C
}
static float    HydroCtlClass::getHum(){
  //貉ｿ蠎ｦ繧貞叙蠕�
  //I2C
}
static float    HydroCtlClass::getIll(){
  //辣ｧ蠎ｦ繧貞叙蠕�
  return analogRead(pin_ill);
}

bool     HydroCtlClass::isFull(void){
  //豌ｴ驥上�ｯOK縺ｧ縺ゅｋ縺薙→繧剃ｼ昴∴繧�
}

bool     HydroCtlClass::isEmpty(void){
  //豌ｴ驥上′0縺ｧ縺ゅｋ縺薙→繧剃ｼ昴∴繧�
}

static void     HydroCtlClass::update(void){
  //迴ｾ蝨ｨ縺ｮ迥ｶ諷九ｒ譖ｴ譁ｰ縺吶ｋ
  
}


