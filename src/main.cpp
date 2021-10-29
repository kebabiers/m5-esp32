#include <Arduino.h>
#include <M5Stack.h>
#include <HTTPClient.h>
#include <wifi.h>
#include <timer.h>
#include <sendJson.h>
#include <micro.h>
#include <co2.h>

int valCo2 = 0;

void setup() {
  // démarre le M5 et le Serial
  M5.begin();
  Serial.begin(115200);
  //connectWifi();
  setupMicro();
  //setupCo2();
  //setTime();

}

void loop() {
  MicroPhoneFFT();
    //valCo2 = loopCo2();

    // envoie les données toutes les 10 secondes 
    
    //if(millis() / 1000 > sec + 10) {
     //   sec = (int) millis() / 1000;
      //  if(WiFi.status() == WL_CONNECTED) sendJson("co2", valCo2);
    //}
    ;
}