
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}
String data="";
void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    delay(50);
    int size_ = Serial.available();
    char a[size_];
    Serial.readBytes(a,size_);
    for(int i=0;i<size_;i++)data+=a[i];
    }
    if(data!="")Serial.println(data);
    data ="";
}
