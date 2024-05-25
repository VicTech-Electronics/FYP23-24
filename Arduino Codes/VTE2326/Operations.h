#include "Arduino.h"
#include "Measurement.h"
#include "Communication.h"
#include <Arduino_JSON.h>

JSONVar json_object;
String device_number = "2";

// Definition of pin conntions
uint8_t pump_pin = 2;

// Definition of usefull variables
float measured_values[3];
float required_values[3];

// Methode to initialize process
void initialize() {
  pinMode(pump_pin, OUTPUT);

  Serial.begin(9600);
  initializeWIFI();
  initializeNPK();
}

// Method for measurements
void measure() {
  measured_values[0] = nitrogen();
  measured_values[1] = phosphorous();
  measured_values[2] = potassium();
}

// Methode to send data to the server
void sendDataToServer() {
  json_object["device_no"] = device_number;
  json_object["nitrogen"] = measured_values[0];
  json_object["phosphorous"] = measured_values[1];
  json_object["potassium"] = measured_values[2];

  String payload = JSON.stringify(json_object);
  String response = postRequest(payload);

  json_object = JSON.parse(response);

  if ((bool)json_object["status"] == true) {
    required_values[0] = (double)json_object["data"]["req_nitrogen"];
    required_values[1] = (double)json_object["data"]["req_phosphorus"];
    required_values[2] = (double)json_object["data"]["req_potassium"];

    Serial.println("Response message: " + (String)json_object["message"]);
  }else Serial.println("Fail to send request to the Server");
  
}
