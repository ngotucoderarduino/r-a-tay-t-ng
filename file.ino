#include <Arduino.h>
//HỆ tHỐNG RỮA TAY TỰ ĐỘNG BY NGÔ TỨ
#include <SoftwareSerial.h> 
#include <JQ6500_Serial.h> //thư viện
JQ6500_Serial mp3(4, 5);
const int cambien1 = 6; //cam bien 1 chan 6
const int cambien2 = 3; // cam bien 2 chan 3
const int cambien3 = 7; //cambien 3 chan 7
int sensor1Value = 0; //ca 3 cam bien dieu nhận giá trị LOW
int sensor2Value = 0;
int sensor3Value = 0;
int giatri = 0, z = 0;
//chan 2 la chan kich may bom, chan 3 voi chan la chan cam bien cho viec thong bao
void tatled()
{
  digitalWrite(cambien3, LOW);
  delay(500);
}
void setup() {
  pinMode(cambien1, INPUT_PULLUP);
  pinMode(cambien2, INPUT_PULLUP);
  //pinMode(cb3, INPUT_PULLUP);
  pinMode(cambien3, OUTPUT);
  mp3.begin(9600);
  mp3.reset();
  mp3.setVolume(30);
  mp3.setLoopMode(MP3_LOOP_NONE);
  pinMode(2, INPUT_PULLUP); // sử dụng điện trở kéo lên cho chân số 2, ngắt 0
  attachInterrupt(0, tatled, LOW);
  Serial.begin(9600);
}
void loop() {
  sensor1Value = digitalRead(cambien1);
  sensor2Value = digitalRead(cambien2);
  digitalWrite(cambien3, HIGH);
  if (sensor1Value == LOW && giatri == 0)
  {
    if (mp3.getStatus() != MP3_STATUS_PLAYING)
    {
      mp3.playFileByIndexNumber(1);
      z = 1;
      giatri = 1;
    }
    if (z == 1 && giatri == 1)
    {
      for (int i = 0; i < 6000; i++)
      {
        digitalWrite(cambien3, HIGH);
        delay(1);
      }
    }
    sensor1Value == HIGH;
  }

  if (sensor2Value == LOW && giatri == 0)
  {
    if (mp3.getStatus() != MP3_STATUS_PLAYING)
    {
      mp3.playFileByIndexNumber(2);
    }
    giatri = 2;
    sensor2Value == HIGH;
  }

  if (giatri != 0)
  {
    delay(500);
    giatri = 0;
  }
}
