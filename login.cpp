#include "login.h"
#include <EEPROM.h>

void login::processRequest(String req){
  int tamanho = req.length();
  
  for(int i=0; i<tamanho; i++){
    if(req.charAt(i) == '?'){
      for(int j=0; j<23; j++){
        i++;
        if(isDigit(req.charAt(i)) > 0){
          command += req.charAt(i);
        }
      }
    }
  }
  for(int i=0; i<tamanho; i++){
    if(req.charAt(i) == '&'){
      i++;
      while(req.charAt(i) != '*'){
        ssid += req.charAt(i);
        i++;
      }
      i++;
      while(req.charAt(i) != '%'){
        pswd += req.charAt(i);
        i++;
      }
    }
  }
}

String login::getCommand(String req){
  command = "";  
  processRequest(req);
  return command;  
};
 
String login::getSSID(String req){
  ssid = "";  
  processRequest(req);
  return ssid;  
};

String login::getPSWD(String req){
  pswd = "";
  processRequest(req);
  return pswd;
};

String login::read(){
  EEPROM.begin(95);
  if(EEPROM.read(0) == '&'){
    String conectionInfo = "";
    int i = 0;
    while(EEPROM.read(i) != '%'){
      conectionInfo += (char) EEPROM.read(i);
      i++;
    }
    conectionInfo += '%';
    EEPROM.end();
    return conectionInfo;
  }
  else{
    EEPROM.end();
    return "0";
  }
}

String login::store(String conectionInfo){
  EEPROM.begin(95);
  for(int i = 0; i < conectionInfo.length(); i++){
    EEPROM.write(i, conectionInfo[i]);
  }
  if(EEPROM.commit()){
    Serial.println("EEPROM successfully committed");
  }
  else{
    Serial.println("EEPROM error: commit failed");
  }
  EEPROM.end();
}

void login::clean(){
  EEPROM.begin(95);
  for (int i = 0; i < 95; i++){
    EEPROM.write(i, 0);
  }
  EEPROM.end();
}
