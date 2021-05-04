// The DHT11 sensor tracks humidity and temperature. 
// Temperature: 0-50 degrees celsius. Humidity: 20 - 80 percent.


//  The circuit for the lcd is:
// * LCD RS pin to digital pin 12
// * LCD Enable pin to digital pin 11
// * LCD D4 pin to digital pin 5
// * LCD D5 pin to digital pin 4
// * LCD D6 pin to digital pin 3
// * LCD D7 pin to digital pin 2
// * LCD R/W pin to ground
// * LCD VSS pin to ground
// * LCD VCC pin to 5V
// * 10K resistor:
// * ends to +5V and ground
// * wiper to LCD VO pin (pin 3)


//include servo:
#include <Servo.h>
// create servo object to control a servo
Servo servo;  


// include the lcd library code:
#include <LiquidCrystal.h>


//soil moisture sensor:
int soilSensorPin = A0;

int soilVal;

int angle = 10;


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print an initial message to the LCD.
  lcd.print("no signal...");
  servo.attach(10);  
  delay(500);
  
}

void loop() {
  delay(300);

  soilVal = analogRead(soilSensorPin);
//  Serial.print("Moisture: ");
//  Serial.print(soilVal);
//  Serial.println();
  

  //Since moisture needs to be converted from the 0-1023 output to 0-100%,
  //the output will be converted/mapped to the latter percentage standard.
  soilVal = map(soilVal,0,1023,0,100);
  Serial.print("Moisture: ");
  Serial.print(soilVal);
  Serial.println();
//  Serial.println();
  //Update the lcd screen and open/close servo's water valve depending:
  if (soilVal < 25) { //if water moisture is less than 25%, the plant needs watering.
     for(angle = 10; angle < 180; angle++)  {       
        //open the valve if water level is low                          
        servo.write(angle);
        delay(30);                   
     } 
  } else {
      for(angle = 180; angle > 10; angle--)    
        {         
          //else, the valve needs to be closed                       
          servo.write(angle);           
          delay(30);       
        }
  }
  
  
}
