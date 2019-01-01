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
  if (analogRead(LDRPin[0]) >  analogRead(LDRPin[2]) +5 )
  { // turn left Sola dön
    digitalWrite(dirPin[0],LOW);
    delay(1000);
    
    for (int Index=0; Index <200; Index++)
    {
      if (digitalRead(endStopPin[0]) == HIGH)
      {
       digitalWrite(stepPin[0],HIGH);
       delayMicroseconds(sure);
       digitalWrite(stepPin[0],LOW);
       delayMicroseconds(sure);
      }
      else
      {
        if (digitalRead(endStopPin[0]) == LOW)
          break;
      }
    }
  }
  if (analogRead(LDRPin[2]) >  analogRead(LDRPin[0]) +5 )
  { // turn right saga dön
    digitalWrite(dirPin[0],HIGH);
    delay(1000);
    
    for (int Index=0; Index <200; Index++)
    {
      if (digitalRead(endStopPin[2]) == HIGH)
      {
       digitalWrite(stepPin[0],HIGH);
       delayMicroseconds(sure);
       digitalWrite(stepPin[0],LOW);
       delayMicroseconds(sure);
      }
      else
      {
        if (digitalRead(endStopPin[2]) == LOW)
          break;
      }
    }
  }

  if (analogRead(LDRPin[1]) >  analogRead(LDRPin[3]) +5 )
  { // Up Yukarı
    digitalWrite(dirPin[1],LOW);
    delay(1000);
    
    for (int Index=0; Index <200; Index++)
    {
      if (digitalRead(endStopPin[1]) == HIGH)
      {
       digitalWrite(stepPin[0],HIGH);
       delayMicroseconds(sure);
       digitalWrite(stepPin[0],LOW);
       delayMicroseconds(sure);
      }
      else
      {
        if (digitalRead(endStopPin[1]) == LOW)
          break;
      }
    }
  }

  if (analogRead(LDRPin[3]) >  analogRead(LDRPin[1]) +5 )
  { // Down Aşağı
    digitalWrite(dirPin[1],HIGH);
    delay(1000);
    
    for (int Index=0; Index <200; Index++)
    {
      if (digitalRead(endStopPin[3]) == HIGH)
      {
       digitalWrite(stepPin[0],HIGH);
       delayMicroseconds(sure);
       digitalWrite(stepPin[0],LOW);
       delayMicroseconds(sure);
      }
      else
      {
        if (digitalRead(endStopPin[3]) == LOW)
          break;
      }
    }
  }
  delay(100);
 
}
