// This tests the environment board
// The board combines a Photocell circuit and Bosch's BME280 barometric pressure, humidity, temperature sensor
// LIBRARIES:
//  * BME280 -- download via the IDE's library manager (Adafruit_BME280)
//  * Photocell -- included in the project. You should calibrate for maximum and minimum cds_resistance readout

#include <Adafruit_BME280.h>
#include <Wire.h>
#include"Photocell.h"

#define PLOTTER

#ifdef PLOTTER
const uint32_t interval = 100;
#else
const uint32_t interval = 1000;
#endif

Photocell light_sensor;

Adafruit_BME280 bme;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // calibrate these!
  light_sensor.set_range(52.5f,220000.0f);
  delay(1000);
  while(!Serial) delay(10);
  Serial.println("");
  Serial.println("");
  if (!bme.begin(0x77)) {
    Serial.println("Could not initialize BME280");
  }
  Wire.setClock(100000);
}

void loop() {
  // put your main code here, to run repeatedly:
  light_sensor.measure();
  static uint32_t t = millis();
  static uint32_t last_event = millis();  
  static bool haslight = false;  
#ifndef PLOTTER
  if (millis()-last_event>interval && !haslight) {
    haslight=true;
    Serial.println("");
    Serial.println("[PHOTOCELL]");
    Serial.print("  Time        = "); Serial.print(float(millis()-t)/1000.0f); Serial.println("s"); yield();
    Serial.print("  U_adc       = "); Serial.print(light_sensor.adc_voltage()); Serial.println("V"); yield();
    Serial.print("  R_total     = "); Serial.print(light_sensor.total_resistance()); Serial.println("Ohm  "); yield();
    Serial.print("  I_total     = "); Serial.print(light_sensor.total_current()*1000.0f); Serial.println("mA"); yield();
    Serial.print("  R_cds       = "); Serial.print(light_sensor.cds_resistance()); Serial.println("Ohm"); yield();
    Serial.print("  Lightness   = "); Serial.print(light_sensor.lightness()); Serial.println("%"); yield();
  }
  if (millis()-last_event>2*interval) {    
    Serial.println("");
    Serial.println("[BME280]");
    Serial.print("  Time        = "); Serial.print(float(millis()-t)/1000.0f); Serial.println("s"); yield();
    Serial.print("  Temperature = "); Serial.print(bme.readTemperature()); Serial.println("C"); yield();
    Serial.print("  Pressure    = "); Serial.print(bme.readPressure()/100.0f); Serial.println("hPa"); yield();
    Serial.print("  Humidity    = "); Serial.print(bme.readHumidity()); Serial.println("%"); yield();    
    // reset counters
    last_event = millis();
    haslight = false;
  }
#else
  if (millis()-last_event>interval) {
    last_event = millis();
    Serial.print(light_sensor.lightness());
    Serial.print(" ");
    Serial.print(bme.readTemperature());
    Serial.print(" ");
    Serial.print(bme.readPressure()*0.001f);
    Serial.print(" ");
    Serial.println(bme.readHumidity());
  }
#endif
  delay(10);
}
