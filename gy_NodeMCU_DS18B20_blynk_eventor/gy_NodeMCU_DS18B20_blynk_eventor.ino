/*
 * gungor 12/01/2019
*/
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(D2); // digital D2 pin
DallasTemperature sensors(&oneWire);
BlynkTimer timer;
// You should get Auth Token in the Blynk App.
char auth[] = "ec1f2bcbcb9d4bc0a52bc4bfce1acc49";
// Your WiFi credentials.
char ssid[] = "Lavender";
char pass[] = "5335921602";

float  temp = 0;

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
 Serial.println(String("Sıcaklik=")+temp+ String(" C"));
 Blynk.virtualWrite(V1, temp);
}

void loop()
{
  Blynk.run();
  timer.run();
}
