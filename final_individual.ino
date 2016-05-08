#include <IRremote.h>
#include <IRremoteInt.h>

int RECV_PIN = 11; 
IRrecv irrecv(RECV_PIN);
decode_results results;
int buzzer = 8; 
int led=13;
float sinVal; 
int toneVal;
int state=0;
void setup(){
Serial.begin(9600); 
irrecv.enableIRIn(); 
pinMode(buzzer, OUTPUT);  
pinMode(led,OUTPUT);
}
void loop(){
if(irrecv.decode(&results) )
  {
   Serial.println(results.value, HEX);
   if (state == 0 && results.value == 0xFFC23D)
    {
     state = 1;
     Serial.println(state);
    }
   else if(state == 1 && results.value == 0xFFC23D)
    {
     state = 0;
     Serial.println(state);
    }
     irrecv.enableIRIn(); // Start the receiver
  }
if(state == 1) {
   int val;
   val = analogRead(A0);
   function(val);
  }
else {
   digitalWrite(buzzer, LOW);
   digitalWrite(led, LOW);
  }
}
void newtone(byte tonePin, int frequency,int duration) {
int period = 1000000L / frequency;
int pulse = period / 2;
for (long i = 0; i < duration * 1000L; i+= period) {
digitalWrite(tonePin, HIGH);
delayMicroseconds(pulse);
digitalWrite(tonePin, LOW);
delayMicroseconds(pulse);
}
}
void function(int val){
if(val<1020){  
for(int x=0; x<180; x++){
sinVal = (sin(x*(3.1412/180)));
toneVal = 2000+(int(sinVal*1000));
newtone(buzzer,toneVal,10);
analogWrite(led,x);
delay(2);
}
}
else{ 
digitalWrite(buzzer,LOW); 
analogWrite(led,LOW);}
}
