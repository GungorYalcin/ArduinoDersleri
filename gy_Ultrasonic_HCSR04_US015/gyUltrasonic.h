#ifndef Ultrasonic_H
#define Ultrasonic_H
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class Ultrasonic
{
  public:
    Ultrasonic(int TP, int EP);
    long Timing();
    long Ranging(int sys);

    private:
    int Trig_pin;
    int Echo_pin;
    long  duration,distacne_cm,distance_inc;
    
};

Ultrasonic::Ultrasonic(int TP, int EP)
{
   pinMode(TP,OUTPUT);
   pinMode(EP,INPUT);
   Trig_pin=TP;
   Echo_pin=EP;
}

long Ultrasonic::Timing()
{
  digitalWrite(Trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_pin, LOW);
  duration = pulseIn(Echo_pin,HIGH);
  return duration;
}

long Ultrasonic::Ranging(int sys)
{
  Timing();
  distacne_cm = duration /29 / 2 ;
  distance_inc = duration / 74 / 2;
  if (sys)
  return distacne_cm;
  else
  return distance_inc;
}

#endif