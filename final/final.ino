#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include <DHT.h>

#define SS_PIN 53
#define RST_PIN 5
#define DHTPIN 2
#define DHTTYPE DHT11 

Servo Servo1;
MFRC522 mfrc522(SS_PIN, RST_PIN);  
DHT dht(DHTPIN, DHTTYPE);

int incoming_message;
int count=0;
int servoPin = 3; 
int output_value ;
int flag=0;
const int trigPin = 30;
const int echoPin = 31;
const int trigPin2 = 26;
const int echoPin2 = 27;
const int trigPin3 = 23;
const int echoPin3 = 22;
int leftcount=0,rightcount=0;
long duration;
int distance,distance2,distance3;


void setup() {
   Serial.begin(9600);
   Serial.print("Welcome type 0. help() to get the list of APIs called");
   Servo1.attach(servoPin); 
   delay(2000);
   pinMode(trigPin, OUTPUT); 
   pinMode(echoPin, INPUT);
   pinMode(trigPin2, OUTPUT); 
   pinMode(echoPin2, INPUT);
   pinMode(trigPin3, OUTPUT); 
   pinMode(echoPin3, INPUT);
   mfrc522.PCD_Init();
   SPI.begin();  
   dht.begin();
   }

void loop() {
initial:
 if (Serial.available() > 0) {
  incoming_message= Serial.read();
  
  Serial.println(incoming_message);
  if ((incoming_message -48 )==0)
  {
    Serial.println("The following are the list of commands");
    Serial.println("1. moisture() : To see the soil moisture in real time and debug with the sprinkler");
    Serial.println("2. trplow(): To see the number of entities on the left and the right hand side of the plowing lanes");
    Serial.println("3. rfid(): To have the concept of supply chain management and diffrenciate between goods");
    Serial.println("4. temp(): To see the current temperature and humidity at once"); 
    Serial.println("5. ps(): View the list of processes");
  }
  if ((incoming_message -49 )==0) 
  {
   Serial.println("We will start reading the values from the sensor");
   Serial.print("Mositure : ");
   Serial.print(output_value+100);
   Serial.println("%");
  }
  if ((incoming_message -50) == 0) 
  {
    Serial.println("No of entities on the right are");
    Serial.println(rightcount);
    Serial.println("No of entities on the left are");
    Serial.println(rightcount);
  }
  if ((incoming_message -51) == 0) goto rfid;
  if ((incoming_message -52) == 0)
  {


    
    float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  
  if (isnan(h) || isnan(t) || isnan(f)) 
    Serial.println("One of the values for the DHT sensor has not been read");
  // Compute heat index
  // Must send in temp in Fahrenheit!
  float hi = dht.computeHeatIndex(f, h);

  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hi);
  Serial.println(" *F");
  }
   if ((incoming_message -53) == 0 &&flag==0)
   { Serial.println("2");
     Serial.println("tractor");
     Serial.println("moist");
     flag=1;}
   if ((incoming_message -53) == 0 &&flag==1)
   { Serial.println("3");
   Serial.println("tractor");
     Serial.println("temp");
     Serial.println("moist");
     flag=1;}
 }
  
imp_read:
  //Moisture
   output_value= analogRead(A0);
   output_value = map(output_value,550,0,0,100);
   delay(1000);
   if(output_value<-60)
   {
    for(int pos=0;pos<180;pos++)
    {Servo1.write(pos); 
   delay(15);  }
   for(int pos=180;pos>0;pos--)
    {Servo1.write(pos); 
   delay(15);  }
   }



// tractor

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;



digitalWrite(trigPin2, LOW);
delayMicroseconds(2);
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
duration = pulseIn(echoPin2, HIGH);
distance2= duration*0.034/2;



digitalWrite(trigPin3, LOW);
delayMicroseconds(2);
digitalWrite(trigPin3, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin3, LOW);
duration = pulseIn(echoPin3, HIGH);
distance3= duration*0.034/2;

if(distance2<10)
{
  leftcount--;
  Serial.println(leftcount);
  delay(1000);
}
if(distance3<10)
{
  rightcount--;
  Serial.println(rightcount);
  delay(1000);
}

if(distance<10 && leftcount==rightcount)
{
Serial.println("Go left");
leftcount++;
Serial.println(leftcount);
delay(2000);
}

else if(distance<10 && leftcount<rightcount)
{
Serial.println("Go left");
leftcount++;
Serial.println(leftcount);
delay(2000);
}

else if(distance<10 && leftcount>rightcount)
{
Serial.println("Go right");
rightcount++;
delay(2000);
}


goto initial;


//RFID
rfid:
    // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "73 57 37 2D" ||content.substring(1) == "52 C6 12 1F" || content.substring(1) == "52 6F 11 1F") 
  {
    Serial.println("Authorized access \n");
    count+=1;
    Serial.println("The material present is=");
    Serial.println(count);
    Serial.println();
    delay(3000);
  }
 
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }

   goto initial;

}
