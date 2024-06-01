#include <Stepper.h>
#include "Communication.h"
#define steps_per_revolution 120

Stepper stepper(steps_per_revolution, 8, 7, 6, 5);

// Definition of pin connections
uint8_t btn_pin = 3, sensor_pin = A4, buzzer_pin = A3, indicator_pin = A2, ldr_pin = A1;

// Decralation of usefull variables
bool emergence = false, info_sent = false;
int ldr_min_value = 400;

// Methode for ISR
void emergenceAlertISR() {
  emergence = true;
}

// Methode to initialize the system
void initialize() {
  pinMode(ldr_pin, INPUT);
  pinMode(sensor_pin, INPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(indicator_pin, OUTPUT);
  pinMode(btn_pin, INPUT_PULLUP);

  initializeGSM();
  stepper.setSpeed(30);
  attachInterrupt(digitalPinToInterrupt(btn_pin), emergenceAlertISR, FALLING);
}

// Methode to send Emergence Alert
void emergenceAlert() {
  digitalWrite(buzzer_pin, HIGH);
  digitalWrite(indicator_pin, HIGH);
  for (int i = 0; i < phones; i++)
    sendSMS(phone_numbers[i], "Someone request emergence alert");
  digitalWrite(buzzer_pin, LOW);
  digitalWrite(indicator_pin, LOW);
}

// Methode to control Stepper motor
void controlStepper() {
  stepper.step(steps_per_revolution);
  delay(1000);
}