#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiUdp.h> 
const char* ssid = "RenegadE";
const char* password = "135792460a";
const char* mqttServer = "49.233.60.32";

const char* host = "49.233.60.32";   
const int httpPort = 3003; 
  
WiFiUDP Udp;
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);  

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);   
  connectWifi();    
  mqttClient.setServer(mqttServer, 1883); 
  connectMQTTServer();
  String topicString = "dev/" + WiFi.macAddress();
  Serial.println(topicString); 
}
 
void loop() {   
  if (mqttClient.connected()) {     
  String topicString = "dev/" + WiFi.macAddress();
  char publishTopic[topicString.length() + 1];  
  strcpy(publishTopic, topicString.c_str());
  String messageString ="";
  while(Serial.available()){    
  char a = Serial.read();
  //Serial.print(a);
  messageString = messageString + String(a);}delay(200);
  
  if(messageString !=""){
    Serial.print("message: ");
  Serial.println(messageString);
  char publishMsg[messageString.length() + 1];   
  strcpy(publishMsg, messageString.c_str());
  
  if(mqttClient.publish(publishTopic, publishMsg)){
    //Serial.print("Publish Topic:");Serial.println(publishTopic);
    //Serial.print("Publish message:");Serial.println(publishMsg);    
  } else {
    //Serial.println("Message Publish Failed."); 
  }
  
// data upload part

    mqttClient.loop();
  }} else {                  
    connectMQTTServer();    
  }
}
 
void connectMQTTServer(){
  String clientId = "esp8266-" + WiFi.macAddress();
  if (mqttClient.connect(clientId.c_str())) { 
    Serial.println("MQTT Server Connected.");
    Serial.println("Server Address: ");
    Serial.println(mqttServer);
    Serial.println("ClientId:");
    Serial.println(clientId);
    delay(3000);
  } else {
    Serial.print("MQTT Server Connect Failed. Client State:");
    Serial.println(mqttClient.state());
    delay(1000);
  }   
}
 
void connectWifi(){   
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected!");  
  Serial.println(""); 
  delay(2000);
}
