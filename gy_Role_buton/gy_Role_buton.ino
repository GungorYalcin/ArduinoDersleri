/*
 gungor 28/10/2017
 bit buton ile role acip/kapatma
 buton 1. pin arduino digital 3 pin, 2. pin arduino GND pin
 Role 1. pin VCC arduino +5v  Role 2. pin Gnd arduino GND
 Role 3. pin arduino digital 2 pin
 */
byte buton_pin = 3;
byte role_pin = 2; 
byte OldValue = 1;
byte NewValue = 1;
void setup() {
  pinMode(role_pin,OUTPUT);
  pinMode(buton_pin,INPUT_PULLUP);
  digitalWrite(role_pin,HIGH);
}
void loop() {
  NewValue = digitalRead(buton_pin);
  if (NewValue != OldValue)
  {
    OldValue = NewValue;
    if  (NewValue == LOW)
    {
      if (digitalRead(role_pin)==LOW)
      {  digitalWrite(role_pin,HIGH); }
      else
      { digitalWrite(role_pin,LOW); }
    }
  }
 delay(250);
}
