/*
  Gungor 26/10/2016 
  LDR 
  1 pin Vcc
  2 pin data
  2 pin 10 K direncle GRD 
 */

int Ldr_pin = A0; // analog 0 pini 
void setup() {
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  int sensorValue = analogRead(Ldr_pin);
  Serial.println(sensorValue);
  delay(100);        // delay in between reads for stability
}
