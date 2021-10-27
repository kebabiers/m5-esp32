#include <Arduino.h>
#include <M5Stack.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <wifi.h>
#include <timer.h>
#include <sendJson.h>


void setup() {
  M5.begin();
  M5.Power.begin();

  connectWifi();
  setTime();

}

void loop() {
  // put your main code here, to run repeatedly:
  if (WiFi.status() == WL_CONNECTED){
    sendJson();
    delay(20000);
  };

}