#include "Arduino.h"
#include "ShiftLed.h"

ShiftLed::ShiftLed(int pin, int * Point, double* Level, int Num){
	//出力ピンの設定
	led = pin;
  pinMode(led, OUTPUT);
	
	//要素数の計算
	num = Num;
	
	//pointの初期化
	point = Point;	
	
	//slopeの初期化
	slope = new double[4 * num + 1];
	for(int i = 0; i < 4 * num + 1; i++){
		switch(i % 4){
			case 0:
				slope[i] = 0;
				break;
			case 1:
				slope[i] = (Level[i / 4] / 5. *255) / (point[i] - point[i - 1]);
				break;
			case 2:
				slope[i] = Level[i / 4] / 5. *255;
				break;
			case 3:
				slope[i] = (Level[i / 4] / -5. *255) / (point[i] - point[i - 1]);
				break;
			
		}
	}
	
	//indexとoldの初期化
	index = 0;
	old = 0;
}

void ShiftLed::light(unsigned long time){
  analogWrite(led, level((int)(time % (point[4 * num]) + 1)));
}

int ShiftLed::level(int time){
	if(time - old < 0)	index = 0;
	old = time;
	
	if(time > point[index])	index++;
	Serial.println(time);
	Serial.println(index);
	
	switch(index % 4){
		case 1:
			return slope[index] * (time - point[index - 1]);
			break;
		case 3:
			return slope[index] * (time - point[index - 1]) + slope[index - 1];
			break;
		default:
			return slope[index];
			break;
	}
}	