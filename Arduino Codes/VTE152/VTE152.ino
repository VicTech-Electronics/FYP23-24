#include "Operation.h"

void setup() {
  initialize();
}

void loop() {
  if(millis() - initial_time > waiting_time){
    if(digitalRead(sensor_pin) == HIGH) highVoiceAlert();
    else {
      digitalWrite(alarm_pin, LOW);
      initial_time = millis();
      info_sent = false;
    }
  }
}
