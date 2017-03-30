#include <ShiftLed.h>

#define count(a) (sizeof(a)/sizeof((a)[0]))
#define d2ms(b) (b * 24 * 3600 * 1000)

int point0[] = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000};
double level0[] = {3.2, 4.1};

int point1[] = {0, 100, 200, 300, 400, 500, 600, 700, 800};
double level1[] = {1.0, 5.0};

ShiftLed* ch0 = new ShiftLed(11, point0, level0, count(level0));
ShiftLed* ch1 = new ShiftLed(10, point1, level1, count(level1));

unsigned long time;
unsigned long reset;

void setup()  { 
  Serial.begin(9600);
  time = millis();
  reset = d2ms(2); //unsigned longは約50日でオーバーフローする。
} 

void loop()  {
  time = millis() % (reset + 1);
  
  ch0->light(time);
  ch1->light(time);
   
  delay(10);              
}

