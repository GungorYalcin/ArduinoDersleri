/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on NodeMCU.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right NodeMCU module
  in the Tools -> Board menu!

  For advanced settings please follow ESP examples :
   - ESP8266_Standalone_Manual_IP.ino
   - ESP8266_Standalone_SmartConfig.ino
   - ESP8266_Standalone_SSL.ino

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "134e85aa43f74efca573cb9e106ca61a";//"YourAuthToken";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Lavender"; //"YourNetworkName";
char pass[] = "5335921602"; //"YourPassword"

/*  gungor 03/05/2018 */
const int PinCLK = 2;
const int PinDT = 3; 
const int PinSW = 4; 
int sayac = 0;
int durum;
int sondurum;
BlynkTimer timer;


void myTimerEvent()
{
  Blynk.virtualWrite(V5, sayac);
}

void setup()
{
   pinMode(PinCLK,INPUT);
   pinMode(PinDT,INPUT);  
   pinMode(PinSW,INPUT);
   sondurum = digitalRead(PinCLK);
   
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
 timer.setInterval(1000L, myTimerEvent);  
}

void loop()
{
  if (digitalRead(PinSW)==LOW)
  { sayac =0;  }
  durum = digitalRead(PinCLK);
  if (durum != sondurum){
    if (digitalRead(PinDT) !=durum)    {
      sayac ++;
    } else {
      sayac --;
    }
    Serial.print("Sayac:");
    Serial.println(sayac);
    Blynk.virtualWrite(V5, sayac);
  }
  sondurum = durum;

  Blynk.run();
 timer.run(); // Initiates BlynkTimer  
}

