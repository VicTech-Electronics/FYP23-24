#include "Operation.h"

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  initializeControl();
}

void loop() {
  systemOperation();
}
