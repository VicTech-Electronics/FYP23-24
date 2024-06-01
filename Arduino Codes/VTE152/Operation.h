#include "Arduino.h"
#include "Communication.h"
#include <Arduino_JSON.h>

JSONVar json_object;

// Definition of pin connections
uint8_t sensor_pin = 12, alarm_pin = 13;

// Definition of usefull variables
bool info_sent = false;
int waiting_time = 30000;
String device_number = "Device 1";
unsigned long initial_time = millis();

// Methode to initialize operations
void initialize() {
  Serial.begin(9600);
  pinMode(sensor_pin, INPUT);
  pinMode(alarm_pin, OUTPUT);
  initializeWIFI();
}


// Method to alert when high sound detected
void highVoiceAlert() {
  digitalWrite(alarm_pin, HIGH);

  if (!info_sent) {
    json_object["device_no"] = device_number;
    String payload = JSON.stringify(json_object);
    String response = postRequest(payload);

    json_object = JSON.parse(response);
    info_sent = (bool) json_object["status"];
  }
}
