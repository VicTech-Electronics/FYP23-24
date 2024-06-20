#include <SoftwareSerial.h>
#define RFID_Rx 12
#define RFID_Tx 14

SoftwareSerial serialRFID(RFID_Rx, RFID_Tx);

// Definition of pin connections
const uint8_t hb_pin=13, mq_pin=16, vib_pin=0, temp_pin=2, frame_pin=A0;

// Decralation of usefull variables
bool vibration, 

// Method to initialize measurements
void initMeasurements(){
  pinMode(hb_pin, INPUT);
  pinMode(mq_pin, INPUT);
  pinMode(vib_pin, INPUT);
  pinMode(temp_pin, INPUT);
  pinMode(frame_pin, INPUT;
}


// Method to read digital sensor values
bool measureDigitalSensors(){
  return digitalRead(vib_pin);
}



// Method to read RFID
String getCardNumber(){
  while(serialRFID.available()){
    
  }
}


