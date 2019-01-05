/*
 * gungor 05/01/2019
 */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "23c6d34a767f42059f4ade1ca7a96fa3";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "lavender";
char pass[] = "5393789681";


int ServoAci = 0;
Servo servo;
WidgetBridge bridge1(V2);
BlynkTimer timer;

BLYNK_WRITE(V1)
{
  ServoAci = param.asInt();
  servo.write(ServoAci);
}

BLYNK_CONNECTED() {
  bridge1.setAuthToken("91e0da2abb3f4d2d879500979527bcc9"); // Place the AuthToken of the second hardware here
}
void blynkAnotherDevice() // Here we will send HIGH or LOW once per second
{
  if (ServoAci>90)
  {
    bridge1.digitalWrite(D1, LOW); 
  }
}
void setup()
{
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  servo.attach(D1); 
  timer.setInterval(1000L, blynkAnotherDevice); 
}

void loop()
{
  Blynk.run();
  timer.run();
}
