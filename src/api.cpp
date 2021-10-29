#ifndef API_CPP
#define API_CPP

#include "api.h"
#include <HTTPClient.h>
#include <config.h>

int send2API(char *json, const char *apiURL, const char *apiKey) {
  HTTPClient http;

  // Your Domain name with URL path or IP address with path
  http.begin(apiURL);

  // Specify content-type header
  http.addHeader("Content-Type", "application/json");
  http.addHeader("x-api-key", apiKey);
  // Send HTTP POST request
  return http.POST(json);
}

void createJSON(int val, char *output, const char *deviceID, const char *name, unsigned long timestamp) {
  char json[1000];
  sprintf(json, "{\n\
        \"deviceId\": \"%s\",\n\
        \"unixTimestamp\": %li,\n\
        \"data\":\n [\n\
                {\n\
                    \"id\": \"%s\",\n\
                    \"type\": \"number\",\n\
                    \"val\": %i\n\
                }\n\
            ]\n\
    }", deviceID, timestamp, name, val);

  memcpy(output, json, sizeof(json));

}

int sendValue(int value, const char *deviceID, const char *name) {
    time_t timestamp;
    time(&timestamp);

    char json[1000];
    createJSON(value, json, DEVICE_ID, DEVICE_NAME, timestamp);
    // return send2API(json, API_URL, API_KEY);
    return 0;
}

#endif