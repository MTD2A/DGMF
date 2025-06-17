// overskæring ver 3 DGMF

#include <Servo.h>

int irSensorPin = 2; // IR sensor input pin
int blinkLedPin = 7; // Blink LED pin
int soundLedPin = 9; // Sound LED pin
int servoPin = 4; // Servo control pin

Servo myServo;

int irSensorState = 0; // Variable to store IR sensor state

void setup() {
  pinMode(irSensorPin, INPUT); // Set IR sensor pin as input
  pinMode(blinkLedPin, OUTPUT); // Set Blink LED pin as output
  pinMode(soundLedPin, OUTPUT); // Set Sound LED pin as output
  myServo.attach(servoPin); // Attach servo to servo pin

  myServo.write(0); // Initialize servo position to up
  Serial.begin(9600); // Start serial communication for debugging
}

void loop() {
  irSensorState = digitalRead(irSensorPin); // Read IR sensor state
  Serial.println(irSensorState); // Print IR sensor state to Serial Monitor for debugging

  if (irSensorState == LOW) { // If IR sensor detects an object
    digitalWrite(blinkLedPin, HIGH); // Turn on Blink LED
    digitalWrite(soundLedPin, HIGH); // Turn on Sound LED
    delay(10000); // Wait for 10 seconds

    myServo.write(90); // Move servo down
    delay(1000); // Give servo time to move
    digitalWrite(soundLedPin, LOW); // Turn off Sound LED

    while (digitalRead(irSensorPin) == HIGH) { // Wait for next LOW signal
      // Do nothing and wait
    }

    myServo.write(0); // Move servo back up
    digitalWrite(blinkLedPin, LOW); // Turn off Blink LED
  }
}
