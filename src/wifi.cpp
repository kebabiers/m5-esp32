#include <WiFi.h>
#include <Arduino.h>
#include <M5Stack.h>
#include "wifi.h"

const char *ssid = "Thomas";
const char *pass = "vx3wcejfb";


// se connecte au wifi
void connectWifi(){
    WiFi.begin(ssid, pass);
    M5.Lcd.print("connection en cours...");

    while (WiFi.status() != WL_CONNECTED) {
        M5.Lcd.print(".");
        delay(50);
    }
    M5.Lcd.clear();
    M5.Lcd.print("connecté ! ");
    delay(2000);
    M5.Lcd.clear();
}