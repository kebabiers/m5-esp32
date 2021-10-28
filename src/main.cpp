#include <Arduino.h>
#include <M5Stack.h>
#include <WiFi.h>
#include "time.h"

#include "config.h"
#include "text.h"
#include "api.h"
#include "camera.h"

#define DEBUG

struct tm timeinfo;
unsigned sec = millis() / 1000;

void setup() {

#ifdef DEBUG
  Serial.begin(115200);
#endif

  M5.begin(true, false, false, false);
  M5.Power.begin();
  displayText("test", 0, 0, 250, TFT_GREEN, 4);

  WiFi.begin(SSID, PASS);
  while(millis() < 20000 && WiFi.status() != WL_CONNECTED) { yield(); }

  if(WiFi.status() == WL_CONNECTED) {

    Serial.println("Wifi ok");
    displayText("wifi connected", 0, 0);
    configTime(3600, 3600, "pool.ntp.org");
    while(!getLocalTime(&timeinfo)) {};
  
  }

#ifdef DEBUG
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
#endif

#ifdef DEBUG
  Serial.println("End setup");
#endif

}

void loop() {
  // put your main code here, to run repeatedly:
#ifdef DEBUG
  // Serial.println("test");
#endif
  if(millis() / 1000 > sec + SEND_DELAY) {
    time_t timestamp;
    time(&timestamp);
    // Serial.println(sec);
    sec = (int) millis() / 1000;
    char json[1000];
    createJSON(10, json, DEVICE_ID, DEVICE_NAME, timestamp);
    Serial.println(json);
    // send2API(json, API_URL, API_KEY);
  }
}