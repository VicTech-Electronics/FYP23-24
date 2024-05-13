#include "Control.h"

//  Definition of usefull variables and constants 
uint8_t no_of_dosage_intake_per_day = 0;

void systemOperation(){
  while(current_mode == "Setting"){
    lcdPrint("Intake per Day", "Intake: " + String(no_of_dosage_intake_per_day));
    if(digitalRead(right_btn_pin) == LOW) no_of_dosage_intake_per_day += 1;
    if(digitalRead(left_btn_pin) == LOW) no_of_dosage_intake_per_day -= 1;
    if(no_of_dosage_intake_per_day > 3) no_of_dosage_intake_per_day = 3;
    if(no_of_dosage_intake_per_day < 0) no_of_dosage_intake_per_day = 0;
  }


}
