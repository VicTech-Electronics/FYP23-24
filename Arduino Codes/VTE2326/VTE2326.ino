#include "Operations.h"

// Definition of usefull variables
int waiting_time = 30000;

void setup() {
  initialize();
}

void loop() {
  unsigned long initiali_time = millis();
  if(millis() - initiali_time > waiting_time){
    measure();
    sendDataToServer();
  }

  for(uint8_t i=0; i<3; i++)
    while(measured_values[i] < required_values[i]) 
      digitalWrite(pump_pin, HIGH);
    digitalWrite(pump_pin, LOW);
}
