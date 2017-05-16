//繝昴Φ繝励ｒ繧ｪ繝ｳ縺吶ｋ髢｢謨ｰ縲�髮ｻ逎∝ｼ√ｒ蜍輔°縺咎未謨ｰ縲・C蛟､縲∵ｰｴ驥上↑縺ｩ繧偵す繝ｼ繝ｫ繝峨�ｮ繧ｻ繝ｳ繧ｵ繝ｼ蛟､繧定ｪｭ縺ｿ蜿悶ｋ繝ｩ繧､繝悶Λ繝ｪ�ｼ�
#ifndef HYDROCTL_H_
#define HYDROCTL_H_

#include <Arduino.h>
#include <Wire.h>

class HydroCtlClass{
	private:
   uint32_t   freq;
   float      waterTemp;
   int        waterLevel; //0or1 蜈･縺｣縺ｦ縺�繧九°蜈･縺｣縺ｦ縺�縺ｪ縺�縺�
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
    
    uint32_t getEcValue(uint8_t[]);
    float    getWaterTemp(uint8_t[]);
    void getSensorValues(uint8_t[]);
    int waterEmpty();
    float    getTemp();
    float    getHum();
    float    getIll();

    bool     isFull(void);
    bool     isEmpty(void);
};

extern HydroCtlClass HydroCtl;

#endif

