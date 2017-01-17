/* Copyright (C) 2016
 * KAUST Maker Space SDG 
 * All Rights Reserved
 *
 * Grove Activity 0.1.WEP 
 * "Add a Button to the LED"
 */

 
// define pins
// LED pin D2
const int ledPin =  2; 
// button pin D4
const int buttonPin = 4;

void setup() {
    // set ledPin to output mode
    pinMode(ledPin, OUTPUT);
    // set buttonPin to input mode
    pinMode(buttonPin, INPUT);
}

void loop(){
    // read state of button
    int buttonState = digitalRead(buttonPin);

    // if HIGH turn on LED
    if (buttonState == HIGH) {
        // turn on 
        digitalWrite(ledPin, HIGH);
    }
    else {
        // turn off 
        digitalWrite(ledPin, LOW);
    }
}