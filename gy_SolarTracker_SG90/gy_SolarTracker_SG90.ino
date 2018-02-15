/*
* gungor 15/02/2018
 * günes takıp sistemi SolarTracker
 * 4 LDR, 2 SG90, 4 endStop, Arduino
*/
 #include <Servo.h>
 Servo sg90a;
 Servo sg90b;
 
const byte LDRPin[4] = {A1,A2,A3,A4};
const byte endStopPin[4] = {2,3,4,5};
const int servoa_pin = 9; //pwm 
const int servob_pin = 10; //pwm 

byte sg90a_pos;
byte sg90b_pos;

void setup() {
   for (int i =0; i<4; i++)
   {
      pinMode( LDRPin[i] , INPUT);
      pinMode( endStopPin[i] , INPUT_PULLUP);
   }
   sg90a.attach(servoa_pin);
   sg90b.attach(servob_pin);
   sg90a_pos = 90;
   sg90b_pos = 90;
   sg90a.write(sg90a_pos);
   sg90b.write(sg90b_pos);
   delay(10);
}   

void loop() {
  if (analogRead(LDRPin[0]) >  analogRead(LDRPin[2]) +5 )
  { // turn left Sola dön
     if (digitalRead(endStopPin[0]) == HIGH)
     {
       sg90a_pos = sg90a_pos -1;
       if (sg90a_pos <0) {sg90a_pos =0;}
       sg90a.write(sg90a_pos);
     }
  }
  if (analogRead(LDRPin[2]) >  analogRead(LDRPin[0]) +5 )
  { // turn left Sola dön
     if (digitalRead(endStopPin[2]) == HIGH)
     {
       sg90a_pos = sg90a_pos +1;
       if (sg90a_pos >180) {sg90a_pos =180;}
       sg90a.write(sg90a_pos);
     }
  }

  if (analogRead(LDRPin[1]) >  analogRead(LDRPin[3]) +5 )
  { // turn up yukari
     if (digitalRead(endStopPin[1]) == HIGH)
     {
       sg90b_pos = sg90b_pos -1;
       if (sg90b_pos <0) {sg90b_pos =0;}
       sg90b.write(sg90b_pos);
     }
  }
  
  if (analogRead(LDRPin[3]) >  analogRead(LDRPin[1]) +5 )
  { // turn down asagi
     if (digitalRead(endStopPin[3]) == HIGH)
     {
       sg90b_pos = sg90b_pos +1;
       if (sg90b_pos >180) {sg90b_pos =180;}
       sg90b.write(sg90b_pos);
     }
  }

  delay(100);
}

