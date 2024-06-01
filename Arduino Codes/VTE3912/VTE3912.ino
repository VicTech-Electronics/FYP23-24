#include "Operations.h"

// Decralation of usefull variable
float min_moisture = 50.0;

void setup() {
  initialization();
}

void loop() {
  measurement();
  if(!watering_state){
    if(moisture_level < min_moisture) digitalWrite(pump_pin, HIGH);
    else digitalWrite(pump_pin, LOW);
  }


  if(raining && moisture_level > min_moisture) openLoof(false);
  else openLoof(true);
}
