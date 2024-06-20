#include <SoftwareSerial.h>
#define gsm_Rx 6
#define gsm_Tx 7

SoftwareSerial serialGSM(gsm_Rx, gsm_Tx);
String host = "http://64.23.247.79";


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

// Methode to Connect GPRS connection
void connectGPRS(){
  commandGSM("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  commandGSM("AT+SAPBR=3,1,\"APN\",\"internet\"");
  commandGSM("AT+SAPBR=1,1");
  commandGSM("AT+SAPBR=2,1");
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

// Methode to get response from the Server
void getResponse(String res_command){
  String payload;
  if(serialGSM.available()) payload = serialGSM.readString();
  payload.trim();
}

// Methode to send HTTP request
void postRequest(String json_data){
  commandGSM("AT+HTTPINIT");
  commandGSM("AT+HTTPPARA=\"CID\",1");
  commandGSM("AT+HTTPPARA=\"URL\",\"" + host + "\"");
  commandGSM("AT+HTTPPARA=\"CONTENT\",\"application/json\"");
  commandGSM("AT+HTTPDATA=" + String(json_data.length()) + ",100000");
  commandGSM(json_data);
  commandGSM("AT+HTTPACTION=1"); delay(20e3);
  commandGSM("AT+HTTPREAD"); delay(2e3);
  getResponse("+HTTPREAD:");
  commandGSM("AT+HTTPTERM");
}