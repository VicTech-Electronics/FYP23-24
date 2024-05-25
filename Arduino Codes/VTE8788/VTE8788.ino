#include "Operation.h"
#include "Communication.h"
#include <Arduino_JSON.h>

JSONVar json_object;
String fingerprint, payload, response;

void setup() {
  Serial.begin(9600);
  nextion_serial.begin(9600);
  
  initializeFingerprint();
  initializeOperations();
  initializeWIFI();
}

void loop() {
  while(mode == "registration"){
    fingerprint = getFingerprintID();
    if(fingerprint.startsWith("printID")){
      uint8_t space_index = fingerprint.indexOf(' ');
      if(space_index != -1){
        fingerprint =  fingerprint.substring(space_index + 1);
        json_object["fingerprint_id"] = fingerprint;
        payload = JSON.stringify(json_object);
        response = postRequest(payload);
        sendDataToNextion(response);
      }
    }
  }

  payload = receiveDataFromNextion();
  response = postRequest(payload);
  sendDataToNextion(response);
}
