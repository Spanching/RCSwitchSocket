#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup_rc_switch() {
  
  mySwitch.enableTransmit(0);
  
  mySwitch.setProtocol(2);

  mySwitch.setRepeatTransmit(3);
  
}

void enableRCDeskSocket() {
  mySwitch.send("10101100101111100111001000000000");
}

void disableRCDeskSocket() {
  mySwitch.send("10100010101111100111001000000000");
}

void genericSendRC(char* message) {
  mySwitch.send(message);
}
