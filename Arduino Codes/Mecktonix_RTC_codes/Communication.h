#include <SoftwareSerial.h>
#define rx 2
#define tx 3

SoftwareSerial serialGSM(rx, tx);

void gsmCommand(String command){
  serialGSM.println(command);
  delay(1e3);

  while(serialGSM.available()){
    Serial.write(serialGSM.read());
    delay(50);
  }
}

void initializeGSM(){
  gsmCommand("AT");
  gsmCommand("AT+CMGF=1");
  gsmCommand("AT+CNMI=1,2,0,0,0");
}

String receiveSMS() {
  while (serialGSM.available()) {
    String sms = serialGSM.readString();
    String phone_number = sms.substring(sms.indexOf("CMT") + 6, sms.indexOf("CMT") + 19);
    sms = sms.substring(sms.indexOf("CMT") + 46, sms.indexOf("CMT") + 100);
    sms.trim();
    sms.toUpperCase();
    Serial.println("SMS Received. \n SMS: " + sms);
    while(serialGSM.available()){
      Serial.write(serialGSM.read());
      delay(50);
    }
  
    return sms;
  } return "";
}