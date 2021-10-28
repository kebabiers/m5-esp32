#include <Arduino.h>
#include <M5Stack.h>
// #include <WiFi.h>
#include <HTTPClient.h>
#include <time.h>
#include <ArduinoJson.h>
#include "Adafruit_SGP30.h"

HTTPClient http;

//CO2
Adafruit_SGP30 sgp;
long last_millis = 0;

const char *ssid = "Huawei P30 Pro";
const char *pass = "kindermaxi";

// void wifiConnect()
// {
//     WiFi.begin(ssid, pass);
// }

unsigned long getTime()
{
    time_t now;
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        //Serial.println("Failed to obtain time");
        return (0);
    }
    time(&now);
    return now;
}

void api()
{
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

void setup()
{
    // Serial.begin(115200);
    // M5.Lcd.setTextColor(WHITE);
    // M5.Lcd.setTextSize(2);

    M5.begin(true, false, true, true);

    // delay(5);

    // M5.Lcd.println("Connexion en cours ...");

    // wifiConnect();
    // while (WiFi.status() != 3)
    // {
    //     yield();
    // }
    // M5.Lcd.clear();
    // M5.Lcd.setCursor(0, 0);
    // M5.Lcd.println("Connexion réussie !");

    // configTime(3600, 3600, "pool.ntp.org");
    // struct tm timeinfo;
    // getLocalTime(&timeinfo);
    // M5.Lcd.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

    // M5.Lcd.print("L'ip est: ");
    // M5.Lcd.println(WiFi.localIP());
    // delay(5000);

    // M5.Lcd.clear();

    //CO2
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(80, 0);
    M5.Lcd.println("TVOC TEST");
    if (!sgp.begin())
    { //Init the sensor. 初始化传感器
        M5.Lcd.println("Sensor not found");
        while (1)
            ;
    }
    M5.Lcd.setCursor(0, 80);
    M5.Lcd.println("\nInitialization...");

    // api();
    // M5.Lcd.print("API OK");
    delay(3000);
}

void loop()
{
    static int i = 15;
    while (i > 0)
    {
        if (millis() - last_millis > 1000)
        {
            last_millis = millis();
            i--;
            M5.Lcd.fillRect(20, 120, 60, 30, BLACK);
            M5.Lcd.drawNumber(i, 20, 120, 2);
        }
    }
    M5.Lcd.fillRect(0, 80, 90, 100, BLACK);

    if (!sgp.IAQmeasure())
    { //Commands the sensor to take a single eCO2/VOC measurement.  命令传感器进行一次eCO2/VOC测量
        Serial.println("Measurement failed");
        return;
    }
    M5.Lcd.fillRect(100, 40, 220, 90, TFT_BLACK);
    M5.Lcd.setCursor(0, 50);
    M5.Lcd.printf("TVOC:%d ppb\n", sgp.TVOC);
    M5.Lcd.printf("eCO2:%d ppm\n", sgp.eCO2);
    delay(500);
}