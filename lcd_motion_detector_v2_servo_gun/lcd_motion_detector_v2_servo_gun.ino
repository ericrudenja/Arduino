/*



  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)



*/
//include servo:
#include <Servo.h>
// create servo object to control a servo
Servo myservo;  

// include the lcd library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;


int ledPin = 13;                // choose the pin for the LED
int motionPin = 9;               // choose the input pin (for PIR sensor)
int motionState = LOW;             // we start, assuming no motion detected
int valMotion;                    // variable for reading the pin status
int servoMicroseconds;


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

// attaches the servo on pin 10 to the servo object
  myservo.attach(10);  
  
  // Print a message to the LCD.
  lcd.print("no signal...");

  pinMode(ledPin, OUTPUT);
  pinMode(motionPin, INPUT);



  
}

void loop() {



  //motion code
  
  valMotion = digitalRead(motionPin);  // read input valMotionue
  if (valMotion == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (motionState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      lcd.clear();
      lcd.print("Motion detected!");
      // We only want to print on the output change, not state
      motionState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (motionState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      lcd.clear();
      lcd.print("Motion ended!");
      // We only want to print on the output change, not state
      motionState = LOW;
    }
  }
  
  //motion code end









  //servo code


  //value of servo microsecond movement
  servoMicroseconds = myservo.readMicroseconds();
  
  // sets the servo position according to a value
  
//  if (motionState == HIGH) {
//    
//    myservo.writeMicroseconds(1600);
//    delay(40);
////    myservo.writeMicroseconds(1500);
//    
//
//  }
//  else if (motionState == LOW) {
//    if (servoMicroseconds == 1600) {
//      myservo.writeMicroseconds(1400);
//      delay(40);
//      myservo.writeMicroseconds(1500);
//    }

Serial.println(servoMicroseconds);
switch (motionState) {

  case HIGH:

    switch (servoMicroseconds) {
      case 1500:
        Serial.println("a");
          myservo.writeMicroseconds(1350);
        delay(500);
        myservo.writeMicroseconds(1500);
        delay(500);
        
        myservo.writeMicroseconds(1650);
        delay(500);
        myservo.writeMicroseconds(1500);
        Serial.println("not returned yet");


      

        break;
        
      case 1502:
        Serial.println("b");
        myservo.writeMicroseconds(1350);
        delay(500);
        myservo.writeMicroseconds(1500);
        delay(500);
        myservo.writeMicroseconds(1650);
        delay(500);
        myservo.writeMicroseconds(1500);
        

        
        break;
      case 1600:
      break;
    }
    

    
  
}






  

  delay(400);
//  Serial.println(servoMicroseconds);

  
  }


 

