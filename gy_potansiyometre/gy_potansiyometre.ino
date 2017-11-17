/*
 * gungor 21/10/2017 Potansiyometre kullanımı
 * analog portlar 0-5 volt 0-1023 arasinda deger verir
*/
void setup() {
    Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(2));
  delay(500);
}
