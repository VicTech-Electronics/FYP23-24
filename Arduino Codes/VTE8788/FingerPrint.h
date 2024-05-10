#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial fingerprint_serial(2, 3); // Arduino RX pin 2, TX pin 3
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerprint_serial);

void initializeFingerprint(){
  if (!finger.begin(57600)) {
    Serial.println("Couldn't find fingerprint sensor :(");
    while (1);
  }
  Serial.println("Found fingerprint sensor!");
}

String getFingerprintID(){  
  Serial.println("Waiting for valid fingerprint...");
  while (!finger.verifyPassword()) delay(500);

  uint8_t found = finger.getImage();
  if (found != FINGERPRINT_OK) return "fail"

  found = finger.image2Tz();
  if (found != FINGERPRINT_OK) return "fail"

  found = finger.fingerFastSearch();
  if (found == FINGERPRINT_OK) {
    return String(finger.fingerID());
  } else return "fail"
}