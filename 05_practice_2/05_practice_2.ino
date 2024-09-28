 void setup() {
  pinMode(13,OUTPUT);
}

void loop() {
  digitalWrite(13,1);
  delay(1000);
  for(int i=0;i<5;i++){
    digitalWrite(13,0);
    delay(100);
    digitalWrite(13,1);
    delay(100);
  }
  digitalWrite(13,0);
  while(1){}
}
