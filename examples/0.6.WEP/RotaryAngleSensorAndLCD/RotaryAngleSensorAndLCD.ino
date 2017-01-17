/* Copyright (C) 2016
 * KAUST Maker Space SDG 
 * All Rights Reserved
 *
 * Grove Activity 0.6.WEP 
 * "Sense Rotation"
 *
 */

#include <Wire.h>
#include "rgb_lcd.h"

// define pin for rotary angle sensor A2
int rotaryAngleSensorPin = A2;

// define LCD
rgb_lcd lcd;

// define backlight color of LCD
int colorR = 255;
int colorG = 255;
int colorB = 255;

void setup() 
{
  // setup pins 
  pinMode(rotaryAngleSensorPin, INPUT);
  // setup LCD (16 columns, 2 rows)
  lcd.begin(16, 2);
  // set LCD backlight color
  lcd.setRGB(colorR, colorG, colorB);
    
  // print first line of LCD
  lcd.print("angle (0-300):");

  delay(1000);
}

void loop() 
{
  // read out degrees of rotary angle sensor
  int degrees;
  degrees = getDegree();
  
  // set the LCD's cursor to the first column (index = 0), of the second line (index = 1)
  lcd.setCursor(0, 1);
  // print an empty row (overwriting all 16 characters)
  lcd.print("                ");
  // set the LCD's cursor again to the first column (index = 0), of the second line (index = 1)
  lcd.setCursor(0, 1);
  // print the degrees
  lcd.print(degrees);

  // wait a tenth of a second (=100 milliseconds)
  delay(100);
}


// reads and converts the analog sensor values to the range 0..300
int getDegree()
{
  // read analog value (range: 0..1023)
  int value = analogRead(rotaryAngleSensorPin);
  // normalize the range
  float normalized;
  normalized = (float)value / 1023.f;
  // convert to the range of the rotary angle sensor (range: 0..300)
  float degrees = (normalized*300.f);
  return degrees;
}

