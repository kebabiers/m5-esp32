#include <Arduino.h>
#include <M5Stack.h>
#include <WiFi.h>

char* ssid = "Iphone";
const char* pass =  "sech38dzk";

void setup() {
  M5.begin();
  M5.Power.begin();

  M5.Lcd. fillScreen(BLACK);
  M5.Lcd.setCursor(0,10);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(3);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.printf("Connexion au WiFi en cours...");
  }
  
  M5.Lcd.printIn("Connexion au WiFi reussi");
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.printf("Merguez");
  
 }

void loop() {
  // put your main code here, to run repeatedly:
}