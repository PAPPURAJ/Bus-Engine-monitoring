#include "FirebaseESP8266.h"  // Install Firebase ESP8266 library
#include <ESP8266WiFi.h>


#define FIREBASE_HOST "iot-load.firebaseio.com" //Without http:// or https:// schemes
#define FIREBASE_AUTH "Jnq5ikOjpEl0G2atw5Q6oI8wdLUi1UvtixTPQEGj"
#define WIFI_SSID "Roboment"
#define WIFI_PASSWORD "roboment2018"
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float Celsius = 0;
int sender;
int Break = 0;
int Load = 0;
FirebaseData firebaseData;
FirebaseData firebaseData1;
FirebaseData firebaseData2;
FirebaseData ledData1;
FirebaseData ledData2;

FirebaseJson json;


void setup()
{
  pinMode(D4,INPUT_PULLUP);
  pinMode(D5,INPUT_PULLUP);
  pinMode(D6,INPUT_PULLUP);
  pinMode(D7,INPUT_PULLUP);
  pinMode(D8,OUTPUT);
  Serial.begin(9600);
  sensors.begin();
  pinMode(16,OUTPUT);
  
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

  if(digitalRead(D5)==0) Break=4;
  else if(digitalRead(D6)==0) Break=3;
  else if(digitalRead(D7)==0) Break=2;
  else Break=1;

  Load=digitalRead(D4)+1;
  sensors.requestTemperatures();
  Celsius = sensors.getTempCByIndex(0);
  
  Serial.println(Celsius);
  if (Celsius<=10) Celsius=10;
  else if (Celsius>=99) Celsius=99;
  sender=Break*1000+Load*100+Celsius;
  Firebase.setInt(firebaseData1, "/ProjectDevelopment/VehicleMonitor/sender",sender);
  if (Firebase.getString(ledData1, "/ProjectDevelopment/VehicleMonitor/Switch"))
  {
    if(ledData1.stringData()=="false")
    digitalWrite(D8, 0);
    else digitalWrite(D8, 1);
  }
  delay(100);
}
