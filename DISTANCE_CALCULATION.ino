#define TRIGGER 5
#define ECHO    4
#define BUZZER 14
 
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "watermonitoring-cbfad.firebaseio.com"
#define FIREBASE_AUTH ""
#define WIFI_SSID "MMUST"
#define WIFI_PASSWORD ""

long duration;
int distance;
const unsigned int MAX_DIST=23;
const unsigned int MIN_DIST=6;
void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting"); 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);
}
 
void loop() {
   
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration/2) / 29.1;

   if ( distance > MAX_DIST) {
   Serial.println("low level water ");
  }else if(distance <  MIN_DIST ){
    Serial.println("water in the tank full");
    digitalWrite(BUZZER,HIGH);
    } else {
    Serial.print(distance);
  Serial.println("Centimeter:");
  Firebase.setInt("Distance",distance);
    
  }
  delay(1000);
}
