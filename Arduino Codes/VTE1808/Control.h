#include <Stepper.h>
#include <uRTCLib.h>
#include "Interface.h"
#define steps_per_revolution 120

// Pin definitions
uint8_t buzzer_pin = A3;
uint8_t indicator_pin = A2;
uint8_t mode_btn_pin = 2, left_btn_pin = 3, right_btn_pin = 4;

uRTCLib rtc(0x68);
Stepper stepper(steps_per_revolution, 8, 7, 6, 5);

// Definition of usefull variables and constants
uint8_t mode_index = 0;
String current_mode = "Operation";
String modes[] = {"Operation", "Setting"};

// Method to handle change mode interrupt
void changeMode(){
  mode_index += 1;
  if(mode_index >= 2) mode_index = 0;
  current_mode = modes[mode_index];

  lcdPrint("Change Mode", "Mode: " + current_mode);
}

// Initialize the setting for operations
void initializeControl(){
  pinMode(buzzer_pin, OUTPUT);
  pinMode(indicator_pin, OUTPUT);
  pinMode(mode_btn_pin, INPUT_PULLUP);
  pinMode(left_btn_pin, INPUT_PULLUP);
  pinMode(right_btn_pin, INPUT_PULLUP);

  URTCLIB_WIRE.begin();
  stepper.setSpeed(30);

  attachInterrupt(digitalPinToInterrupt(mode_btn_pin), changeMode, FALLING);
}

// Methode to control Stepper motor
void controlStepper(uint8_t section) {
  uint8_t section_steps = 15;
  stepper.step(section * section_steps);
  delay(1000);
}

// Method to Check the current time
String getTime_RTC() {
  rtc.refresh();
  return String(rtc.hour()) + String(rtc.minute());
}

// Method for alerting
void alert(bool status) {
  if (status) {
    digitalWrite(buzzer_pin, HIGH);
    digitalWrite(indicator_pin, HIGH);
    delay(1000);
    digitalWrite(indicator_pin, LOW);
    delay(1000);
  } else {
    digitalWrite(buzzer_pin, LOW);
    digitalWrite(indicator_pin, LOW);
  }
}