/*
 gungor 13/08/2017 
*/
#include <SPI.h>
#include <EEPROM.h> 
#include <EtherCard.h> // EtherCard kütüphanesini ekliyoruz.
#include <avr/wdt.h>

const String Versiyon =  "1.17.9.15.22.19";
#define TIMEOUT_MS 10000; 
#define TIMEOUT_Sensor 2000; // 1 saniye= 1000


static byte KartID;
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

static byte myip[] = { 192,168,68,51 }; /*KartID göre degişiyor*/
const static uint8_t gwip[] = {192,168,68,15}; 
const static uint8_t dnsip[] = {192,168,68,15};  
const static uint8_t netmask[] = {255,255,255,0}; 
byte hisip[] = { 192,168,68,15 };
   
Stash stash;
byte session;
const char website[] PROGMEM = "192.168.68.15";

byte Ethernet::buffer[300];
static uint32_t GecenSure = 0;
static uint32_t SensorSure = 0;

/* Sensor Pinleri */
const int trigPin = 4;
const int echoPin = 3;

/* manyetik Sensor1 Pinleri */
const int ManyetikSensorA1 = 5;
const int ManyetikSensorB1 = 6;


long sure =0;
int mesafe=0;

/* 
Enc28j60  Arduino Mega
CS  --> 53  
SI  --> 51
SO  --> 50
SCK --> 52
VCC --> 3.3V
GND --> GND 

Enc28j60  Arduino nano
CS  --> 10  
SI  --> 11
SO  --> 12
SCK --> 13
VCC --> 3.3V
GND --> GND 
*/

static void my_callback (byte status, word off, word len) {
  Ethernet::buffer[off+300] = 0;
  if(strstr((char *)Ethernet::buffer+off, "HTTP/1.1 200 OK") != 0) {
    Serial.println(">>OK<<");   
  }
  else
  {
    Serial.println(">>>");   
    Serial.print((const char*) Ethernet::buffer + off);
    Serial.println("...");
  }
}

void setup () {
  Serial.begin(57600); //Seri iletişimi başlatıyoruz. 
  
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(ManyetikSensorA1, INPUT_PULLUP);
  pinMode(ManyetikSensorB1, INPUT_PULLUP);
    
  KartID = EEPROM.read(0);
  if (KartID==0)
  {
    KartID = 100;
    EEPROM.write(0,KartID);
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
    
/*
if (!ether.staticSetup(myip))
    Serial.println("Sabit IP atama islemi yapilamadi.");
*/

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);  
  ether.printIp("DNS: ", ether.dnsip);  
//  char websiteIP[] = "192.168.68.15";
//  ether.parseIp(ether.hisip, websiteIP);
   ether.copyIp(ether.hisip, hisip);

  ether.printIp("SRV: ", ether.hisip);
  
  Serial.println();
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
  
  Serial.println("***********************");
}
String veri ="";
String veri2 ="";

char inChar;

void SensorOku() {
  if (millis() > SensorSure) {
    SensorSure = millis() + TIMEOUT_Sensor; 
  /* sensorden veri okuma */
  mesafe = 0;
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  sure = pulseIn(echoPin,HIGH);
  mesafe  = (sure*0.34/2) / 10;
  delay(100);
  
  Serial.print (mesafe);
  Serial.println (" cm ");
  }
}

void PaketGonder() {
  if ( (millis() > GecenSure) && (mesafe < 450)) {
    GecenSure = millis() + TIMEOUT_MS; /* 5 saniye */
    ether.copyIp(ether.hisip, hisip);

  byte sd = stash.create();
  stash.print("ID=");
  stash.print(KartID);
  stash.print("&value=");
  stash.println(mesafe);
  stash.print("&Sensor1=");
  if (digitalRead(ManyetikSensorA1)=HIGH)
    stash.println("1")
  else
    stash.println("0");
  
  stash.print("&Sensor2=");
  if (digitalRead(ManyetikSensorB1)=HIGH)
    stash.println("1")
  else
    stash.println("0");
  
  stash.save();

Stash::prepare(PSTR("POST http://$F/sensor.php HTTP/1.0" "\r\n"
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
   {
              BufferFiller bfill = ether.tcpOffset();
    bfill.emit_p(PSTR("HTTP/1.0 200 OK\r\n"
          "Content-Type: text/html\r\nPragma: no-cache\r\n\r\n"
          "<html><head><title>ArduinoTurkiye WebServer</title></head><body>"
          "<br>"
          ));
    bfill.emit_p(PSTR("OK</body></html>"));
    ether.httpServerReply(bfill.position());

   }
   
  }


  SensorOku();
  PaketGonder();

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
       Serial.print("ID gecerli olmasi icin cihazi kapatip tekrar aciniz");
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
  
}

