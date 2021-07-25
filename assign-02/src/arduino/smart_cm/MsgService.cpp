#include "Arduino.h"
#include "MsgService.h"

String content;
Msg* currentMsg;

bool MsgService::isMsgAvailable(){
  return currentMsg != NULL;
}

Msg* MsgService::receiveMsg(){
  if (currentMsg != NULL){
    Msg* msg = currentMsg;
    currentMsg = NULL;
    content = "";
    return msg;  
  } else {
    return NULL; 
  }
}

void MsgService::init(){
  Serial.begin(9600);
  content.reserve(256);
  content = "";
  currentMsg = NULL;
}

void MsgService::sendMsg(const String& msg){
  Serial.println(msg);  
}

void serialEvent() {
  delay(50);
  
  /* reading the content */
  while (Serial.available()) {
    content += (char)Serial.read();      
  }
  
  currentMsg = new Msg(content);
  // MsgService.msgAvailable = true;
}

bool MsgService::isMsgAvailable(Pattern& pattern){
  return (currentMsg != NULL && pattern.match(*currentMsg));
}

Msg* MsgService::receiveMsg(Pattern& pattern){
  if (currentMsg != NULL && pattern.match(*currentMsg)){
    Msg* msg = currentMsg;
    currentMsg = NULL;
    content = "";
    return msg;  
  } else {
    return NULL; 
  }
  
}


