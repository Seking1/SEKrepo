//接收
#include <ESP8266WiFi.h>
#include <espnow.h>

//接收数据保存的结构体和发送方一致
typedef struct struct_message {
    String x;
} struct_message;
struct_message myData;

void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  String data = myData.x+'#';
  Serial.print(data);
}
void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop(){
}
