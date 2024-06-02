#include "Display.h"
#include "Measurements.h"
#include "Communication.h"


// Decralation of usefull variables
String device_no = "1";
bool leakage = false;
float ph_value, 
      flowrate, 
      flowrate1_value, 
      flowrate2_value,
      turbidity_value,
      min_flowrate_error = 10.;


void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcdPrint("Welcome", ""); delay(500);
  initialization();
  initializeWIFI();
  lcdPrint("Leakage", "Detection System"); delay(1000);
}

void loop() {
  ph_value = getPHValue();
  turbidity_value = digitalRead(turbidity_pin);
  flowrate1_value = getFlowrate(flowrate1_pulses);
  flowrate2_value = getFlowrate(flowrate2_pulses);

  flowrate = (flowrate1_value + flowrate2_value) / 2.;

  if(abs(flowrate1_value - flowrate2_value) > min_flowrate_error) leakage = true;
  else leakage = false;


  // Default lcd screen
  lcdPrint("PH: " + String(ph_value) + "   Turb: " + String(turbidity_value), 
           "Flow: " + String(flowrate) + " Leak: " + String(leakage));

  json_object["device_no"] = device_no;
  json_object["ph"] = ph_value;
  json_object["flowrate"] = flowrate;
  json_object["leakage"] = leakage;
  json_object["turbidity"] = turbidity_value;

  String payload = JSON.stringify(json_object);
  String response = postRequest(payload);

  lcdPrint("Report", response);
  
 }
