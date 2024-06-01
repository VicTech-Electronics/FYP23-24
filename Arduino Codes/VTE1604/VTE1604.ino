#include "Control.h"

void setup() {
  initSystem();
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  if(in_setting_mode) settingMode();
  inOperation();
}