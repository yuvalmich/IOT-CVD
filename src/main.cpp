#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "token";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ssid";
char pass[] = "pass";

BlynkTimer timer;
int uptimeCounter;
String someStaticData = "SomeStaticData";

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

void increment()
{
    uptimeCounter++;

    //storing int and string in V0 pin on server
    Blynk.virtualWrite(V0, uptimeCounter, someStaticData);

    //updating value display with uptimeCounter
    Blynk.virtualWrite(V1, uptimeCounter);
}

void setup()
{
    // Debug console
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);
    // You can also specify server:
    //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
    //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

    timer.setInterval(1000L, increment);
}

void loop()
{
    Blynk.run();
    timer.run();
}
