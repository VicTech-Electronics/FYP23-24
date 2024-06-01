#include "Operations.h"

void setup() {
  Serial.begin(9600);
  initialize();
}

void loop() {
  count_rate++;
  systemOperation();
}
