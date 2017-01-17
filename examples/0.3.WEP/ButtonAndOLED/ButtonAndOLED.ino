/* Copyright (C) 2016
 * KAUST Maker Space SDG 
 * All Rights Reserved
 *
 * Grove Activity 0.3.WEP 
 * "Add a Button to the OLED Display!"
 *
 */

#include <Wire.h>
#include <SeeedOLED.h>

// define pin for button D4
int buttonPin = 4;

void setup()
{
  // set buttonPin to input mode
  pinMode(buttonPin, INPUT);
  
  // initialze serial communication
  Wire.begin();
  
  //initialze SEEED OLED display
  SeeedOled.init();  
  DDRB|=0x21;        
  PORTB |= 0x21;
  SeeedOled.clearDisplay();          
  SeeedOled.setNormalDisplay();      
  SeeedOled.setPageMode();           
}

void loop()
{
  // set cursor of display to row 0
  SeeedOled.setTextXY(0,0);          
  // write line 0
  SeeedOled.putString("The button is..."); 

  // read state of button
  int buttonState = digitalRead(buttonPin);

  // if HIGH turn on LED
  if (buttonState == HIGH) {
      // display message
      // set cursor of display to row 1 
      SeeedOled.setTextXY(1,0);          
      // write line 1
      SeeedOled.putString("...ON! "); 
  }
  else {
      // display different message
      // set cursor of display to row 1 
      SeeedOled.setTextXY(1,0);          
      // write line 1
      SeeedOled.putString("...OFF!"); 
  }

}

