#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 8
#define RST_PIN 4

MFRC522 mfrc522(SS_PIN, RST_PIN);

// Definition of pin connection
uint8_t acceptor_pin = 2;

// Decralation of usefull variable
uint8_t pulse_counter;
unsigned long count_rate;
String card_number;

// Method to handle the countingPulse interrupt
void coutingPulseISR() {
  pulse_counter++;
  count_rate = 0;
}

// Initialize the sensor activities
void initializeSensors() {
  pinMode(acceptor_pin, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(acceptor_pin), coutingPulseISR, FALLING);
}

// Method to read card number
String getCardNumber() {
  // Check if a new card is present
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Get the card number
    card_number = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      card_number += String(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println("Card Number: " + card_number);

    // Halt PICC and stop reading
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();

    return card_number;
  }
  return "";
}