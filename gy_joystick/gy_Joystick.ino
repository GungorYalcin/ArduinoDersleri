/*
 * 20/06/2016 gungor joystick 
 */ 
const int button_pin = 10;
const int x_pin = 1;
const int y_pin = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(button_pin,INPUT);
  digitalWrite(button_pin,HIGH);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print (" Click: " );
  Serial.print (digitalRead(button_pin));
  Serial.print (" X: ");
  Serial.print (analogRead(x_pin));
  Serial.print (" Y: ");
  Serial.print (analogRead(y_pin));
  Serial.print ("\n");
  delay(500);
}
