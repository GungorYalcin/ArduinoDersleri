/*
 * gungor 06/01/2019
 */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "91e0da2abb3f4d2d879500979527bcc9";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "lavender";
char pass[] = "5393789681";

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
