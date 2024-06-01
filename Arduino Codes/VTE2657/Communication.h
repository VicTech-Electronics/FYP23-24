#include <SoftwareSerial.h>
#define gsm_Rx 9
#define gsm_Tx 10

SoftwareSerial serialGSM(gsm_Rx, gsm_Tx);

// Decralation of useful variables
const char* phone_numbers[] = {
  "+255683628828", 
  "+255655191803", 
  "+255768031174", 
  "+255744788692"
};

uint8_t phones = sizeof(phone_numbers) / sizeof(phone_numbers[0]);


// Method for gsm command
void commandGSM(String command) {
  serialGSM.println(command);
  delay(2e3); 
  while (serialGSM.available()) {
    Serial.write(serialGSM.read());
    delay(50);
  }
}

void initializeGSM(){
  commandGSM("AT");
  commandGSM("AT+CMGF=1");
  commandGSM("AT+CNMI=2,2,0,0,0");
}

void sendSMS(String phone, String message) {
  commandGSM("AT+CMGS=\"" + phone + "\"");
  commandGSM(message); delay(3e3);
  serialGSM.println(char(26));
  while (serialGSM.available()) {
    Serial.write(serialGSM.read());
    delay(50);
  }
}

