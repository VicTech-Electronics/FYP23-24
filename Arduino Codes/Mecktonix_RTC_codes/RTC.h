#include <ThreeWire.h>
#include <RtcDS1302.h>
#define countof(a) (sizeof(a) / sizeof(a[0]))

ThreeWire myWire(6, 5, 7);  // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

void initiateRTC() {
  pinMode(7, INPUT_PULLUP);
  Rtc.Begin();

  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);

  if (!Rtc.IsDateTimeValid()) Rtc.SetDateTime(compiled);
  if (Rtc.GetIsWriteProtected()) Rtc.SetIsWriteProtected(false);
  if (!Rtc.GetIsRunning()) Rtc.SetIsRunning(true);

  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled) Rtc.SetDateTime(compiled);
}

String getTimeRTC(const RtcDateTime& dt) {
  char timestring[20];
  snprintf_P(timestring,
             countof(timestring),
             PSTR("%02u%02u"),
             dt.Hour(),
             dt.Minute());
  return timestring;
}