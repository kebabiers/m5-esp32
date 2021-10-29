#ifndef SENSOR_CPP
#define SENSOR_CPP

#include "sensor.h"
#include "Adafruit_SGP30.h"

Adafruit_SGP30 sgp;

int initSensor(int type) {
    switch (type)
    {
    case 0: initCO2(10);
        break;

    case 1:
        break;
    
    default:
        break;
    }
}

int getSensorValue(int type) {

    int r;
    switch (type)
    {
    case 0: r = getC02value();
        break;
    
    default:
        break;
    }

    return r;
}

int initCO2(unsigned maxWait) {
    
    maxWait += (int) millis() / 1000;
    
    while(millis() / 1000 > maxWait && !sgp.begin())
    {
        yield();
    }
    return sgp.begin();
}

int waitSensor(unsigned maxWait) {
    maxWait += (int) millis() / 1000;
    
    while(millis() / 1000 > maxWait)
    {
        yield();
    }

    return 0;
}

int getC02value() {
    if(!sgp.IAQmeasure()) return -1;

    return sgp.eCO2;
}

unsigned ppm2Critair(unsigned ppm) {

    if(ppm > 1000) return 5;
    if(ppm > 800) return 4;
    if(ppm > 600) return 3;
    if(ppm > 500) return 2;
    if(ppm > 450) return 1;

    return 0;
}

#endif