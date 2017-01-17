/* Copyright (C) 2016
 * KAUST Maker Space SDG 
 * All Rights Reserved
 *
 * Grove Activity 0.1.WEP 
 * "Blinky LED"
 */
 
// define LED pin D2
int ledPin = 2;

// the setup function runs once
void setup() {
  // init the ledPin
  pinMode(ledPin, OUTPUT);
}

// the loop function runs over and over 
void loop() {
  // set ledpin to high (LED will light up)
  digitalWrite(ledPin, HIGH);   
  // wait for 1 second (=1000ms)
  delay(1000);                       
  // set ledpin to low (LED will turn off)
  digitalWrite(ledPin, LOW);    
  // wait for 1 second (=1000ms)
  delay(1000);                       
}
