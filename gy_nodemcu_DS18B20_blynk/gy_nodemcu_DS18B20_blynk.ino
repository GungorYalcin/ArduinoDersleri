#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(D2); // digital D2 pin
DallasTemperature sensors(&oneWire);
BlynkTimer timer;

char auth[] = "ceecb258c5ef4db085dbb24393ea131f";
char ssid[] = "Lavender";
char pass[] = "5335921602";

float SonMesaj = 0;
float SonEMail = 0;

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  sensors.begin();
// Setup a function to be called every second  
  timer.setInterval(1000L, sendTemps);
}

void sendTemps()
{
 sensors.requestTemperatures();
 float temp = sensors.getTempCByIndex(0);
 Serial.println(temp);
 Blynk.virtualWrite(V1, temp);
 
 /* uyari */
 if ( (temp > 30 ) && (millis() > SonMesaj+3000 ) )
 {
  SonMesaj = millis();
  Blynk.notify(String("Uyari ")+temp + String("C"));
 }
 /* Email */
 if ( (temp > 30 ) && (millis() > SonEMail+3000 ) )
 {
  SonEMail = millis();
  Blynk.email("gungor_yalcin68@Gmail.com","Blynk Deneme",String("Uyari ")+temp + String("C"));
 }
 
}
void loop()
{
  Blynk.run();
  timer.run();
//  sendTemps();
}
