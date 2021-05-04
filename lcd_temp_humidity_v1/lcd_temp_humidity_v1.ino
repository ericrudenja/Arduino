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

//include humidity + temperature library
#include <dht.h>

//digital pin of the sensor goes into digital pin 8
#define dataPin 8
dht DHT;

// include the lcd library code:
#include <LiquidCrystal.h>



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
  
}

void loop() {



  int readData = DHT.read11(dataPin);
  int temperature = DHT.temperature;
  int humidity = DHT.humidity;
  Serial.print("Temperature = "); 
  Serial.print(temperature);
  Serial.print(" *C ");
  Serial.println();
  Serial.print("Humidity = "); 
  Serial.print(humidity);
  Serial.print(" % ");
  Serial.println();
  Serial.println(); 

  //Update the lcd screen:
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" *C");


  lcd.setCursor(0, 1);
  lcd.print("Humi: ");
  lcd.print(humidity);
  lcd.print(" %");
  //The update rate on DHT11 sensor is 1Hz, delay needs to be at least two seconds between
  //reading for them to be accurate.
  delay(2000);
  
  
}
