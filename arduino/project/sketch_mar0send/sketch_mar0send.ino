#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Wire.h> 
#define SDA_PIN D2
#define SCL_PIN D3

uint8_t broadcastAddress[] = {0xE0, 0x98, 0x06, 0x18, 0x7F, 0xCC};
int ADXL345 = 0x53; // The ADXL345 sensor I2C address
float X_out, Y_out, Z_out;

typedef struct struct_message {
  int x;
  int y;
  int z;
} struct_message;

struct_message myData;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}

void setup() {
  //初始化串行监视器以进行调试
  Serial.begin(115200);
Wire.begin(SDA_PIN,SCL_PIN,ADXL345);
Wire.beginTransmission(ADXL345); 
Wire.write(0x2D);
Wire.write(8);
Wire.endTransmission();

  WiFi.mode(WIFI_STA);

  //立即初始化ESP
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return; 
    delay(10);
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
   Wire.beginTransmission(ADXL345);
  Wire.write(0x32); // Start with register 0x32 (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  X_out = ( Wire.read()| Wire.read() << 8); 
  if(X_out>65000)X_out=int(X_out-65536);else  X_out = int(X_out);if(X_out<0)X_out=abs(X_out)+1000;else X_out=X_out+2000;
  Y_out = ( Wire.read()| Wire.read() << 8);
  if(Y_out>65000)Y_out=int(Y_out-65536);else  Y_out = int(Y_out);if(Y_out<0)Y_out=abs(Y_out)+3000;else Y_out=Y_out+4000;
  Z_out = ( Wire.read()| Wire.read() << 8);
  if(Z_out>65000)Z_out=int(Z_out-65536);else  Z_out = int(Z_out);if(Z_out<0)Z_out=abs(Z_out)+5000;else Z_out=Z_out+6000;

  myData.x = X_out;
  myData.y = Y_out;
  myData.z = Z_out;
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  delay(100);
}
