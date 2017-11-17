const int stepPin = 3;
const int dirPin = 4;
const int sure = 500;
const int sure2 = 500;
int Index;
void setup() {
  // put your setup code here, to run once:
// pinMode(6,OUTPUT);// enable
 pinMode(3,OUTPUT);// step
 pinMode(4,OUTPUT);// Direction
 pinMode(13, OUTPUT);
 
// digitalWrite(6,HIGH);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  
  digitalWrite(13,LOW);
  
  digitalWrite(dirPin,HIGH);
  delay(1000);
  
 for (Index=0; Index <2000; Index++)
 {
  digitalWrite(stepPin,HIGH);
  delayMicroseconds(sure);
  digitalWrite(stepPin,LOW);
  delayMicroseconds(sure2);
  }
  
  delay(1000);
  digitalWrite(13,HIGH);
  digitalWrite(dirPin,LOW);
  delay(1000);
  
 for (Index=0; Index <2000; Index++)
 {
  digitalWrite(stepPin,HIGH);
  delayMicroseconds(sure);
  digitalWrite(stepPin,LOW);
  delayMicroseconds(sure2);
  }
 
   delay(1000);
}
