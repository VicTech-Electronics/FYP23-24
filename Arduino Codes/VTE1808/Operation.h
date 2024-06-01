#include "WString.h"
#include "Control.h"

//  Definition of usefull variables and constants
uint8_t no_of_dosage_intake_per_day = 0;
bool at_default_portion = true;
uint8_t current_portion = 0;
uint8_t hours_setting = 0,
        minute_setting = 0;
String time_settings[3];
String current_time = "20:30";

// Method to alert and open for dosage
void dosageTime(String time) {
  if (current_time == time) {
    current_portion += 1;
    if (current_portion > 7) current_portion = 1;
    controlStepper(current_portion);
    at_default_portion = false;
    alert(true);
  }
  if (!at_default_portion) {
    controlStepper(current_portion + (8 - current_portion));
    at_default_portion = true;
    alert(false);
  }
}

void systemOperation() {
  while (current_mode == "Setting") {
    delay(2000);
    lcdPrint("Intake per Day", "Intake: " + String(no_of_dosage_intake_per_day));
    if (!digitalRead(right_btn_pin)) no_of_dosage_intake_per_day += 1;
    if (no_of_dosage_intake_per_day > 3) no_of_dosage_intake_per_day = 3;
    if (no_of_dosage_intake_per_day < 0) no_of_dosage_intake_per_day = 0;


    if (!digitalRead(left_btn_pin)) {
      if (no_of_dosage_intake_per_day > 0) {
        for (int i = 1; i <= no_of_dosage_intake_per_day; i++) {
          delay(1000);

          while (digitalRead(left_btn_pin)) {
            lcdPrint("Intake " + String(i) + ": Set H", "Time: " + String(hours_setting) + ":" + String(minute_setting));
            if (!digitalRead(right_btn_pin)) hours_setting += 1;
            if (hours_setting > 23) hours_setting = 0;
          }

          delay(1000);

          while (digitalRead(left_btn_pin)) {
            lcdPrint("Intake " + String(i) + ": Set M", "Time: " + String(hours_setting) + ":" + String(minute_setting));
            if (!digitalRead(right_btn_pin)) minute_setting += 1;
            if (minute_setting > 59) minute_setting = 0;
          }

          time_settings[i-1] = String(hours_setting) + ":" + String(minute_setting);
          hours_setting = 0;
          minute_setting = 0;
        }
      }
    }
  }

  current_time = getTime_RTC();
  lcdPrint("Dosage System", "Time: " + current_time);

  for(int i=0; i<3; i++){
    if(current_time == time_settings[i]){
      lcdPrint("Time: " + current_time, "Dosage Time");
      dosageTime(time_settings[i]);
    }
  }
}
