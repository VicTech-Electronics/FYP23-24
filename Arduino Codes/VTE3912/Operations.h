#include "Arduino.h"
// Definition of pins connections
uint8_t btn_pin=3, rain_pin=A4, moisture_pin=A5, red_pin=A1, green_pin=A2, buzzer_pin=A3, pump_pin=9, motor_pin1=8, motor_pin2=10;

// Decralation of usefull variables
float moisture_level;
bool raining=false, watering_state=false;

// Method to handle interrupt 
void watering(){
  watering_state = !watering_state;
  digitalWrite(red_pin, watering_state);
  digitalWrite(green_pin, !watering_state);
  digitalWrite(pump_pin, watering_state);
  digitalWrite(buzzer_pin, watering_state);
}


// Method to initialize process
void initialization() {
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(pump_pin, OUTPUT);
  pinMode(motor_pin1, OUTPUT);
  pinMode(motor_pin2, OUTPUT);
  pinMode(btn_pin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(btn_pin), watering, FALLING);
}

// Method for measurements
void measurement() {
  raining = digitalRead(rain_pin);
  moisture_level = map(analogRead(moisture_pin), 0, 1023, 0, 100);
}

// Method to close and open the roof
void openLoof(bool status) {
  digitalWrite(motor_pin1, status);
  digitalWrite(motor_pin2, !status);
}