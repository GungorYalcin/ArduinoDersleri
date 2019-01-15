/*
 * gungor 15/01/2019
*/
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

const int trigPin = D1;
const int echoPin = D2;
long sure =0;
int  mesafe=0;

// You should get Auth Token in the Blynk App.
char auth[] = "e0430f3213b34c858b64938eac23a410"; //YourToken
// Your WiFi credentials.
char ssid[] = "Lavender"; //YourNetworkName
char pass[] = "5335921602"; //YourPassword

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  digitalWrite(trigPin,LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  sure = pulseIn(echoPin,HIGH);
  //mesafe  = sure*0.34/2 / 10 ;   //cm
   mesafe = (sure/2) / 29.1;
  delayMicroseconds(200);  
  Blynk.virtualWrite(V1,mesafe);
  Serial.println(String("Mesafe=")+mesafe+ String(" cm"));
  Blynk.run();
}
