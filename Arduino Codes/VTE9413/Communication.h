#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Arduino_JSON.h>

JSONVar json_object;

const char* ssid = "Civilian Teachers SKUA";
const char* password = "civilian1234";
const char* serverUrl = "http://64.23.247.79";


// Definition of pin connections

// Decralation of usefull variable
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

// Method to post request to the web server
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

  if ((bool)json_object["success"]) return "Sent.";
  else return "Fail.";
}