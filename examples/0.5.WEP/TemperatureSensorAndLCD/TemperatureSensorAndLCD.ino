/* Copyright (C) 2016
 * KAUST Maker Space SDG 
 * All Rights Reserved
 *
 * Grove Activity 0.5.WEP 
 * "Sensing Temperature"
 *
 */

#include "rgb_lcd.h"

// define LCD
rgb_lcd lcd;

// define temperature sensor pin A2
const int temperatureSensorPin = A2;     

void setup()
{
   // setup LCD (16 columns, 2 rows)
  lcd.begin(16, 2);
  // set LCD backlight color
  lcd.setRGB(128, 128, 255);
  // print first line of LCD
  lcd.print("temperature [C]:");

  delay(1000);
}

void loop()
{
  // read out degrees Celsius of temperature sensor
  float degreesCelsius = getDegreesCelsius();
  
  // print an empty row (overwriting all 16 characters)
  lcd.print("                ");
  // set the LCD's cursor again to the first column (index = 0), of the second line (index = 1)
  lcd.setCursor(0, 1);
  // print the degrees
  lcd.print(degreesCelsius);

  // wait quater of a second (=250 milliseconds)
  delay(250);
}


// reads and converts the analog sensor values
float getDegreesCelsius()
{
  // read out analog value of temperature sensor 
  int a = analogRead(temperatureSensorPin);

  // convert to R
  float R = 1023.0/((float)a)-1.0;
  //conversion to temperature according to datasheet of the sensor
  float temperature=1.0/(log(R)/4275.0+1.0/298.15)-273.15;

  return temperature;
}
