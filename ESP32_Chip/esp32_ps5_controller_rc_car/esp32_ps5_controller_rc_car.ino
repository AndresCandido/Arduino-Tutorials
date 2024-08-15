#include <ps5Controller.h>
#include <ESP32Servo.h>

#include "pitches.h"

#define LED_BUILTIN 2

#define motor1A 13
#define motor2A 14

#define Horn 25

// PWM settings
const int freq = 500; // PWM frequency: 500 Hz
const int resolution = 8; // PWM resolution: 8 bits
const int channelA = 0; // PWM channel for motor1A: 0
const int channelB = 1; // PWM channel for motor2A: 1
const int channeHorn = 2; // PWM channel for horn: 2

// Define the servo and the pin it is connected to
Servo myServo;
const int servoPin = 32;
// Define the minimum and maximum pulse widths for the servo
const int minPulseWidth = 500; // 0.5 ms
const int maxPulseWidth = 2500; // 2.5 ms

void setup() {
  Serial.begin(115200);
  delay(1000);

  ps5.begin("48:18:8D:0C:8C:AD"); //MAC address of my ps5 controller
  Serial.println("Ready.");

  pinMode(LED_BUILTIN, OUTPUT);

  //Attach PWM channels to GPIO pins
  ledcAttachChannel(motor1A, freq, resolution, channelA);
  ledcAttachChannel(motor2A,freq, resolution, channelB);
  ledcAttachChannel(Horn,freq, resolution, channeHorn);

  // Attach the servo to the specified pin and set its pulse width range
  myServo.attach(servoPin, minPulseWidth, maxPulseWidth);
  // Set the PWM frequency for the servo
  myServo.setPeriodHertz(50); // Standard 50Hz servo
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

    int LStick_yValue = ps5.LStickY(); // Read the Y axis value for motor speed and direction
    int motorSpeed = 0; // Initialize motor speed (dutyCycle)

    if (LStick_yValue > 7) { // Joystick pushed up
      motorSpeed = map(LStick_yValue, 0, 127, 0, 255); // Map upper half range to motor speed
      ledcWrite(motor1A, 0);
      ledcWrite(motor2A, motorSpeed);
    } else if (LStick_yValue < -7) { // Joystick pushed down
      motorSpeed = map(LStick_yValue, -1, -128, 0, 255); // Map lower half range to motor speed
      ledcWrite(motor1A, motorSpeed);
      ledcWrite(motor2A, 0);
    } else { // Joystick centered
      motorSpeed = 0;
      ledcWrite(motor1A, 0);
      ledcWrite(motor2A, 0);
    }

    if (ps5.L3()) { // Honk buzzer when L3 switch is pressed
      ledcWrite(Horn, NOTE_E4);
    } else {
      ledcWrite(Horn, REST);
    }

    int RStick_xValue = ps5.RStickX(); // Read the X axis value of R stick for wheel steering
    int pulseWidth = map(RStick_xValue, -128, 127, minPulseWidth, maxPulseWidth);
    myServo.writeMicroseconds(pulseWidth);


    Serial.printf("Left Stick y at %d\n", LStick_yValue);
    Serial.printf("Right Stick x at %d\n", RStick_xValue);


    Serial.println();
    // This delay is to make the output more human readable
    // Remove it when you're not trying to see the output
    delay(100);
  }

}