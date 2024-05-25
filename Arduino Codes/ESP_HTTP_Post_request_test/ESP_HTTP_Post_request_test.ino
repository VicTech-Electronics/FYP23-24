#include <Arduino_JSON.h>
#include "Communication.h"

JSONVar object;
uint8_t flash_btn = 0;

void setup() {
  pinMode(flash_btn, INPUT);
  Serial.begin(9600);
  initializeWIFI();
}

void loop() {
  if (digitalRead(flash_btn) == LOW) {
    object["fingerprint_id"] = "1234";
    String payload = JSON.stringify(object);
    String response = postRequest(payload);

    Serial.println("Response: " + response);
  }
}
