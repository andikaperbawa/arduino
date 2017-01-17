/* Copyright (C) 2016
 * KAUST Maker Space SDG 
 * All Rights Reserved
 *
 * Grove Activity 0.7.WEP 
 * "Sensing Light"
 *
 */

#include "rgb_lcd.h"

// define LCD
rgb_lcd lcd;

// define light sensor pin A2
const int lightSensorPin = A2;   

// define LED pin D2
const int ledPin = 2;  

void setup()
{
  // init the ledPin
  pinMode(ledPin, OUTPUT);
  
   // setup LCD (16 columns, 2 rows)
  lcd.begin(16, 2);
  // set LCD backlight color
  lcd.setRGB(255, 255, 32);
  // print first line of LCD
  lcd.print("light [0..1]:");
  delay(1000);
}

void loop()
{
  // read the analog value of the light sensor (range: [0..1023])
  int sensorValue = analogRead(lightSensorPin);
  // normalize the value (bring it in the range [0..1])
  float normalizedValue = sensorValue / 1023.0f;

  // if the normalizedValue is lower than 0.25 turn the LED on
  if (normalizedValue < 0.25) {
    // turn on 
    digitalWrite(ledPin, HIGH); 
  } else {
    // turn off 
    digitalWrite(ledPin, LOW);
  }

  // print the output on the LCD
  // print an empty row (overwriting all 16 characters)
  lcd.print("                ");
  // set the LCD's cursor again to the first column (index = 0), of the second line (index = 1)
  lcd.setCursor(0, 1);
  // print the degrees
  lcd.print(normalizedValue);

  // wait quater of a second (=250 milliseconds)
  delay(250);
}


