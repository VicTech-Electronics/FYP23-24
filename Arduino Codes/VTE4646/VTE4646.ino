#include "Activities.h"

void setup() {
  initialize();
}

void loop() {
  while (getOutputCurrent() > min_load_current) {
    if (mode == "auto") {
      if (getBatteryVolt(0) < min_battery_volt && getBatteryVolt(1) < min_battery_volt) connectBatteries();
      else if (getBatteryVolt(2) > min_battery_volt) changeOver(false);
      else if (getBatteryVolt(0) > min_battery_volt) changeOver();
      overchargeProtection();

    } else if (mode == "manual") {
      if (manual_selected == 1) changeOver(false);
      else if (manual_selected == 2) changeOver(true);
      else if (manual_selected == 3) connectBatteries();
      overchargeProtection();
    }
  }
}
