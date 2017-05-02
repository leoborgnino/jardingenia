/* La ClAsee de la PlAANta wacHO

LiceNcIADo por FuLGor y TARpuY
No aL cOPyriGht
*/

// #include "Planta.h"
Planta::Planta(float maxHumS, float maxHum, float maxTemp, float maxLuz, float maxFlujo){
  humSMax= maxHumS;
  humMax= maxHum;
  tempMax= maxTemp;
  luzMax= maxLuz;
  flujoMax= maxFlujo;
}
void Planta::begin(){
  dht.begin();
  // SI1145.Begin();
  // pinMode(PinSensor, INPUT);
  // attachInterrupt(0,ContarPulsos,RISING);
}

float Planta::cheqHumS(){
  return analogRead(15)/7;
}

float Planta::cheqHum(){
  return dht.readHumidity();
}

float Planta::cheqTemp(){
  return dht.readTemperature();
}

// float Planta::cheqLuz(){
//   return (float)SI1145.ReadVisible();
// }

float Planta::cheqFlujo(){
  int frecuencia;
  // NumPulsos=0;
  // interrupts();
  // delay(1000);
  // noInterrupts();
  // frecuencia= NumPulsos;
  // frecuencia= frecuencia/factor_conv;
  return frecuencia;
}

// void Planta::ContarPulsos(){
//   NumPulsos++;
// }
