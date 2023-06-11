#include <FS.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <painlessMesh.h>
#include <Thinary_AHT10.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#define SDA_PIN D3
#define SCL_PIN D4
#define   MESH_PREFIX     "MeshNetwork"
#define   MESH_PASSWORD   "NetPassword"
#define   MESH_PORT       5555

AHT10Class AHT10;
TFT_eSPI tft = TFT_eSPI(); 
painlessMesh  mesh;

int prepage=0;
int nowpage=0;
int meshnodenum=0;
String file_name = "/dateFile.txt";   
const int httpPort = 3003;
void mainpageprogram(float t,float h);
void mainpage();
char tem[100]={0};
char hum[100]={0};
int numposition=0;
int loopnumber=0;
float t=0;
float h=0;
float tt=0;
float th=0;
unsigned long lasttime=0; 
String labviewdata="";
void serialchipdata(char node[10]){
  labviewdata="";
  labviewdata+="3";
  labviewdata+=node;
  Serial.print(labviewdata);
  }
  IRAM_ATTR void page(){
  if(nowpage==2){nowpage=0;return;}
  nowpage++;
  }
void serialdata(String x,String te,String hu){
  labviewdata="";
  labviewdata+=x;
  labviewdata+=te;
  labviewdata+=hu;
  Serial.print(labviewdata);
  }

void receivedCallback( uint32_t from, String &msg ) {
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, msg);
  long dec_data=0;
  String msgt=doc["tem"]; 
  String msgh=doc["hum"];
  char msgtem[10]={0};
  char msghum[10]={0};
  for(int i=0;i< msgt.length();i++)
{ msgtem[i]=msgt[i];}
for(int i=0;i< msgh.length();i++)
{ msghum[i]=msgh[i];}
  if((millis()-lasttime)>1000){
  t = AHT10.GetTemperature();
  h = AHT10.GetHumidity();
  mainpageprogram(t,h);
     }
  dec_data=strtol(msgtem,NULL,16);
  tt=(float)dec_data;
  if(tt>16384)tt=(tt-16384)/100;
  else tt=tt*(-1)/100;
  dec_data=strtol(msghum,NULL,16);
  th=((float)(dec_data-16384))/100;
  if((tt-t)>15 || (th-h)>30){
    char node[10];
    sprintf(node,"%d",doc["node"]);
    serialchipdata(node);
    delay(50);
    if((tt-t)>15){
    serialdata("1",msgt,msgh);
    }
    else serialdata("2",msgt,msgh);
    }
    else{
      if(loopnumber==10){
    tem[numposition]=(t+tt)/2;
    hum[numposition]=(h+th)/2;
    if(numposition<99)numposition++;
    else {
    for(int i=0;i<99;i++){
      tem[i]=tem[i+1];hum[i]=hum[i+1];
    }}
    loopnumber=0;
    }
    loopnumber++;
      float fint=(t+tt)/2*100;
      if (fint>0)fint+=16384;
      sprintf(msgtem,"%d",(String)fint);
      sprintf(msghum,"%d",(String)((h+th)/2*100));
      msgt = msgtem;
      msgh= msghum;
      serialdata("0",msgt,msgh);
      }
  }
void meshsetup(){
  mesh.setDebugMsgTypes( ERROR | STARTUP);  
  mesh.init( MESH_PREFIX, MESH_PASSWORD, MESH_PORT);
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
  tft.setCursor(18,210);
  tft.fillCircle(23,215,5,TFT_GREEN);
  mainpage();
  }

void setup() {
  Serial.begin(9600);
  pinMode(D0,OUTPUT);
  pinMode(D2,INPUT);
  digitalWrite(D0,HIGH);
  attachInterrupt(digitalPinToInterrupt(D1),page,FALLING);
  Wire.begin(SDA_PIN,SCL_PIN);
  AHT10.begin();
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  tft.setCursor(20,20);
  if(SPIFFS.begin()){ 
    tft.print("SPIFFS Started.");
  } else {
    tft.print("SPIFFS Failed to Start.");
  }
  SPIFFS.format();
  tft.setCursor(20,40);
  tft.print("SPIFFS formated.");
  meshsetup();
  tft.setTextSize(2);
  setupmainpage();
}

void drawpage(){
    tft.fillRect(0,0,320,50,TFT_WHITE);
  prepage=1;
   tft.setTextColor(TFT_BLACK,TFT_WHITE);
  tft.setCursor(20,20);
  tft.print("Last 1000s");
  tft.setCursor(150,20);
  tft.print("tem:");tft.fillRect(195,23,20,10,TFT_RED);
  tft.setCursor(230,20);
  tft.print("hum:");tft.fillRect(275,23,20,10,TFT_BLUE);
  tft.drawLine(10,50,10,196,TFT_WHITE);
  for(int i=0;i<14;i++){
    tft.drawLine(10,194-(i*10),13,194-(i*10),TFT_WHITE);
    }
    tft.drawLine(10,174,17,174,TFT_WHITE);
    tft.setTextSize(1);
      tft.setTextColor(TFT_WHITE,TFT_BLACK);
    tft.setCursor(0,186);tft.print("-20");
    tft.setCursor(0,170);tft.print("0");
    tft.setCursor(0,150);tft.print("20");
    tft.setCursor(0,130);tft.print("40");
    tft.setCursor(0,110);tft.print("60");
    tft.setCursor(0,90);tft.print("80");
    tft.setCursor(0,70);tft.print("100");
    tft.setTextSize(2);
  tft.setTextColor(TFT_BLACK,TFT_DARKGREY);
  tft.setCursor(115,210);
  tft.print("drawpage");
  tft.setCursor(257,210);
  tft.print("main");
  }

void mainpage(){
    tft.fillRect(0,0,320,50,TFT_WHITE);
  prepage=0;
  tft.setTextColor(TFT_BLACK,TFT_DARKGREY);
  tft.fillRect(0,120,320,2,TFT_WHITE);
  tft.fillRect(159,50,2,144,TFT_WHITE);
  tft.setCursor(257,210);
  tft.print("draw");
  tft.setCursor(115,210);
  tft.print("mainpage");
  }

void mainpageprogram(float t,float h){
  tft.setTextColor(TFT_WHITE,TFT_BLACK); 
  tft.setCursor(15,80);
  tft.print("temperature");
  tft.setCursor(30,152);
  tft.print("humidity");
  tft.setCursor(210,80);
  tft.print(t);
  tft.setCursor(210,152);
  tft.print(h);
  delay(1000);
  }
void drawpageprogram(){
  if(loopnumber==1){
  tft.fillRect(0,50,320,144,TFT_BLACK);
  drawpage();
  for(int i=0;i<99;i++){
        tft.drawLine(10+3*i,194-((int)tem[i]+20),13+3*i,194-((int)tem[i+1]+20),TFT_RED);
        tft.drawLine(10+3*i,194-((int)hum[i]+20),13+3*i,194-((int)hum[i+1]+20),TFT_BLUE);
     }
     }
  delay(1000);
  }
  String comdata ="";
void loop() {mesh.update();
  t = AHT10.GetTemperature();
  //if(t<0)t=-3277-t; 
  //float h = dht22.readHumidity();
  h = AHT10.GetHumidity();
  //File adataFile = SPIFFS.open(file_name, "a");
  //adataFile.print(t);
  //adataFile.print("*");
  //adataFile.print(h);
  //adataFile.print("*");
  //adataFile.close();
  if(loopnumber==10){
  tem[numposition]=t;
  hum[numposition]=h;
  if(numposition<99)numposition++;
  else {
    for(int i=0;i<99;i++){
      tem[i]=tem[i+1];hum[i]=hum[i+1];
    }}
    loopnumber=0;
    }
    loopnumber++;
  if(prepage!=nowpage){
    tft.fillRect(0,50,320,144,TFT_BLACK);
    if(nowpage==1)drawpage();
    if(nowpage==0)mainpage();   
  }
  if(prepage==0)mainpageprogram(t,h);
  if(prepage==1)drawpageprogram();
  tft.setTextColor(TFT_BLACK,TFT_WHITE);
  tft.setCursor(20,20);
    if(nowpage==0){tft.print(comdata);}
  int ft=(int)t*100;int fh=(int)(h*100+16384);
    if(ft>0)ft+=16384;
    char finalt[10]={0};char finalh[10]={0};
    sprintf(finalt,"%x",ft);
    sprintf(finalh,"%x",fh);
    String finaltt=finalt;String finalth=finalh;
    serialdata("0",finaltt,finalth);
      comdata="";
   while(Serial.available() > 0){
        comdata += char(Serial.read());
        delay(2);
    }
}
