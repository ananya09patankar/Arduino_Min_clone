#include <DHT.h>  
#include <ESP8266WiFi.h>  
#include <WiFiClient.h>  
#include <ThingSpeak.h>  
#define DHTPIN D5  
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE); 
const char* ssid = "vivo1804";  
const char* password = "ananya09";  
WiFiClient client;  
unsigned long myChannelNumber = 889337;  
const char * myWriteAPIKey = "2DELB2SZ9SQO37G3";  
uint8_t temp, hum;  
void setup()  
{  
  Serial.begin(115200);  
  dht.begin();  
  delay(10); 
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(600);  
   Serial.print(".");  
  }    
  Serial.println("Success");  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);  
}  
void loop()   
{  
  static boolean data_state = false;  
  temp = dht.readTemperature();  
  hum = dht.readHumidity();  
  Serial.print("Temperature Value is :");  
  Serial.print(temp);  
  Serial.println("C");  
  Serial.print("Humidity Value is :");  
  Serial.print(hum);  
  Serial.println("%");   
  if( data_state )  
  {  
   ThingSpeak.writeField(myChannelNumber, 1, temp, myWriteAPIKey);  
   data_state = false;  
  }  
  else  
  {  
   ThingSpeak.writeField(myChannelNumber, 2, hum, myWriteAPIKey);  
   data_state = true;  
  }  
  delay(30000); 
} 
