#include "Display.h"

uint8_t motor_pin1 = A4, motor_pin2 = A5;
uint8_t setting_btn_pin = 2, change_btn_pin = 3, next_btn_pin = 4;

String current_setting = "";
bool in_setting_mode = false;
int count_downn_sec;
int hours, minutes;


void startSetting() {
  in_setting_mode = true;
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

void setting(String parameter) {
  if (parameter == "hours") {
    lcdPrint("Setting (Hours)", String(hours) + ":" + String(minutes));
    if (digitalRead(change_btn_pin) == LOW) hours += 1;
    if (hours > 23) hours = 0;

  } else if (parameter == "minutes") {
    lcdPrint("Setting (Min.)", String(hours) + ":" + String(minutes));
    if (digitalRead(change_btn_pin) == LOW) minutes += 1;
    if (minutes > 59) minutes = 0;
  }
}

void settingMode() {
  in_setting_mode = false;
  current_setting = "hours";
  while(true) {
    setting(current_setting);
    if(digitalRead(next_btn_pin) == LOW){
      if(current_setting == "hours") current_setting = "minutes";
      else if(current_setting == "minutes") {
        current_setting = "";
        break;
      }
    }
  }
}

void countDown(){
  count_down_sec = hours * 3600 + minutes * 60;
  while(count_down_sec > 1){
    lcdPrint("TUMBLE DRUM", "Processing...");
    count_down_sec -= 1;
    delay(1000);
  }
}
