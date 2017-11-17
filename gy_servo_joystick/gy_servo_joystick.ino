/*
 gungor 28/10/0217
 Servo motor(SG90)  ve Joystick kontrolu
 */
 #include <Servo.h>
 Servo sg90;
 int serve_pin = 9; //pwm pinleri
 byte x_joystick_pin = A0;
 int aci = 0;
 
void setup() {
  sg90.attach(serve_pin);
  pinMode(x_joystick_pin,INPUT);
  aci = map( analogRead(x_joystick_pin),0,1023,0,180);
  sg90.write(aci);
  delay(10);
}

void loop() {
  aci = map( analogRead(x_joystick_pin),0,1023,0,180);
  sg90.write(aci);
  delay(10);
}
