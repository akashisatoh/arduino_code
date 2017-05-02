//
// キャリア波発生 TIMER1 16bit CTCモード
//
// 14/04/30
//
// OC1A(PB1/D9)  38KHz/5KHz 実測により動作確認済
//

void initCTC1() {

  pinMode(9, OUTPUT);                 // これ必要

  // ************ 4MHz ***************
  // 16MHz * 1/1 = 16MHz
  // T = 1 / 16MHz = 0.0625us
  // 逆算 F = 1 / (0.0625 * 2 * 2) = 4MHz

  // OC1A(PB1/D9) toggle
  TCCR1A &= ~(1 << COM1A1);   // 0
  TCCR1A |=  (1 << COM1A0);   // 1

  // WGM13-10 = 0100 CTCモード
  TCCR1B &= ~(1 << WGM13);    // 0
  TCCR1B |=  (1 << WGM12);    // 1
  TCCR1A &= ~(1 << WGM11);    // 0
  TCCR1A &= ~(1 << WGM10);    // 0

  // ClockSource CS12-CS10 = 001 16MHz / 1 T= 0.0625us
  TCCR1B &= ~(1 << CS12);     // 0
  TCCR1B &= ~(1 << CS11);     // 0
  TCCR1B |=  (1 << CS10);     // 1

  OCR1A = 7;                // コンペア値
}

void setup(void) {

  //  analogWrite(9, 100);

  initCTC1();

}

void loop(void) {
}
