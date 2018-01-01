/*
 gungor 13/08/2017
*/
#include <SPI.h>
#include <EEPROM.h> 
#include <EtherCard.h> // EtherCard kütüphanesini ekliyoruz.
#include <avr/wdt.h>

#define TIMEOUT_MS 5000; 
const String Versiyon = "1.17.9.15.22.19";
const byte RoleMinPin =22; 
const byte RoleMaxPin =32; 

static byte KartID;
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

static byte myip[] = { 192,168,68,51 }; /*KartID göre degişiyor*/
const static uint8_t gwip[] = {192,168,68,15}; 
const static uint8_t dnsip[] = {192,168,68,15};  
const static uint8_t netmask[] = {255,255,255,0}; 
byte hisip[] = {192,168,68,15 };
const char website[] PROGMEM = "192.168.68.15";
/* 198.211.121.13 */
Stash stash;
byte session;

byte Ethernet::buffer[700];
static uint32_t GecenSure = 0;

String veri ="";
String veri2 ="";
char inChar;

/* 
Enc28j60  Arduino Mega
CS  --> 53  
SI  --> 51
SO  --> 50
SCK --> 52
VCC --> 3.3V
GND --> GND 
*/
void setup () {
  Serial.begin(57600); //Seri iletişimi başlatıyoruz. 
  
   KartID = EEPROM.read(0);
  if ( (KartID==0) || (KartID==255) )
  {
    KartID = 100;
    EEPROM.write(0,KartID);
    for (int i =RoleMinPin; i<RoleMaxPin; i++)
    {
     EEPROM.write(i,1);
    }
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
    
  Serial.println();
  Serial.print("* * * * ");
  Serial.print(Versiyon);
  Serial.println(" * * * *");

  Serial.print("Kart ID:");
  Serial.println(KartID);
  Serial.print("IP :");
  for (int i =0; i<4; i++)
  {
    Serial.print(ether.myip[i]);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("GW :");
  for (int i =0; i<4; i++)
  {
    Serial.print(ether.gwip[i]);
    Serial.print(".");
  }
  Serial.println("");
  
  for (int i =RoleMinPin; i<RoleMaxPin; i++)
  {
    Serial.print(i);
    Serial.print(".Pin :");
    
    pinMode(i, OUTPUT);
    if (EEPROM.read(i)==0 )
    {
      digitalWrite(i,LOW);
      Serial.print("ON");
    }
    else
    {
      digitalWrite(i, HIGH);
      Serial.print("OFF");
    }
    Serial.println("");
  }
  Serial.println("***********************");  
}

void PaketGonder() {
  if (millis() > GecenSure) {
    GecenSure = millis() + TIMEOUT_MS; /* 5 saniye */
    ether.copyIp(ether.hisip, hisip);
  byte sd = stash.create();
  stash.print("ID=");
  stash.print(KartID);
  stash.print("&value=");
  for (int i =RoleMinPin; i<RoleMaxPin; i++)
  {
    if (EEPROM.read(i)==0 )
    {
      stash.print("1");
    }
    else
    {
      stash.print("0");
    }
  }
  stash.println(";");
  
  stash.save();

Stash::prepare(PSTR("POST http://$F/role.php HTTP/1.0" "\r\n"
      "Host:  $F" "\r\n"
      "Connection: close" "\r\n"
      "Content-Type: application/x-www-form-urlencoded" "\r\n"      
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

    /*http://192.168.68.51/SETPINVALUE&PIN=25;VALUE=1 */
    /*http://192.168.68.51/RESET */
    if(pos) {
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
      else if(strstr((char *)Ethernet::buffer + pos, "GET /SETPINVALUE") != 0) {
        String fullResponse = (const char*) Ethernet::buffer+pos;
        int xpos1 = fullResponse.indexOf("PIN=");
        int xpos2 = fullResponse.indexOf("HTTP/1.1");
        fullResponse = fullResponse.substring(xpos1,xpos2);
        xpos1 = fullResponse.indexOf("PIN=")+4;
        xpos2 = fullResponse.indexOf(";");
        String pinStr = fullResponse.substring(xpos1,xpos2);
        xpos1 = fullResponse.indexOf("VALUE=");
        String valueStr = fullResponse.substring(xpos1+6,xpos1+9);
        if ( (pinStr.toInt() >= RoleMinPin) &&  (pinStr.toInt() <= RoleMaxPin) )
        {
          if (valueStr.toInt() == 0 )
          {
             EEPROM.write(pinStr.toInt(),1);
             digitalWrite(pinStr.toInt(),HIGH);
             Serial.println("");    
             Serial.print(pinStr.toInt());
             Serial.println(".:OFF");
          }
          else
          {
             EEPROM.write(pinStr.toInt(),0);
             digitalWrite(pinStr.toInt(),LOW);
             Serial.println("");    
             Serial.print(pinStr.toInt());
             Serial.println(".:ON");
          }
        }
        else
        {
          Serial.println("Hatali Pin");    
        }
        
        BufferFiller bfill = ether.tcpOffset();
        bfill.emit_p(PSTR("HTTP/1.0 200 OK\r\n"
          "Content-Type: text/html\r\nPragma: no-cache\r\n\r\n"
          "<html><head><title>ArduinoTurkiye WebServer</title></head><body>"
          "<br>"
          ));
        bfill.emit_p(PSTR("OK</body></html>"));
       ether.httpServerReply(bfill.position());
    /*   GecenSure = GecenSure - TIMEOUT_MS - 10; */
    }
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
       for (int i =RoleMinPin; i<RoleMaxPin; i++)
       {
          EEPROM.write(i,1);
          digitalWrite(i,HIGH);
       }

       Serial.print("Yeni Kart ID:");
       Serial.println(KartID);       
       Serial.print("ID gecerli olması icin cihazi kapatip tekrar acinız");
       wdt_enable( WDTO_60MS);
       while(1) {} 
    veri = "";
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
