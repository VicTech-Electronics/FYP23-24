#include "Display.h"

// Definition of usefull pins
uint8_t btn_pin=2, green_led_pin=6, red_led_pin=7, buzzer_pin=8, backlight_pin=12, sensor_pin=A5; 

// Definition of usefull variables
int alcohol_level = 0;
bool paused = false;

// Alerting method
void alert(bool status){
  if(status){
    digitalWrite(green_led_pin, LOW);
    digitalWrite(buzzer_pin, HIGH);
    digitalWrite(red_led_pin, HIGH);
    delay(1000);
    digitalWrite(red_led_pin, LOW);
  }else{
    digitalWrite(buzzer_pin, LOW);
    digitalWrite(red_led_pin, LOW);
    digitalWrite(green_led_pin, HIGH);
  }
}

// Methode to handle pause interrupt service
void pause(){
  paused = !paused;
}

void setup() {
  pinMode(buzzer_pin, OUTPUT);
  pinMode(red_led_pin, OUTPUT);
  pinMode(green_led_pin, OUTPUT);
  pinMode(btn_pin, INPUT_PULLUP);
  pinMode(backlight_pin, OUTPUT);


  lcd.begin(16, 2);
  digitalWrite(backlight_pin, HIGH);
  welcomeMessage();
  digitalWrite(backlight_pin, LOW);
  delay(1000);
  attachInterrupt(digitalPinToInterrupt(btn_pin), pause, FALLING);
  digitalWrite(backlight_pin, HIGH);
}

void loop() {
  while(paused){
    alert(false);
    lcdPrint("Alcohol Detector", "System PAUSED");
    delay(1000);
  }

  alcohol_level = int(map(analogRead(sensor_pin), 0, 1023, 0, 100));
  lcdPrint("Alcohol Detector", "Level: " + String(alcohol_level) + "%");
  if(alcohol_level > 50) alert(true);
  else alert(false);
}
