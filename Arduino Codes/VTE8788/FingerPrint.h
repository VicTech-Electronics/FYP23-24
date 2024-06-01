#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial nextion_serial(14, 16);
SoftwareSerial fingerprint_serial(13, 12); 
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerprint_serial);


uint8_t fingerprint_data;

void initializeFingerprint() {
  fingerprint_serial.listen();
  if (fingerprint_serial.isListening()) {
    finger.begin(57600);
    delay(5);
    if (finger.verifyPassword()) {
      Serial.println("Found fingerprint sensor!");
    } else {
      Serial.println("Did not find fingerprint sensor :(");
      while (1) { delay(1); }
    }
  } else Serial.println("Fail to listen to FingerPrint serial");
}

String getFingerprintID() {
  Serial.println("Waiting for valid fingerprint...");

  fingerprint_serial.listen();
  if (fingerprint_serial.isListening()) {
    fingerprint_data = finger.getImage();
    if (fingerprint_data != FINGERPRINT_OK) return "Fail to get finger image";

    fingerprint_data = finger.image2Tz();
    if (fingerprint_data != FINGERPRINT_OK) return "Fail to convert finger image to ID";

    fingerprint_data = finger.fingerFastSearch();
    if (fingerprint_data == FINGERPRINT_OK)
      return "printID:" + String(finger.fingerID);
    else return "Fail to get printID";
  }

  return "Fail to listen";
}