#include "Arduino.h"

#ifndef PhotoInterruptor_h
#define PhotoInterruptor_h

class PhotoInterruptor
{

  private:
    int sentryLED = 0;          // LED to turn on when the beam is broken
    int flash = 11;             // LED half of photointerruptor
    int IPin  =  7;             // PhotoTransistor
    bool beamBroken = false;    // true for broken beam
  
  public:
    PhotoInterruptor(int iPin, int ledPin);
    void init( int iPin, int ledPin );
    void controlLED(bool led_on);
    bool sample();
    void setSentryLED(int ledPin);
};
#endif
