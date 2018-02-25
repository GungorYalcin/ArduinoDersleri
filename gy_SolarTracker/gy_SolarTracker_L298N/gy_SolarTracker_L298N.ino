/*
 * gungor 15/02/2018
 * günes takıp sistemi SolarTracker
 * 4 LDR, L298N, 2 DC motor 4 endStop, Arduino
*/
const byte LDRPin[4] = {A1,A2,A3,A4};
const byte endStopPin[4] = {7,8,9,10};
const byte L298N_A_pin = A0;
const byte L298N_A_In1_pin = 2;
const byte L298N_A_In2_pin = 3;
const byte L298N_B_pin = A1;
const byte L298N_B_In3_pin = 4;
const byte L298N_B_In4_pin = 5;

void setup() {
   for (int i =0; i<4; i++)
   {
      pinMode( LDRPin[i] , INPUT);
      pinMode( endStopPin[i] , INPUT_PULLUP);
   }
  pinMode(L298N_A_pin,OUTPUT);
  pinMode(L298N_A_In1_pin,OUTPUT);
  pinMode(L298N_A_In2_pin,OUTPUT);
  pinMode(L298N_B_pin,OUTPUT);
  pinMode(L298N_B_In3_pin,OUTPUT);
  pinMode(L298N_B_In4_pin,OUTPUT);
  stopMotor_a();
  stopMotor_b();
}

void stopMotor_a()
{
  analogWrite(L298N_A_pin,0);
  digitalWrite(L298N_A_In1_pin,LOW);
  digitalWrite(L298N_A_In2_pin,LOW);
}

void stopMotor_b()
{
  analogWrite(L298N_B_pin,0);
  digitalWrite(L298N_B_In3_pin,LOW);
  digitalWrite(L298N_B_In4_pin,LOW);
}
void turnleft()
{
   analogWrite(L298N_A_pin,255);
   digitalWrite(L298N_A_In1_pin,HIGH);
   digitalWrite(L298N_A_In2_pin,LOW);
   delay(100);  
}

void turnright()
{
   analogWrite(L298N_A_pin,255);
   digitalWrite(L298N_A_In1_pin,LOW);
   digitalWrite(L298N_A_In2_pin,HIGH);
   delay(100);  
}

void turnup()
{
   analogWrite(L298N_B_pin,255);
   digitalWrite(L298N_B_In3_pin,HIGH);
   digitalWrite(L298N_B_In4_pin,LOW);
   delay(100);  
}

void turndown()
{
   analogWrite(L298N_B_pin,255);
   digitalWrite(L298N_B_In3_pin,LOW);
   digitalWrite(L298N_B_In4_pin,HIGH);
   delay(100);  
}

void loop() {
  if (analogRead(LDRPin[0]) >  analogRead(LDRPin[2]) +5 )
  { // turn left Sola dön
    stopMotor_b();
    if (digitalRead(endStopPin[0]) == HIGH)
    {
      turnleft();
    }
    stopMotor_a();
  }

  if (analogRead(LDRPin[2]) >  analogRead(LDRPin[0]) +5 )
  { // turn right Sola dön
    stopMotor_b();
    if (digitalRead(endStopPin[2]) == HIGH)
    {
      turnright();
    }
    stopMotor_a();
  }

  if (analogRead(LDRPin[1]) >  analogRead(LDRPin[3]) +5 )
  { // turn up yukarı
    stopMotor_a();
    if (digitalRead(endStopPin[1]) == HIGH)
    {
      turnup();
    }
    stopMotor_b();
  }
  if (analogRead(LDRPin[3]) >  analogRead(LDRPin[1]) +5 )
  { // turn down asagi
    stopMotor_a();
    if (digitalRead(endStopPin[3]) == HIGH)
    {
      turndown();
    }
    stopMotor_b();
  }

  delay(100);  
}
