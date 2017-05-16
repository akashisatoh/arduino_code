//ポンプをオンする関数、電磁弁を動かす関数、EC値、水量などをシールドのセンサー値を読み取るライブラリ！
#ifndef HYDROCTL_H_
#define HYDROCTL_H_

#include <Arduino.h>
#include <Wire.h>

class HydroCtlClass{
	private:
   uint32_t   freq;
   float      waterTemp;
   int        waterLevel; //0or1 入っているか入っていないか
   int        pin_pump1;
   int        pin_pump2;
   int        pin_solenoid;
   int        pin_temp;
   int        pin_hum;
   int        pin_ill;

		
	public:
    HydroCtlClass(int pump1, int pump2, int sole, int temp, int hum, int ill);
		static void     begin(void);
		
		static int8_t   turnOnPump(int  pumpId);
		static int8_t   turnOffPump(int  pumpId);


		int8_t   turnOnSolenoid();
		int8_t   turnOffSolenoid();
    
    static void     update(void);
    
    uint32_t getEcValue(void);
    float    getWaterTemp(void);
    void getSensorValues();
    int waterEmpty();
    float    getTemp();
    float    getHum();
    float    getIll();

    bool     isEmpty(void);
};

extern HydroCtlClass HydroCtl;

#endif
