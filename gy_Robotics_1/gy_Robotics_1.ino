/*
 Güngör 02/12/2017
 6 potansiyometre ile robot kol yapımı
 */
 void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print(" R0: ");
  Serial.print(analogRead(7));
  Serial.print(" R1: ");
  Serial.print(analogRead(6));
  Serial.print(" R2: ");
  Serial.print(analogRead(5));
  Serial.print(" R3: ");
  Serial.print(analogRead(4));
  Serial.print(" R4: ");
  Serial.print(analogRead(3));
  Serial.print(" R5: ");
  Serial.print(analogRead(2));
  Serial.println("");
  delay(500);
}
