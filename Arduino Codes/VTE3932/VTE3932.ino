#include "Display.h"
#include "Operations.h"
#include <Arduino_JSON.h>

JSONVar json_object;

// Decralation of usefull variables
String payload = "";
String device_no = "1";
String phone = "+255673131807";
unsigned long initial_time = 0;
const int send_interval_time = 5000;
float ph_value, turbidity_value, ammonia_value, temperature_value;


float normal_ph=7, normal_ammonia=10, normal_turbidity=20;
float max_allowed_ph_error = 2, max_allowed_ammonia_error = 5, max_allowed_turbidity_error = 7;

void setup() {
  Serial.begin(9600);
  initialize();
  lcd.begin(16, 2);

  lcdPrint("Welcome", ""); delay(1000);
  lcdPrint("Smart Water", "Q-Management"); delay(1000);
}

void loop() {
  ph_value = getPHValue();
  turbidity_value = getTurbidityValue();
  ammonia_value = getAmmoniaConcetration();
  temperature_value = getTemperature();

  // Default lcd screen
  lcdPrint("PH: " + String(ph_value) + " Turb: " + String(turbidity_value), 
           "Amm: " + String(ammonia_value) + " Temp: " + String(temperature_value));

  if(millis() - initial_time > send_interval_time){
    json_object["device_no"] = device_no;
    json_object["ph"] = ph_value;
    json_object["turbidity"] = turbidity_value;
    json_object["ammonia"] = ammonia_value;
    json_object["temperature"] = temperature_value;

    payload = JSON.stringify(json_object);
    postRequest(payload);

    initial_time = millis();
  }

  if(abs(normal_ph - ph_value) > max_allowed_ph_error || 
     abs(normal_ammonia - ammonia_value) > max_allowed_ammonia_error ||
     abs(normal_turbidity - turbidity_value) > max_allowed_turbidity_error){

      String message = "Water changed when measurement was as follows \nData: " + payload;
      changeWater();
      sendSMS(phone, message);
    }
}
