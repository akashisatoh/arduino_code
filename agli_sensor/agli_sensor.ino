#include <FreqCount.h>
#include <Wire.h>

#define WL_H  7
#define WL_L  8
#define WTMP  0
#define EC_SW 9
#define WL_SW 10
#define VAREF 2.5*32/(32+4.7)

void requestEvent();

// 異なる型の3つのデータを共用体でまとめる
/*
     ______________________________________________________________
    |                           |                                  |
    |            temp           |                                  |
    |___________________________|__________________________________|
    |                           :                           |      |
    |            freq[0]        :           freq[1]         |      |
    |___________________________:___________________________|______|
    |      :      :      :      :      :      :      :      :      |
    |reg[0]:reg[1]:reg[2]:reg[3]:reg[4]:reg[5]:reg[6]:reg[7]:reg[8]|
    |______:______:______:______:______:______:______:______:______|

*/
typedef union {
  uint8_t reg[9];   // reg[8]の下位2bitで水位状態を表現
  uint32_t temp;       // 温度センサの出力電圧
  unsigned long freq[2]; // freq[1]に周波数カウンタの値を格納
} _data;

_data ret;


void setup() {
  // アナログ基準電圧をAREFピンに設定(2.5V)
  analogReference(EXTERNAL);

  // ゲートタイム1000msで初期化
  FreqCount.begin(1000);

  // Slave ID #8 でI2Cに登録
  Wire.begin(8);
  Wire.onRequest(requestEvent);

  //　シリアル通信
  Serial.begin(9600);

  // ピンの設定
  pinMode(WL_L, INPUT);
  pinMode(WL_H, INPUT);
  pinMode(EC_SW, OUTPUT);
  pinMode(WL_SW, OUTPUT);
  digitalWrite(EC_SW, LOW);
  digitalWrite(WL_SW, LOW);
}

void loop() {
}

void requestEvent() {
  ret.temp=0;
  ret.freq[1] = 0;
  ret.reg[8] = 0;
  // 周波数の取得
  setFreq();

  // 水温の取得
  setWtmp();

  // 水位の取得
  setWlevel();

  // データの送信
  Wire.write(ret.reg, 9);
}

// 周波数を取得して共用体に格納する
void setFreq() {
  // 発振開始
  
  digitalWrite(EC_SW, HIGH);
  delay(100);

  // フラグが立つまで待機
  while (!FreqCount.available()) {}

  // 周波数はret.reg[4-7]に格納(4byte)
  ret.freq[1] = FreqCount.read();
  if(ret.freq[1] > 0){
  }else if(ret.freq[1] == 0){
    ret.freq[1] = 2000;
  }
  // 発振終了
  digitalWrite(EC_SW, LOW);
}

// 水温を取得して共用体に格納する
void setWtmp() {
  uint16_t val = analogRead(WTMP);

  // センサの値を電圧に変換
  //ret.temp = map_f(val, 0, 1023, 0, VAREF);
  ret.temp = analogRead(WTMP);
}

// 水位状態を取得して共用体に格納する
void setWlevel() {
  // 発振開始
  digitalWrite(WL_SW, HIGH);
  delay(5);

  // 水位状態の取得(2値)
  uint8_t valH = 0b00000000;
  uint8_t valL = 0b00000000;
  if(digitalRead(WL_H)==HIGH){
    valH = 0b00000010;
  }
  if(digitalRead(WL_L)==HIGH){
    valL = 0b00000001;
  }
  //uint8_t valH = digitalRead(WL_H);
  //uint8_t valL = digitalRead(WL_L);

  // 下位2bitに状態を格納
  ret.reg[8] = valH | valL;

  // 発振終了
  digitalWrite(WL_SW, LOW);
}

// map関数をfloat型に対応させたもの
float map_f(uint32_t val, uint32_t in_l, uint32_t in_h, float out_l, float out_h) {
  return val * (out_h - out_l) / (in_h - in_l) + out_l;
}

