#include "Operations.h"

void setup() {
  initialize();
}

void loop() {
  // Wait for the finger print
  while (!getFingerprint())
    ;

  if (isAuthorized(fingerprint_id))
    openDoor();

  for (int i = 0; i < phones; i++)
    sendSMS(phone_numbers[i], scanned_person);
}
