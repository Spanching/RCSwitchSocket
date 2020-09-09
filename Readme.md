# PC Switch

## 1. Motivation

This repository shows my effort to be able to control an RC Socket and my PC with MQTT/Alexa. It is highly recommendet to have a look at my [PC Socket repository](https://github.com/Spanching/PCSwitch) to understand the usage.

## 2. Hardware

- Wemos D1 mini
- RC Sender Module
- perf board with some male/female header pins

Just connect the sender module with 5V/GND and any data input of the wemos that you want, I used D3/GPIO0.

## 3. Installation

For this to work you will need the following Arduino Libraries:
- Arduino
- PubSubClient
- WiFiClient
- ESP8266WiFi
- WiFiManager
- ArduinoOTA
- RCSwitch

All of which are available in the Arduino IDE.

## 4. Usage

I built this device to enable and disable my RC Socket that is responsible for the power connection to my PC. I did connect it with a module inside my PC, so starting and stopping my setup will correspond to enable RC Socket, turn on PC or turn off PC - wait until it is shutdown, disable RC Socket. I use Node-Red for the mapping of Inputs like Alexa to the corresponding outputs like this RC Socket or my PC Switch. 