#include "FingerPrint.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Arduino_JSON.h>

JSONVar json_object;

const char* ssid = "Civilian Teachers SKUA";
const char* password = "civilian1234";
const char* serverUrl = "http://64.23.247.79:8000/api/fingerprint/update";

String http_response = "";
String nextion_message;
int httpResponseCode;

void initializeWIFI() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");
}

String postRequest(String payload) {
  WiFiClient client;
  HTTPClient http;
  http.begin(client, serverUrl);

  http.addHeader("Content-Type", "application/json");
  httpResponseCode = http.POST(payload);
  http_response = http.getString();
  http.end();

  Serial.println("HTTP Response code: " + String(httpResponseCode));
  Serial.println("HTTP Response string: " + String(http_response));

  json_object = JSON.parse(http_response);

  if ((bool)json_object["success"]) return "success";
  else return "fail";
}


void sendDataToNextion(String data) {
  nextion_serial.listen();
  if (nextion_serial.isListening()) {
    nextion_serial.print(data);
    nextion_serial.write(0xfff);
    nextion_serial.write(0xfff);
    nextion_serial.write(0xfff);
  }
}

String receiveDataFromNextion() {
  nextion_serial.listen();
  nextion_message = "";
  if (nextion_serial.isListening()) {
    if (nextion_serial.available()) {
      delay(50);
      while (nextion_serial.available()) {
        nextion_message += char(nextion_serial.read());
      }
    }
  }
  return nextion_message;
}
