/*
 * Refrigerator Door Ajar Project
 * David Martin, david@hamsterlabs.com
 * 
 * $Id$
 */
/* Globals */
/* Pulse rate in milliSeconds */
int pulseRate = 250;

// Sound output pin
int Squeaker     = 11; // connect to speaker

/* PhotoInterruptor */
int IndicatorLED = 9; // Interrupt Pin, LOW Indicates that the door is ajar
int IPin = 10;        // PhotoInterruptor Input Pin

int isPowerOn = 12;   // Power LED

/* 74HC595 Shift Register Pins */
int datapin = 2; 
int clockpin = 3;
int latchpin = 4;
byte data = 0;
int lights[] = {1, 3, 7, 15, 31, 63, 127, 255};

void setup() {
  /* PhotoInerrutpor Pin is an Input */
    pinMode(IPin, INPUT);
    pinMode(IndicatorLED, OUTPUT);
    pinMode(isPowerOn, OUTPUT);
    pinMode(Squeaker, OUTPUT);
    digitalWrite(isPowerOn, HIGH);

    /*74HC595 Control Pins are Outputs*/
  pinMode(datapin, OUTPUT);
  pinMode(clockpin, OUTPUT);  
  pinMode(latchpin, OUTPUT);
  PowerOnSelfTest();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int status = digitalRead(IPin);
  if ( status == LOW ){
    // In this condition the door is open
    digitalWrite(IndicatorLED, HIGH);
    data++;
  }
  else {
    // in this position the door is closed
    digitalWrite(IndicatorLED, LOW);
      data = 0;
  }
    //shiftWrite(data,LOW);
  binaryDisplay(data, pulseRate);
  while ( data == 127 ){
    if ( VisibleAlarm() == 0 )
    {
      if ( AudibleAlarm() > 0 )
      {
        data = 0;   
      }
    }
  }
}

int AudibleAlarm(){
  int maxTimes = 5;
  while ( digitalRead(IPin) == LOW && maxTimes > 0 )
  {
    maxTimes--;
    binaryDisplay(1+4+16+64, 300);
    binaryDisplay( 2+8+32, 300);
    delay(200);
  }
  
  return maxTimes;
}

int VisibleAlarm(){
  int maxTimes = 5;
  binaryDisplay(data,100);
  while( digitalRead(IPin) == LOW && maxTimes > 0 ){
  //  marquee();
  //  if ( digitalRead(IPin) == LOW ) break;
    pingPong(10);
 //   if ( digitalRead(IPin) == LOW ) break;
//    pingPong(75);
 //   if ( digitalRead(IPin) == LOW ) break;
 //   marquee();

    maxTimes--;
  }
  return maxTimes;
}

void shiftWrite(int desiredPin, boolean desiredState){
  bitWrite(data,desiredPin,desiredState);
  shiftOut(datapin, clockpin, MSBFIRST, data);
  digitalWrite(latchpin, HIGH);
  digitalWrite(latchpin, LOW);
}

void PowerOnSelfTest() {
 playTones(Squeaker); 
  binaryDisplay(127, 500);
  binaryDisplay(0,300);
}
void binaryDisplay(byte d, int delayTime) {
  shiftOut(datapin, clockpin, MSBFIRST, d);
  digitalWrite(latchpin, HIGH);
  digitalWrite(latchpin, LOW);  
  delay(delayTime);
}

void playTones(int IOPin) {
  int tempo = 600;
  int notes[] = {392, 440, 349, 175, 261};
  int dur [] = {1, 1, 2, 2, 1};
  for(int i = 0; i < 5 ; i++ )
  {
    tone(IOPin, 2 * notes[i], dur[i] * tempo);
    delay( tempo / 2 );
  } 
}
void wormCount(){
    
}

void binaryCount()
{
  int delayTime = 200; // time (milliseconds) to pause between LEDs
                        // make this smaller for faster switching

  shiftOut(datapin, clockpin, MSBFIRST, data);
  digitalWrite(latchpin, HIGH);
  digitalWrite(latchpin, LOW);
  
  data++;

  // Delay so you can see what's going on:
  delay(delayTime);
}

void marquee()
{
  int index;
  int delayTime = 200; // Time (milliseconds) to pause between LEDs
                       // Make this smaller for faster switching
  
  // Step through the first four LEDs
  // (We'll light up one in the lower 4 and one in the upper 4)
  
  for(index = 0; index <= 3; index++)
  {
    shiftWrite(index, HIGH);    // Turn a LED on
    shiftWrite(index+4, HIGH);  // Skip four, and turn that LED on
    delay(delayTime);    // Pause to slow down the sequence
    shiftWrite(index, LOW); // Turn both LEDs off
    shiftWrite(index+4, LOW);
  }
}

void pingPong(int delayTime){
  int index;
  if ( delayTime == 0 )
    delayTime = 100; // time (milliseconds) to pause between LEDs
                       // make this smaller for faster switching
  
  // step through the LEDs, from 0 to 7
  
  for(index = 0; index <= 7; index++)
  {
    shiftWrite(index, HIGH);  // turn LED on
    delay(delayTime);   // pause to slow down the sequence
    shiftWrite(index, LOW); // turn LED off
  }

  // step through the LEDs, from 7 to 0
  
  for(index = 7; index >= 0; index--)
  {
    shiftWrite(index, HIGH);  // turn LED on
    delay(delayTime);   // pause to slow down the sequence
    shiftWrite(index, LOW); // turn LED off
  }
}
