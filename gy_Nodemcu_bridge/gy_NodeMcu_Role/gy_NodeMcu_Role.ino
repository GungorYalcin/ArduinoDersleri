/*
 * gungor 06/01/2019
 */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "6a0dbceb342d4d2797a87ac656bb6ad0";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Lavender";
char pass[] = "5335921602";

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(D1,OUTPUT); //GPIO5
  pinMode(D2,OUTPUT); //GPIO4
  pinMode(D3,OUTPUT); //GPIO0
  pinMode(D4,OUTPUT); //GPIO2
  digitalWrite(D1,HIGH);
  digitalWrite(D2,HIGH);
  digitalWrite(D3,HIGH);
  digitalWrite(D4,HIGH);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}
