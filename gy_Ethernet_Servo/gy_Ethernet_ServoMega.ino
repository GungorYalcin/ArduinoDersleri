/*
 gungor 13/08/2017
*/
#include <SPI.h>
#include <EEPROM.h> 
#include <EtherCard.h> // EtherCard kütüphanesini ekliyoruz.
#include <avr/wdt.h>

const String Versiyon =  "1.17.9.25.22.19";
#define TIMEOUT_MS 10000; 

static byte MotorPos;
const byte ileri = 1; /* Motorun ileri dogru donmesi icin */
const byte geri = 0; /* Motorun geri dogru donmesi icin */

int motorYonu;
boolean sonsuzdon;

static byte KartID;
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

static byte myip[] = { 192,168,68,51 }; /*KartID göre degişiyor*/
const static uint8_t gwip[] = {192,168,68,15}; 
const static uint8_t dnsip[] = {192,168,68,15};  
const static uint8_t netmask[] = {255,255,255,0}; 
byte hisip[] = {192,168,68,15 };

Stash stash;
byte session;
const char website[] PROGMEM = "192.168.68.15";
/* 198.211.121.13 */

byte Ethernet::buffer[300];
static uint32_t GecenSure = 0;

/* 
Enc28j60  Arduino Mega
CS  --> 53  
SI  --> 51
SO  --> 50
SCK --> 52
VCC --> 3.3V
GND --> GND 
*/

/* Pinleri */
const int switchPowerPin_1= 2;//2 nano ;   
const int switchPin_1= 5;// 5 nano;  
const int switchPowerPin_2= 4;//4 nano ; 
const int switchPin_2= 3;//3 nano; 

const int MotorGnd= 6;
const int MotorPin= 7;
const int MotorDirPin= 8;

void setup () {
  Serial.begin(57600); //Seri iletişimi başlatıyoruz. 

  pinMode (switchPowerPin_1,OUTPUT);
  digitalWrite(switchPowerPin_1,HIGH);
  pinMode (switchPin_1,INPUT);
  
  pinMode (switchPowerPin_2,OUTPUT);
  digitalWrite(switchPowerPin_2,HIGH);
  pinMode (switchPin_2,INPUT);
  
  pinMode (MotorPin,OUTPUT);
  pinMode (MotorDirPin,OUTPUT);
  pinMode (MotorGnd,OUTPUT);
  digitalWrite(MotorGnd,LOW);
  
   KartID = EEPROM.read(0);
  if ( (KartID==0) || (KartID==255) )
  {
    KartID = 100;
    EEPROM.write(0,KartID);
  }
  MotorPos  = EEPROM.read(1);
  if (MotorPos>100) {
    MotorPos =100;
    EEPROM.write(1,MotorPos);
  }
  
    /* Kart ID göre IP ve MAC adresleri oluşturuldu*/
  myip[3] = KartID; // 192.168.2.?
  mymac[5] = KartID; // 0x74,0x69,0x69,0x2D,0x30,???

  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0)
    Serial.println( "Ethernet denetleyicisine erisim saglanamadi.");
 else
   Serial.println("Ethernet denetleyicisi baslatildi.");
   
if (!ether.staticSetup(myip,gwip, dnsip, netmask))
    Serial.println("Sabit IP atama islemi yapilamadi.");
    
  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);  
  ether.printIp("DNS: ", ether.dnsip);  
//  char websiteIP[] = "192.168.68.15";
//  ether.parseIp(ether.hisip, websiteIP);
   ether.copyIp(ether.hisip, hisip);

  ether.printIp("SRV: ", ether.hisip);
    
    
  Serial.println();
  /*Serial.print("******** Ver: ");*/
  Serial.println(Versiyon);
/*  Serial.println(" ********");*/

  Serial.print("Kart ID:");
  Serial.println(KartID);
  Serial.print("IP :");
  for (int i =0; i<4; i++)
  {
    Serial.print(ether.myip[i]);
    Serial.print(".");
  }
/*  Serial.println("");
  Serial.print("GW :");
  for (int i =0; i<4; i++)
  {
    Serial.print(ether.gwip[i]);
    Serial.print(".");
  }
*/
  digitalWrite(MotorPin,LOW);
  if (MotorPos < 100) 
  { motorYonu = ileri;  }
  else
  { motorYonu =geri;  }
  digitalWrite(MotorDirPin,motorYonu);
  yaz_posisyon();

/*  Serial.println("***************************");  */
}

String veri ="";
String veri2 ="";
int fark;
double sayac;

char inChar;
void yaz_posisyon()
{
 /*
 Serial.println("");
     Serial.print("Motor pos:");
     Serial.print( EEPROM.read(1) );
     Serial.print(" S1: ");
     Serial.print( digitalRead(switchPin_1) );
     Serial.print(" S2: ");
     Serial.print(digitalRead(switchPin_2) );
    Serial.print(" Motor Yonu: ");
  if (motorYonu == ileri)
  { Serial.println("ileri");}
  else
  {Serial.println("Geri");}
     
   Serial.println("");
*/   
}

void MotorSur(int pos)
{
  sonsuzdon = false;
  fark =0;
  if (MotorPos !=  pos) 
  {
//   Serial.println(pos);
    if ( (MotorPos<100) && (pos > MotorPos) )
    {
      motorYonu = ileri;
      fark = pos - MotorPos;
//      Serial.println(" A ");
    }

    if ( (MotorPos >0) && ( MotorPos > pos) )
    {
      motorYonu =geri;
      fark = MotorPos - pos;
//      Serial.println(" B ");
    }
    if (pos==0)
    {  
       motorYonu =geri; 
       sonsuzdon = true;
//       Serial.println(" C ");
     }
    if (pos==100)
    { 
      motorYonu =ileri; 
      sonsuzdon = true;
//      Serial.println(" D ");
    }
    digitalWrite(MotorDirPin,motorYonu);
    
    /* posisyonu 0 veya 100 olmasi istendi */
    if (sonsuzdon)
    {
//      Serial.println(" Sonsuzdongu ");
      sayac =0;
      while (sonsuzdon)
      {
          digitalWrite(MotorPin,LOW);
          delayMicroseconds(200); 
          for (int i =0; i<200; i++)
          {
             digitalWrite(MotorPin,HIGH);
             delayMicroseconds(100); 
             digitalWrite(MotorPin,LOW);
             delayMicroseconds(100); 
          }
          if ((motorYonu ==geri) && (digitalRead(switchPin_1)==0))
          {
            delayMicroseconds(100); 
            if (digitalRead(switchPin_1)==0)
            {
               sonsuzdon = false; 
               MotorPos = 0;
               EEPROM.write(1,MotorPos);
               break;
            }
           }
           
          if ((motorYonu ==ileri) && (digitalRead(switchPin_2)==0) )
          {
            delayMicroseconds(100); 
            if (digitalRead(switchPin_2)==0) 
            {
              sonsuzdon = false; 
              MotorPos = 100;
              EEPROM.write(1,MotorPos);
              break;
            }
          }
          sayac = sayac +100;
//          Serial.print("Sayac:");
//          Serial.println(sayac);
          
      } /*while (sonsuzdon)*/
     yaz_posisyon(); 
    } /*if (sonsuzdon) */
    else
    {
/*      
      Serial.print(" Fark :");
      Serial.print(fark);
      Serial.print(" S1:");
      Serial.print(digitalRead(switchPin_1));
      Serial.print(" S2: ");
      Serial.print(digitalRead(switchPin_2));
      Serial.println("");
      Serial.print(" Motor Yonu:");
      if (motorYonu == ileri) 
      { Serial.print(" ileri");}
      if (motorYonu == geri) 
      { Serial.print(" geri");}
      Serial.println("");
*/      
      fark = (fark * 2);
     /* %1 icin kac pulse olmasi gerekiyor*/
    for (int j=0; j < (fark); j++)
    {
       if ( ( (digitalRead(switchPin_1)==0) && (motorYonu == ileri) ) || 
            ( (digitalRead(switchPin_2)==0) && (motorYonu == geri) ) || 
            ( (digitalRead(switchPin_1)==1) && (digitalRead(switchPin_2)==1) ) 
          )
       {   
//         Serial.println(" 200 pulse yapacak");
          digitalWrite(MotorPin,LOW);
          delayMicroseconds(200); 
          for (int i =0; i<200; i++)
          {
             digitalWrite(MotorPin,HIGH);
             delayMicroseconds(100); 
             digitalWrite(MotorPin,LOW);
             delayMicroseconds(100); 
          }
       }

       if ((motorYonu ==geri) && (digitalRead(switchPin_1)==0) )
       {
         delayMicroseconds(100); 
         if (digitalRead(switchPin_1)==0)
         {
//           Serial.println(" 200 pulse ta S1  0 oldu");
           MotorPos = 0;
           EEPROM.write(1,MotorPos);
           break;
         }
       }
       else if ((motorYonu ==ileri) && (digitalRead(switchPin_2)==0) )
       {
         delayMicroseconds(100); 
         if (digitalRead(switchPin_2)==0)
         {
//           Serial.println(" 200 pulse ta S2  100 oldu");
            MotorPos = 100;
            EEPROM.write(1,MotorPos);
            break;
         }
        }
        else
        {
          if (pos != MotorPos)
          {
//              Serial.println("aaaa");
              MotorPos = pos;
              EEPROM.write(1,MotorPos);
          }
        }
    }/*for (int j=0; j < (fark*100); j++)*/
         
/*       if ( (MotorPos >0) &&  (MotorPos<100) )
       { 
         Serial.println("bbbb");
           MotorPos = pos;
          EEPROM.write(1,MotorPos);
       }
*/
    } /*if (sonsuzdon) else */
    
    yaz_posisyon() ;    
  }
}

void ok_Gonder(const int value)
{
    BufferFiller bfill = ether.tcpOffset();
    bfill.emit_p(PSTR("HTTP/1.0 200 OK\r\n"
          "Content-Type: text/html\r\nPragma: no-cache\r\n\r\n"
          "<html><head><title>Koala</title></head><body>"
          "<br>"
          ));
   if ( value>-1) 
  {
    bfill.emit_p(PSTR("POS=$D;"),value);
  }
  else
  {
     bfill.emit_p(PSTR("OK"));
  }
  bfill.emit_p(PSTR("</body></html>"));
  
  ether.httpServerReply(bfill.position());
}

void PaketGonder() {
  if (millis() > GecenSure) {
    GecenSure = millis() + TIMEOUT_MS; /* 5 saniye */
    ether.copyIp(ether.hisip, hisip);
  byte sd = stash.create();
  stash.print("ID=");
  stash.print(KartID);
  stash.print("&value=");
  stash.println(EEPROM.read(1) );
  stash.save();

Stash::prepare(PSTR("POST http://$F/servo.php HTTP/1.0" "\r\n"
      "Host:  $F" "\r\n"
      "Connection: close" "\r\n"
      "Content-Type: application/x-www-form-urlencoded \r\n"      
      "Content-Length: $D" "\r\n"
      "\r\n"
      "$H"),
       website,website,stash.size(), sd);

    // send the packet - this also releases all stash buffers once done
    session = ether.tcpSend(); 
    Serial.println("Gonderdi");
  }
}



void loop() {
    word len = ether.packetReceive();
    word pos = ether.packetLoop(len);
    
    if(pos) {
       /*http://192.168.2.60/SETPOSISYON&POS=15 */
       if(strstr((char *)Ethernet::buffer + pos, "GET /RESET") != 0) {
          Serial.println("Reset"); 
         BufferFiller bfill = ether.tcpOffset();
         bfill.emit_p(PSTR("HTTP/1.0 200 OK\r\n"
          "Content-Type: text/html\r\nPragma: no-cache\r\n\r\n"
          "<html><head><title>ArduinoTurkiye WebServer</title></head><body>"
          "<br>"
          ));
         bfill.emit_p(PSTR("OK</body></html>"));
         ether.httpServerReply(bfill.position());

         wdt_enable( WDTO_60MS);
         while(1) {} 

       }
       else
       if(strstr((char *)Ethernet::buffer + pos, "GET /GETPOSISYON") != 0) {
         /* "POS="+EEPROM.read(1);*/
         ok_Gonder(EEPROM.read(1) );
       }
       else if(strstr((char *)Ethernet::buffer + pos, "GET /SETPOSISYON") != 0) {
//         Ethernet::buffer[pos+300] = 0;//bu satir cok önemli
        String fullResponse = (const char*) Ethernet::buffer+pos;
//        fullResponse = (const char*) Ethernet::buffer+pos;
//        Serial.print(fullResponse);        
        int xpos1 = fullResponse.indexOf("POS=");
        int xpos2 = fullResponse.indexOf("HTTP/1.1");
        String veriStr = fullResponse.substring(xpos1+4,xpos2);
        veriStr.trim();
        ok_Gonder(-1);
        GecenSure = GecenSure - TIMEOUT_MS - 10;

        if ( (veriStr.toInt() >= 0) &&  (veriStr.toInt() <= 100) )
        {
           MotorSur(veriStr.toInt() );
        } 
       }
       else
       {ok_Gonder(-2);}
    }
   
   if (Serial.available() > 0) {
    veri = "";
    for (int i =0; i<100; i++)
    {
      if (Serial.available() > 0)
      {
       inChar =  Serial.read();
       veri = veri + inChar;
      }
    }
    veri.trim();
    int pos = veri.indexOf("SETKARTID=");
    if (pos > -1) 
    {
       veri2 = veri.substring(10);
       veri2.trim();
       KartID = veri2.toInt();
       EEPROM.write(0,KartID);
       Serial.print("Yeni Kart ID:");
       Serial.println(KartID);       
       Serial.print("ID gecerli olması icin cihazi kapatip tekrar acinız");
       veri = "";
       wdt_enable( WDTO_60MS);
       while(1) {} 
    }
    if (veri.length() > 0) 
    {
      Serial.print("GelenVeri:");
      Serial.println(veri);
    }
    veri = "";
  }

//1000 saniye 1000*60*60*24
  if (millis() > 86400000) {
    Serial.print("Reset");// gunde bir sefer reset
    wdt_enable( WDTO_60MS);
    while(1) {} 
  }
   PaketGonder(); 
}    

