#ifndef SENSOR_H
#define SENSOR_H

#include "Adafruit_SGP30.h"

extern Adafruit_SGP30 sgp;

int initSensor(int);
int initCO2(unsigned);
int waitSensor(unsigned);
int getC02value();
int getSensorValue(int);

#endif