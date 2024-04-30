#include "Communication.h"
#include "Keypad.h"
// #include "RTC.h"
#include "DS1307RTC.h"

String current_time, time_on, time_off, hours, minutes;
String received_sms;
byte relay1_pin = A2, relay2_pin = A3;

void setup(){
  pinMode(relay1_pin, OUTPUT);
  pinMode(relay2_pin, OUTPUT);
  
  Serial.begin(9600);
  serialGSM.begin(9600);
  lcd.init();
  lcd.backlight();
  // initiateRTC();
  URTCLIB_WIRE.begin();
  initializeGSM();
}
  
void loop(){
  key = keypad.getKey();

  if(key == 'A'){
    time_on = getTime("ON");
    time_on.trim();
  }else if(key == 'B'){
    time_off = getTime("OFF");
    time_off.trim();
  }

  key = 'z';
  time = "";

  // RtcDateTime now = Rtc.GetDateTime();
  // current_time = getTimeRTC(now);

  current_time = getTime_RTC();
  if(current_time == time_on) switchRelay(HIGH);
  else if(current_time == time_off) switchRelay(LOW);

  received_sms = receiveSMS();
  if(received_sms == "ON") switchRelay(HIGH);
  else if(received_sms == "OFF") switchRelay(LOW);

  defaultScreen();
}

void switchRelay(bool state){
  digitalWrite(relay1_pin, state);
  digitalWrite(relay2_pin, state);
}

void defaultScreen(){
  hours = time_on.substring(0, 2);
  minutes = time_on.substring(2);
  String set_time_on = hours + ":" + minutes;

  hours = time_off.substring(0, 2);
  minutes = time_off.substring(2);
  String set_time_off = hours + ":" + minutes;
  
  lcdPrint("Time ON: " + set_time_on, "Time OFF: " + set_time_off);
  delay(2000);

  hours = current_time.substring(0, 2);
  minutes = current_time.substring(2);
  String set_current_time = hours + ":" + minutes;

  lcdPrint("Current Time", set_current_time);
  delay(2000);
}
