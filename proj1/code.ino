const int trigPin = 4;
const int echoPin = 5;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034

long duration;
float distanceCm;

void setup() {
  Serial.begin(115200);
  
  pinMode(1, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  // Convert to inches
  

  if (distanceCm > 26){
    digitalWrite(1, HIGH);
  }else{
    digitalWrite(1,LOW);
  }
  
  Serial.println(distanceCm);
  delay(500);
}

