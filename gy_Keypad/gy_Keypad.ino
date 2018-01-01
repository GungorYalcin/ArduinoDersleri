/*
gungor 4x4 KeyPad kullanımı
https://github.com/GungorYalcin/ArduinoDersleri/tree/master/Fritzing/KeyPad
https://github.com/GungorYalcin/ArduinoDersleri/tree/master/Library/KeyPad
keypad.zip kütüphane olarak eklemeniz gerekiyor

*/
#include <Keypad.h>
const byte satir = 4;
const byte sutun = 4;

char tus_tanim[satir][sutun] = {
{'1','2','3','A'},
{'3','4','5','B'},
{'6','7','8','C'},
{'*','0','#','D'}
};
byte satir_pin[satir] = {9,8,7,6};
byte sutun_pin[sutun] = {5,4,3,2};
Keypad tus_takimi = Keypad(makeKeymap(tus_tanim),satir_pin,sutun_pin,satir,sutun);
char tus;

void setup() {
 Serial.begin(9600);
}

void loop() {
  tus = tus_takimi.getKey();
  if (tus)
  { 
    Serial.println(tus);
    if (tus ==  '#') 
    {
      Serial.println("# basıldı");
    }
  }
   delay(100);
}
