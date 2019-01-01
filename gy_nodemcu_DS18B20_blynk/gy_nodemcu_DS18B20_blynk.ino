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

float  temp = 0;
float SonMesaj = 0;
float SonEMail = 0;
int MesajGonder = 0;
int EMailGonder = 0;

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
 temp = sensors.getTempCByIndex(0);
 Serial.println(String("Sıcaklik=")+temp+ String(" C Uyari=")+MesajGonder+String(" EMail=")+EMailGonder);
 Blynk.virtualWrite(V1, temp);

 
}

BLYNK_READ(V2)
{
  Blynk.virtualWrite(V2,MesajGonder);
}
BLYNK_READ(V3)
{
  Blynk.virtualWrite(V3,EMailGonder);
}

BLYNK_WRITE(V2)
{
  MesajGonder = param.asInt(); 
}

BLYNK_WRITE(V3)
{
  EMailGonder = param.asInt(); 
}

void loop()
{
  Blynk.run();
  timer.run();
 /* uyari */
 if ( (MesajGonder==true) &&  (temp > 30 ) && (millis() > SonMesaj+3000 ) )
 {
  SonMesaj = millis();
  Blynk.notify(String("Uyari ")+temp + String("C"));
 }
 /* Email */
 if ( (EMailGonder==true)  && (temp > 30 ) && (millis() > SonEMail+3000 ) )
 {
  SonEMail = millis();
  Blynk.email("gungoryalcin68@Gmail.com","Blynk Deneme",String("Uyari ")+temp + String("C"));
 }

}
