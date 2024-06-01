#include "Operation.h"

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

    Serial.println("Obtain from FP: " + String(fingerprint));

    if(fingerprint.startsWith("printID")){
      uint8_t colon_index = fingerprint.indexOf(':');
      if(colon_index != -1){
        fingerprint =  fingerprint.substring(colon_index + 1);

        Serial.println("Fingerprint: " + String(fingerprint));

        json_object["fingerprint_id"] = fingerprint.toInt();
        payload = JSON.stringify(json_object);
        response = postRequest(payload);

        Serial.println("Response to screen: " + response);
        // sendDataToNextion(response);
      }
    }
  }

  // payload = receiveDataFromNextion();
  // response = postRequest(payload);

  // json_object = JSON.parse(response);
  // if((bool) json_object["success"])  sendDataToNextion("success");
  // else sendDataToNextion("fail");
}
