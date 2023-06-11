#include <ESP8266WiFi.h>        
#include <ESP8266WebServer.h>
#include <FS.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <dht11.h>
dht11 DHT11; 
#define DHT11PIN 2
TFT_eSPI tft = TFT_eSPI(); 
int check =0;
int temperaturedata[20];
int humiditydata[20];
int i=0,j=0,value0,value1,x;
const char *ssid = "Sekingtest";  
const char *password = "12345678"; 

ESP8266WebServer esp8266_server(80);

void setup() {
  Serial.begin(115200); 
  pinMode(16,OUTPUT);
  pinMode(5,OUTPUT);
  digitalWrite(16,HIGH);
  digitalWrite(5,LOW);           
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  pinMode(4,INPUT);
  WiFi.softAP(ssid, password);
  tft.setCursor(10,10);    
  tft.print("Access Point: ");  
  tft.print(ssid);
  tft.setCursor(10,20);    
  tft.print("Access Password: ");  
  tft.print(password);   
  tft.setCursor(10,30);
  tft.print("IP address: ");  
  tft.print(WiFi.softAPIP());
  tft.setCursor(10,40);   
  if(SPIFFS.begin()){ 
    tft.print("SPIFFS Started.");
  } else {
    tft.print("SPIFFS Failed to Start.");
  }
  esp8266_server.on("/getDHT",handleDHT);
  esp8266_server.onNotFound(handleUserRequet);      
  esp8266_server.begin();
  tft.setCursor(10,50);  
  tft.print("HTTP server started");
  delay(5000);
} 
void loop(void) {
   if(digitalRead(4) == HIGH){
                tft.fillScreen(TFT_BLACK);
                tft.drawLine(5,8,150,8,TFT_WHITE);
                tft.drawLine(5,30,150,30,TFT_WHITE);
                tft.drawLine(5,52,150,52,TFT_WHITE);
                tft.drawLine(5,8,5,52,TFT_WHITE);
                tft.drawLine(100,8,100,52,TFT_WHITE);
                tft.drawLine(150,8,150,52,TFT_WHITE);
                tft.setTextFont(1);
                tft.setCursor(45,120);
                tft.print("B01914005,Sukening");
                tft.setTextFont(2);
                tft.setCursor(22,12);
                tft.print("Humidity(%");
                tft.setCursor(8,34);
                tft.print("Temperature(C");
                while(1){
                  if(digitalRead(4) == LOW){break;}
                  DHT11.read(DHT11PIN);
                tft.setCursor(108,12);
                tft.print((float)DHT11.humidity,2);
                tft.setCursor(108,34);
                tft.print((float)DHT11.temperature,2); 
                if(i < 20){
                  temperaturedata[i]=DHT11.temperature;
                  humiditydata[i]=DHT11.humidity;
                  i++;
                    Serial.print(DHT11.temperature*100+DHT11.humidity+digitalRead(4)*10000);                  
                  }
                else{
                  for(i=0;i<19;i++){
                  temperaturedata[i]=temperaturedata[i+1];
                  humiditydata[i]=humiditydata[i+1];
                    }
                  temperaturedata[i]=DHT11.temperature;
                  humiditydata[i]=DHT11.humidity;
                    Serial.print(DHT11.temperature*100+DHT11.humidity+digitalRead(4)*10000);                                     
                  } 
                  esp8266_server.handleClient(); 
                  delay(1000);                                       
                    }
    }
      else{
        while(digitalRead(4) == LOW){
          tft.fillScreen(TFT_BLACK);
          tft.setTextFont(1);
          tft.setCursor(40,120);
          tft.print("B01914005,Sukening");
          tft.setTextFont(2);
          tft.setCursor(20,106);
          tft.print("0");
          tft.setCursor(70,106);
          tft.print("10");
          tft.setCursor(122,106);
          tft.print("20");
          tft.drawLine(20,6,20,106,TFT_WHITE);
          tft.drawLine(80,106,80,101,TFT_WHITE);
          tft.drawLine(20,106,140,106,TFT_WHITE);
          tft.drawLine(20,6,140,6,TFT_WHITE);
          tft.drawLine(140,6,140,106,TFT_YELLOW);
          tft.setCursor(2,101);
          tft.print(temperaturedata[0]-10);
          tft.setCursor(2,1);
          tft.print(temperaturedata[0]+10);
          tft.setCursor(2,51);
          tft.print(temperaturedata[0]);
          tft.setCursor(142,106-((humiditydata[i-1]-20)*2));
          tft.print(humiditydata[i-1]);
          tft.setCursor(142,101);
          tft.print(20);
          tft.setCursor(142,1);
          tft.print(70);
          for(j=6;j<110;j=j+5){
            tft.drawLine(20,j,25,j,TFT_WHITE);
            tft.drawLine(135,j,140,j,TFT_YELLOW);
            }
          tft.drawLine(25,56,31,106-((temperaturedata[1]+10-temperaturedata[0])*5),TFT_WHITE);
          tft.drawLine(25,106-((humiditydata[0]-20)*2),31,106-((humiditydata[1]-20)*2),TFT_YELLOW);
          if(digitalRead(4) == HIGH){break;}
          DHT11.read(DHT11PIN);
          for(j=1,x=25;j<i-1;){
            value0 = 106-((temperaturedata[j]+10-temperaturedata[j-1])*5);
            j++;
            value1 = 106-((temperaturedata[j]+10-temperaturedata[j-1])*5);
            tft.drawLine(x,value0,x+6,value1,TFT_WHITE);
            j--;
            value0 = 106-((humiditydata[j]-20)*2);
            j++;
            value1 = 106-((humiditydata[j]-20)*2);
            tft.drawLine(x,value0,x+6,value1,TFT_YELLOW);
            x+=6;
            }
            if(i<20){
              temperaturedata[i]=DHT11.temperature;
              humiditydata[i]=DHT11.humidity;
              i++;
              Serial.print(DHT11.temperature*100+DHT11.humidity+(digitalRead(4)+2)*10000);
              esp8266_server.handleClient();              
              delay(1000);      
                    }
            else{              
              for(i=0;i<19;i++){
                temperaturedata[i]=temperaturedata[i+1];
                humiditydata[i]=humiditydata[i+1];
                    }
                temperaturedata[i]=DHT11.temperature;
                humiditydata[i]=DHT11.humidity;  
                i++;
                Serial.print(DHT11.temperature*100+DHT11.humidity+(digitalRead(4)+2)*10000);
                esp8266_server.handleClient();                
                delay(1000);
                }            
        }
      }
}
void handleDHT(){
    esp8266_server.send(200, "text/plain", String(DHT11.temperature*100+DHT11.humidity));}
void handleUserRequet() {              
  String webResource = esp8266_server.uri();
  bool fileReadOK = handleFileRead(webResource);
  if (!fileReadOK){                                                 
    esp8266_server.send(404, "text/plain", "404 Not Found"); 
  }
}
bool handleFileRead(String path) {            
  if (path.endsWith("/")) {                   
   path = "/index.html";                   
  }   
  String contentType = getContentType(path);   
  if (SPIFFS.exists(path)) {                    
    File file = SPIFFS.open(path, "r");         
    esp8266_server.streamFile(file, contentType);
    file.close();
    return true;                             
  }
  return false;                               
}

String getContentType(String filename){
  if(filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".png")) return "image/png";
  return "text/plain";
}
