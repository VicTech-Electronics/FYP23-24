#include "Operation.h"

void setup() {
  Serial.begin(9600);
  initialize();

}

void loop() {
  if (digitalRead(sensor_pin) == LOW) {
    digitalWrite(indicator_pin, HIGH);
    controlStepper();
    digitalWrite(indicator_pin, LOW);
  }

  if (analogRead(ldr_pin) < ldr_min_value) {
    digitalWrite(indicator_pin, HIGH);
    if (!info_sent) {
      digitalWrite(buzzer_pin, HIGH);
      for (int i = 0; i < phones; i++)
        sendSMS(phone_numbers[i], "Warning.! Toilet run out of paper.");

      digitalWrite(buzzer_pin, LOW);
      info_sent = true;
    }
  }else{
    digitalWrite(indicator_pin, LOW);
    digitalWrite(buzzer_pin, LOW);
    info_sent = false;
  }
}
