#include "Communication.h"

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcdPrint("Welcome", ""); delay(1000);
  lcdPrint("RFID", "Billing system"); delay(1000);
  initializeWIFI();
}

void loop() {
  card_number = getCardNumber();
  while(card_number == "") card_number = getCardNumber();

  lcdPrint("Billing system", "Processing...");
  json_object["card_no"] = card_number;
  String payload = JSON.stringify(json_object);
  String response = postRequest(payload);

  digitalWrite(buzzer_pin, HIGH); delay(500);
  digitalWrite(buzzer_pin, LOW);
  lcdPrint(response, "..."); delay(1000);
}
