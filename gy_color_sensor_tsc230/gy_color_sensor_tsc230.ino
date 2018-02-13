/*
 * gungor 13/02/2018
 * Renk sensoru
 */
#include <Servo.h>
const byte Led_pin = 3;  
const byte s0_pin = 5;
const byte s1_pin = 4;
const byte s2_pin = 7;
const byte s3_pin = 6;
const byte sensorout_pin = 8; 
const byte SG90_a_pin = 9;
const byte SG90_b_pin = 10;
const byte renk_tolarans = 2; 
int Red_color = 0;
int Blue_color = 0;
int Green_color = 0;
const byte maxSepet=6;
int sepet [maxSepet][3];
int sg90_a_aci [3] = {0,45,90};
int sg90_b_aci [6] = {0,25,50,75,100,125};

boolean buldu=false;
Servo sg90_a;
Servo sg90_b;

void setup() {
  pinMode(s0_pin,OUTPUT);
  pinMode(s1_pin,OUTPUT);
  pinMode(s2_pin,OUTPUT);
  pinMode(s3_pin,OUTPUT);
  pinMode(Led_pin,OUTPUT);

  pinMode(sensorout_pin,INPUT);
  
  // frequency-scaling %20
  digitalWrite(s0_pin,HIGH);
  digitalWrite(s1_pin,LOW);

  sg90_a.attach(SG90_a_pin);
  sg90_b.attach(SG90_b_pin);

  sg90_a.write(0);
  sg90_b.write(0);
  
  delay(10);
  for (int i =0; i<maxSepet; i++)
  {
    for (int j =0; i<4; j++)
    {
      sepet[i][j] =0;
    }
  }

  Serial.begin(9600);
}

void color_read()
{
  digitalWrite(Led_pin,HIGH);
  // Red filter
  digitalWrite(s2_pin,LOW);
  digitalWrite(s3_pin,LOW);
  Red_color = pulseIn(sensorout_pin,LOW);
  delay(100);

  // Green filter
  digitalWrite(s2_pin,HIGH);
  digitalWrite(s3_pin,HIGH);
  Green_color = pulseIn(sensorout_pin,LOW);
  delay(100);

  // Blue filter
  digitalWrite(s2_pin,LOW);
  digitalWrite(s3_pin,HIGH);
  Blue_color = pulseIn(sensorout_pin,LOW);
  delay(100);
  digitalWrite(Led_pin,LOW);
  if ((Red_color <0) && (Red_color >254 )) { Red_color = 0; }
  if ((Green_color <0)&& (Green_color >254) ) { Green_color = 0; }
  if ((Blue_color <0) && (Blue_color >254) ) { Blue_color = 0; }

  Serial.print("R:");
  Serial.print(Red_color);
  Serial.print(" G:");
  Serial.print(Green_color);
  Serial.print(" B:");
  Serial.println(Blue_color);
}

void loop() {
  sg90_a.write(sg90_a_aci[0]);
  delay(100);
  sg90_a.write(sg90_a_aci[1]);
  delay(100);
  color_read();
  
  if ( (Red_color > 0) && (Green_color > 0) && (Blue_color > 0) )
  {
    buldu = false;
    for (int i =0; i<maxSepet-1; i++)
    {
      if ( (sepet[i][0] => Red_color - renk_tolarans ) &&  (sepet[i][0] =< Red_color + renk_tolarans ) 
          (sepet[i][1] => Green_color - renk_tolarans ) &&  (sepet[i][1] =< Green_color + renk_tolarans )
          (sepet[i][2] => Blue_color - -renk_tolarans ) && (sepet[i][2] =< Blue_color + renk_tolarans ) )
      {
        buldu = true;
        sg90_b.write( sg90_b_aci[i]); 
        delay(100);
        sg90_a.write(sg90_a_aci[2]);
        break;
      }
      else
      if ( (sepet[i][0] == 0 ) && (sepet[i][0] == 0 ) && (sepet[i][0] == 0 ) )
      { // yeni bir renk geldi
        buldu = true;
        sg90_b.write( sg90_b_aci[i]); 
        delay(100);
        sg90_a.write(sg90_a_aci[2]);
        sepet[i][0] = Red_color;
        sepet[i][1] = Green_color;
        sepet[i][2] = Blue_color;
        break;
      }
   }
   //En son sepete atilacak
   if (buldu == false)
   {
    sg90_b.write(sg90_b_aci[5]); 
    delay(100);
    sg90_a.write(sg90_a_aci[2]);
   } 
  }
  delay(100);
}
