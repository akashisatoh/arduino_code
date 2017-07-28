#include <Wire.h>
#include <Arduino.h>
#include "HydroCtl.h"
#include <MsTimer2.h>


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
#define pin_currentSolenoid 0



unsigned long pumpOnTime=0, pumpOffTime=0;
unsigned long pumpTime = 0; //ポンプがオン，オフになり始めた時間を記録
unsigned long sensorTime = 0;
boolean runningPump = false;
uint32_t waterTemp, ec;
int mode1, mode2, index; //00:on-15,0ff-585, 01:on-60,0ff-540, 10:0n-360,off-240, 11:on-600,off-0
String str; //取得した結果を表示する用
String command, arg1, arg2, inputString;
int current1, current2; //ポンプ1，ポンプ2に流れる電流
uint8_t receive_data[9];
HydroCtlClass ctl = HydroCtlClass(pin_pump1, pin_pump2, pin_solenoid, pin_temp, pin_hum, pin_ill);



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

  MsTimer2::set(3000, getInput); //入力を受け取る関数をたまに実行
  
  Serial.begin(9600);
  while(!Serial);
  Serial.print("start");
  MsTimer2::start();

  //ポンプの動作時間を調べる
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
    pumpOffTime = 100;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //mloop(&mainloop);
  //iloop(&inputloop);

  static unsigned long timestamp = 0;
  //メインとなるループ
  //ポンプとかを回す処理  
  //ポンプの動作時間を見る
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
    pumpOffTime = 100;
  }

  if((millis() - pumpTime) < 0){
    //50日でリセットされるリセットされたらポンプの状態，開始時間もリセット
    runningPump = false;
    pumpTime = 0;    
  }

  //ポンプをおんしたり，オフしたり
  if(pumpTime == 0){
    //ポンプ回す
    Serial.print("turn on pump1 ");
    Serial.println(pumpOnTime);
    Serial.println(analogRead(pin_currentPump1));
    ctl.turnOnPump((int)pin_pump1);
    pumpTime = millis();
    runningPump = true;
  }else{
    if(runningPump){
      //ポンプが動いていたら
      //指定した時間動かしていなければ継続して動かし，
      //指定した時間以上動かしていればポンプを止める
      if((millis() - pumpTime) < pumpOnTime*10){
        //そのまま動かす
      }else{
        //ポンプ止める
        Serial.print("turn off pump1 ");
        Serial.println(pumpOffTime);
        Serial.println(analogRead(pin_currentPump1));
        ctl.turnOffPump((int)pin_pump1);
        pumpTime = millis();
        runningPump = false;
      }
    }else{
      //ポンプが動いていなかったら
      //指定した時間より止めていなければそのまま止めておき，
      //指定した時間以上止めていたらポンプを動かし始める
      if((millis() - pumpTime) < pumpOffTime*10){
        //そのまま止めておく
      }else{
        //ポンプ動かす
        Serial.print("turn on pump1 ");
        Serial.println(pumpOnTime);
        Serial.println(analogRead(pin_currentPump1));
        ctl.turnOnPump((int)pin_pump1);
        pumpTime = millis();
        runningPump = true;
      }
    }
  }

  if((millis() - sensorTime) > 3000){
    //10秒に一回センシング
    //ここに処理を書く

    //Serial.println("sensing!");
    getInput();
    //水温を取得
    getSensorData();
    waterTemp = ctl.getWaterTemp(receive_data);
    printData(receive_data);
    Serial.write("waterTemp:");
    Serial.println(waterTemp);
    str = String(waterTemp, BIN);
    Serial.println(str);
    sensorTime = millis();

  }
}


static int getInput() {
  // スレッド内で基準となるタイムスタンプ
  static unsigned long timestamp = 0;
  // input
  Serial.println("input");
  char inputchar;
  if(Serial.available() > 0){
    // 受信したデータが存在する
    int i=0;
    while(Serial.available()>0){
      inputchar = Serial.read();    //文字の読み込み
      inputString.concat(inputchar);
    }
    inputString[inputString.length()-2] = '\0';
    index = split(inputString, ' ');
    Serial.println(inputString);
  }
    
  if( index == 1){
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
      Serial.println(analogRead(pin_currentSolenoid));
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
      //Serial.println(receive_data[8]);
      getSensorData();
      printData(receive_data);
      Serial.write("water is full?:");
      if(ctl.isFull(receive_data)){
        Serial.write("full");
      }else{
        Serial.write("not full");
      }
    }else if(command.equals("isempty")){
      //Serial.println(receive_data[8]);
      getSensorData();
      printData(receive_data);
      Serial.write("water is empty?:");
      if(ctl.isEmpty(receive_data)){
        Serial.write("empty!");
      }else{
        Serial.write("not empty!");
      }
    }else if(command.equals("getwatertemp")){
      //水温を取得
      getSensorData();
      waterTemp = ctl.getWaterTemp(receive_data);
      printData(receive_data);
      Serial.write("waterTemp:");
      Serial.println(waterTemp);
      str = String(waterTemp, BIN);
      Serial.println(str);
    }else if(command.equals("getwaterec")){
      //EC値を取得
      getSensorData();
      ec = ctl.getEcValue(receive_data);
      printData(receive_data);
      Serial.write("ec:");
      Serial.println(ec);
      str = String(ec, BIN);
      Serial.println(str);
    }
  }else if(index == 3){
    //入力系or取得系
    if(command.equals("setTimer")){
      Serial.println("set timerrrrrrrr");
      pumpOnTime = arg1.toInt();
      pumpOffTime = arg2.toInt();
    }else{
      Serial.println(command);
      Serial.println(arg1);
      Serial.println(arg2);
    }
  }
  index = 0;
  inputString = "";
  command="";
  arg1 = "";
  arg2 = "";
}

int split(String data, char delimiter){
    int index = 0;
    int arraySize = (sizeof(data)/sizeof((data)[0]));  
    int datalength = data.length();
    for (int i = 0; i < datalength; i++) {
        char tmp = data.charAt(i);
        if ( tmp == delimiter ) {
            index++;
            if ( index > (arraySize - 1)) return -1;
        }else{
          if(index == 0){
            command.concat(tmp);
          }else if(index == 1){
            arg1.concat(tmp);
          }else{
            arg2.concat(tmp);
          }
        }
    }
    command.concat('\0');
    arg1.concat('\0');
    arg2[arg2.length()-2] = '\0';
    return (index + 1);
}

void printData(uint8_t receiveData[]){
  int i=0;
  for(i=0; i<9; i++){
    //Serial.println(receiveData[i]);
  }

}

void getSensorData(){
  int index = 0;
      Wire.requestFrom(8, 9);
      while(Wire.available()){
        receive_data[index] = Wire.read();
        Serial.println(receive_data[index]);
        index++;
        if(index > 9)
          break;
      }
}

