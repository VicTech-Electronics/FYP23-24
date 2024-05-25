#include <Arduino_JSON.h>
#include "Communication.h"

JSONVar json_object;

void setup() {
  Serial.begin(9600);
  
  initializeWIFI();
  initializeFingerprint();
}

void loop() {
  if(registerFingerprint()){
    json_object["fingerprint_id"] = fingerprint;
    String payload = JSON.stringify(json_object);
    String response = postRequest(payload);
    Serial.println("Response: " + response);
  }
}
