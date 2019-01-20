/*
 * gungor 20/01/2019
*/
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
char auth[] = "e0430f3213b34c858b64938eac23a410"; //YourToken
// Your WiFi credentials.
char ssid[] = "lavender"; //YourNetworkName
char pass[] = "5393789681"; //YourPassword
BlynkTimer timer;
const byte L298N_A_pin = D1; // GPIO5
const byte L298N_A_In1_pin = D2; // GPIO4
const byte L298N_A_In2_pin = D3; // GPIO0
const byte L298N_B_pin = D4; // GPIO2
const byte L298N_B_In3_pin = D5; //GPIO14
const byte L298N_B_In4_pin = D6; //GPIO12
const byte Led1_pin =  D7; //GPIO13  // Sol Sinyal
const byte Led2_pin =  D8; //GPIO15  // On Far
const byte Led3_pin =  D9; //GPIO3   // Arka Lamba
const byte Led4_pin = D10; //GPI01   // Sag Sinyal
const byte Korna_pin = D0; //GPI016  //Korna

WidgetLED led1(V1);
WidgetLED led2(V2);
WidgetLED led3(V3);
WidgetLED led4(V4);

byte SolSinyal = 0;
byte SagSinyal = 0;
byte ArkaLamba = 0;
/*
 * blynk ekranı
 * V0 joystick,  
 * v1,v2, v3, v4 Led  
 * v5  button push
 * v6 button switch
 * v7 gauge
*/

BLYNK_WRITE(V5) {
/* Korna*/  
  digitalWrite(Korna_pin,param.asInt());
}

BLYNK_WRITE(V6) {
/* On Far*/  
  digitalWrite(Led2_pin,param.asInt());
}

void motorSpeed(byte prmA, byte prmA1, byte prmA2, byte prmB, byte prmB1, byte prmB2)
{
  analogWrite(L298N_A_pin,prmA);
  digitalWrite(L298N_A_In1_pin,prmA1);
  digitalWrite(L298N_A_In2_pin,prmA2);
  analogWrite(L298N_A_pin,prmB);
  digitalWrite(L298N_B_In3_pin,prmB1);
  digitalWrite(L298N_B_In4_pin,prmB2);
  if ((prmA==0) && (prmB==0))
  {
    Blynk.virtualWrite(V7,0);
  }
   else if ((prmA==250) && (prmB==250))
  {
    Blynk.virtualWrite(V7,80);
  }
  else
  {
    Blynk.virtualWrite(V7,40);
  }
}


BLYNK_WRITE(V0) {
  int x = param[0].asInt();
  int y = param[1].asInt();
// x =  -2 -1 0 1 2 
// Y =  -2 -1 0 1 2 
 if (y>=0)
 {
  ArkaLamba = 0;
 }
 else
 {
  ArkaLamba = 1;
  SolSinyal = 1;
  SagSinyal = 1;
   digitalWrite(Led1_pin,HIGH);
   digitalWrite(Led4_pin,HIGH);
 }
 
 if ((x==0) && (y==0)) // duruyor
 {
   motorSpeed(0,LOW,LOW,0,LOW,LOW); 
   SolSinyal = 0;
   SagSinyal = 0;
   digitalWrite(Led1_pin,LOW);
   digitalWrite(Led4_pin,LOW);
 }
 else if ((x==0) && (y>0)) // düz ileri 
 {
  if (y==1){ motorSpeed(200,HIGH,LOW,200,HIGH,LOW); }
  else { motorSpeed(250,HIGH,LOW,250,HIGH,LOW); }
  SolSinyal = 0;
  SagSinyal = 0;
  digitalWrite(Led1_pin,LOW);
  digitalWrite(Led4_pin,LOW);
 }
 else if ((y==0) && (x>0))// Tam Sag donuş
 { 
  motorSpeed(200,HIGH,LOW,200,LOW,HIGH); 
  SagSinyal = 1;
  digitalWrite(Led4_pin,HIGH);
  }
 else if ((y>0) && (x>0))// Sag donuş
 {  
  motorSpeed(250,HIGH,LOW,200,HIGH,LOW); 
  SagSinyal = 1;
  digitalWrite(Led4_pin,HIGH);
  }
 else if ((y==0) && (x<0))// Tam sola donuş
 { 
  motorSpeed(200,LOW,HIGH,200,HIGH,LOW); 
  SolSinyal = 1;
  digitalWrite(Led1_pin,HIGH);
  }
 else if ((y>0) && (x>0))// Sola donuş
 {   
  motorSpeed(200,LOW,HIGH,250,LOW,HIGH); 
  SolSinyal = 1;
  digitalWrite(Led1_pin,HIGH);
  }
 else if ((y<0) && (x<0))// Sola geri
 {   motorSpeed(200,LOW,HIGH,250,LOW,HIGH); }
 else if ((y<0) && (x<0))// Sag geri
 {   motorSpeed(250,LOW,HIGH,200,LOW,HIGH); }
 else if ((y<0) && (x==0))// tam geri
 {   
    motorSpeed(200,LOW,HIGH,200,LOW,HIGH); 
 }

}

void setup() {
  Serial.begin(115200);
  pinMode(L298N_A_pin,OUTPUT);
  pinMode(L298N_A_In1_pin,OUTPUT);
  pinMode(L298N_A_In2_pin,OUTPUT);
  pinMode(L298N_B_pin,OUTPUT);
  pinMode(L298N_B_In3_pin,OUTPUT);
  pinMode(L298N_B_In4_pin,OUTPUT);

 digitalWrite(L298N_A_pin,LOW);
 digitalWrite(L298N_A_In1_pin,LOW);
 digitalWrite(L298N_A_In2_pin,LOW);
 digitalWrite(L298N_B_pin,LOW);
 digitalWrite(L298N_B_In3_pin,LOW);
 digitalWrite(L298N_B_In4_pin,LOW);

  pinMode(Led1_pin,OUTPUT);
  pinMode(Led2_pin,OUTPUT);
  pinMode(Led3_pin,OUTPUT);
  pinMode(Led4_pin,OUTPUT);

  digitalWrite(Led1_pin,LOW);
  digitalWrite(Led2_pin,LOW);
  digitalWrite(Led3_pin,LOW);
  digitalWrite(Led4_pin,LOW);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendTemps);
}
void sendTemps()
{
  if (SolSinyal==1)
    digitalWrite(Led1_pin,!digitalRead(Led1_pin));

  if (SagSinyal==1)
    digitalWrite(Led4_pin,!digitalRead(Led4_pin));

  if (ArkaLamba==1)
    digitalWrite(Led3_pin,!digitalRead(Led3_pin));

  if (digitalRead(Led1_pin)==HIGH)
    led1.on();
  else
    led1.off();

  if (digitalRead(Led2_pin)==HIGH)
    led2.on();
  else
    led2.off();

  if (digitalRead(Led3_pin)==HIGH)
    led3.on();
  else
    led3.off();

  if (digitalRead(Led4_pin)==HIGH)
    led4.on();
  else
    led4.off();
    

  //Blynk.virtualWrite(V1,digitalRead(Led1_pin));
  //Blynk.virtualWrite(V2,digitalRead(Led2_pin));
  //Blynk.virtualWrite(V3,digitalRead(Led3_pin));
  //Blynk.virtualWrite(V4,digitalRead(Led4_pin));
}


void loop() {
  Blynk.run();
  timer.run();
}
