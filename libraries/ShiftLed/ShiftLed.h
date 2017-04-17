#ifndef ShiftLed_h
#define ShiftLed_h

class ShiftLed{
  public:
    ShiftLed(int pin, int * Point, double* Level, int Num);	//コンストラクタ
    void light(unsigned long time);	//LEDを光らせる関数
    int level(int time);	//その時刻における光量を返す関数
    
  private:
    int led;	//出力ピン
		int* point;	//波形の各ポイント
    int num;	//波形数
		double* slope;	//波形の傾きを記録
		int index;
		int old;	
};

#endif