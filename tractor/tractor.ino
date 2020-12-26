const int trigPin = 30;
const int echoPin = 31;

int count=0;
long duration;
int distance;
void setup() {
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
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
if(distance<10 && count==0)
{
Serial.println("Go left");
count++;
delay(5000);
}
else if(distance<10 && count==1)
{
Serial.println("Go right");
count--;
delay(5000);
}
Serial.println(distance);
}
