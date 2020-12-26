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
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT);
pinMode(trigPin2, OUTPUT); 
pinMode(echoPin2, INPUT);
pinMode(trigPin3, OUTPUT); 
pinMode(echoPin3, INPUT);
Serial.begin(9600); 
}
void loop() {
// Clears the trigPin
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
Serial.println(rightcount);
delay(2000);
}








}
