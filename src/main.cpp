#define BLYNK_PRINT Serial

#include "imports.h"

#include "vibration.h"
#include "gps.h"
#include "bluetooth.h"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const unsigned long NOTIFICATION_INTERVAL = 1000 * 10;
unsigned long lastTimeMoved = 0;

// server base url
String baseUrl = "http://192.168.0.111:3000/park/";
char auth[] = "";

// Blynk auth key
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";

// Wifi credentials

BlynkTimer timer;
VibrationSensor *vibrationSensor = NULL;
GpsSensor *gpsSensor = NULL;
BluetoothSensor *bluetoothSensor = NULL;

bool savePark() {
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Couldn't save parking becuase WiFi disconnected");
        return true;
    }

    WiFiClient client;
    HTTPClient http;

    double* lonLat = gpsSensor->getLongLat();
    String url = baseUrl + "parking?lon=" + lonLat[0] + "&lat=" + lonLat[1];

    // Your Domain name with URL path or IP address with path
    http.begin(client, url.c_str());

    // Send HTTP GET request
    int httpResponseCode = http.GET();

    if (httpResponseCode == 200)
    {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        return payload.equals("true");
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        Blynk.notify("We are so sorry! We couldn't verify if your parking is safe");
        return true;
    }

    // Free resources
    http.end();

}

void onVandalismDetected()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Couldn't report an accident becuase WiFi disconnected");
        return;
    }

    if (!bluetoothSensor->isParking())
    {
        Serial.println("Accident accoured but not in parking mode");
        return;
    }

    Blynk.notify("Ohh shit! someone hit your car");

    WiFiClient client;
    HTTPClient http;

    double* lonLat = gpsSensor->getLongLat();
    String url = baseUrl + "accident?lon=" + lonLat[0] + "&lat=" + lonLat[1];

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

BLYNK_WRITE(V0)
{
    bluetoothSensor->setConnection(param.asInt());

    Serial.println(bluetoothSensor->isParking() ? "bluetooth disconnected": "bluetooth connected");

    if (bluetoothSensor->isParking()) {
        bool isSafe = savePark();
        if(!isSafe) {
            Blynk.notify("WARNING! Unsafe parking area");
        } else {
            Blynk.notify("Hooray! You parked in a great parking spot!");
        }
    }
}

void applicationLoop()
{
    unsigned long timeSinceLastMovement = millis() - lastTimeMoved;

    if (vibrationSensor->isMoving())
    {
        if (timeSinceLastMovement > NOTIFICATION_INTERVAL) {
            onVandalismDetected();
            lastTimeMoved = millis();
        } else {
            Serial.println("Accident accoured but notifaction interval was not passes");
        }
    }
}

void setup()
{
    Serial.begin(9600);

    vibrationSensor = new VibrationSensor(A0);
    gpsSensor = new GpsSensor(5, 6);
    bluetoothSensor = new BluetoothSensor(2, 3);

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
