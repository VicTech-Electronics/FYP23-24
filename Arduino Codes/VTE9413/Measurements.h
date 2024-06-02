// Definition of pin connection
const uint8_t ph_pin=A0, flowrate1_pin=15, flowrate2_pin=2, turbidity_pin=13, valve_pin1=16, valve_pin2=14;


// Decralation of usefull variables and constants
const int interval = 2000;
const uint8_t pH_samples = 10;
unsigned long current_time, previous_time;
volatile int flowrate1_pulses=0, flowrate2_pulses=0;

// Method to handle count pulse Interrupt
void countPulse1() {
  flowrate1_pulses++;
}
void countPulse2() {
  flowrate2_pulses++;
}

// Method to initialize the proecess
void initialization(){
  pinMode(valve_pin1, OUTPUT);
  pinMode(valve_pin2, OUTPUT);
  pinMode(turbidity_pin, INPUT);
  pinMode(flowrate1_pin, INPUT);
  pinMode(flowrate2_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(flowrate1_pin), countPulse1, RISING);
  attachInterrupt(digitalPinToInterrupt(flowrate2_pin), countPulse2, RISING);
}



float getFlowrate(int flowCounter){
  current_time = millis();
  float flowrate = 0.;
  if (current_time - previous_time >= interval) {
    noInterrupts();  // Disable interrupts
    flowrate = (float)flowCounter / ((float)interval / 1000.0);
    previous_time = current_time;
    flowrate1_pulses = 0;
    flowrate2_pulses = 0;
    interrupts();  // Enable interrupt
  }
  return flowrate;
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


// Method to conctrol the valve
void openValve(bool state){
  digitalWrite(valve_pin1, state);
  digitalWrite(valve_pin2, !state);
}