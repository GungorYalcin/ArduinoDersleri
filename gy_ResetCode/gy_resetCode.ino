/*
 gungor 28/10/2017
 Arduino kodla resetleme
*/
#include <avr/wdt.h>
void setup() {
  Serial.begin(9600);
  Serial.println("Ardiuno Start");

}

void loop() {
  Serial.println( millis() );
  //1 saniye = 1000 millis
  if (millis() > 5000) {
    Serial.print("Reset");// gunde bir sefer reset
    wdt_enable( WDTO_60MS);
    while(1) {} 
  }

  delay(250);
}
