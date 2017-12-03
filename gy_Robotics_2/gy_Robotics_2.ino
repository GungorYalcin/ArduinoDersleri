/*
 gungor 03/12/2017
 6 eksenli robot kol / 6 axis robotics arm
 Arduino Mega PWM pin D2..D13, D44..D46
 */
#include <Servo.h>
Servo sg90_0;
Servo sg90_1;
Servo sg90_2;
Servo sg90_3;
Servo sg90_4;
Servo sg90_5;
const byte motorcount = 6;
 
byte servoPin[motorcount] = {2,3,4,5,6,7}; //PWM pins
byte potPin[motorcount] = {A0,A1,A2,A3,A4,A5};
byte servoAngleMinMax [motorcount][2] = { {0,180},{0,180},{0,180},{0,180}, {0,180},{0,180} };
int pot_calibration[motorcount] = {0,0,0,0,0,0};
int angle_calibration[motorcount] = {0,0,0,0,0,0};
int pot_value[motorcount] = {0,0,0,0,0,0};
int angle_value[motorcount] = {0,0,0,0,0,0};



void pot_read(){
  for (int i=0; i<motorcount; i++)
  {
    pot_value[i] = analogRead(potPin[i]);
    pot_value[i] = pot_value[i] + pot_calibration[i]; // potansiyometre kaydirmasi
    if (pot_value[i] > 1023){
      pot_value[i] = 1023;
    }
    if (pot_value[i] < 0){
      pot_value[i] = 0;
    }
  }
}
void angle_kontrol() {
  // her servo icin belirledigimiz min,max aci degerleri arasındami kontrolu
  for (int i=0; i<motorcount; i++)
  {
   angle_value[i] =  map( pot_value[i],0,1023,0,180);
   angle_value[i] = angle_value[i] + angle_calibration[i];//aci kaydirmasi
   if (servoAngleMinMax[i][0] > angle_value[i])
   {
    angle_value[i] = servoAngleMinMax[i][0]; // min aci degeri
   } 
   if (servoAngleMinMax[i][1] < angle_value[i])
   {
    angle_value[i] = servoAngleMinMax[i][1]; // max aci degeri
   } 
  }  
}
void servo_kontrol(){
  // servor motorları pozisyonuna gitmesi
  Serial.println("");
  Serial.println("");
  for (int i=0; i<6; i++)  {
    Serial.print(i);
    Serial.print(".Pot: ");
    Serial.print(pot_value[i]);
    Serial.print(" , ");
  }
  Serial.println("");
  for (int i=0; i<6; i++){
    Serial.print(i);
    Serial.print(".Angel: ");
    Serial.print(angle_value[i]);
    Serial.print(" , ");
  }
  sg90_0.write(angle_value[0]); 
  sg90_1.write(angle_value[1]);
  sg90_2.write(angle_value[2]); 
  sg90_3.write(angle_value[3]); 
  sg90_4.write(angle_value[4]); 
  sg90_5.write(angle_value[5]); 
  delay(10);
}

void setup() {
  Serial.begin(9600);  
  sg90_0.attach(servoPin[0]);
  sg90_1.attach(servoPin[1]);
  sg90_2.attach(servoPin[2]);
  sg90_3.attach(servoPin[3]);
  sg90_4.attach(servoPin[4]);
  sg90_5.attach(servoPin[5]);
  for (int i=0; i<angle_value; i++)  {
    pinMode(potPin[i],INPUT);
  }

}
void loop() {
  pot_read();
  angle_kontrol();
  servo_kontrol();
  delay(100);
}
