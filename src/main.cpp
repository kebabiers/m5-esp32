#include <Arduino.h>
#include <M5Stack.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <time.h>
#include <ArduinoJson.h>

WiFiClient client;
HTTPClient http;

const char *ssid = "iPhone";
const char *pass = "sech38dzk";

void wifiConnect() {
    WiFi.begin(ssid, pass);
}

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

void api(){
    // Your Domain name with URL path or IP address with path
    http.begin("https://api.bagtower.bag-era.fr/prod/logs");

    // Specify content-type header
    http.addHeader("Content-Type", "application/json");
    http.addHeader("x-api-key", "7ce8BjFztCaFt5q9jdPYLaxtyagBh1xK8iaplrTF");
    // Data to send with HTTP POST
    StaticJsonDocument<200> doc;
    doc["deviceId"] = "6f34c9b0-1791-1:3089fe40-3656-11ec-8";
    doc["unixTimestamp"] = getTime();

    JsonArray data = doc.createNestedArray("data");
    StaticJsonDocument<200> sousDoc;
    sousDoc["id"] = "patate";
    sousDoc["type"] = "percent";
    sousDoc["val"] = "string";

    data.add(sousDoc);

    String requestBody;
    serializeJson(doc, requestBody);

    // Send HTTP POST request
    int httpResponseCode = http.POST(requestBody);
    Serial.println(requestBody);
    Serial.println(httpResponseCode);

}

void setup(){
    Serial.begin(115200);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    
    M5.begin();

    delay(5);

    M5.Lcd.println("Connexion en cours, veuillez patienter.");

    wifiConnect();
    while (WiFi.status() != 3) { 
        yield(); 
    }
    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("Connexion réussi, vous avez accès à Internet.");

    configTime(3600, 3600, "pool.ntp.org");
    struct tm timeinfo;
    getLocalTime(&timeinfo);
    M5.Lcd.println(&timeinfo,"%A, %B %d %Y %H:%M:%S");

    
    M5.Lcd.print("L'ip est: ");
    M5.Lcd.println(WiFi.localIP());
    // delay(25000);

    M5.Lcd.clear();
    
    api();
}

    
void loop(){
    delay(500);
}