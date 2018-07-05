#include <AccelStepper.h>

/*
 * A camera timelapse rotator 
 * using arduino and 28BYJ-48 stepper motor.
 * 
 * ULN2003A driver setup
 *   + IN1 to D2 (digital pin 2)
 *   + IN2 to D3
 *   + IN3 to D4
 *   + IN4 to D5
 */

#define SPEED_PIN A0
#define STEP_NUM 64
#define MULTIPLIER 5 // change this value to adjust min/max speed

AccelStepper stepper = AccelStepper(AccelStepper::HALF4WIRE, 2, 4, 3, 5);
// notice that two pins(3, 4) are swapped.

float readSpeed(void);

void setup() {
  stepper.setMaxSpeed(1000);
}

void loop() {
  float speed = readSpeed();
  Serial.println(speed);
  float stepperSpeed = speed * STEP_NUM * MULTIPLIER * 2; // x2 for half stepping
  stepper.setSpeed(stepperSpeed);
  stepper.runSpeed();
}

/*
 * Read value from potentiometer
 * and return normalized value
 */
float readSpeed() {
  int value = analogRead(SPEED_PIN);
  return (double)value / 1024;
}
