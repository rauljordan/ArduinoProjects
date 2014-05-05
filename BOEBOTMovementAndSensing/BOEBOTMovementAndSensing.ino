/*
 * The Nose Knows Code
 */
 
#include <Servo.h>                           // Include servo library
#include <Stepper.h>

// sets up the stepper digital pins
int in1Pin = 2;
int in2Pin = 10;
int in3Pin = 4;
int in4Pin = 8;
 
Servo servoLeft;                             // Declare left and right servos
Servo servoRight;

Stepper motor(512, in1Pin, in2Pin, in3Pin, in4Pin);  

const int pingPin = 3;
 
void setup()                                 // Built-in initialization block

{   
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);  
  servoLeft.attach(11);                      // Attach left signal to pin 11
  servoRight.attach(12);    // Attach right signal to pin 12
  
  while (!Serial);

   Serial.begin(9600);
   motor.setSpeed(20);
}  
 
void loop()                                  // Main loop auto-repeats
{

  int irLeft   =  digitalRead(5);       // Set value of LEFT sensor
  int irCenter =  digitalRead(6);       // Set value of CENTER sensor
  int irRight  =  digitalRead(7);       // Set value of RIGHT sensor
  
  Serial.println(irCenter);     //If enabled will display feedback of pin i in serial monitor
  //delay(250);
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  
  long duration, inches, cm;
  
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  /*
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  */
  
  
 if (irLeft == 1 || irCenter == 1 || irRight == 1)
 {
     motor.step(-100);
 }
 
 if (cm < 40 && cm > 5)
  {
     
    maneuver(100,100,60);
  }
 
 else if (cm > 40)
 {
   maneuver(0,0,20);
 }
 
 else if (cm < 5) {
     motor.step(100);
      maneuver(100, 100, -1); 
 }
    
  else {
    maneuver(0,0,20);
  }
 

}


void maneuver(int speedLeft, int speedRight, int msTime) // Defines maneuver function
{
  // speedLeft, speedRight ranges: Backward  Linear  Stop  Linear   Forward
  //                               -200      -100......0......100       200
  servoLeft.writeMicroseconds(1500 + speedLeft);   // Set Left servo speed
  servoRight.writeMicroseconds(1500 - speedRight); // Set right servo speed
  if(msTime==-1)                                   // if msTime = -1
  {                                  
    servoLeft.detach();                            // Stop servo signals
    servoRight.detach();   
  }
  delay(msTime);                                   // Delay for msTime
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
