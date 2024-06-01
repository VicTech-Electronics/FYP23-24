#include <SoftwareSerial.h>
#define BT_Rx 6
#define BT_Tx 7

SoftwareSerial serialBT(BT_Rx, BT_Tx);

// Definition of pin connections
uint8_t conv_pin=13, led_pin=9, buzzer_pin=10, bt_lev_pin=A1, 
        left_wheel_pin1=A5, left_wheel_pin2=A4, right_wheel_pin1=A3, right_wheel_pin2=A2;

// Method to initialize process
void initialize(){
  pinMode(led_pin, OUTPUT);
  pinMode(conv_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(left_wheel_pin1, OUTPUT);
  pinMode(left_wheel_pin2, OUTPUT);
  pinMode(right_wheel_pin1, OUTPUT);
  pinMode(right_wheel_pin2, OUTPUT);
}


char listenBT() {
  if (serialBT.available()) return serialBT.read();
  else return ' ';
}

// Method to measure batter level
uint8_t batteryLevel(){
  return map(analogRead(bt_lev_pin), 0, 920, 0, 100);
}

// Method to control wheels
void controlWheels(String status) {
  bool pin_state[4];

  if (status == "forward") {
    pin_state[0] = true;
    pin_state[1] = false;
    pin_state[2] = true;
    pin_state[3] = false;
  } else if (status == "backward") {
    pin_state[0] = false;
    pin_state[1] = true;
    pin_state[2] = false;
    pin_state[3] = true;
  } else if (status == "left") {
    pin_state[0] = false;
    pin_state[1] = true;
    pin_state[2] = true;
    pin_state[3] = false;
  } else if (status == "right") {
    pin_state[0] = true;
    pin_state[1] = false;
    pin_state[2] = false;
    pin_state[3] = true;
  } else {
    pin_state[0] = false;
    pin_state[1] = false;
    pin_state[2] = false;
    pin_state[3] = false;
  }

  digitalWrite(left_wheel_pin1, pin_state[0]);
  digitalWrite(left_wheel_pin2, pin_state[1]);
  digitalWrite(right_wheel_pin1, pin_state[2]);
  digitalWrite(right_wheel_pin2, pin_state[3]);
}