#include "Arduino.h"
#include "uRTCLib.h"

uRTCLib rtc(0x68);

String getTime_RTC() {
  rtc.refresh();
  return String(rtc.hour()) + String(rtc.minute());
}
    