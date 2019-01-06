#define BLYNK_DEBUG
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>


char auth[] = "ceecb258c5ef4db085dbb24393ea131f";  // Put your Auth Token here. (see Step 3 above)


SimpleTimer timer;

#define I2C_SCL D5 //14      // D5 Barometric Pressure Sensor (BMP085)
#define I2C_SDA D6 //12      // D6

Adafruit_BMP085 bmp;

float dst, bt, bp, ba,bn;
char dstmp[20], btmp[20], bprs[20], balt[20];
bool bmp085_present = true;

void setup()
{
  Serial.begin(115200); // See the connection status in Serial Monitor
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
   }
  
  Blynk.begin(auth, "Lavender", "5335921602"); //insert here your SSID and password
  Wire.begin(I2C_SDA, I2C_SCL);
  timer.setInterval(3000L, sendUptime);
  
}

void sendUptime()
{
  
  float bp =  bmp.readPressure(); // basınc 
  Blynk.virtualWrite(10, bp); // virtual pin

  float ba =  bmp.readAltitude(); // rakım 
  Blynk.virtualWrite(11, ba); // virtual pin

  float bt =  bmp.readTemperature(); //sıcaklık 
  Blynk.virtualWrite(12, bt); // virtual pin

  float dst =  bmp.readSealevelPressure(); 
  Blynk.virtualWrite(13, dst); // virtual pin

  Serial.print("Temperature = ");
  Serial.print(bt);
  Serial.print(" C ");

  Serial.print(" Pressure = ");
  Serial.print(bp);
  Serial.print(" Pa ");
  
  Serial.print(" Altitude = ");
  Serial.print(ba);
  Serial.print(" M ");

  Serial.println("");
}

void loop()
{
  Blynk.run();
  timer.run();
 
}
