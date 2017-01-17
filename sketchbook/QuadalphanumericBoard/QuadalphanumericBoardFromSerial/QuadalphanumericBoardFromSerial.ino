// Demo the quad alphanumeric display LED backpack kit
// scrolls through every character, then scrolls Serial
// input onto the display
#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>


#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#define WLAN_SSID       "WEP2017_IoT"
#define WLAN_PASS       "WeP@2017IoT"

#define AIO_SERVER      "mqtt.vis.kaust.edu.sa"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "andika.perbawa@kaust.edu.sa"
#define AIO_KEY         "adf88bf6704fe58a2b526147e2141beb"
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe leddisplay = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/leddisplay");


Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to ");
   Serial.println( WLAN_SSID );
   
   WiFi.begin(WLAN_SSID, WLAN_PASS);
   
   while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println( WiFi.localIP() );

  mqtt.subscribe(&leddisplay);
  
  alpha4.begin(0x70);  // pass in the address

  alpha4.writeDigitRaw(3, 0x0);
  alpha4.writeDigitRaw(0, 0xFFFF);
  alpha4.writeDisplay();
  delay(50);
  alpha4.writeDigitRaw(0, 0x0);
  alpha4.writeDigitRaw(1, 0xFFFF);
  alpha4.writeDisplay();
  delay(50);
  alpha4.writeDigitRaw(1, 0x0);
  alpha4.writeDigitRaw(2, 0xFFFF);
  alpha4.writeDisplay();
  delay(50);
  alpha4.writeDigitRaw(2, 0x0);
  alpha4.writeDigitRaw(3, 0xFFFF);
  alpha4.writeDisplay();
  delay(50);
  
  alpha4.clear();
  alpha4.writeDisplay();

  // display every character, 
  for (uint8_t i='A'; i<='W'; i++) {
    alpha4.writeDigitAscii(0, i);
    alpha4.writeDigitAscii(1, i+1);
    alpha4.writeDigitAscii(2, i+2);
    alpha4.writeDigitAscii(3, i+3);
    alpha4.writeDisplay();
    
    delay(150);
  }

  // display every number, 
  for (uint8_t i='0'; i<='6'; i++) {
    alpha4.writeDigitAscii(0, i);
    alpha4.writeDigitAscii(1, i+1);
    alpha4.writeDigitAscii(2, i+2);
    alpha4.writeDigitAscii(3, i+3);
    alpha4.writeDisplay();
    
    delay(150);
  }
  Serial.println("Start typing to display!");
}

void MQTT_connect();

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

char displaybuffer[4] = {' ', ' ', ' ', ' '};

void loop() {
  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  char displaybuffer[4] = {' ', ' ', ' ', ' '};
  while ((subscription = mqtt.readSubscription(100))) {
  
  uint16_t datalength = leddisplay.datalen;
  Serial.println(datalength);
  
  //char* string = new char[datalength];
  if (datalength<5){
    if (*leddisplay.lastread == 1111 ){
    displaybuffer[0]='H';
    displaybuffer[1]='A';
    displaybuffer[2]='L';
    displaybuffer[3]='O';}
  for(int i=0; i<datalength;i++){
    displaybuffer[i] = leddisplay.lastread[i];
  }
  }
  //Serial.println(string);
 /// delete[] string;
 // return;
  //if (! isprint(c)) return; // only printable!
  
  // scroll down display
 //displaybuffer[0] = displaybuffer[1];
  //displaybuffer[1] = displaybuffer[2];
 // displaybuffer[2] = displaybuffer[3];
 // displaybuffer[3] = 0;
 
  // set every digit to the buffer
  alpha4.writeDigitAscii(0, displaybuffer[0]);
  alpha4.writeDigitAscii(1, displaybuffer[1]);
  alpha4.writeDigitAscii(2, displaybuffer[2]);
  alpha4.writeDigitAscii(3, displaybuffer[3]);
 
  // write it out!
  alpha4.writeDisplay();
  delay(150);
  }
}
