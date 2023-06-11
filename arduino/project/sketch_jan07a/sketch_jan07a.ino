#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <FS.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <PubSubClient.h>
//#include <DHT.h>
#include <Wire.h>
#include <painlessMesh.h>
#include <Thinary_AHT10.h>
#include <TimeLib.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#define SDA_PIN D3
#define SCL_PIN D4
#define   MESH_PREFIX     "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555

AHT10Class AHT10;
//DHT dht22(D4,DHT22);
//DHT dht11(D2,DHT11);
TFT_eSPI tft = TFT_eSPI(); 
Scheduler userScheduler;
WiFiClient wifiClient; 
PubSubClient mqttClient(wifiClient);  
time_t getNtpTime();
WiFiUDP Udp;
painlessMesh  mesh;

const char* ssid = "LWLAN1408";
const char* password = "sU2019.9.16.01";
const char* mqttServer = "49.233.60.32";
const char* host = "49.233.60.32";   
const int httpPort = 3003; 
static const char ntpServerName[] = "ntp.ntsc.ac.cn";
const int timeZone = +8;
unsigned int localPort = 8888; 
void digitalClockDisplay();
void printDigits(int digits);
String DigitalNum(int digits);
void mainpage();
void sendNTPpacket(IPAddress &address);
void receivedCallback( uint32_t from, String &msg ) {
  
  Serial.printf(msg.c_str());Serial.println();
  }
void quitwifi(){
  WiFi.mode(WIFI_OFF);
  detachInterrupt(D2);
  attachInterrupt(digitalPinToInterrupt(D2),confirm,RISING);
  tft.setCursor(50,120);
  tft.print("cansel connect wifi");
  delay(2000);
  tft.fillScreen(TFT_BLACK);
  mainpage();
  }
void wificonnect(){
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(50,100);
  tft.print("Connect wifi on your phone");
  detachInterrupt(D2);
  attachInterrupt(digitalPinToInterrupt(D2),quitwifi,RISING);
  WiFiManager wifiManager;   
  wifiManager.autoConnect("AutoConnectAP");
  }

void meshsetup(){
  mesh.setDebugMsgTypes( ERROR | STARTUP ); 
  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  }
void setupmainpage(){
  tft.fillScreen(TFT_BLACK);
  delay(2000);
  tft.fillRect(0,0,320,50,TFT_WHITE);
  tft.fillRect(0,194,320,240,TFT_WHITE);
  tft.fillRoundRect(10,200,60,36,10,TFT_DARKGREY);
  tft.fillRoundRect(250,200,60,36,10,TFT_DARKGREY);
  tft.fillRoundRect(100,200,120,36,10,TFT_DARKGREY);
  mainpage();
  }
void setup() {
  Serial.begin(9600);
  pinMode(D0,OUTPUT);
  digitalWrite(D0,HIGH);
  attachInterrupt(digitalPinToInterrupt(D1),page,FALLING);
  attachInterrupt(digitalPinToInterrupt(D2),confirm,FALLING);
  Wire.begin(SDA_PIN,SCL_PIN);
  AHT10.begin();
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  mqttClient.setServer(mqttServer, 1883); 
  connectMQTTServer();
  meshsetup();
  //dht11.begin(); 
  //dht22.begin();
  Udp.begin(localPort);
  setSyncProvider(getNtpTime);
  setSyncInterval(300);
  setupmainpage();
}
time_t prevDisplay = 0; 
bool onlinetag=0;
int prepage=0;
int nowpage=0;
void drawpage(){
  prepage=1;
  tft.setTextColor(TFT_BLACK,TFT_DARKGREY);
  tft.setCursor(115,210);
  tft.print("drawpage");
  tft.setCursor(18,210);
  tft.print("main");
  tft.setCursor(257,210);
  tft.print("wifi");}
  
void wifipage(){
  prepage=2;
  tft.setTextColor(TFT_BLACK,TFT_DARKGREY);
  tft.setCursor(115,210);
  tft.print("wifipage");
  tft.setCursor(18,210);
  tft.print("draw");
  tft.setCursor(257,210);
  tft.print("main");
  }
void mainpage(){
  prepage=0;
  tft.setTextColor(TFT_BLACK,TFT_DARKGREY);
  tft.fillRect(0,120,320,2,TFT_WHITE);
  tft.fillRect(159,50,2,144,TFT_WHITE);
  tft.setCursor(18,210);
  tft.print("wifi");
  tft.setCursor(257,210);
  tft.print("draw");
  tft.setCursor(115,210);
  tft.print("mainpage");
  }
IRAM_ATTR void page(){
  if(nowpage==2){nowpage=0;return;}
  nowpage++;
  }
IRAM_ATTR void confirm(){
  static int countconfirm=0;
  countconfirm++;
  tft.setCursor(20,150);
  tft.print("count:");
  tft.setCursor(80,150);
  tft.print(countconfirm);
  }
void mainpageprogram(){
  tft.setTextColor(TFT_BLACK,TFT_WHITE);
  tft.setCursor(20,20);
  if(onlinetag==1){
  tft.print(year());
  tft.print(".");
  tft.print(month());
  tft.print(".");
  tft.print(day());
  tft.print(" ");
  tft.print(hour());
  tft.print(":");
  String Minute = DigitalNum(minute());
  tft.print(Minute);
  tft.print(":");
  String Second = DigitalNum(second());
  tft.print(Second);
  }
  else tft.print("Offline mode");
  tft.setTextColor(TFT_WHITE,TFT_BLACK); 
  tft.setCursor(15,80);
  tft.print("temperature");
  tft.setCursor(30,152);
  tft.print("humidity");
  //float t = dht22.readTemperature();
  float t = AHT10.GetTemperature();
  //if(t<0)t=-3277-t; 
  //float h = dht22.readHumidity();
  float h = AHT10.GetHumidity();
  tft.setCursor(210,80);
  tft.print(t);
  tft.setCursor(210,152);
  tft.print(h);
  delay(1000);
  }
void drawpageprogram(){
  static int drawcount=0;tft.setCursor(20,100);
  tft.print(drawcount++);delay(1000);
  }
void wifipageprogram(){
  static int wificount=0;tft.setCursor(20,120);
  tft.print(wificount++);delay(1000);
  }
void loop() { 
  mesh.update(); 
  if (timeStatus() != timeNotSet) {
    if (now() != prevDisplay) { //update the display only if time has changed
      prevDisplay = now();
    }
  } 
  if(prepage!=nowpage){
    tft.fillRect(0,50,320,144,TFT_BLACK);
    if(nowpage==1)drawpage();
    if(nowpage==2)wifipage();
    if(nowpage==0)mainpage();   
  }
  if(prepage==0)mainpageprogram();
  if(prepage==1)drawpageprogram();
  if(prepage==2)wifipageprogram();
  if (mqttClient.connected()) { 
  String topicString = "dev/" + WiFi.macAddress();
  tft.setCursor(20,20);
  tft.print(topicString);
  char publishTopic[topicString.length() + 1];  
  strcpy(publishTopic, topicString.c_str());
  int message=0;
  if(t>0){   message = int(t*10000+h*10+1000000);}
  else{ message = int(abs(t)*10000+h*10+2000000); }
  String messageString = String(t)+","+String(h)+","+String(AHT10.GetHumidity())+","+String(AHT10.GetTemperature())+","+String(dht11.readHumidity())+","+String(dht11.readTemperature())+","+String(year())+"."+String(month())+"."+String(day())+" "
                        +String(hour())+":"+Minute+":"+Second; 
  char publishMsg[messageString.length() + 1];   
  strcpy(publishMsg, messageString.c_str());
  
  if(mqttClient.publish(publishTopic, publishMsg)){
    Serial.println("Publish Topic:");Serial.println(publishTopic);
    Serial.println("Publish message:");Serial.println(publishMsg);    
  } else {
    Serial.println("Message Publish Failed."); 
  }
  
 data upload part

    mqttClient.loop();
  } else {                  
    connectMQTTServer();    
  }
  delay(500);
}
 
void connectMQTTServer(){
  String clientId = "esp8266-" + WiFi.macAddress();
  if (mqttClient.connect(clientId.c_str())) { 
    Serial.println("MQTT Server Connected.");
    tft.setCursor(20,60);
    tft.print("MQTT Server Connected.");
    Serial.println("Server Address: ");
    Serial.println(mqttServer);
    tft.setCursor(20,80);
    tft.print("Server Address: ");tft.print(mqttServer);
    Serial.println("ClientId:");
    Serial.println(clientId);
    tft.setCursor(20,120);
    tft.print("ClientId:");tft.print(clientId);
    delay(3000);
    tft.fillScreen(TFT_BLACK);
  } else {
    Serial.print("MQTT Server Connect Failed. Client State:");
    Serial.println(mqttClient.state());
    tft.setCursor(20,60);
    tft.print("MQTT Server Connect Failed. Client State:");tft.print(mqttClient.state());
    delay(1000);
    tft.fillScreen(TFT_BLACK);
  }   
}
 
void connectWifi(){   
  tft.setCursor(20,20);
  tft.print("ConnectWiFi");
  WiFi.begin(ssid, password);
  int count=20; 
  while ((WiFi.status() != WL_CONNECTED) && count>0) {
    delay(1000);
    tft.print(".");
    count--;
  }
  if(WiFi.status()==WL_CONNECTED){
  tft.setCursor(20,40);
  tft.print("WiFi Connected!");
  delay(2000);}
  else{
  tft.setCursor(20,40);
  tft.print("Can not Connected WiFi!"); 
  delay(2000);
    }
}

String DigitalNum(int digits)
{
  String digitime;
  if (digits < 10)
  {digitime = "0"+String(digits);}
  else digitime = String(digits);
  return digitime;
}

/*-------- NTP code ----------*/

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

time_t getNtpTime()
{
  IPAddress ntpServerIP; // NTP server's ip address

  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  // get a random server from the pool
  WiFi.hostByName(ntpServerName, ntpServerIP);
  Serial.print(ntpServerName);
  Serial.print(": ");
  Serial.println(ntpServerIP);
  sendNTPpacket(ntpServerIP);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println("Receive NTP Response");
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}
