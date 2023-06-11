#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <PubSubClient.h>
#include <ThreeWire.h>  
#include <RtcDS1302.h>

ThreeWire myWire(D7,D8,D6); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);
WiFiClient wifiClient; 
PubSubClient mqttClient(wifiClient);  
WiFiManager wifiManager;   
const char* mqttServer = "49.233.60.32";
const char* host = "49.233.60.32";   


void setup() {
  Serial.begin(9600);
  wifiManager.autoConnect("AutoConnectAP");
  mqttClient.setServer(mqttServer, 1883); 
  connectMQTTServer();
  Rtc.Begin();
      RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
   if (!Rtc.IsDateTimeValid()) Rtc.SetDateTime(compiled);
 if (Rtc.GetIsWriteProtected()) Rtc.SetIsWriteProtected(false);
if (!Rtc.GetIsRunning())Rtc.SetIsRunning(true);
    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled)Rtc.SetDateTime(compiled);
}
String comdata = "";
String timedata = "";
void loop() { 
  
  comdata="";
   while(Serial.available() > 0){//串口接收到数据
        comdata += char(Serial.read());//获取串口接收到的数据
          delay(2);
    }
    if(Serial.available()==0 && comdata.length()==9){
      RtcDateTime now = Rtc.GetDateTime();
      printDateTime(now);
  if (mqttClient.connected()) { 
  String topicString = "dev/" + WiFi.macAddress();
  char publishTopic[topicString.length() + 1];  
  strcpy(publishTopic, topicString.c_str());
  int message=0;
  String messageString = comdata+","+timedata;
  char publishMsg[messageString.length() + 1];   
  strcpy(publishMsg, messageString.c_str());
  mqttClient.publish(publishTopic, publishMsg);
  mqttClient.loop();
  } else {                  
    connectMQTTServer();    
  }}
  delay(1000);
}
#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];
    int hournow = (int)dt.Hour();
    int minutenow = ((int)dt.Minute())-20;
      int secondnow = (int)dt.Second()-20;
      if(secondnow<0){
      minutenow--;
      secondnow=60+secondnow;
      }
      if(minutenow<0){
      hournow--;
      minutenow=60+minutenow;
      } 
    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%04u.%02u.%02u %02u:%02u:%02u"),
            dt.Year(),
            dt.Month(),
            dt.Day(),
            hournow,
            minutenow,
            secondnow);
    Serial.print(datestring);
} 
void connectMQTTServer(){
  String clientId = "esp8266-" + WiFi.macAddress();
  if (mqttClient.connect(clientId.c_str())) { 
    delay(3000);
  } else {
    delay(1000);
  }   
}
 
