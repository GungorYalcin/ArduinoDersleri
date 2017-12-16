/*
 * gungor 16/12/2017
 * L298N , 2 adet DC motor, 2 joystick
 * 5 iler 5 geri vites
*/
byte joystick_AX_pin = A2;
byte joystick_BX_pin = A3;
byte L298N_A_pin = A0;
byte L298N_A_In1_pin = 2;
byte L298N_A_In2_pin = 3;
byte L298N_B_pin = A1;
byte L298N_B_In3_pin = 4;
byte L298N_B_In4_pin = 5;
int joystick_A_pos =0;
int joystick_B_pos =0;

void setup() {
  pinMode(joystick_AX_pin,INPUT);
  pinMode(joystick_BX_pin,INPUT);
  pinMode(L298N_A_pin,OUTPUT);
  pinMode(L298N_A_In1_pin,OUTPUT);
  pinMode(L298N_A_In2_pin,OUTPUT);
  pinMode(L298N_B_pin,OUTPUT);
  pinMode(L298N_B_In3_pin,OUTPUT);
  pinMode(L298N_B_In4_pin,OUTPUT);
  
  analogWrite(L298N_A_pin,0);
  digitalWrite(L298N_A_In1_pin,LOW);
  digitalWrite(L298N_A_In2_pin,LOW);
  analogWrite(L298N_B_pin,0);
  digitalWrite(L298N_B_In3_pin,LOW);
  digitalWrite(L298N_B_In4_pin,LOW);
  
  Serial.begin(9600);  
}

void loop() {
  joystick_A_pos = map(analogRead(joystick_AX_pin),0,1023,-5,+5);
  joystick_B_pos = map(analogRead(joystick_BX_pin),0,1023,-5,+5);
  Serial.println("");
  Serial.print("joystick_A_pos : ");
  Serial.print(joystick_A_pos);
   Serial.print(",joystick_B_pos : ");
  Serial.print(joystick_B_pos);
  
  if (joystick_A_pos > 0) {
    //1= 50, 2 = 100, 3=150,4=200, 5=250 motor hizi ileri
    analogWrite(L298N_A_pin,joystick_A_pos*50);
    digitalWrite(L298N_A_In1_pin,HIGH);
    digitalWrite(L298N_A_In2_pin,LOW);
  }
  else if (joystick_A_pos < 0)  {
    //-1= 50, -2 = 100, -3=150,-4=200, -5=250 motor hizi geri
    analogWrite(L298N_A_pin,joystick_A_pos*50*-1);
    digitalWrite(L298N_A_In1_pin,LOW);
    digitalWrite(L298N_A_In2_pin,HIGH);
  }
  else  {
    // motor stop
    digitalWrite(L298N_A_In1_pin,LOW);
    digitalWrite(L298N_A_In2_pin,LOW);
  }
  if (joystick_B_pos > 0) {
    //1= 50, 2 = 100, 3=150,4=200, 5=250 motor hizi ileri
    analogWrite(L298N_B_pin,joystick_B_pos*50);
    digitalWrite(L298N_B_In3_pin,HIGH);
    digitalWrite(L298N_B_In4_pin,LOW);
  }
  else if (joystick_B_pos < 0)  {
    //-1= 50, -2 = 100, -3=150,-4=200, -5=250 motor hizi geri
    analogWrite(L298N_B_pin,joystick_B_pos*50*-1);
    digitalWrite(L298N_B_In3_pin,LOW);
    digitalWrite(L298N_B_In4_pin,HIGH);
  }
  else  {
    // motor stop
    digitalWrite(L298N_B_In3_pin,LOW);
    digitalWrite(L298N_B_In4_pin,LOW);
  }

delay(100);  
}
