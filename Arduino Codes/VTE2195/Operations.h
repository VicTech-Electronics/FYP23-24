#include <EEPROM.h>
#include "Activities.h"
#include "Communication.h"

// Definitions of usefull terms
float ch1_units, ch2_units, ch3_units;
uint8_t units_storage_address = 0;

struct units_storage {
  float ch1_units_storage;
  float ch2_units_storage;
  float ch3_units_storage;
};

// Methode to store unit
void storeUnitsEEPROM(){
  units_storage units = {
    ch1_units,
    ch2_units,
    ch3_units
  };
  EEPROM.put(units_storage_address, units);
}

// Methode to get unit from EEPROME
void getUnitsEEPROM(){
  units_storage units;
  EEPROM.get(units_storage_address, units);
  ch1_units = units.ch1_units_storage;
  ch2_units = units.ch2_units_storage;
  ch3_units = units.ch3_units_storage;
}