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

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"


#define WLAN_SSID       "WEP2017_IoT"
#define WLAN_PASS       "WeP@2017IoT"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "mqtt.vis.kaust.edu.sa"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "greg.wickham@kaust.edu.sa"
#define AIO_KEY         "4418767a477de7de48d92f8710994a18"

WiFiClient client;
//WiFiClientSecure client;

int led = 0;

void MQTT_connect();

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe blinky = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/blinky");

void setup() {
  
   Serial.begin(115200);
  delay(10);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  mqtt.subscribe(&blinky);

  pinMode( led, OUTPUT );
}


void loop() {

  MQTT_connect();

  Adafruit_MQTT_Subscribe *subscription;
  
  while ((subscription = mqtt.readSubscription(100))) {
 
      if (subscription == &blinky) {
          Serial.print(F("door: "));
          Serial.println((char *)blinky.lastread);

          if ( *blinky.lastread == '0' ) {
            Serial.println( "Off");
            digitalWrite( led, LOW );
          } else if ( *blinky.lastread == '1' ) {
            Serial.println( "On");
            digitalWrite( led, HIGH );
          }
          
      }

  }
  
}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}

