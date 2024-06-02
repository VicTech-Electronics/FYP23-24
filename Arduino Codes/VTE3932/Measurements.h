#include <OneWire.h>
#include <DallasTemperature.h>
#define onewire_bus A0

OnoWire onewire(onewire_bus);
DallasTemperature tempSensor(&onewire);

// Definition of pin connection
const uint8_t mq_pin=A1, ph_pin=A2, turbidity_pin=A3, pump1_pin=A4, pump2_pin=A5;


// Decralation of usefull variables and constants
float Ro = 10.0; // Initial value for Ro, needs calibration
float RL_VALUE = 5.0;    // Load resistance in kilo ohms
float RO_CLEAN_AIR_FACTOR = 1.0; // RO value in clean air
const float normal_ntu = 3000.0;

// Method to handle count pulse Interrupt
void countPulse1() {
  flowrate1_pulses++;
}
void countPulse2() {
  flowrate2_pulses++;
}

// Method to initialize the proecess
void initialization(){
  pinMode(pump1_pin, OUTPUT);
  pinMode(pump2_pin, OUTPUT);

  tempSensor.begin();
  Ro = calibrateSensor(mq_pin);
}


// Method to measures the parameters
float getTemperature(){
  tempSensor.requestTemperatures();
  return tempSensor.getTempCByIndex(0);
}

float getPHValue(){
  int measurings=0;
  for (int i = 0; i < pH_samples; i++){
    measurings += analogRead(ph_pin);
    delay(10);
  }

  float voltage = 5/1024.0 * measurings/pH_samples;
  return 7 + ((2.5 - voltage) / 0.18);
}

float roundToDecimalPoint(float in_value, int decimal_place ){
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}

float getTurbidityValue(){
  float volt = 0.0, ntu = 0.0; 
  for(int i=0; i<800; i++){
    volt += ((float)analogRead(turbidity_pin)/1023)*5;
    delay(50);
  }
    
  volt = volt/800;
  volt = roundToDecimalPoint(volt, 2);

  if(volt < 2.5) ntu = normal_ntu;
  else ntu = -1120.4*square(volt)+5742.3*volt-4353.8;

  return ntu;
}


// Methods to measure ammonia contents
float calibrateSensor(int pin) {
  int i;
  float val = 0;
  
  for (i = 0; i < 50; i++) {
    val += analogRead(pin);
    delay(100);
  }
  val = val / 50; // Calculate the average value
  
  val = RL_VALUE * (1023 - val) / val;
  val = val / RO_CLEAN_AIR_FACTOR;
  
  return val; // Return the calibrated Ro value
}


float getAmmoniaConcetration(){
  float sensorValue = analogRead(mq_pin);
  float ratio = sensorValue / Ro;
  float ammoniaConcentration = calculateAmmoniaPPM(ratio);
}

float calculateAmmoniaPPM(float ratio) {
  float ppm = pow(10, (log10(ratio) - 0.88) / -0.58); // Adjust the constants based on calibration
  return ppm;
}