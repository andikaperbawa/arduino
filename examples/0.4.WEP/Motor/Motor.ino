/* Copyright (C) 2016
 * KAUST Maker Space SDG 
 * All Rights Reserved
 *
 * Grove Activity 0.4.WEP 
 * "Spin It Fast"
 *
 */

// define pin for motor A2
int motorPin = A2;

// define button pin D4
int buttonPin = 4;

// the setup function is called once
void setup() {
  // set buttonPin to input mode
  pinMode(buttonPin, INPUT);  
}

// the loop function is called over and over again
void loop() {
  
  // read state of button
  int buttonState = digitalRead(buttonPin);

  // if button pressed 
  if (buttonState == HIGH) {
    analogWrite(motorPin, 255);
  } else {
		analogWrite(motorPin, 0);
	}
  
}
