#include "Arduino.h"
#include "Sensor.h"
#include "Communication.h"

// Definition of pin connection
uint8_t btn1_pin=1, btn2_pin=2, pump1_pin=3, pump2_pin=4, sensor_pin=5;


// Decralation of usefull terms
int time_to_fill = 10000;
uint8_t required_service_number = 0;
bool payment_confirmed = false, service_selected = false;


// Method to handle the Interrupt service functions
void provideService1() {
  required_service_number = 1;
  service_selected = true;
}

void provideService2() {
  required_service_number = 2;
  service_selected = true;
}


// Method to initialize operations
void initialize() {
  pinMode(sensor_pin, INPUT);
  pinMode(pump1_pin, OUTPUT);
  pinMode(pump2_pin, OUTPUT);
  pinMode(btn1_pin, INPUT_PULLUP);
  pinMode(btn2_pin, INPUT_PULLUP);
  initializeSensors();

  attachInterrupt(digitalPinToInterrupt(btn1_pin), provideService1, FALLING);
  attachInterrupt(digitalPinToInterrupt(btn1_pin), provideService2, FALLING);
}


// Method to open the Service
void openPump(uint8_t index) {

  bool state, open = true, cup_detected = false;

  if (index == 1) state = true;
  else if (index == 2) state = false;
  else open = false;

  if (open) {
    while (!cup_detected)
      if (digitalRead(sensor_pin) == LOW) cup_detected = true;

    digitalWrite(pump1_pin, state);
    digitalWrite(pump2_pin, !state);
    delay(time_to_fill);
  }

  digitalWrite(pump1_pin, LOW);
  digitalWrite(pump2_pin, LOW);
}


// Method to handle the system operation
void systemOperation() {
  String card_no = getCardNumber();
  payment_confirmed = sendCardNumber(card_no);

  if (count_rate <= 30 && pulse_counter > 1) {
    pulse_counter = 0;
    payment_confirmed = true;
  }

  if(payment_confirmed){
    if (service_selected) openPump(required_service_number);
    payment_confirmed = false;
    service_selected = false;
  }
}