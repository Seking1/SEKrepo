#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t broadcastAddress[] = {0x2C, 0xF4, 0x32, 0x47, 0xCD, 0x84};
typedef struct struct_message {
  String x;
} struct_message;

struct_message myData;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return; 
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
 
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}
String data="";
int tag;
void readd(){
  if(Serial.available()){
    delay(50);
    int size_ = Serial.available();
    char p[size_];
    Serial.readBytes(p,size_);
    //Serial.println("date: ");
    for(int i=0;i<size_;i++)data+=p[i];
    }}
  
void loop() {  
  readd(); 
  if(data!=""){
Serial.println(data);
myData.x= data; 
esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
data="";
}}
