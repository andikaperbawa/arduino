/* Copyright (C) 2016
 * KAUST Maker Space SDG 
 * All Rights Reserved
 *
 * Grove Activity 0.2.WEP 
 * "Make it Move"
 *
 */

#include <Servo.h>

// create servo object to control a servo
Servo myservo;  

// define pin for servo D3
int servoPin = 3;

// variable to store the servo position
int pos = 0;    

// the setup function is called once
void setup() {
  // assign pin 
  myservo.attach(servoPin);  
}

// the loop function is called over and over again
void loop() {
  
  // move from 0 to 180 degrees in steps of 5 degrees
  for (pos = 0; pos <= 180; pos += 5) { 
    // move servo to position pos
    myservo.write(pos);              
    // wait 
    delay(100);                       
  }

  // move from 180 to 0 degrees in steps of 5 degrees
  for (pos = 180; pos >= 0; pos -= 5) { 
    // move servo to position pos
    myservo.write(pos);              
    // wait 
    delay(100);                       
  }
  
}
