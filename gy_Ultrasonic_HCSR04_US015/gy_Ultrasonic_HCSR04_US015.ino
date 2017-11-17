/*
Gungor 14/09/2016
https://www.youtube.com/watch?v=bhWYVS_Rhug
https://www.youtube.com/watch?v=ZejQOX69K5M
v=340 m/s    0,034 cm    0,34 mm 
*/
const int trigPin = 4;
const int echoPin = 5;
long sure =0;
int mesafe=0;

void setup (){
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 Serial.begin(9600); 
}

void loop () {
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  sure = pulseIn(echoPin,HIGH);
  mesafe  = sure*0.34/2;
 
  Serial.print ("sure:");
  Serial.print (sure);
  Serial.print ("  mesafe:");
  Serial.print (mesafe);
  Serial.print (" mm ");
  Serial.print (mesafe/10);
  Serial.println (" cm ");
  delay(250);
}
