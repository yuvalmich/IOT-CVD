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
int uptimeCounter;
String someStaticData = "SomeStaticData";
VibrationSensor* vibrationSensor = NULL;
GpsSensor* gpsSensor = NULL;
byte BLUETOOTH_STATE_PIN = 6;

// This function will run every time Blynk connection is established
BLYNK_CONNECTED()
{
    //get data stored in virtual pin V0 from server
    Blynk.syncVirtual(V0);
}

// restoring counter from server
BLYNK_WRITE(V0)
{
    //restoring int value
    uptimeCounter = param[0].asInt();
    //restoring string value
    someStaticData = param[1].asString();
}

void onVandalismDetected()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        WiFiClient client;
        HTTPClient http;

        String url = host + "?lon=32&lat=35";

        // Your Domain name with URL path or IP address with path
        http.begin(client, url.c_str());

        // Send HTTP GET request
        int httpResponseCode = http.GET();

        if (httpResponseCode > 0)
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
    else
    {
        Serial.println("WiFi Disconnected");
    }
}

bool wasMoved = false;

bool isBluetoothConnected() {
  return digitalRead(BLUETOOTH_STATE_PIN) == HIGH;
}

void applicationLoop() {
  if(isBluetoothConnected()) {
    Serial.println("BT is connected");
  } else {
    Serial.println("BT is not connected");
  }
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

    pinMode(BLUETOOTH_STATE_PIN, INPUT);
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
