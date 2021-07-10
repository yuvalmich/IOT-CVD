#include <Blynk.h>
#include <ESP8266WiFi.h>

const char* ssid     = "Honeypot U";
const char* password = "";

// const char* host = "data.sparkfun.com";
// const char* streamId   = "....................";
// const char* privateKey = "....................";

void setup() {
  Serial.begin(9600);
  delay(100);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  delay(5000);
}