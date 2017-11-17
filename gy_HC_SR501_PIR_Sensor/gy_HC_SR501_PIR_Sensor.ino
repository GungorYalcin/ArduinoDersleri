/*
 gungor 17/09/2016
*/
int pirSensorPin = 4;
int relayPin = 13; //led

void setup (){
  pinMode(pirSensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
}

void loop() {
  if (digitalRead(pirSensorPin) == 1 )
  {
    digitalWrite(relayPin,HIGH);
  }
  else
  {
    digitalWrite(relayPin,LOW);
  }
  delay(100);

}
