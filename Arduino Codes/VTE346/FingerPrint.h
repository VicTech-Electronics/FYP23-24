#include "Arduino.h"
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#define Rx 8
#define Tx 7

SoftwareSerial serialFingerprint(Rx, Tx);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&serialFingerprint);

int fingerprint, fingerprint_id = 0, tz = 1;
bool error = false;

// Method for buzzer beep
void beepSound() {
  digitalWrite(buzzer_pin, HIGH);
  delay(1000);
  digitalWrite(buzzer_pin, LOW);
}

void warningSound() {
  beepSound();
  delay(500);
  beepSound();
  delay(500);
  beepSound();
}


// Methode to initialize fingerprint
void initializeFingerprint() {
  serialFingerprint.listen();
  Serial.println("\n\nAdafruit Fingerprint sensor enrollment");
  finger.begin(57600);

  if (finger.verifyPassword()) {
    beepSound();
    Serial.println("Found fingerprint sensor!");
  } else {
    warningSound();
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }
  serialFingerprint.stopListening();
}


// Method to scann fingerprint
void scanFingerprint() {
  fingerprint = finger.getImage();
  while (fingerprint == FINGERPRINT_NOFINGER)
    fingerprint = finger.getImage();


  if (fingerprint == FINGERPRINT_OK) {
    if (tz == 1) {
      fingerprint = finger.image2Tz(tz);
      tz = 2;
    } else if (tz == 2) {
      fingerprint = finger.image2Tz(tz);
      tz = 1;
    }

    if (fingerprint == FINGERPRINT_OK)
      beepSound();
    else {
      warningSound();
      error = true;
    }
  } else {
    warningSound();
    error = true;
  }

  while (fingerprint != FINGERPRINT_NOFINGER)
    fingerprint = finger.getImage();
  fingerprint = -1;
}

// Methode to get New finger print
bool getFingerprint() {
  serialFingerprint.listen();
  scanFingerprint();
  if (error == true) {
    error = false;
    return false;
  }

  fingerprint = finger.fingerSearch();
  if (fingerprint == FINGERPRINT_OK) {
    fingerprint_id = finger.fingerID;
    serialFingerprint.stopListening();
    return true;
  }
  serialFingerprint.stopListening();
  return false;
}
