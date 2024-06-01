#include "Display.h"

// Definition of pin connections
uint8_t btn1_pin=2, btn2_pin=3, mq_pin=A3, frame_pin=11, buzzer_pin=6, led_pin=7;

// Decralation of usefull constants and variables
bool in_setting_mode = false;
uint8_t sensitivity_level_index = 0;
String sensitivities[] = {"LOW", "MEDIUM", "HIGH"};

// Method to handle changeMode interrupt function
void changeMode(){
  in_setting_mode = !in_setting_mode;
  delayMicroseconds(10000);
}

// Method to initilize the system
void initialization(){
  pinMode(led_pin, OUTPUT);
  pinMode(frame_pin, INPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(btn1_pin, INPUT_PULLUP);
  pinMode(btn2_pin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(btn1_pin), changeMode, FALLING);
}


// Method to control settings
void settings(){
  while(in_setting_mode){
    lcdPrint("Setting Mode", "Sense: " + sensitivities[sensitivity_level_index]);
    if(!digitalRead(btn2_pin)) sensitivity_level_index += 1;
    if(sensitivity_level_index > 2) sensitivity_level_index = 0;
  }
}

// Method to hande the alert
void alert(bool status){
  if(status){
    digitalWrite(led_pin, HIGH);
    delay(1000);
    digitalWrite(led_pin, LOW);
    digitalWrite(buzzer_pin, HIGH);
  }else digitalWrite(buzzer_pin, LOW);
}


// Method to check alert
bool checkAlert(bool frame, int current_gase_level){
  int max_gas_level = 100;
  if(sensitivity_level_index == 0) max_gas_level = 80;
  else if(sensitivity_level_index == 1) max_gas_level = 50;
  else max_gas_level = 30;
 
  if(current_gase_level > max_gas_level || frame) return true;
  else return false;
}