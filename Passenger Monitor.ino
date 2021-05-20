
#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>


#define FIREBASE_HOST "iot-load.firebaseio.com" //Without http:// or https:// schemes
#define FIREBASE_AUTH "Jnq5ikOjpEl0G2atw5Q6oI8wdLUi1UvtixTPQEGj"
#define WIFI_SSID "Roboment"
#define WIFI_PASSWORD "roboment2018"

int Fuel = 0;
FirebaseData firebaseData;
FirebaseData firebaseData1;
FirebaseData firebaseData2;
FirebaseData ledData1;
FirebaseData ledData2;

FirebaseJson json;


void setup()
{
  Serial.begin(9600);

  pinMode(16,OUTPUT);
  pinMode(D8,INPUT_PULLUP);
  pinMode(D7,INPUT_PULLUP);
  pinMode(D6,INPUT_PULLUP);
  pinMode(D5,INPUT_PULLUP);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(16,1);
    delay(150);
    Serial.print(".");
    digitalWrite(16,0);
    delay(150);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}


void loop() {
  if(WiFi.status() != WL_CONNECTED)
  {
    while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(16,1);
    delay(150);
    Serial.print(".");
    digitalWrite(16,0);
    delay(150);
  }
  }
  Serial.println(analogRead(A0));
  Firebase.setInt(firebaseData1, "/ProjectDevelopment/PassengerMonitor/Fuel",analogRead(A0));
  Firebase.setInt(firebaseData1, "/ProjectDevelopment/PassengerMonitor/D8",digitalRead(D8));
  Firebase.setInt(firebaseData1, "/ProjectDevelopment/PassengerMonitor/D7",digitalRead(D7));
  Firebase.setInt(firebaseData1, "/ProjectDevelopment/PassengerMonitor/D6",digitalRead(D6));
  Firebase.setInt(firebaseData1, "/ProjectDevelopment/PassengerMonitor/D5",digitalRead(D5));
  delay(100);
}
