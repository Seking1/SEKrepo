#include <Wire.h> 
#include "painlessMesh.h"

#define   MESH_PREFIX     "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555
#define SDA_PIN D2
#define SCL_PIN D3
int ADXL345 = 0x53; // The ADXL345 sensor I2C address
float X_out, Y_out, Z_out;
Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;

// User stub
void sendMessage() ; // Prototype so PlatformIO doesn't complain

Task taskSendMessage( TASK_MILLISECOND * 40 , TASK_FOREVER, &sendMessage );

void sendMessage() {
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
  mesh.sendBroadcast( data );
  taskSendMessage.setInterval(TASK_MILLISECOND * 40); 
}

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN,SCL_PIN,ADXL345);
  Wire.beginTransmission(ADXL345);
  Wire.write(0x2D);
  Wire.write(8);
  Wire.endTransmission();
//mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages
  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable(); 
  delay(10);
}

void loop() {
  // it will run the user scheduler as well
  mesh.update();
}
