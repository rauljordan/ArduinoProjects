/*
Adafruit Arduino - Lesson 16. Stepper
*/

#include <Stepper.h>

// pin 12 is pin 2 in actual circuit
int in1Pin = 12;
// pin 11 is pin 10 in actual circuit
int in2Pin = 11;
// pin 10 is pin 4 in actual circuit
int in3Pin = 10;
// pin 9 is pin 8 in actual circuit
int in4Pin = 9;

Stepper motor(512, in1Pin, in2Pin, in3Pin, in4Pin);  

void setup()
{
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  // this line is for Leonardo's, it delays the serial interface
  // until the terminal window is opened
  while (!Serial);
  
  Serial.begin(9600);
  motor.setSpeed(20);
}

void loop()
{
  if (Serial.available())
  {
    int steps = Serial.parseInt();
    motor.step(steps);
  }
}
