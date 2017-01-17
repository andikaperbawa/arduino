/* Copyright (C) 2016
 * KAUST Maker Space SDG 
 * All Rights Reserved
 *
 * Grove Activity 0.4.WEP 
 * "Switch the Button for two Touch Sensors"
 *
 */

// define pin for motor A2
int motorPin = A2;

// define first touch sensor pin D4
int touchSensorPin1 = 4;
// define second touch sensor pin D5
int touchSensorPin2 = 5;

// the setup function is called once
void setup() {
  // set touch sensor pins to input mode
  pinMode(touchSensorPin1, INPUT);  
  pinMode(touchSensorPin2, INPUT);  
}

// the loop function is called over and over again
void loop() {
  
  // read state of button
  int touchSensorState1 = digitalRead(touchSensorPin1);
  int touchSensorState2 = digitalRead(touchSensorPin2);
  

  // if button 1 is pressed
  if (touchSensorState1 == HIGH) {
    analogWrite(motorPin, 255);
  } 
  if(touchSensorState2 == HIGH) {
		analogWrite(motorPin, 0);
	}
  
}
