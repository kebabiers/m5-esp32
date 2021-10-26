#include <Arduino.h>
#include <M5Stack.h>

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.Lcd.print("hello world");
}

void loop() {
  // put your main code here, to run repeatedly:
}