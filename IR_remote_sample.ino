/*
IR_remote_tester_and_detector
Connect the output pin of Infrared remote to DIG 2 
Connect an LED to pin 13.
*/
#include <IRremote.h> 
const int irReceiverPin = 2; 
const int ledPin = 13;
IRrecv irrecv(irReceiverPin); //create an IRrecv object
decode_results decodedSignal; //stores results from IR sensor

void setup()
{
pinMode(ledPin, OUTPUT);
irrecv.enableIRIn(); // Start the receiver object
}
boolean lightState = false; //keep track of whether the LED is on
unsigned long last = millis(); //remember when we last received an IRmessage
void loop()
{
if (irrecv.decode(&decodedSignal) == true) //this is true if a message has been received

{
if (millis() - last > 250) { //has it been 1/4 sec since last message
lightState = !lightState; //toggle the LED
digitalWrite(ledPin, lightState);
}
last = millis();
irrecv.resume(); // watch out for another message
}
}
