#include <time.h>
#include <HTTPClient.h>
#include "timer.h"

//récupère le timestamp pour le m5
void setTime(){
    configTime(3600,3600, "pool.ntp.org");
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

//récupère le timestamp a partir du m5 pour nous
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    //Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}