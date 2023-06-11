#include <Wire.h> 
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#define SDA_PIN D2
#define SCL_PIN D3
const char *ssid = "seking8266test";
const char *password = "12345678";
ESP8266WiFiMulti wifiMulti; 
int ADXL345 = 0x53; // The ADXL345 sensor I2C address
float X_out, Y_out, Z_out;  // Outputs
void setup() {
  Serial.begin(9600); // Initiate serial communication for printing the results on the Serial monitor
  Wire.begin(SDA_PIN,SCL_PIN,ADXL345); // Initiate the Wire library
  // Set ADXL345 in measuring mode
  Wire.beginTransmission(ADXL345); // Start communicating with the device
  Wire.write(0x2D); // Access/ talk to POWER_CTL Register - 0x2D
  // Enable measurement
  Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable
  Wire.endTransmission();
  delay(10);
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
  String data = "x"+String(int(X_out))+"y"+String(int(Y_out))+"z"+String(int(Z_out));
  Serial.println(data);
  delay(40);
}
