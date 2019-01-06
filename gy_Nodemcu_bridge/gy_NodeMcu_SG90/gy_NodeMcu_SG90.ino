/*
 * gungor 05/01/2019
 */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "2f4b091ac4f14158b49efb1e37ebcdcd";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Lavender";
char pass[] = "5335921602";


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
  bridge1.setAuthToken("6a0dbceb342d4d2797a87ac656bb6ad0"); // Place the AuthToken of the second hardware here
}
void blynkAnotherDevice() // Here we will send HIGH or LOW once per second
{
  if (ServoAci>90)
  {
    bridge1.digitalWrite(D1, LOW); 
    bridge1.virtualWrite(V5, ServoAci);
  }
  else
  {
    bridge1.digitalWrite(D1, HIGH);
  }

  if (ServoAci>150)
  {
    bridge1.digitalWrite(D2, LOW); 
    bridge1.virtualWrite(V5, ServoAci);
  }
  else
  {
    bridge1.digitalWrite(D2, HIGH);
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
