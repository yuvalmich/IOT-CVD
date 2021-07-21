// // #include "imports.h"
// // #include "led.h"
// // #include "vibration.h"
// // #include "wifi.h"


// #include <ESP8266WiFi.h>
// #include <BlynkSimpleEsp8266.h>

// #define BLYNK_PRINT Serial

// BlynkTimer timer;

// // LedActuator *ledActuator = NULL;
// // VibrationSensor *vibrationSensor = NULL;
// // WifiModule *wifiModule = NULL;

// char auth[] = "0xYy2V_c-tvsxpwJUGZHwdR8gGgByIGd";
// char ssid[] = "Honeypot U";
// char pass[] = "";

// int isMoving;

// BLYNK_CONNECTED() {
//   // get data stored in virtual pin V0 from server
//   Blynk.syncVirtual(V0);
// }

// // restoring counter from server
// BLYNK_WRITE(V0)
// {
//     //restoring int value
//     isMoving = param[0].asInt();
// }


// void sendIsMoving() {
//   isMoving = 1;
//   Serial.println("sending data to blynk");

//   //storing int and string in V0 pin on server
//   Blynk.virtualWrite(V0, isMoving);
// }

// // the setup function runs once when you press reset or power the board
// void setup()
// {
//     Serial.begin(9600);
//     // Serial.println("Car Violation Detection starting up");

//     // ledActuator = new LedActuator(LED_BUILTIN);
//     // vibrationSensor = new VibrationSensor(A0);
//     // wifiModule = new WifiModule(auth, ssid, pass);

//     // wifiModule->connect();
//     Blynk.begin(auth, ssid, pass);

//     timer.setInterval(1000L, sendIsMoving);
//     // delay(10);
// }

// // the loop function runs over and over again forever
// void loop()
// {
//     Blynk.run();
//     // timer.run();

//     // if (vibrationSensor->isMoving())
//     // {
//     //     ledActuator->turnOn();
//     // }
//     // else
//     // {
//     //     ledActuator->turnOff();
//     // }

//     // delay(100);
// }
