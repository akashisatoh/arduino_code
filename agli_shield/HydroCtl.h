//ポンプをオンする関数、電磁弁を動かす関数、EC値、水量などをシールドのセンサー値を読み取るライブラリ！
#ifndef HYDROCTL_H_
#define HYDROCTL_H_

#include <Arduino.h>
#include <Wire.h>

class HydroCtlClass{
	private:
    static uint32_t    freq;
    static float    waterTemp;
    static int  waterLevel;

		
	public:
    HydroCtlClass();
		static void     begin(void);
		
		static int8_t   turnOnPump(int  pumpId);
		static int8_t   turnOffPump(int  pumpId);


		static int8_t   turnOnSolenoid(int solenoidId);
		static int8_t   turnOffSorenoid(int solenoidId);
    
    static void     update(void);
    
    static uint32_t getEcValue(void);
    static float    getWaterTemp(void);
    static float    getTemp(int tempId);
    static float    getHum(int humId);

    
    static bool     isEmpty(void);
    static bool     isFull(void);
};

extern HydroCtlClass HydroCtl;

#endif
