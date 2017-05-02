#include <Arduino.h>
#include <Wire.h>
#include "DHT.h"

#define DHTPIN A0
#define DHTTYPE DHT11
DHT dht (DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("begin...");
  dht.begin();

}

void loop() {
  float temp = dht.readTemperature ();
  float hum = dht.readHumidity ();
  Serial.print ("Temp = ");
  Serial.print(temp);
  Serial.println ("C");
  Serial.print("Hum =");
  Serial.print (hum);
  Serial.println ("%");
  Serial.println ();
  delay (1000);
}


