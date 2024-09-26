#define LED 7

void setup() {
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()<=0) return;
  
  int period=Serial.read();
  int duty=Serial.read();
  
}

void sep_period
