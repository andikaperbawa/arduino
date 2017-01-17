/* Copyright (C) 2016
 * KAUST Maker Space SDG 
 * All Rights Reserved
 *
 * Grove Activity 0.2.WEP 
 * "Add a Button to the Servo"
 *
 */

#include <Servo.h>

// create servo object to control a servo
Servo myservo;  

// define pin for servo D3
int servoPin = 3;

// define button pin D4
int buttonPin = 4;

// variable to store the servo position
int pos;    

// the setup function is called once
void setup() {
  // set servoPin 
  myservo.attach(servoPin); 
  // init pos
  pos = 5;
  // move to pos
  myservo.write(pos);
  
  // set buttonPin to input mode
  pinMode(buttonPin, INPUT);  
  
  // wait for the servo to settle
  delay(1000);
}

// the loop function is called over and over again
void loop() {
  
  // read state of button
    int buttonState = digitalRead(buttonPin);

    // if button pressed 
    if (buttonState == HIGH) {
        // increase pos of servo 
		pos = pos + 1;
    } else {
		// decrease pos of servo 
		pos = pos - 1;
	}
	
	// check if pos is too high
	if(pos > 180){
		// truncate at 180 degree (that's the range of the servo)
		pos = 180;
	}
	
	// check if pos is too low 
	if(pos < 5){
		// truncate at 5 degree (below 5 it starts humming)
		pos = 5;
	}

  // move the servo
  myservo.write(pos);
  
}