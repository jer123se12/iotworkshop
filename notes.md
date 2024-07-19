Thing to take note of:
Ask for everyone created account, using Chrome

Then wait

Select esp32-s3

Left code

Right circuit

Explain pins:
	- 3v3: 3.3
	- 5v: 5v
	- GND: ground
	- numbers: gpio 
		- for each pin they can be turned on and off, 0v / 3.3v
notes:
VP and VN can only be used for input

Click plus LED
LED:
How to turn it on
Potential difference
Voltage at long leg > short leg

Use pin to control
Connect to 1
Connect to gnd
Pin on, 5v -> ground so light on
Pin off, both 0v so off



Left side
Code
C++
Using Arduino library
	makes life easier
	diff company diff commands
	diff way of controlling
	standardise 
	know Arduino -> use many microcontrollers
Setup:
	ran once at start
Loop:
	keeps looping

To use pin:
	tell you want to use the pin
`pinMode()`
	first is pin next is type input/output

Check if it works
Talk about delay
```
void setup() {
  // put your setup code here, to run once:
  pinMode(1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000); // this speeds up the simulation
  digitalWrite(1, HIGH);
  delay(1000);
  digitalWrite(1, LOW);
}
```


Pause here


TEST CODE ON ARDUINO
Install:ESP32 in boards

Select esp32s3 Dev module

Blink done
Go to slides
get ultrasond working
Delete code
Click plus add ultrasound


Search up how to use
As chances are someone already written about it
https://randomnerdtutorials.com/esp32-hc-sr04-ultrasonic-arduino/
Copy definitions as well
Define: variables that you cannot change

** TRIG: 4 ECHO: 5

Get distance in cm

To test:
Turn light off when > 26 degrees celcius 

```
if (distance > 26){
    digitalWrite(1, HIGH);
  }else{
    digitalWrite(1,LOW);
  }
```


BREAK



How see on computer?

Serial
Send text messages from the Arduino to u

First start the chat with Arduino
Can use autofill

The number is the speed
There are set speeds

serial.println

Delay 500 for it to run faster




```
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
```





* Google Chrome needed if not not working

Angle brackets vs quotes:
When you use angle brackets, the compiler searches for the file in the include path list. When you use double quotes, it first searches the current directory (i.e. the directory where the module being compiled is) and only then it'll search the include path list.

https://www.upesy.com/blogs/tutorials/how-to-connect-wifi-acces-point-with-esp32

Lets search it up and copy the code
** create wifi client `WiFiClient client;`
And then you connect wifi

```
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
```

Compilation takes very long



THINKSPEAK
Signup to think speak
Use school email

Dashboard


Create a new channel

Each channel store data like column in spreadsheet

Create 1 channels, distance

The rest no need






Use thingspeak library
Search how to use this
https://www.arduino.cc/reference/en/libraries/thingspeak/ 

Lets include lib


`#include "ThingSpeak.h"`

Store Channel and keys
Identify which channel

Keys: password
```
const int myChannelNumber = 2601373;
const char* myApiKey = "W7TL4MVK7XF068Z8";
const char* server = "api.thingspeak.com";
```

Then we need to initialise the connection

```
ThingSpeak.begin(client);
```

To write fields, we can use 
`int x = ThingSpeak.writeField(myChannelNumber, 1, number, myWriteAPIKey);`

Need delay so we don't spam the server

```
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

```














Add function to turn on light


Go back to think speak create another field
This field used to store the button state
Called button
Use thingspeak to control the button

To change the state of the button

Use the url on the left to set it

Call the url, changed the field 1 to 2 and then call the url to edit the field number

Lets make it so that if it is one the light is on and when 0 light is off

https://github.com/mathworks/thingspeak-arduino

Use example

Change channel and api key and name of variable

Change if statements 





















