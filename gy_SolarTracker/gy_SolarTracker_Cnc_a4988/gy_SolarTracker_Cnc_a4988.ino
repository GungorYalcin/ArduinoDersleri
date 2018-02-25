/*
 * gungor 15/02/2018
 * günes takıp sistemi SolarTracker
 * 4 LDR, 2 A4988, 2 Step Motor, 4 endStop, Arduino, CNC shied
*/
const byte stepPin[2] = {3,5};
const byte dirPin[2] = {4,6};
const byte LDRPin[4] = {A1,A2,A3,A4};
const byte endStopPin[4] = {7,8,9,10};
const int sure = 500;

void myStep(boolean Dir,int dirPin, int stepPin,int step)
{
  // motor yönü değişitor
  if (digitalRead(dirPin) != Dir)
  {
    digitalWrite(dirPin,Dir);
    delay(1000);
  }
  for (int Index=0; Index <step; Index++)
  {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(sure);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(sure);
  }
}

void setup() {
   for (int i =0; i<2; i++)
   {
     pinMode( stepPin[i] , OUTPUT);
     pinMode( dirPin[i] , OUTPUT);
   }
   for (int i =0; i<4; i++)
   {
      pinMode( LDRPin[i] , INPUT);
      pinMode( endStopPin[i] , INPUT_PULLUP);
   }
}

void loop() {
  if ( (analogRead(LDRPin[0]) >  analogRead(LDRPin[2]) +5 ) && (digitalRead(endStopPin[0]) == HIGH) )
  { // turn left Sola dön
     myStep(LOW,dirPin[0],stepPin[0],50); // motor 50 step 
  }
  if ( (analogRead(LDRPin[2]) >  analogRead(LDRPin[0]) +5 )  && (digitalRead(endStopPin[2]) == HIGH) )
  { // turn right saga dön
      myStep(HIGH,dirPin[0],stepPin[0],50); // motor 50 step
  }

  if ( (analogRead(LDRPin[1]) >  analogRead(LDRPin[3]) +5 ) && (digitalRead(endStopPin[1]) == HIGH) )
  { // Up Yukarı
    myStep(LOW,dirPin[1],stepPin[1],50); // motor 50 step 
  }
  if ( (analogRead(LDRPin[3]) >  analogRead(LDRPin[1]) +5 ) && (digitalRead(endStopPin[3]) == HIGH) )
  { // Down Aşağı
    myStep(HIGH,dirPin[1],stepPin[1],50); // motor 50 step 
  }
  delay(100);
 
}
