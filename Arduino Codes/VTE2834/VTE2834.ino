#include "Operation.h"
#include "Communication.h"

#include <Arduino_JSON.h>

JSONVar json_object;

// Decralation of usefull constants and variables
int gas_level = 0;
unsigned long initial_time = 0;
bool frame_detected = false, warning = false, sms_sent = false;
String device_no = "1", payload, phone = "+255757856755";

void setup() {
  initialization();
  initializeGSM();
  connectGPRS();

  lcd.init();
  lcd.backlight();
}

void loop() {
  settings();

  frame_detected = digitalRead(frame_pin);
  gas_level = map(analogRead(mq_pin), 0, 1023, 0, 100);
  warning = checkAlert(frame_detected, gas_level);

  lcdPrint("Sense: " + sensitivities[sensitivity_level_index], "Frame:" + String(frame_detected) + " Gase:" + String(gas_level));

  if(warning) {
    alert(true);
    String sms_to_send = "WARNING: \nGas level: " + String(gas_level) +"\nFrame detected: " + String(frame_detected) + "\nPlease to quack action"; 
    if(!sms_sent){
      sendSMS(phone, sms_to_send);
      sms_sent = true;
    }
  }else{
    alert(false);
    sms_sent = false;
  };

  json_object["device_no"] = device_no;
  json_object["gas_level"] = gas_level;
  json_object["frame"] = frame_detected;
  json_object["warning"] = warning;

  payload = JSON.stringify(json_object);

  if(millis() - initial_time > 5000){
    postRequest(payload);
    initial_time = millis();
  }

}
