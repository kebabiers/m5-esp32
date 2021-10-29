#ifndef TEXT_CPP
#define TEXT_CPP

#include <Arduino.h>
#include "text.h"
#include <M5Stack.h>
#include <sensor.h>

#define DEFAULT_TEXT_SIZE 2
#define DEFAULT_TEXT_COLOR TFT_WHITE

uint8_t checkBtn() {

  M5.update();

  if(M5.BtnA.isPressed()) return 0;
  //if(M5.BtnB.isPressed()) return 1;
  if(M5.BtnC.isPressed()) return 2;

}

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

void createCritAir(unsigned x, unsigned y, unsigned s, unsigned val) {
  int color = TFT_BLUE;
  M5.Lcd.setTextSize(s / 10);

  char message[20];
  sprintf(message, "CRIT'AIR %i", val);

  uint16_t cwidth = M5.Lcd.textWidth(String(val)); // Find the pixel width of the string in the font
  uint16_t cheight = 8 * M5.Lcd.textsize;

  switch (val)
  {
  case 0: color = 0x2649;
    break;
  case 1: color = 0xE8FB;
    break;
  case 2: color = 0xEFE0;
    break;
  case 3: color = 0xFC00;
    break;
  case 4: color = 0xCB24;
    break;
  case 5: color = 0x8C51;
    break;
  default:
    break;
  }
  Serial.printf("color : %x", color);
  M5.Lcd.fillCircle(x, y, s, color);
  for(int i = 0; i < 5; i++) {
    M5.Lcd.drawCircle(x, y, ((s / 3) * 2) + i, TFT_WHITE);
  }
  M5.Lcd.textbgcolor = color;
  M5.Lcd.drawNumber(val, x - (cwidth / 2), y - (cheight / 2));

  M5.Lcd.textbgcolor = TFT_BLACK;
  M5.Lcd.setTextSize(M5.Lcd.textsize / 2);
  //M5.Lcd.setTextDatum(1);
  M5.Lcd.drawString(message, x - (M5.Lcd.textWidth(String(message)) / 2), y + s + 4);

  M5.Lcd.setTextSize(DEFAULT_TEXT_SIZE);
}

void showSensor(int sensor, int value) {
  switch (sensor)
  {
  case 0: createCritAir(TFT_HEIGHT / 2, (TFT_WIDTH / 2 - 40), 80, ppm2Critair(value));
    break;
  case 1: displayText("Appui bouton 1", 0, 0);
    break;
  case 2: displayText("Appui bouton 2", 0, 0);
    break;
  default:
    break;
  }
}

#endif
