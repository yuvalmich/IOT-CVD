#include "imports.h"
#include "led.h"
#include "vibration.h"

LedActuator* ledActuator = NULL;
VibrationSensor* vibrationSensor = NULL;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  Serial.println("Car Violation Detection starting up");
  
  ledActuator = new LedActuator(LED_BUILTIN);
  vibrationSensor = new VibrationSensor(A0);

  delay(10);
}

// the loop function runs over and over again forever
void loop() {
  if(vibrationSensor->isMoving()) {
    ledActuator->turnOn();
  } else {
    ledActuator->turnOff();
  }

  delay(100);
}
