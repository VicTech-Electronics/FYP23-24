#include "Display.h"

uint8_t motor_pin1 = A4, motor_pin2 = A5;
uint8_t setting_btn_pin = 2, change_btn_pin = 3, next_btn_pin = 4;

String current_setting = "";
bool in_setting_mode = false, in_operation = false;
uint8_t minutes = 0;
int count_down_sec = 0;

void startSetting() {
  in_setting_mode = true;
  count_down_sec = 0;
}

void initSystem() {
  pinMode(motor_pin1, OUTPUT);
  pinMode(motor_pin2, OUTPUT);
  pinMode(setting_btn_pin, INPUT_PULLUP);
  pinMode(change_btn_pin, INPUT_PULLUP);
  pinMode(next_btn_pin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(setting_btn_pin), startSetting, FALLING);
}

void motorControl(bool dir) {
  digitalWrite(motor_pin1, dir);
  digitalWrite(motor_pin2, !dir);
}

void motorStop() {
  digitalWrite(motor_pin1, false);
  digitalWrite(motor_pin2, false);
}

void setting() {
    lcdPrint("Time setting",  "Time:" + String(minutes) + " min.");
    if (digitalRead(change_btn_pin) == LOW) minutes += 1;
    if (minutes > 59) minutes = 0;
}

void settingMode() {
  while (true) {
    setting();
    if (digitalRead(next_btn_pin) == LOW) break;
  }
  in_setting_mode = false;
  count_down_sec = minutes * 60;
}

void inOperation() {
  if (count_down_sec > 1) {
    lcdPrint("Time: " + String(minutes) + " min.", "Processing...");
    bool clockwise = true;
    while (count_down_sec >= 1) {
      if(!digitalRead(change_btn_pin)) clockwise = !clockwise;
      motorControl(clockwise);
      count_down_sec -= 1;
      delay(1000);
    }
    motorStop();
    minutes = 0;
  }else{
    lcdPrint("TUMBLE DRUM", "Fish Scaling");
  }
}
