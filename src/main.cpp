#define BLYNK_PRINT Serial

#include "imports.h"

#include "vibration.h"
#include "gps.h"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

String host = "";

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";

BlynkTimer timer;
VibrationSensor* vibrationSensor = NULL;
GpsSensor* gpsSensor = NULL;

bool isBluetoothConnected = false;
bool wasMoved = false;

BLYNK_WRITE(V0)
{
    isBluetoothConnected = param.asInt();

    Serial.println(isBluetoothConnected ? "bluetooth connected" : "bluetooth disconnected");
}

void onVandalismDetected()
{
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Couldn't report an accident becuase WiFi Disconnected");
        return;
    }

    if (!isBluetoothConnected) {
        Serial.println("Accident accoured but not in parking mode");
        return;
    }

    WiFiClient client;
    HTTPClient http;

    String url = host + "?lon=32&lat=35";

    // Your Domain name with URL path or IP address with path
    http.begin(client, url.c_str());

    // Send HTTP GET request
    int httpResponseCode = http.GET();

    if (httpResponseCode == 200)
    {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }

    // Free resources
    http.end();

}


void applicationLoop() {
  if(vibrationSensor->isMoving() && !wasMoved) {
      wasMoved = true;
      onVandalismDetected();
  } else if (!vibrationSensor->isMoving()) {
      wasMoved = false;
  }
}

void setup()
{
    Serial.begin(115200);

    vibrationSensor = new VibrationSensor(A0);
    gpsSensor = new GpsSensor(2, 3);

    // Debug console
    Blynk.begin(auth, ssid, pass);

    WiFi.begin(ssid, pass);
    Serial.println("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());

    timer.setInterval(100, applicationLoop);
}


void loop()
{
    Blynk.run();
    timer.run();
}
