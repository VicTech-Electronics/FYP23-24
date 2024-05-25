// Decralation of pin connections
uint8_t btn_pin = 3,
        door_pin = 13,
        buzzer_pin = A3,
        red_led_pin = A1,
        green_led_pin = A2;

#include <Servo.h>
#include "FingerPrint.h"
#include "Communication.h"

Servo door;

//  Definition of usefull variables
int alerting_time = 5000; //Adjast this to change the alerting alarm time
int door_waiting_time = 5000; // Adjast this to change the door waiting time to close after being opened
String scanned_person = "Unknown";
unsigned long initial_alerting_time;
const char* authorized_members[][2] = {
  {"Kapilima", "1234"},
  {"Agaton", "2343"},
  {"Agness", "243"},
  {"Rose", "23423"}
};

const char* unauthorized_members[][2] = {
  {"Chavala", 1231},
  {"Jiulize", 2341},
  {"John Mtaalam", 234}
};

uint8_t number_of_authorized = sizeof(authorized_members) / sizeof(authorized_members[0]),
        number_of_unauthorized = sizeof(unauthorized_members) / sizeof(unauthorized_members[0]);

// Method to show alert
void alertISR() {
  digitalWrite(buzzer_pin, HIGH);
  initial_alerting_time = millis();
}

// Alert method
void stopAlert() {
  if (millis() - initial_alerting_time > alerting_time)
    digitalWrite(buzzer_pin, LOW);
}

// Method to initialize system
void initialize() {
  pinMode(buzzer_pin, OUTPUT);
  pinMode(red_led_pin, OUTPUT);
  pinMode(green_led_pin, OUTPUT);
  pinMode(btn_pin, INPUT_PULLUP);

  initializeFingerprint();
  door.attach(door_pin);
  door.write(0);
  initializeGSM();

  attachInterrupt(digitalPinToInterrupt(btn_pin), alertISR, FALLING);
}


// Method to check for authorized fingerprint
bool isAuthorized(const char* target) {
  for (int i = 0; i < number_of_authorized; i++)
    if (strcmp(authorized_members[i][1], target) == 0){
      scanned_person = authorized_members[i][0];
      return true;
    } 

  for(int i=0; i<number_of_unauthorized; i++)
    if(strcmp(unauthorized_members[i][1], target) == 0){
      scanned_person = unauthorized_members[i][0];
      return false;
    }
  
  scanned_person = "Unknown";
  return false;
}


// Meethod to open the gate
void openDoor(){
  int postion = 0;
  for (postion = 0; postion <= 180; postion += 1) {
    door.write(postion);            
    delay(15);                       
  }

  delay(door_waiting_time);

  for (postion = 180; postion >= 0; postion -= 1) {
    door.write(postion);
    delay(15);
  }
}
