/*
gungor 13/11/2017
 4 role 4 buton ile role kullanımı
*/
const byte ilkButtonPin = 1; //digital 1,2,3,4
const byte ilkRolePin = 5; // digital 5,6,7,8
const byte maxButon = 4;
byte RolePin [maxButon];
byte ButonPin [maxButon];
byte OldValue [maxButon];
byte NewValue;

void setup () {
    for (int i =0; i<maxButon; i++)
    {
      RolePin[i] = i + ilkRolePin;
      pinMode( RolePin[i] , OUTPUT);
      digitalWrite(RolePin[i], HIGH); // role stop
      ButonPin[i] = i + ilkButtonPin;
      pinMode( ButonPin[i] , INPUT_PULLUP);
      OldValue[i] = HIGH;
    }
}

void loop() {
    for (int i =0; i<maxButon; i++)
    {
      NewValue = digitalRead(ButonPin[i]);
      if (NewValue != OldValue[i] )
      {
          OldValue[i] = NewValue;
          if (NewValue == LOW)
         {
           if (digitalRead(RolePin[i]) == LOW)
           { digitalWrite(RolePin[i],HIGH);  }
           else
           { digitalWrite(RolePin[i],LOW); }
         }
      }
    }  
  
  delay(100); 
}
