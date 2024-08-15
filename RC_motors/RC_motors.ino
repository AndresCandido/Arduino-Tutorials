/************************
Control the DC motor using
the L293D chip and a Joystick with an elegoo UNO board
************************/

#include "pitches.h"

// Arduino pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = A0; // analog pin connected to X output
const int Y_pin = A1; // analog pin connected to Y output

#define ENABLE 5  // Motor on / off
#define DIRA 3    // Motor direction 1
#define DIRB 4    // Motor direction 2
#define BUZZER_PIN 13 // Horn pin

void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);

  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600);
}


void loop() {
  int xValue = analogRead(X_pin); // Read the X axis value
  int yValue = analogRead(Y_pin); // Read the Y axis value

  int motorSpeed = 0; // Initialize motor speed

  if (yValue > 510) { // Joystick pushed up
    motorSpeed = map(yValue, 512, 1023, 0, 255); // Map upper half range to motor speed
    digitalWrite(DIRA, HIGH);
    digitalWrite(DIRB, LOW);
  } else if (yValue < 518) { // Joystick pushed down
    motorSpeed = map(yValue, 511, 0, 0, 255); // Map lower half range to motor speed
    digitalWrite(DIRA, LOW);
    digitalWrite(DIRB, HIGH);
  } else { // Joystick centered
    motorSpeed = 0;
    digitalWrite(DIRA, LOW);
    digitalWrite(DIRB, LOW);
  }

  analogWrite(ENABLE, motorSpeed); // Set motor speed

  if (digitalRead(SW_pin)==1) { // Buzzer honk when switch is pressed
    noTone(BUZZER_PIN);
  } else {
    tone(BUZZER_PIN, NOTE_E4);
  }

  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(" Y: ");
  Serial.print(yValue);
  Serial.print(" Switch: ");
  Serial.println(digitalRead(SW_pin));

  delay(100); // Small delay for stability
}
