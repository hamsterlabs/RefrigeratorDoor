#include "Arduino.h"
#include "PhotoInterruptor.h"


PhotoInterruptor::PhotoInterruptor(){
    init();
  }

PhotoInterruptor::PhotoInterruptor(int iPin, int ledPin){
    init(iPin, ledPin);
  }

  void PhotoInterruptor::init(){
    init(11, 10);
  }
  
  void PhotoInterruptor::init( int iPin, int ledPin ){
    this->flash = ledPin;
    this->IPin  = iPin;
    pinMode(this->IPin, INPUT);
    pinMode(this->flash, OUTPUT);
  }
  
  void PhotoInterruptor::controlLED(bool led_on){
    if ( led_on )
      digitalWrite(flash, HIGH);
    else 
      digitalWrite(flash, LOW);
  }

  bool PhotoInterruptor::sample(){
    controlLED(true);
    beamStatus = ( digitalRead(IPin) == HIGH ) ? true : false;
    
    if ( this->sentryLED != 0 ){
      digitalWrite(this->sentryLED, (beamStatus) ? HIGH : LOW );
    }
      
    controlLED(false);
    return beamStatus;
  }

  void PhotoInterruptor::setSentryLED(int ledPin){
    this->sentryLED = ledPin;
    pinMode(this->sentryLED, OUTPUT);
  }
  
