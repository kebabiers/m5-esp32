#ifndef TEXT_CPP
#define TEXT_CPP

#include <Arduino.h>
#include "text.h"
#include <M5Stack.h>

#define DEFAULT_TEXT_SIZE 2
#define DEFAULT_TEXT_COLOR TFT_WHITE

void initDisplay() {
  M5.begin(true, false, true, true);
  M5.Power.begin();
}

void clearDisplay() {
  M5.Lcd.clear();
}

void clearDisplay(int x, int y, int w, int h) {
  M5.Lcd.fillRect(x, y, w, h, TFT_BLACK);
}

void displayText(const char *text, int x, int y, unsigned d, uint16_t color, uint8_t s) {
  M5.Lcd.setTextColor(color);
  M5.Lcd.setTextSize(s);
  M5.Lcd.drawString(String(text), x, y);
  delay(d); // A le faire en non-bloquant
  M5.Lcd.setTextSize(DEFAULT_TEXT_SIZE);
  M5.Lcd.setTextColor(DEFAULT_TEXT_COLOR);
}

void displayText(const char *text, int x, int y) {
  M5.Lcd.drawString(String(text), x, y);
}

void displayProgressBar(int x, int y, int w, int h, int val) {
  M5.Lcd.progressBar(x, y, w, h, ((float) 600 / val) * 100);
}

#endif