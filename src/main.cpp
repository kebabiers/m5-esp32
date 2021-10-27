#include <Arduino.h>
#include <M5Stack.h>
#include <WiFi.h>
#include "time.h"

#include "config.h"
#include "text.h"
#include "api.h"

#define DEBUG

struct tm timeinfo;
unsigned sec = millis() / 1000;

void setup() {

#ifdef DEBUG
  Serial.begin(115200);
#endif

  M5.begin();
  M5.Power.begin();
  displayText("test", 0, 0, 250, TFT_GREEN, 4);

  WiFi.begin(SSID, PASS);
  while(WiFi.status() != WL_CONNECTED) { yield(); }

  displayText("wifi connected", 0, 0);
  configTime(3600, 3600, "pool.ntp.org");
  getLocalTime(&timeinfo);

#ifdef DEBUG
  Serial.println("wifi connected");
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
#endif

}

void loop() {
  // put your main code here, to run repeatedly:
#ifdef DEBUG
  // Serial.println("test");
#endif
  if(millis() / 1000 > sec + 20) {
    // Serial.println(sec);
    sec = (int) millis() / 1000;
    char json[1000];
    createJSON(10, json, DEVICE_ID, DEVICE_NAME);
    Serial.println(json);
    // send2API(json, API_URL, API_KEY);
  }
}