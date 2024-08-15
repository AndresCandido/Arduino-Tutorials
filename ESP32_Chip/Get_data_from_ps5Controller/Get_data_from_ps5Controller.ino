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

  } else {
    Serial.println("Waiting for controller to connect.");
    Serial.println();
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(1000);                      // wait for a second
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    delay(1000);                      // wait for a second
  }

  while (ps5.isConnected() == true) {
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)

    if (ps5.Right()) Serial.println("Right Button");
    if (ps5.Down()) Serial.println("Down Button");
    if (ps5.Up()) Serial.println("Up Button");
    if (ps5.Left()) Serial.println("Left Button");

    if (ps5.Square()) Serial.println("Square Button");
    if (ps5.Cross()) Serial.println("Cross Button");
    if (ps5.Circle()) Serial.println("Circle Button");
    if (ps5.Triangle()) Serial.println("Triangle Button");

    if (ps5.UpRight()) Serial.println("Up Right");
    if (ps5.DownRight()) Serial.println("Down Right");
    if (ps5.UpLeft()) Serial.println("Up Left");
    if (ps5.DownLeft()) Serial.println("Down Left");

    if (ps5.L1()) Serial.println("L1 Button");
    if (ps5.R1()) Serial.println("R1 Button");

    if (ps5.Share()) Serial.println("Share Button");
    if (ps5.Options()) Serial.println("Options Button");
    if (ps5.L3()) Serial.println("L3 Button");
    if (ps5.R3()) Serial.println("R3 Button");

    if (ps5.PSButton()) Serial.println("PS Button");
    if (ps5.Touchpad()) Serial.println("Touch Pad Button");

    if (ps5.L2()) {
      Serial.printf("L2 button at %d\n", ps5.L2Value());
    }
    if (ps5.R2()) {
      Serial.printf("R2 button at %d\n", ps5.R2Value());
    }

    if (ps5.LStickX()) {
      Serial.printf("Left Stick x at %d\n", ps5.LStickX());
    }
    if (ps5.LStickY()) {
      Serial.printf("Left Stick y at %d\n", ps5.LStickY());
    }
    if (ps5.RStickX()) {
      Serial.printf("Right Stick x at %d\n", ps5.RStickX());
    }
    if (ps5.RStickY()) {
      Serial.printf("Right Stick y at %d\n", ps5.RStickY());
    }

    Serial.println();
    // This delay is to make the output more human readable
    // Remove it when you're not trying to see the output
    delay(300);
  }

}