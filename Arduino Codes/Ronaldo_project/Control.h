#include "Arduino.h"
#include <cstdint>

// Definition of pin connection
uint8_t pump1_pin, pump2_pin;
uint8_t release_time = 5;  // Time in sec
int wait_cup_time = 30; // Time in sec
bool time_out = false;

// Method to make payment
void makePayment(){

}

// Method to output tea
void teaOut(int pump_pin) {
  time_out = false;
  unsigned long initial_time = millis();
  while(digitalRead(sensor_pin) == HIGH){
    if(millis() -  initial_time > wait_cup_time * 1000){
      time_out = true;
      break;
    }
  }; // Wait for cup to be placed

  if(!time_out){
    digitalWrite(pump_pin, HIGH);
    delay(release_time * 1000);
    digitalWrite(pump_pin, LOW);
    makePayment();
  }
}

void initializeControl() {
  pinMode(pump1_pin, OUTPUT);
  pinMode(pump2_pin, OUTPUT);
}