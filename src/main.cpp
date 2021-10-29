#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include <M5Display.h>
#include "config.h"
#include "text.h"
#include "api.h"
#include "sensor.h"
//#include "camera.h"

#define DEBUG

struct tm timeinfo;
unsigned sec = millis() / 1000;

void setup() {

  initDisplay();
  
  displayText("Chargement du capteur..", 0, 0);
  initSensor(SENSOR);
  waitSensor(10);
  clearDisplay();
#ifdef DEBUG
  Serial.begin(115200);
#endif

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

    int value = getSensorValue(SENSOR);
    clearDisplay();
    displayText(String(value).c_str(), 10, 10);
    displayProgressBar(0, 20, TFT_HEIGHT, 10, value);
    time_t timestamp;
    time(&timestamp);
    // Serial.println(sec);
    sec = (int) millis() / 1000;
    char json[1000];
    createJSON(getC02value(), json, DEVICE_ID, DEVICE_NAME, timestamp);
    Serial.println(json);
    // send2API(json, API_URL, API_KEY);
  }
}