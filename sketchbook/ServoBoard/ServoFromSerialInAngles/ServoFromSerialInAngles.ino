/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 16 servos, one after the other

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!


// minimum pulse length (of 4096) for each servo
int SERVOMIN[8] = {150,150,150,150,150,150,150,150};
// maximum pulse length (of 4096) for each servo
int SERVOMAX[8] = {550,550,550,550,550,550,550,550};

// our servo # counter
uint8_t servonum = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  yield();

  delay(500);
  
  for (uint16_t pulselen = 150; pulselen < 550; pulselen++) {
    pwm.setPWM(servonum, 0, pulselen);
  }


  delay(500);
  for(int servonum=0; servonum<8; servonum++){
    pwm.setPWM(servonum, 0, 300);
  }
}


void loop() {
  // Drive each servo one at a time
  while (! Serial.available()) return;
  
  int val = Serial.parseInt();
  val = min(val, 180);
  val = max(val, 0);
  Serial.print("mapping ");
  Serial.print(val, DEC);
  Serial.println(" degree to ");
  
  for(int servonum=0; servonum<8; servonum++){
    // map degrees to pulselength
    int pulselength = map(val, 0, 180, SERVOMIN[servonum], SERVOMAX[servonum]);
    Serial.print(servonum, DEC);
    Serial.print(" pulselength ");
    Serial.println(pulselength, DEC);
    pwm.setPWM(servonum, 0, pulselength);
  }

  delay(500);
}



// you can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000;
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
 
}
