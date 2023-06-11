#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <FS.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <SPI.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI(); 
WiFiClient wifiClient; 
int id=0;
    WiFiManager wifiManager; 
void wificonnect(){
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(50,100);
  tft.print("Connect wifi on your phone");
  wifiManager.autoConnect("AutoConnectAP");
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
  void setup() {
  Serial.begin(9600);
  wifiManager.resetSettings();
  wifiManager.setTimeout(120);
  wifiManager.setBreakAfterConfig(1);
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  wificonnect();
}
void loop(){
  Serial.print(id);
  delay(1000);
  }
