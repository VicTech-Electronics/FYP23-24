#include "Operation.h"
#include "Communication.h"

void setup() {
  Serial.begin(9600);
  nextion_serial.begin(9600);
  
  initializeFingerprint();
  initializeOperations();
  initializeWIFI();

}

void loop() {
  // put your main code here, to run repeatedly:
}
