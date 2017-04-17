//ポンプをオンする関数、電磁弁を動かす関数、EC値、水量などをシールドのセンサー値を読み取るライブラリ！
#ifndef HYDROCTL_H_
#define HYDROCTL_H_

#include <Arduino.h>
#include <Wire.h>

class HydroCtlClass{
	private:
    static uint32_t freq;
    static float    waterTmep;
    static uint8_t  a;
		
	public:
		static void     begin(void);
		
		static int8_t   turnOnPump(uint8_t  pumpId);
		static int8_t   turnOffPump(uint8_t  pumpId);
		static int8_t   turnOnSolenoid(void);
		static int8_t   turnOffSorenoid(void);
    
    static void     update(void);
    
    static uint16_t getEcValue(void);
    static float    getWaterTemp(void);
    static float    getTemp(void);
    static float    getHum(void);
    
    static bool     isEmpty(void);
    static bool     isFull(void);
};

extern HydroCtlClass HydroCtl;

#endif
