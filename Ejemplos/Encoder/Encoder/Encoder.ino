#define EncoderPin1 3
#define EncoderPin2 4

float i = 0;

void setup() {
  Serial.begin(9600);
  pinMode(EncoderPin1, INPUT);
  pinMode(EncoderPin2, INPUT);
  attachInterrupt(1, EncoderRotate, RISING); 

}

void EncoderRotate()
{
    if(digitalRead(EncoderPin1) == 1) {
        delay(10);
        if(digitalRead(EncoderPin1) == 1) {
                if(digitalRead(EncoderPin2) == 1) {
                    i++ ; 
                    
                } else {
                    i-- ;
                    
                }
        } else {
        }
    } else {
    }
}

void loop() {
  Serial.print ("Encoder: ");Serial.println(i);
  delay (1000);

}
