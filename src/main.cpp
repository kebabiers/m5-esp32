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

uint8_t btn = 0;

void setup() {

  initDisplay();
  
  displayText("Chargement du capteur..", 0, 0);
  initSensor(SENSOR);
  waitSensor(10);
  clearDisplay();
#ifdef DEBUG
  Serial.begin(115200);
#endif

  //WiFi.begin(SSID, PASS);
  // while(millis() < 20000 && WiFi.status() != WL_CONNECTED) { yield(); }

  // if(WiFi.status() == WL_CONNECTED) {

  //   Serial.println("Wifi ok");
  //   displayText("wifi connected", 0, 0);
  //   configTime(3600, 3600, "pool.ntp.org");
  //   while(!getLocalTime(&timeinfo)) {};
  
  // }

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
  uint8_t tmpBtn = checkBtn();
  if(tmpBtn != btn) btn = tmpBtn;

  Serial.println(btn);
  // Start loop with delay
  if(millis() / 1000 > sec + SEND_DELAY) {
    sec = (int) millis() / 1000;

    int value = getSensorValue(SENSOR);
    clearDisplay();
    showSensor(btn, value);
    //sendValue(value, DEVICE_ID, DEVICE_NAME);
    //displayText(String(value).c_str(), 10, 10);
    //displayProgressBar(0, 20, TFT_HEIGHT, 10, value);

#ifdef DEBUG
    char ppm[20];
    sprintf(ppm, "ppm: %i", value);
    displayText(ppm, 0, TFT_WIDTH - 20);
#endif
  }
}