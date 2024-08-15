#include <ps5Controller.h>
#include <Arduino.h>

#define LED_BUILTIN 2

void setup() {
  Serial.begin(115200);
  delay(1000);

  ps5.begin("48:18:8D:0C:8C:AD"); //MAC address of my ps5 controller
  Serial.println("Ready.");

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (ps5.isConnected()) {
    Serial.println("Connected!");

    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(3000);

  } else {
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(1000);                      // wait for a second
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    delay(1000);                      // wait for a second
  }
}