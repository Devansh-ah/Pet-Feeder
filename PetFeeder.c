#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include<Servo.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include <Wire.h> 

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800,60000);

Servo servo;

#define WIFI_SSID "Redmi"
#define WIFI_PASS "devansh1"

#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "devansh1"
#define MQTT_PASS "aio_xMAV53joO7Neye8iWq0aAM7pRUtx"

int SERVO_PIN = D3;    // The pin which the servo is attached to
int CLOSE_ANGLE = 0;  // The closing angle of the servo motor arm
int OPEN_ANGLE = 120;  // The opening angle of the servo motor arm
int  hh, mm, ss;
int feed_hour = 0;
int feed_minute = 0;

//Set up MQTT and WiFi clients
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);

//Set up the feed you're subscribing to
Adafruit_MQTT_Subscribe onoff = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/onoff");
boolean feed = true; // condition for alarm

void setup()
{
  Serial.begin(9600);
  timeClient.begin();
  Wire.begin(D2, D1);
  
  
  //Connect to WiFi
  Serial.print("\n\nConnecting Wifi... ");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  Serial.println("OK!");

  //Subscribe to the onoff feed
  mqtt.subscribe(&onoff);
  servo.attach(SERVO_PIN);
  servo.write(CLOSE_ANGLE);
  
  
}

void loop()
{
   MQTT_connect();
   timeClient.update();
   hh = timeClient.getHours();
   mm = timeClient.getMinutes();
   ss = timeClient.getSeconds();
  
  
 
  Adafruit_MQTT_Subscribe * subscription;
  while ((subscription = mqtt.readSubscription(5000)))
  {
    
    if (subscription == &onoff)
    {
      //Print the new value to the serial monitor
      Serial.println((char*) onoff.lastread);
     
    if (!strcmp((char*) onoff.lastread, "ON"))
      {
        
        open_door();
        delay(5000);
        close_door();
       }
      if (!strcmp((char*) onoff.lastread, "morning"))
      {
        feed_hour = 10;
        feed_minute = 30;
      }
      if (!strcmp((char*) onoff.lastread, "afternoon"))
      {
        feed_hour = 13;
        feed_minute = 30; 
      }
      if (!strcmp((char*) onoff.lastread, "evening"))
      {
        feed_hour = 18;
        feed_minute = 30; 
      }
     }
   }
   if( hh == feed_hour && mm == feed_minute &&feed==true) //Comparing the current time with the Feed time

    { 
      open_door();
      delay(5000);
      close_door();
      feed= false; 
      }
}

void MQTT_connect() 
{
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) 
  {
    return;
  }

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) // connect will return 0 for connected
  { 
       
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) 
       {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  
}

void open_door(){
  
  servo.write(OPEN_ANGLE);   // Send the command to the servo motor to open the trap door
}

void close_door(){
  
  servo.write(CLOSE_ANGLE);   // Send the command to the servo motor to close the trap door
}
 
