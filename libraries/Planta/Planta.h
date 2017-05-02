#include <Wire.h>
#include "/home/leo/Documentos/jardingenia/libraries/DHT/DHT.h"
#include "/home/leo/Documentos/jardingenia/libraries/DHT/DHT.cpp"
/* #include "/home/leo/Documentos/jardingenia/libraries/SI114X/SI114X.h" */
#include <Arduino.h>

#define DHT_TYPE DHT11
#define DHTPIN A0
#define PinsHums A1
/* volatile int NumPulsos; */
/* int PinSensor=2; */
/* float factor_conv=7.5; */
	
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
  DHT dht = DHT(DHTPIN, DHT_TYPE);
	/* SI114X SI1145= SI114X(); */
 public:
  Planta(float maxHumS, float maxHum, float maxTemp, float maxLuz, float maxFlujo);
  float cheqHumS();
  float cheqHum();
  float cheqTemp();
  float cheqLuz();
  float cheqFlujo();
	void ContarPulsos();
	void begin();
};
