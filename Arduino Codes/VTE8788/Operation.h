uint8_t buzzer_pin = 1, mode_btn_pin = 2;
String mode = "operation";


void changeMode(){
  digitalWrite(buzzer_pin, HIGH);

  if(mode == "operation") mode = "registration";
  else mode = "operation";

  delayMicroseconds(65535);
  digitalWrite(buzzer_pin, LOW);
}

void initializeOperations(){
  pinMode(buzzer_pin, OUTPUT);
  pinMode(mode_btn_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(mode_btn_pin), changeMode, FALLING);
}