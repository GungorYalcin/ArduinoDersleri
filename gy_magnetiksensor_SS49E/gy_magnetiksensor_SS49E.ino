/*
 gungor 29/10/2017
 magyatik senser SS49E
 1.Vcc, 2.GND, 3.Output
 */
byte sensor_pin = A0;
void setup() {
  Serial.begin(9600);
  pinMode(sensor_pin,INPUT); 
}

void loop() {
  Serial.println(analogRead(sensor_pin));
  delay(250);
}
