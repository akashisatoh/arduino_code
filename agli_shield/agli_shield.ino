#include <Wire.h>
#include <Arduino.h>
#include "HydroCtl.h"
#include <pt.h>


#define pin_pump1 5
#define pin_pump2 6
#define pin_solenoid 5
#define pin_temp 0 
#define pin_hum 1
#define pin_ill 24
#define pin_mode1 3
#define pin_mode2 2
#define pin_currentPump1 2
#define pin_currentPump2 3

#define PT_WAIT(pt, timestamp, usec) PT_WAIT_UNTIL(pt, millis() - *timestamp > usec);*timestamp = millis();




uint8_t receive_data[9];
HydroCtlClass ctl = HydroCtlClass(pin_pump1, pin_pump2, pin_solenoid, pin_temp, pin_hum, pin_ill);

uint32_t waterTemp, ec;
int mode1, mode2; //00:on-15,0ff-585, 01:on-60,0ff-540, 10:0n-360,off-240, 11:on-600,off-0
int mode, pumpOnTime=15, pumpOffTime=585; //モードに寄って変化
String str; //取得した結果を表示する用
String command;



//時間をカウントするためのもの

static struct pt mainloop, inputloop;

static int mloop(struct pt *pt){
  //スレッド内の処理
  //ここをメインループとする
  static unsigned long timestamp = 0;
  PT_BEGIN(pt);

  while(true){
    //メインとなるループ
    //ポンプとかを回す処理

    int current1, current2; //ポンプ1，ポンプ2に流れる電流

    //ポンプの時間を見る
    if(digitalRead(pin_mode1) == HIGH && digitalRead(pin_mode2) == HIGH){
      pumpOnTime = 15;
      pumpOffTime = 585;
    }else if(digitalRead(pin_mode1) == LOW && digitalRead(pin_mode2) == HIGH){
      pumpOnTime = 60;
      pumpOffTime = 540;
    }else if(digitalRead(pin_mode1) == HIGH && digitalRead(pin_mode2) == LOW){
      pumpOnTime = 360;
      pumpOffTime = 240;
    }else if(digitalRead(pin_mode1) == LOW && digitalRead(pin_mode2) == LOW){
      pumpOnTime = 600;
      pumpOffTime = 0;
    }

    //ポンプ回す
    Serial.print("turn on pump1 ");
    Serial.println(pumpOnTime);
    Serial.println(analogRead(pin_currentPump1));
    ctl.turnOnPump((int)pin_pump1);
    PT_WAIT(pt, &timestamp ,pumpOnTime*10);//待つ
    //ポンプ止める
    Serial.print("turn off pump1 ");
    Serial.println(pumpOffTime);
    Serial.println(analogRead(pin_currentPump1));
    ctl.turnOffPump((int)pin_pump1);
    PT_WAIT(pt, &timestamp, pumpOffTime*10);//待つ
  }

  PT_END(pt);
}


static int iloop(struct pt *pt) {
    // スレッド内で基準となるタイムスタンプ
    static unsigned long timestamp = 0;
    PT_BEGIN(pt);

    while(true) {
        // input
        PT_WAIT(pt, &timestamp, 1000);
        Serial.println("input");
        char inputchar;
        // 受信したデータが存在する
        int i=0;
        while(Serial.available()>0){
          inputchar = Serial.read();    //文字の読み込み」
          if (inputchar == '.' || inputchar == '¥n') {       //「/」が読み込まれたなら文字列の最後とみなし
            inputchar = '\0';           //終端文字（「Null」と同様）を挿入
            command.concat(inputchar);
            Serial.print(command);       //シリアルに文字列を書込
            Serial.write("\n");     //改行コードを書込
            i=0;                    //カウントを戻す
            
          }else { 
            command.concat(inputchar);
          } 
        }
       


        if(command.equals("update")){
          //update
          //タンクの情報を更新
          //receive_dataに水温，水位，EC値を取得
          int index = 0;
          Wire.requestFrom(8, 9);
          while(Wire.available()){
            receive_data[index] = Wire.read();
            Serial.println(receive_data[index]);
            index++;
            if(index > 9)
              break;
          }
    
          //水温を取得
          waterTemp = ctl.getWaterTemp(receive_data);
          Serial.write("waterTemp:");
          Serial.println(waterTemp);
          str = String(waterTemp, BIN);
          Serial.println(str);
    
          //EC値を取得
          ec = ctl.getEcValue(receive_data);
          Serial.write("ec:");
          Serial.println(ec);
          str = String(ec, BIN);
          Serial.println(str);
    
          //水位を取得
          Serial.write("water is full?:");
          if(ctl.isFull(receive_data)){
            Serial.write("full");
          }else{
            Serial.write("not full");
          }
          Serial.write("water is empty?:");
          if(ctl.isEmpty(receive_data)){
            Serial.write("empty!");
          }else{
            Serial.write("not empty!");
          }
          //Serial.write("update");
          break;
        }else if(command.equals("quit")){
          //exit
        }else if(command.equals("pump1on")){
          //pump on
          ctl.turnOnPump((int)pin_pump1);
          Serial.write("ctl.turn on pump1");
          Serial.write("\n");
        }else if(command.equals("pump2on")){
          ctl.turnOnPump((int)pin_pump2);
          Serial.write("ctl.turn on pump2");
          Serial.write("\n");
        }else if(command.equals("pump1off")){
          ctl.turnOffPump((int)pin_pump1);
          Serial.write("ctl.turn off pump1");
          Serial.write("\n");
        }else if(command.equals("pump2off")){
          ctl.turnOffPump((int)pin_pump2);
          Serial.write("ctl.turn off pump2");
          Serial.write("\n");
        }else if(command.equals("solenoidon")){
          ctl.turnOnSolenoid();
          Serial.write("ctl.turn on solenoid");
          Serial.write("\n");
        }else if(command.equals("solenoidoff")){
          ctl.turnOffSolenoid();
          Serial.write("ctl.turn off solenoid");
          Serial.write("\n"); 
        }else if( command.equals("gettemp")){
          float temp;
          temp = ctl.getTemp();
          Serial.write("get temp");
          Serial.write("\n");
        }else if(command.equals("gethum")){
          float hum;
          hum = ctl.getHum();
          Serial.write("get hum:");
          //Serial.write(hum);
          Serial.write("\n");
        }else if(command.equals("getill")){
          float ill;
          ill = ctl.getIll();
          Serial.write("get ill:");
          //Serial.write(ill);
          Serial.write("\n");
        }else if(command.equals("isfull")){
          Serial.println(receive_data[8]);
          Serial.write("water is full?:");
          if(ctl.isFull(receive_data)){
            Serial.write("full");
          }else{
            Serial.write("not full");
          }
        }else if(command.equals("isempty")){
          Serial.println(receive_data[8]);
          Serial.write("water is empty?:");
          if(ctl.isEmpty(receive_data)){
            Serial.write("empty!");
          }else{
            Serial.write("not empty!");
          }
        }else if(command.equals("getwatertemp")){
          //水温を取得
          waterTemp = ctl.getWaterTemp(receive_data);
          Serial.write("waterTemp:");
          Serial.println(waterTemp);
          str = String(waterTemp, BIN);
          Serial.println(str);
        }else if(command.equals("getwaterec")){
          //EC値を取得
          ec = ctl.getEcValue(receive_data);
          Serial.write("ec:");
          Serial.println(ec);
          str = String(ec, BIN);
          Serial.println(str);
        }
        command = "";
    }
    PT_END(pt);
}



void setup() {
  // put your setup code here, to run once:
  //master  ※I2C
  Wire.begin();

  pinMode(pin_pump1, OUTPUT);
  pinMode(pin_pump2, OUTPUT);
  pinMode(pin_solenoid, OUTPUT);

  pinMode(pin_mode1, INPUT);
  pinMode(pin_mode2, INPUT);
  pinMode(pin_temp, INPUT);
  pinMode(pin_hum, INPUT);
  pinMode(pin_ill, INPUT);

  //pt初期化
  PT_INIT(&mainloop);
  PT_INIT(&inputloop);
  //SoftwareSerial Serial(0,1);
  Serial.begin(9600);
  while(!Serial);
  Serial.print("start");
}

void loop() {
  // put your main code here, to run repeatedly:
  mloop(&mainloop);
  iloop(&inputloop);
}



