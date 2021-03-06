#define PinsHums A1
Planta::Planta(float minHumS, float maxHumS, float maxHum, float maxTemp, float maxLuz, float maxFlujo){
  humSMax= maxHumS;
  humSMin= minHumS;
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


