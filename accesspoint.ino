#include <ESP8266WiFi.h>
#include <WiFiManager.h>

void setup_wifi(boolean reset) {
    
  WiFiManager wifiManager;

  // to reset the wifiManager and the EEPROMto input new information
  if(reset){
    wifiManager.resetSettings();
  }

  wifiManager.autoConnect("rc-desk-switch-AP");

  // if you get here you have connected to the WiFi
  Serial.println("Connected.");
}
