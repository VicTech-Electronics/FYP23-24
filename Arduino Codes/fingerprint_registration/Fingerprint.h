#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#define Rx 13
#define Tx 12


SoftwareSerial serialFingerprint(Rx, Tx);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&serialFingerprint);

int fingerprint, fingerprint_id = 0, tz = 1;
uint8_t buzzer_pin = 5;
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
void initializeFingerprint(){
  pinMode(buzzer_pin, OUTPUT);
  Serial.println("\n\nAdafruit Fingerprint sensor enrollment");

  // set the data rate for the sensor serial port
  finger.begin(57600);

  if (finger.verifyPassword()) {
    beepSound();
    Serial.println("Found fingerprint sensor!");
  } else {
    warningSound();
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  Serial.println(F("Reading sensor parameters"));
  finger.getParameters();
  Serial.print(F("Status: 0x")); Serial.println(finger.status_reg, HEX);
  Serial.print(F("Sys ID: 0x")); Serial.println(finger.system_id, HEX);
  Serial.print(F("Capacity: ")); Serial.println(finger.capacity);
  Serial.print(F("Security level: ")); Serial.println(finger.security_level);
  Serial.print(F("Device address: ")); Serial.println(finger.device_addr, HEX);
  Serial.print(F("Packet len: ")); Serial.println(finger.packet_len);
  Serial.print(F("Baud rate: ")); Serial.println(finger.baud_rate);
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


// Methode to register new fingerprint
boolean registerFingerprint() {
  fingerprint_id = random(1000);
  while (finger.loadModel(fingerprint_id) == FINGERPRINT_OK) fingerprint_id = random(1000);

  scanFingerprint();
  if (error == true) {
    error = false;
    return false;
  }

  fingerprint = finger.fingerSearch();
  if (fingerprint != FINGERPRINT_NOTFOUND) {
    warningSound();
    return false;
  }

  scanFingerprint();
  if (error == true) {
    warningSound();
    error = false;
    return false;
  }

  fingerprint = finger.createModel();
  if (fingerprint == FINGERPRINT_OK) {
    beepSound();
    return true;
  } else {
    warningSound();
    return false;
  }
}

// Methode to get New finger print
bool getFingerprint() {
  scanFingerprint();
  if (error == true) {
    error = false;
    return false;
  }

  fingerprint = finger.fingerSearch();
  if (fingerprint == FINGERPRINT_OK) {
    fingerprint_id = finger.fingerID;
    return true;
  } else return false;
}
