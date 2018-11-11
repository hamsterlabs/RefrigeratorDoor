#include "Arduino.h"
#include "PhotoInterruptor.h"


PhotoInterruptor::PhotoInterruptor(int iPin, int ledPin){
    init(iPin, ledPin);
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
    // turn on the LED, then check if the beam is broken
    // if the beam is broken it is logical HIGH so return true   ~ 5 VDC
    // if the beam is not broken it is logical LOW, return false ~ 0 VDC
    controlLED(true);
    
    beamBroken = ( digitalRead(IPin) == HIGH ) ? true : false;

    // if there is a pin to control it is Active Low
    if ( this->sentryLED != 0 ){
      digitalWrite(this->sentryLED, (beamBroken) ? LOW : HIGH );
    }
      
    controlLED(false);
    return beamBroken;   // true if the beam is broken
  }

  void PhotoInterruptor::setSentryLED(int ledPin){
    this->sentryLED = ledPin;
    pinMode(this->sentryLED, OUTPUT);
  }

  
