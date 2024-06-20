#include "Arduino.h"

// Definitions of pins connection
uint8_t battery_volt_pins[] = { A0, A2 };
uint8_t charge_switch_pins[] = { 8, 9 };
uint8_t ouput_volt_pins[] = { A3, A1 };
uint8_t button_pins[] = { 2, 3 };
uint8_t led_pins[] = { 5, 7 };
uint8_t buzzer_pin = 6;
uint8_t channel_selector_pin = 10;
uint8_t batteries_connection_pin = 11;

//  Definition of usefull constants and variables
float min_load_current = 0.1,
      min_battery_volt = 12,
      max_battery_volt = 14;
uint8_t counter, manual_selected = 1;  // 1 = Battery 1, 2 = Battery 2, 3 = All batteries
String mode;

void auto_manual_change() {
  digitalWrite(buzzer_pin, HIGH);
  if (mode == "auto") mode = "manual";
  if (mode == "manual") mode = "auto";
  delayMicroseconds(1000);
  digitalWrite(buzzer_pin, LOW);
}

void selectBattery() {
  if (mode == "manual") {
    digitalWrite(buzzer_pin, HIGH);
    manual_selected += 1;
    if (manual_selected > 3) manual_selected = 0;
    delayMicroseconds(1000);
    digitalWrite(buzzer_pin, LOW);
  }
}

// Method to initialize the fuction
void initialize() {
  for (counter = 0; counter < 2; counter++) {
    pinMode(charge_switch_pins[counter], OUTPUT);
    pinMode(battery_volt_pins[counter], INPUT);
    pinMode(ouput_volt_pins[counter], INPUT);
    pinMode(button_pins[counter], INPUT_PULLUP);
    pinMode(led_pins[counter], OUTPUT);
  }

  pinMode(batteries_connection_pin, OUTPUT);
  pinMode(channel_selector_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(button_pins[0]), auto_manual_change, FALLING);
  attachInterrupt(digitalPinToInterrupt(button_pins[1]), selectBattery, FALLING);
}

// Method to measure battery voltage
float getBatteryVolt(uint8_t battery_index) {
  return map(analogRead(battery_volt_pins[battery_index]), 0., 1023., 0., 12.);
}

// Method to measure output voltage
float getOutputVoltage(uint8_t index) {
  return 2.470588235 * map(analogRead(battery_volt_pins[index]), 0., 1023., 0., 5.);
}

// Method to calculate output current
float getOutputCurrent() {
  return (getOutputVoltage(1) - getOutputVoltage(0)) / 1.;
}

// Method to change the usefull output voltage
void changeOver(bool state = true) {
  digitalWrite(channel_selector_pin, state);
  digitalWrite(led_pins[0], state);
  digitalWrite(led_pins[1], !state);
}

// Method to connect battery together
void connectBatteries() {
  digitalWrite(batteries_connection_pin, HIGH);
  digitalWrite(channel_selector_pin, HIGH);
  digitalWrite(led_pins[0], HIGH);
  digitalWrite(led_pins[1], HIGH);
}

// Method to stop overcharging of the batteries
void overchargeProtection() {
  if (getBatteryVolt(0) > max_battery_volt) digitalWrite(charge_switch_pins[0], HIGH);
  else digitalWrite(charge_switch_pins[0], LOW);

  if (getBatteryVolt(1) > max_battery_volt) digitalWrite(charge_switch_pins[1], HIGH);
  else digitalWrite(charge_switch_pins[1], LOW);
}