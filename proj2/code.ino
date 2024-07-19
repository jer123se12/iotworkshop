#include <WiFi.h>
#include "ThingSpeak.h"

const char* WIFI_NAME = "iotworkshop";
const char* WIFI_PASSWORD = "88888888";

const int myChannelNumber = 2602387;
const char* myApiKey = "4XKMK7NEVFZ1ME0I";
const char* server = "api.thingspeak.com";

const int trigPin = 4;
const int echoPin = 5;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034

long duration;
float distanceCm;
WiFiClient client;

void setup() {
  Serial.begin(115200);
  
  pinMode(1, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  Serial.println("\nConnecting");
  while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(100);
  }
  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);
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
  ThingSpeak.setField(1,distanceCm);

  int x = ThingSpeak.writeFields(myChannelNumber,myApiKey);
  
  Serial.println(distanceCm);
  delay(20000);
}
