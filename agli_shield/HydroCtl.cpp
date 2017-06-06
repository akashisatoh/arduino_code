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
  digitalWrite(pumpId, HIGH);
}
static int8_t   HydroCtlClass::turnOffPump(int  pumpId){
  digitalWrite(pumpId, LOW);
}
static int8_t   HydroCtlClass::turnOnSolenoid(){
  digitalWrite(pin_solenoid, HIGH);
}
 int8_t   HydroCtlClass::turnOffSolenoid(){
  digitalWrite(pin_solenoid, LOW);
}

 uint32_t HydroCtlClass::getEcValue(uint8_t data[]){
  //I2C
  uint32_t ecValue;
  ecValue = data[4];
  ecValue = (data[5] << 8) | ecValue;
  ecValue = (data[6] << 16) | ecValue;
  ecValue = (data[7] << 24) | ecValue;
  
  return ecValue;
}

 float    HydroCtlClass::getWaterTemp(uint8_t data[]){
  //I2C
  uint32_t tempValue;
  tempValue = data[0];
  tempValue = (tempValue) | data[1]<<8;
  tempValue = (tempValue) | data[2]<<16;
  tempValue = (tempValue) | data[3]<<24;
}

void HydroCtlClass::getSensorValues(uint8_t data[]){
}

int HydroCtlClass::waterEmpty(){
  //I2C
}

static float    HydroCtlClass::getTemp(){
  //I2C
}
static float    HydroCtlClass::getHum(){
  //I2C
}
static float    HydroCtlClass::getIll(){
  return analogRead(pin_ill);
}

bool     HydroCtlClass::isFull(uint8_t data[]){
  //水位が上の方まで荒ればtrueを返す
  uint8_t height;
  height = data[8];
  if(data[8] & 0b00000010 == 0b00000010){
    return true;
  }else{
    return false;
  }
  
}

bool     HydroCtlClass::isEmpty(uint8_t data[]){
  //水位が下の方を下回っていたらtrueを返す
  uint8_t height;
  height = data[8];
  if(data[8] & 0b00000001 == 0b00000001){
    return false;
  }else{
    return true;
  }
}

static void     HydroCtlClass::update(void){
  
}


