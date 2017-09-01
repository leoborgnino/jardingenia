/* La ClAsee de la PlAANta wacHO

LiceNcIADo por FuLGor y TARpuY
No aL cOPyriGht
*/
#define PinsHums A1
Planta::Planta(float maxHumS, float maxHum, float maxTemp, float maxLuz, float maxFlujo){
  humSMax= maxHumS;
  humMax= maxHum;
  tempMax= maxTemp;
  luzMax= maxLuz;
  flujoMax= maxFlujo;
  
}

void Planta::begin(){
  dht.begin();
  while (!SI1145.Begin())
    delay (1000);
  
  pinMode(PinFlujo, INPUT);

}

float Planta::cheqHumS(){
  return analogRead(PinsHums)/7;
}

float Planta::cheqHum(){
  return dht.readHumidity();
}

float Planta::cheqTemp(){
  return dht.readTemperature();
}

float Planta::cheqLuz(){
  float UVIndex =(float)SI1145.ReadIR ();
  return UVIndex;
}

int Planta::cheqFlujo(){
return 1;
}


