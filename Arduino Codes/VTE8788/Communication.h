#include "FingerPrint.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "YourNetworkSSID";                        // Replace with your network SSID
const char* password = "YourNetworkPassword";                // Replace with your network password
const char* serverUrl = "http://64.23.247.79";  

SoftwareSerial nextion_serial(1, 2);
String nextion_message = "";
String http_response = "";
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
  Serial.println("HTTP Response Code: " + String(httpResponseCode));
  http.end();

  if (httpResponseCode == 200) return "success";
  else return "fail";
}


void sendDataToNextion(String data) {
  nextion_serial.print(data);
  nextion_serial.write(0xfff);
  nextion_serial.write(0xfff);
  nextion_serial.write(0xfff);
}

String receiveDataFromNextion() {
  if (nextion_serial.available()) {
    nextion_message = "";
    delay(50);
    while (nextion_serial.available()) {
      nextion_message += char(nextion_serial.read());
    }
  } else return "No message";
  return nextion_message;
}
