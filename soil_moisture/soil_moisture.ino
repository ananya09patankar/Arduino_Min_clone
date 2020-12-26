#import <Servo.h>
int servoPin = 3; 
int output_value ;
Servo Servo1;
void setup() {
   Serial.begin(9600);
   Serial.println("We will start reading the values from the sensor");
   Servo1.attach(servoPin); 
   delay(2000);
   }

void loop() {
   output_value= analogRead(A0);
   output_value = map(output_value,550,0,0,100);
   Serial.print("Mositure : ");
   Serial.print(output_value+100);
   Serial.println("%");
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
}
