#include <Wire.h>
#include <Thinary_AHT10.h>
//#include <DHT.h>
#define SDA_PIN D6
#define SCL_PIN D5
//#define DHTPIN D4
//#define DHTTYPE DHT22
//DHT dht22(DHTPIN,DHTTYPE);
//DHT dht11(D2, DHT11);
AHT10Class AHT10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(SDA_PIN,SCL_PIN);
    //dht11.begin(); 
    //dht22.begin(); 
  if(AHT10.begin(eAHT10Address_Low))
    Serial.println("Init AHT10 Sucess.");
  else
    Serial.println("Init AHT10 Failure.");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(String("aht10")+"Humidity(%RH):\t"+AHT10.GetHumidity()+"%");
  Serial.println(String("")+"Temperature(℃):\t"+AHT10.GetTemperature()+"℃");
   //Serial.print(String("dht22")+"Humidity(%RH):\t"+dht22.readHumidity()+"%");
     //Serial.println(String("")+"Temperature(℃):\t"+dht22.readTemperature()+"℃");
    // Serial.print(String("dht11")+"Humidity(%RH):\t"+dht11.readHumidity()+"%");
    // Serial.println(String("")+"Temperature(℃):\t"+dht11.readTemperature()+"℃");
   //  Serial.println();
  delay(500);
}
