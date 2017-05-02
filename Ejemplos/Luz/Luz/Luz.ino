#include "Arduino.h"
#include "SI114X.h"

SI114X SI1145 = SI114X();

float UVIndex = 0;
float IRIndex = 0;
float VisibleIndex = 0;

void setup() {
  Serial.begin(9600);
 while (!SI1145.Begin()){
    delay (1000);
  }
}

void loop() {
 UVIndex = (float)SI1145.ReadUV ()/100 + 0.5;
 Serial.print("UV: ");Serial.println(UVIndex);
 IRIndex = (float)SI1145.ReadIR ();
 Serial.print("IR: ");Serial.println(IRIndex);
 VisibleIndex = (float)SI1145.ReadVisible ();
 Serial.print("Luz Visible: ");Serial.println(VisibleIndex);
 delay(1000);
          
}
