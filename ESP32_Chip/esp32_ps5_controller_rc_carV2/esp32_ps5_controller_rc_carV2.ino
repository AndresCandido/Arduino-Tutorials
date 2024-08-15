#include <ps5Controller.h>
#include "pitches.h"

#define LED_BUILTIN 2

#define motor1A 13 // Pins for back and forth motor
#define motor1B 14

#define motor2A 27 // Pins for steering motor
#define motor2B 26

#define Horn 25 // Horn, beep beep

// PWM settings
const int freq = 500; // PWM frequency: 500 Hz
const int resolution = 8; // PWM resolution: 8 bits
const int channelA = 0; // PWM channel for motor1 Direction A: 0
const int channelB = 1; // PWM channel for motor1 Direction B: 1
const int channeHorn = 2; // PWM channel for horn: 2
const int channelC = 3; // PWM channel for motor2 Direction A: 3
const int channelD = 4; // PWM channel for motor2 Direction B: 4


void setup() {
  Serial.begin(115200);
  delay(1000);

  ps5.begin("48:18:8D:0C:8C:AD"); //MAC address of my ps5 controller
  Serial.println("Ready.");

  pinMode(LED_BUILTIN, OUTPUT);

  //Attach PWM channels to GPIO pins
  ledcAttachChannel(motor1A, freq, resolution, channelA);
  ledcAttachChannel(motor1B,freq, resolution, channelB);
  ledcAttachChannel(Horn,freq, resolution, channeHorn);
  ledcAttachChannel(motor2A, freq, resolution, channelC);
  ledcAttachChannel(motor2B,freq, resolution, channelD);
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
    int motor1Speed = 0; // Initialize motor speed (dutyCycle)

    if (LStick_yValue > 7) { // Joystick pushed up
      motor1Speed = map(LStick_yValue, 0, 127, 0, 255); // Map upper half range to motor speed
      ledcWrite(motor1A, 0);
      ledcWrite(motor1B, motor1Speed);
    } else if (LStick_yValue < -7) { // Joystick pushed down
      motor1Speed = map(LStick_yValue, -1, -128, 0, 255); // Map lower half range to motor speed
      ledcWrite(motor1A, motor1Speed);
      ledcWrite(motor1B, 0);
    } else { // Joystick centered
      motor1Speed = 0;
      ledcWrite(motor1A, 0);
      ledcWrite(motor1B, 0);
    }

    if (ps5.L3()) { // Honk buzzer when L3 switch is pressed
      ledcWrite(Horn, NOTE_E4);
    } else {
      ledcWrite(Horn, REST);
    }

    int RStick_xValue = ps5.RStickX(); // Read the X axis value of R stick for wheel steering
    int motor2Speed = 0; // Initialize motor speed (dutyCycle)
    if (RStick_xValue > 7) { // Joystick pushed rigth
      motor2Speed = map(RStick_xValue, 0, 127, 0, 255); // Map upper half range to motor speed
      ledcWrite(motor2A, 0);
      ledcWrite(motor2B, motor2Speed);
    } else if (RStick_xValue < -7) { // Joystick pushed left
      motor2Speed = map(RStick_xValue, -1, -128, 0, 255); // Map lower half range to motor speed
      ledcWrite(motor2A, motor2Speed);
      ledcWrite(motor2B, 0);
    } else { // Joystick centered
      motor2Speed = 0;
      ledcWrite(motor2A, 0);
      ledcWrite(motor2B, 0);
    }


    Serial.printf("Left Stick y at %d\n", LStick_yValue);
    Serial.printf("Right Stick x at %d\n", RStick_xValue);


    Serial.println();
    // This delay is to make the output more human readable
    // Remove it when you're not trying to see the output
    delay(100);
  }

}