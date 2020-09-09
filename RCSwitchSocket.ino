
void loopRCSwitch();
void setupRCSwitch();
void setupWifi(bool reset);

void setup() {
  Serial.begin(115200);
  setup_wifi(false);
  setup_mqtt();
  setup_ota();
  setup_rc_switch();
}

void loop() {
  loop_ota();
  loop_mqtt();
}
