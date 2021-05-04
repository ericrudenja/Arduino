/* following code is meant to be used with a four-servo based robotic arm with a single claw.
 * the following project was made using MeArm library.
 * using inverse kinematics with joysticks
 * uses two analogue joystcks (two pots each)
 * first stick moves gripper forwards, backwards, base left and right
 * second stick moves gripper up, down, and closes and opens.
 * 
 * joysticks are sintrol 5-pins. Switch pin can be disconnected if not in use, leaving us with four used pins.
 * 
 * 
 * 
 * Pins:
 * Arduino      Joystick1 Joystick2    Base   Shoulder  Elbow    Gripper
 *    GND       GND       GND          Brown     Brown   Brown     Brown
 *     5V                              Red       Red     Red       Red
 *     3.3V     VCC       VCC
 *     A0       X
 *     A1       Y
 *     A2                 X
 *     A3                 Y
 *     11                             Yellow
 *     10                                        Yellow
 *      9                                                 Yellow
 *      6                                                           Yellow
 */
#include "meArm.h"
#include <Servo.h>

// create a separate servo object to control the gripper
Servo gripperServo;  

//servo setup
int basePin = 11;
int shoulderPin = 10;
int elbowPin = 9;
//gripperPin pin is only declared because the meArm library requires 4 pins to be declared to
//initialize the arm.begin() function. The gripper servo will be controlled with the default
//manual servo library instead of the meArm library to ensure a better calibrated claw.
int gripperPin = 5;

//initial claw angle
int gripperAngle = 10;

//joystick pin setup
int xdirPin = 0;
int ydirPin = 1;
int zdirPin = 3;
int gdirPin = 2;

//arm from the meArm library
meArm arm;


void setup() {
  arm.begin(basePin, shoulderPin, elbowPin, gripperPin);
  Serial.begin(9600);
  gripperServo.attach(6);
}

void loop() {
  //map 
  float dx = map(analogRead(xdirPin), 0, 672, -5.0, 5.0);
  float dy = map(analogRead(ydirPin), 0, 672, 5.0, -5.0);
  float dz = map(analogRead(zdirPin), 0, 672, 5.0, -5.0);
  float dg = map(analogRead(gdirPin), 0, 672, 5.0, -5.0);
  //make sure the servos don't move when the joystick is touched only slightly
  if (abs(dx) < 5) dx = 0;
  if (abs(dy) < 5) dy = 0;
  if (abs(dz) < 5) dz = 0;
  if (abs(dg) < 1.5) dg = 0;
  if (!(dx == 0 && dy == 0 && dz == 0))
    arm.goDirectlyTo(arm.getX() + dx, arm.getY() + dy, arm.getZ() + dz);

  // if claw joystick is pulled upwards, slowly close the claw
   if (dg > 4) {
    for(gripperAngle = 70; gripperAngle < 112; gripperAngle++)  
    {                                  
      gripperServo.write(gripperAngle);               
      delay(30);         
      
    } 
  }

  // if claw joystick is pulled downwards, slowly open the claw
  else if (dg < -4) {
    for(gripperAngle = 112; gripperAngle > 70; gripperAngle--)  
    {                                  
      gripperServo.write(gripperAngle);               
      delay(15);                   
    } 
  }
  
  delay(50);
  
Serial.println(dg);
}
