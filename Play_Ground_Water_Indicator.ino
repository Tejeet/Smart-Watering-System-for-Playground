/*
 ***************** TeJEEt Magar ***********************
 *
 * --------Play Ground Water Level Indicator----------
 * 
 *     
 *
 *
 *
 *
 ******************************************************
 */


#include <ESP8266WiFi.h>

  String apiKey = "WXGTF3LOFL2YG7BP"; 
  const char* ssid = "F/401"; 
  const char* password = "rahulyeole"; 

  const char* server = "api.thingspeak.com"; 

   int Relay = 16; 
   int MoistureSensor = 2;

   WiFiClient client; // starts a WiFi client.

void setup() 

{

    Serial.begin(115200);
    
    pinMode(Relay, OUTPUT);
    pinMode(MoistureSensor, INPUT); 

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password); // starts WiFi & login

    while (WiFi.status() != WL_CONNECTED)
              { 
                delay(500);
                Serial.print(".");
              }
    Serial.println("");
    Serial.println("WiFi connected");
}

void loop()

{

  int MSval = analogRead(MoistureSensor);
 
 if (client.connect(server,80))
  Serial.println("Sending Data to Thingspeks");
   
  {

   String postStr = apiKey;
   postStr +="&field1=";
   postStr += String(MSval);
   postStr += "\r\n\r\n"; 
   client.print("POST /update HTTP/1.1\n");
   client.print("Host: api.thingspeak.com\n");
   client.print("Connection: close\n");
   client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
   client.print("Content-Type: application/x-www-form-urlencoded\n");
   client.print("Content-Length: ");
   client.print(postStr.length());
   client.print("\n\n");
   client.print(postStr);
   
   Serial.println("Data is Sent on thingSpeks Channel");
 

   Serial.print("Water lavel is :");
   Serial.print(MSval);
   Serial.print("\n\n");
}
    if((MSval) == 0)
       {
       delay(1000);
       digitalWrite(Relay, HIGH);
       }
   else 
       { 
        delay(100);
        digitalWrite(Relay, LOW);
       }
} 
