//ポンプをオンする関数、電磁弁を動かす関数、EC値、水量などをシールドのセンサー値を読み取るライブラリ！
#ifndef HYDROCTL_H_
#define HYDROCTL_H_

#include <Arduino.h>
#include <Wire.h>

class HydroCtlClass{
	private:

    static float    waterTemp;
    static uint8_t  waterLevel;

		
	public:
    HydroCtlClass();
		static void     begin(void);
		
		static int8_t   turnOnPump(uint8_t  pumpId);
		static int8_t   turnOffPump(uint8_t  pumpId);


		static int8_t   turnOnSolenoid(uint8_t solenoidId);
		static int8_t   turnOffSorenoid(uint8_t solenoidId);
    
    static void     update(void);
    
    static uint32_t getEcValue(void);
    static float    getWaterTemp(void);
    static float    getTemp(uint8_t tempId);
    static float    getHum(uint8_t humId);

    
    static bool     isEmpty(void);
    static bool     isFull(void);
};

extern HydroCtlClass HydroCtl;

#endif
