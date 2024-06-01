#include <SoftwareSerial.h>
#include <Arduino_JSON.h>
#define Rx 1
#define Tx 2

JSONVar json_object;
SoftwareSerial serialESP(Rx, Tx);

// Method to send card number to ESP for payment
bool sendCardNumber(String card_no){
  json_object["card_number"] = card_no;
  String payload = JSON.stringify(json_object);

  serialESP.println(payload);
  
  while(!serialESP.available()){
    Serial.println("Waiting for the data from the network");
    delay(1e3);
  } 
  String response = serialESP.readString();
  Serial.println("Response: " + response);

  if(response == "confirmed") return true;
  else return false;
}