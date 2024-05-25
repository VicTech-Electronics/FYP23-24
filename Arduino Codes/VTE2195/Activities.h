// Definitions of pins connection
uint8_t sensor_pins[] = { A3, A4, A5 };
uint8_t switch_pins[] = { 9, 10, 11 };
uint8_t led_pins[] = { 2, 3, 4 };

// Definition of usefull variables
uint8_t counter;


// Initiate activities
void initiateActivities() {
  for (counter = 0; counter < 3; counter++) {
    pinMode(sensor_pins[counter], INPUT);
    pinMode(switch_pins[counter], OUTPUT);
    pinMode(led_pins[counter], OUTPUT);
  }
}

// Method to switch the channel
void switchChannel(uint8_t channel_index, bool state) {
  digitalWrite(switch_pins[channel_index], state);
  digitalWrite(led_pins[channel_index], state);
}

// Method to calculate power rate
float powerRate(uint8_t channel_index) {
  float sensor_value = analogRead(sensor_pins[channel_index]);
  float voltage_reading = map(sensor_value, 0., 1023., 0., 5.);
  float current_value = voltage_reading / 2.2;
  float power_rating = current_value * 220.;

  return sensor_value;
}
