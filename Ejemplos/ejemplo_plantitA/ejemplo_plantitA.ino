#include "/home/ingenia/jardingenia/libraries/Planta/Planta.h"
#include "/home/ingenia/jardingenia/libraries/Planta/Planta.cpp"
#include "Wire.h"
#include "/home/ingenia/jardingenia/libraries/SI114X/SI114X.h"
//#include "/home/ingenia/jardingenia/libraries/SI114X/SI114X.cpp"
#include "/home/ingenia/jardingenia/libraries/DHT/DHT.h"
#include "Arduino.h"


Planta plantita (1,1,1,1,1);
void setup() {
  plantita.begin();
  Serial.begin(9600);
  //plantita.cheqHum();

}

void loop() {
 //Serial.println(plantita.cheqHum());
 //Serial.println(plantita.cheqHumS());
 Serial.println(plantita.cheqLuz());
 delay(1000);

}
