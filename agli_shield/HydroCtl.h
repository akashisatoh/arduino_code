#ifndef HYDROCTL_H_
#define HYDROCTL_H_

#include <Arduino.h>
#include <Wire.h>

class HydroCtlClass{
	private:
   uint32_t   freq;
   float      waterTemp;
   int        waterLevel; //0or1 
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

    bool     isFull(uint8_t[]);
    bool     isEmpty(uint8_t[]);
};

extern HydroCtlClass HydroCtl;

#endif

