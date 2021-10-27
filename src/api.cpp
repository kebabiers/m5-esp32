#ifndef API_CPP
#define API_CPP

#include "api.h"
#include <HTTPClient.h>

int send2API(char *json, const char *apiURL, const char *apiKey) {
  HTTPClient http;

  // Your Domain name with URL path or IP address with path
  http.begin(apiURL);

  // Specify content-type header
  //http.addHeader("Content-Type", "application/json");
  http.addHeader("x-api-key", "IYr3nL2H9Wah6HwVYTunAMvm8ZNMzsA9zBvPDR3f");
  // Send HTTP POST request
  return http.POST(json);
}

void createJSON(int val, char *output, const char *deviceID, const char *name) {
  char json[1000];
  sprintf(json, "{\n\
        \"deviceId\": \"%s\",\n\
        \"data\":\n [\n\
                {\n\
                    \"id\": \"%s\",\n\
                    \"type\": \"number\",\n\
                    \"val\": %i\n\
                }\n\
            ]\n\
    }", deviceID, name, val);

// #ifdef DEBUG
//   Serial.println(json);
// #endif

  memcpy(output, json, sizeof(json));

}

#endif