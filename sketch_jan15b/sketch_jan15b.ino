#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#define WLAN_SSID       "WEP2017_IoT"
#define WLAN_PASS       "WeP@2017IoT"

#define AIO_SERVER      "mqtt.vis.kaust.edu.sa"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "andika.perbawa@kaust.edu.sa"
#define AIO_KEY         "adf88bf6704fe58a2b526147e2141beb"

WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe blinky = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/blinky");
Adafruit_MQTT_Publish text = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/text");

/* The blue LED is on PIN 2 - HIGH turns it off; LOW turns it on */
/* The red LED is on PIN 0 - HIGH turns it off; LOW turns it on */

#define  LED_RED  0
#define  LED_BLUE 2

void setup() {

   Serial.begin(115200);
   delay(10);

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

  mqtt.subscribe(&blinky);

  pinMode( LED_BLUE, OUTPUT );

}

void MQTT_connect();

void loop() {
 
  MQTT_connect();

  Adafruit_MQTT_Subscribe *subscription;
  
  while ((subscription = mqtt.readSubscription(100))) {
 
      if (subscription == &blinky) {
          Serial.print(F("blibky: "));
          Serial.println((char *)blinky.lastread);

          if ( *blinky.lastread == '0' ) {
            Serial.println( "Off");
            digitalWrite( LED_BLUE, HIGH );
          } else if ( *blinky.lastread == '1' ) {
            Serial.println( "On");
            digitalWrite( LED_BLUE, LOW );
          }
          
      }

  }
  if ( Serial.available() > 0 ) {
    // read the incoming byte
    int byte = Serial.read();
    Serial.print("Sending text ");
    Serial.print( byte );
    Serial.print(" . . ");

    if ( ! text.publish( byte ++)) {
        Serial.println("Failed");
    } else {
        Serial.println("OK!");
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
