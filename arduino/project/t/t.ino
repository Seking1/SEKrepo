#include <Wire.h>
#define slave_adr 0x76//I2C写传感器地址(0xEC)前7位
#define SDA_PIN D2//数据脚
#define SCL_PIN D3//时钟脚
#define exp18 262144//二的18次方，用于将二进制转为十进制
#define RESET 0x06//RESET指令
#define INT_SRC 0x8d//读寄存器指令(10+寄存器地址0x0d：10001100)
#define READ_PT 0x10//让传感器发送温度和压力数据指令
int DEV_RDY = 0;
int error_sign=0;
void setup() {
    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN);//初始化
    re: delay(1000);
    Wire.beginTransmission(slave_adr); 
    Wire.write(RESET); //发送重置指令            
    error_sign = Wire.endTransmission(0);//error_sign=0: 成功;1: 数据量超过传送缓存容纳限制;
                                         //2: 传送地址时收到 NACK(无应答);3: 传送数据时收到 NACK;4: 其它错误
    if(error_sign!=0){
      Serial.print("reset commend transimisson error,error code:");
      Serial.println(error_sign);
      goto re;//失败则重新初始化
    }
    Serial.println("reset ok");
    delay(10);       
    Wire.beginTransmission(slave_adr); 
    Wire.write(INT_SRC); //读寄存器查看准备状态          
    error_sign = Wire.endTransmission(0);
    if(error_sign!=0){
      Serial.print("read register error，error code：");
      Serial.println(error_sign);
      goto re;//失败则重新初始化
    }
    Wire.requestFrom(slave_adr,8);
    DEV_RDY=Wire.read();
    DEV_RDY = bitRead(DEV_RDY,6); 
    if(DEV_RDY==1)Serial.println("READY");
    else goto re;//失败则重新初始化
    delay(1000);
     }

int tp[48]={0};//温度和压力数组
int h[24]={0};//高度数组
void tem(){
    int *p=&tp[7];int tem=0;int pre=0;
    Wire.beginTransmission(slave_adr); 
    Wire.write(0x48); //写入信道和模拟量精度              
    error_sign = Wire.endTransmission(0);
    if(error_sign!=0){
      Serial.println("write 0x48 commend error");
      goto endline;
    }
    delay(40); 
    Wire.beginTransmission(slave_adr); 
    Wire.write(READ_PT);//发送读温度和压力指令               
    error_sign = Wire.endTransmission(0);
    if(error_sign!=0){
      Serial.println("read PT value error");
      goto endline;
    }
    Wire.requestFrom(slave_adr,6);//读6个字节的数据
    
    while(Wire.available()){
      byte a=Wire.read();//读一个字节数据
      int i=0;
      int *b = p;
        for(int j=0;j!=8;j++){//取最低位送入数组，可以同时与计算数据进行，但会影响程序可读性，增加复杂度
          i = a%2;
          *b = i;
          b--;
          a=a>>1;
          }
      p=p+8;
    }//正确排列48位二进制数据
      for(int z=5,f=exp18;z<24;z++){
        tem+=f*tp[z];f/=2;
        }//计算温度数据
        if(tp[4]==1){
          tem=-1*(524288-tem);
        }//判断正负
        Serial.print("tem: ");Serial.print(float(tem)/100);Serial.println("摄氏度^c"); 
      for(int z=28,f=exp16;z<48;z++){
        pre+=f*tp[z];f/=2;
        }//计算压力
        Serial.print("pre: ");Serial.print(float(pre)/100);Serial.println("毫巴mbar");
        endline: error_sign++;//无实际作用，为跳转语句设置语句运行
      }
           
void high(){
  int *p=&h[7];int hg=0;
    Wire.beginTransmission(slave_adr); 
    Wire.write(0x31);               
    error_sign = Wire.endTransmission(0);
    if(error_sign!=0){
      Serial.print(error_sign);
      Serial.println("read high value error");
      goto endl;
    }
    Wire.requestFrom(slave_adr,3);
    while(Wire.available()){
    byte aa=Wire.read();
    int i=0;
    int *b=p;
    for(int j=0;j!=8;j++){
      i=aa%2;
      *b=i;
      b--;
      aa=aa>>1;
      }
      p=p+8;
      }  
      for(int z=4,f=exp16;z<24;z++){
        hg+=f*h[z];f/=2;
        }
        Serial.print("h: ");Serial.print(float(hg)/100);Serial.println("米m");
        endl: error_sign++;
      }
  
void loop() {  
   tem(); 
   delay(10);
    high();
    delay(950);
  }
