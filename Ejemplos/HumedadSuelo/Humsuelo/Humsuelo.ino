#define MoisturePin A1

float MoisHumedity = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  MoisHumedity = analogRead(MoisturePin)/7;
  Serial.print("Humedad del suelo: ");Serial.println(MoisHumedity);
  delay(1000);
}
