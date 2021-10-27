#ifndef TEXT_CPP
#define TEXT_CPP

#include <Arduino.h>
#include "text.h"
#include <M5Stack.h>

#define DEFAULT_TEXT_SIZE 2
#define DEFAULT_TEXT_COLOR TFT_WHITE

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

#endif