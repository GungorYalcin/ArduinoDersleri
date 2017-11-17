/*
 gungor 28/10/2017
 ilave buton ile arduino resetleme
 buton 1. pin arduino Reset pin
 buton 2. pin arduino GND pin
  
 */
void setup() {
  Serial.begin(9600);
  Serial.println("Arduino start");
}

void loop() {
  Serial.println(millis());
  delay(250);
}
