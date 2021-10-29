#ifndef TEXT_H
#define TEXT_H

#include <Arduino.h>

void initDisplay();
void displayText(const char *, int, int, unsigned, uint16_t, uint8_t);
void displayText(const char *, int, int);
void clearDisplay();
void clearDisplay(int, int, int, int);
void displayProgressBar(int, int, int, int, int);
void createCritAir(unsigned, unsigned, unsigned, unsigned);
void showSensor(int, int);
uint8_t checkBtn();

#endif