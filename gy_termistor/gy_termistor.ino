/*
 Gungor 10K termistör kullanımı
 +5V -- 10K termistor -- Arduino A0 -- 10K direnc -- GND 
 PTC sıcaklık artıkca direnci artar
 NTC sıcaklık artıkca direnci azalır
*/
#include <math.h>

double Thermistor(int RawADC) {
 double Temp;
 Temp = log(10000.0*((1024.0/RawADC-1))); 
//         =log(10000.0/(1024.0/RawADC-1)) // for pull-up configuration
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;            // Convert Kelvin to Celcius
 //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
 return Temp;
}

void setup() {
 Serial.begin(115200);
}

void loop() {
  Serial.println("");
  Serial.print("1.Termistor: ");
  Serial.print(int(Thermistor(analogRead(0))));  
  Serial.print(" C 2.Termistor: ");
  Serial.print(int(Thermistor(analogRead(1))));  
  Serial.println(" C");
  
 delay(500);
}

