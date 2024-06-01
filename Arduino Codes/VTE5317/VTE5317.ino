#include "Control.h"

// Decralation of usefull variables
char bt_data;
uint8_t bat_level, min_bat_level=80;

void setup(){
  initialize();
}

void loop() {
  bt_data = listenBT();
  bat_level = batteryLevel();

  serialBT.println(bat_level);
  if(bat_level < min_bat_level){
    digitalWrite(buzzer_pin, HIGH);
    digitalWrite(led_pin, HIGH);
    delay(500);
    digitalWrite(led_pin, LOW);
  }else digitalWrite(buzzer_pin, LOW);

  if(bt_data == 'F') controlWheels("forward");
  else if(bt_data == 'B') controlWheels("backward");
  else if(bt_data == 'L') controlWheels("left");
  else if(bt_data == 'R') controlWheels("right");
  else if(bt_data == 'S') controlWheels("stop");
  else if(bt_data == 'C') digitalWrite(conv_pin, HIGH);
  else if(bt_data == 'D') digitalWrite(conv_pin, LOW);
  else if(bt_data == 'H') {
    digitalWrite(buzzer_pin, HIGH);
    delay(2000);
    digitalWrite(buzzer_pin, LOW);
  }
 }
