#include "Arduino.h"
#include "Display.h"
#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Arduino_JSON.h>
#include <SoftwareSerial.h>
#define SS_PIN 16
#define RST_PIN 2

JSONVar json_object;
MFRC522 mfrc522(SS_PIN, RST_PIN);

const char* ssid = "Civilian Teachers SKUA";
const char* password = "civilian1234";
const char* serverUrl = "http://64.23.247.79";


// Definition of pin connections
uint8_t buzzer_pin = 15;

// Decralation of usefull variable
String card_number;
String http_response = "";
int httpResponseCode;

void initializeWIFI() {
  pinMode(buzzer_pin, OUTPUT);
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

  if ((bool)json_object["success"]) return "Success";
  else return "Fail";
}

// Method to read card number
String getCardNumber(){
  // Check if a new card is present
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()){
    digitalWrite(buzzer_pin, HIGH);
    lcdPrint("Billing system", "Scanning...");
    // Get the card number
    card_number = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      card_number += String(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println("Card Number: " + card_number);

    // Halt PICC and stop reading
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();

    delay(1000);
    digitalWrite(buzzer_pin, LOW);
    lcdPrint("Billing system", "Card: " + card_number);
    delay(1000);

    return card_number;
  } return "";
}