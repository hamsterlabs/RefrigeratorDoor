#include "Arduino.h"
#include "PhotoInterruptor.h"


int PhotoLED = 6;
int IndicatorLED = 7;
int IPin = 5;
PhotoInterruptor pi;

void setup(){
  pi = new PhotoInterruptor(IPin, PhotoLED);
  pi.setSentryLED(IndicatorLED);
//    pinMode(IPin, INPUT);
//    pinMode(PhotoLED, OUTPUT);  
//    pinMode(IndicatorLED, OUTPUT);
//    digitalWrite(IPin, HIGH);
//    digitalWrite(IndicatorLED, LOW);
}
void loop(){
 
  pi.sample();
 
 // if ( digitalRead(transistor) == HIGH) {
 //   digitalWrite(IndicatorLED, HIGH);
 // }
 // else {
 //   digitalWrite(IndicatorLED, LOW);
//  }
  
}

/*
void setupTest(){
 pinMode(transistor, INPUT);
 pinMode(IPin, OUTPUT);  
 pinMode(IndicatorLED, OUTPUT);
}

void testLights{
  digitalWrite(IPin, HIGH);
  digitalWrite(IndicatorLED, LOW);
  delay(100);
  
  digitalWrite(IPin, LOW);
  digitalWrite(IndicatorLED, HIGH);
  delay(100);
}
*/
