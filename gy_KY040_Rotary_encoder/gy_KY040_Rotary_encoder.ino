/*
 * gungor 03/05/2018
*/
const int PinCLK = 2;
const int PinDT = 3; 
const int PinSW = 4; 
int sayac = 0;
int durum;
int sondurum;

void setup() {
   pinMode(PinCLK,INPUT);
   pinMode(PinDT,INPUT);  
   pinMode(PinSW,INPUT);
   Serial.begin (9600);
   sondurum = digitalRead(PinCLK);
}

void loop() {
  if (digitalRead(PinSW)==LOW)
  {
    sayac =0;
    Serial.print("Sayac: ");
    Serial.println(sayac);
 }
  durum = digitalRead(PinCLK);
  if (durum != sondurum){
    if (digitalRead(PinDT) !=durum)    {
      sayac ++;
    } else {
      sayac --;
    }
    Serial.print("Sayac: ");
    Serial.println(sayac);
  }
  sondurum = durum;
  
}
