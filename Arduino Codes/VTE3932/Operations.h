#include "Arduino.h"
#include "Measurements.h"
#include "Communication.h"

// Definition of pin connections
const uint8_t  pump1_pin=A4, pump2_pin=A5;

// Decrlation of usefull variable
int time_to_fullfill = 10000; // Time in milliseconds


// Method to initialize the operations
void initialize(){
  pinMode(pump1_pin, OUTPUT);
  pinMode(pump2_pin, OUTPUT);

  initializeMeasurement();
  initializeGSM();
  connectGPRS();
}


// Method to change water
void changeWater(){
  digitalWrite(pump1_pin, HIGH);
  delay(0.8 * time_to_fullfill);
  digitalWrite(pump2_pin, HIGH);
  delay(0.2 * time_to_fullfill);
  digitalWrite(pump1_pin, LOW);
  delay(0.8 * time_to_fullfill);
  digitalWrite(pump2_pin, LOW);
}