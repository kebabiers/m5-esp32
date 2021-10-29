#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <timer.h>
#include <M5Stack.h>
#include "sendJson.h"

const String serverName = "https://api.bagtower.bag-era.fr/prod/logs";

void sendJson(const char *id, int value) {
    HTTPClient http;

    // démarre le http en lui donnant l'adresse du serveur (adresse API)
    http.begin(serverName);

    // définis le header, besoin du type et de la clé api
    // http.addHeader("x-api-key", "IYr3nL2H9Wah6HwVYTunAMvm8ZNMzsA9zBvPDR3f__PP");
    http.addHeader("x-api-key", "WpLpFtjXIW7gqIjdNq7508JgnSpWySZV8bkwGnSm");
    http.addHeader("Content-Type", "application/json");

    // création du json
    StaticJsonDocument<200> doc;
    // doc["deviceId"] = "6f34c9b0-1791-1:24ca0730-3656-11ec-8";
    doc["deviceId"] = "6f34c9b0-1791-1:482ed870-3725-11ec-b";
    doc["unixTimestamp"] = getTime();

    JsonArray data = doc.createNestedArray("data");
    StaticJsonDocument<200> sousDoc;
    sousDoc["id"] = id;
    sousDoc["type"] = "number";
    sousDoc["val"] = value;

    data.add(sousDoc);
    
    // on s'assure que requestbody soit typé string et on serialize
    String requestBody;
    serializeJson(doc, requestBody);

    Serial.println(requestBody);
    // Send HTTP POST request
    int httpResponseCode = http.POST(requestBody);
    // M5.Lcd.print(String(httpResponseCode) + " ");
    // String httpResp = http.getString();
    Serial.printf("HTTP status code: %d\n", httpResponseCode);
    // Serial.printf("http string: %s", httpResp.c_str());
}
