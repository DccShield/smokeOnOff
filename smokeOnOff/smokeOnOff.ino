//--------------------------------------------------------------------------------
// レイアウト用発煙装置スケッチ
// [smokeOnOff.ino]
// Copyright (c) 2020 Ayanosuke(Maison de DCC)
// https://desktopstation.net/bb/index.php
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//--------------------------------------------------------------------------------
#include <arduino.h>

unsigned long PreviosTimeBtn = 0;  // PreviosTime 前時間

void setup() {
  Serial.begin(115200);         // 115200bpsでシリアルポートを開く
  pinMode(10, OUTPUT);   // 出力に設定
  pinMode(12, INPUT_PULLUP);   // 入力プルアップに設定
  pinMode(3, OUTPUT);   // 出力に設定
  pinMode(4, OUTPUT);   // 出力に設定
  
  // モード指定
  TCCR1A = 0b00100001;
  TCCR1B = 0b00010010; // 001:1分周 　010: 8分周　011:64分周 100:256分周 101:1024分周

  // TOP値指定
  OCR1A = 9;
  // Duty比指定
  OCR1B=0;
  PreviosTimeBtn = millis();
}

void loop() {
  static char mod = 0;
    if( (millis() - PreviosTimeBtn ) >= 200 ){  // 1000:1000msec 前回から1000ms経過したかチェック
      if(digitalRead( 12 ) == LOW){
        mod = !mod;
        if(mod == 0){
            digitalWrite(3,LOW);
          OCR1B=0;
        }
        else {
          digitalWrite(3,HIGH);
          OCR1B=4;
        }
    }
    PreviosTimeBtn = millis();                 // 現在の時刻に更新
  }
}
