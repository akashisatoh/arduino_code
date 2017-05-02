#include <Arduino.h>
#include "HydroCtl.h"
#include <Wire.h>


HydroCtlClass::HydroCtlClass(int pump1, int pump2, int sole, int temp, int hum){
    freq = 0;
    waterTemp = 0;
    waterLevel = 0;
    pin_pump1 = pump1;
    pin_pump2 = pump2;
    pin_solenoid = sole;
    pin_temp = temp;
    pin_hum = hum;
    pinMode(pin_pump1, OUTPUT);
    pinMode(pin_pump2, OUTPUT);
    pinMode(pin_solenoid, OUTPUT);
    analogRead(pin_temp);
    analogRead(pin_hum);
}

static void     begin(void){
  
}

static int8_t   turnOnPump(int  pumpId){
  //ポンプを動かす命令
  digitalWrite(pumpId, HIGH);
}
static int8_t   turnOffPump(int  pumpId){
  //ポンプを止める命令
  digitalWrite(pumpId, LOW);
}
static int8_t   turnOnSolenoid(int solenoidId){
  //電磁弁
  digitalWrite(solenoidId, HIGH);
}
static int8_t   turnOffSolenoid(int solenoidId){
  //電磁弁
  digitalWrite(solenoidId, LOW);
}

static uint32_t getEcValue(){
  //EC値を取得
  
}

static float    getWaterTemp(){
  //waterTemp = data >> 40;
  //waterTemp = data & 0xFFFFFFFF;
  //return waterTemp;
}
static float    getTemp(int tempId){
  //気温を取得
}
static float    getHum(int humId){
  //光量を取得
}

static bool     isEmpty(void){
  //水量が無いことを伝える
}
static bool     isFull(void){
  //水量はOKであることを伝える
}

static void     update(void){
  //現在の状態を更新する
  float temp;
  //temp= getTemp(pin_temp);
  //this.freq = getEcValue();
  
}

