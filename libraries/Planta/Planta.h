#include "/home/leo/jardingenia/libraries/DHT/DHT.h"
#include "/home/leo/jardingenia/libraries/DHT/DHT.cpp"
#include "/home/leo/jardingenia/libraries/SI114X/SI114X.h"
#include "/home/leo/jardingenia/libraries/SI114X/SI114X.cpp"
#include <Arduino.h>
#include <Wire.h>

#define DHT_TYPE DHT11
#define DHTPIN A0
#define PinsHums A1
#define  PinFlujo 2
volatile int NumPulsos;
float factor_conv=7.5;
	
class Planta {
 private:
  float Humsuelo;
  float Humedad;
  float Temperatura;
  float luz;
  float flujo;
	float humSMax;
	float humMax;
	float tempMax;
	float luzMax;
	float flujoMax;
	int NumPulsos;
  DHT dht = DHT(DHTPIN, DHT_TYPE);
   SI114X SI1145= SI114X();
 public:
  Planta(float maxHumS, float maxHum, float maxTemp, float maxLuz, float maxFlujo);
  float cheqHumS();
  float cheqHum();
  float cheqTemp();
  float cheqLuz();
  int cheqFlujo();
  void begin();
};
