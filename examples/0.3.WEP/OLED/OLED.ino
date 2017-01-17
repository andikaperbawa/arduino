/* Copyright (C) 2016
 * KAUST Maker Space SDG 
 * All Rights Reserved
 *
 * Grove Activity 0.3.WEP 
 * "Display It!"
 *
 */

#include <Wire.h>
#include <SeeedOLED.h>

// define variable for counter
int counter;

void setup()
{
   // initialize counter
  counter = 0;
  
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
  // set cursor to row 0
  SeeedOled.setTextXY(0,0);          
  // print a string
  SeeedOled.putString("Hello World!"); 
  // set cursor to row 1
  SeeedOled.setTextXY(1,0);          
  // print counter
  SeeedOled.putNumber(counter); 

  // increment counnter
  counter = counter + 1;
  // wait for 0.5 seconds (= 500 ms)
  delay(500);
  
}

