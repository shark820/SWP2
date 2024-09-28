#define PIN_LED  9
#define PIN_TRIG 11
#define PIN_ECHO 12

// configurable parameters
#define SND_VEL 346.0     
#define INTERVAL 100      
#define PULSE_DURATION 10 
#define _DIST_MIN 100.0   
#define _DIST_MAX 300.0

#define TIMEOUT ((INTERVAL / 2) * 1000.0)
#define SCALE (0.001 * 0.5 * SND_VEL)

unsigned long last_sampling_time;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIG, LOW);
  analogWrite(PIN_LED,0);
  
  Serial.begin(57600);
}

void loop() {
  float distance,brightness;

  if (millis() < (last_sampling_time + INTERVAL))
    return;

  distance = USS_measure(PIN_TRIG, PIN_ECHO); // read distance
  
  if(distance> _DIST_MAX){
    distance=_DIST_MAX+10.0;
  }
  else if(distance< _DIST_MIN){
    distance=_DIST_MIN-10.0;
  }

  if(100.0<=distance && distance <=300.0){
    brightness= 255.0/100.0 * (100.0 - ( (distance-200.0 > 0) ? (distance-200.0) : (200.0-distance) ));
  }
  else {
    brightness=0;
  }

  analogWrite(PIN_LED,int(brightness));

  Serial.print("Min:");        Serial.print(_DIST_MIN);
  Serial.print(",distance:");  Serial.print(distance);
  Serial.print(",Max:");       Serial.println(_DIST_MAX);
  
  last_sampling_time += INTERVAL;
}

float USS_measure(int TRIG, int ECHO)
{
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(PULSE_DURATION);
  digitalWrite(TRIG, LOW);
  
  return pulseIn(ECHO, HIGH, TIMEOUT) * SCALE; // unit: mm
}
