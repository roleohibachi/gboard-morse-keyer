//This code is specifically for sparkfun pro micro
//it's pretty much te same as a leonardo or arduino nano
//only important difference is with the LED pins
//there's no builtin LED on pin 13 (or anywhere)
//there's an "RX" led, bright yellow, on pin 17. Output is INVERTED.
//there's a "TX" led, dim green, accessed by macros TXLED1 and TXLED0.
//if you're using a different board, rewrite the LEDs or disable them.

#include "Keyboard.h"

#define ditPin 0
#define dahPin 1

//used for display
#define ledPin 17 //specific to sparkfun pro micro 
volatile boolean diting, dahing;

void setup()
{

  //display
  diting = false;
  dahing = false;
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Keyboard.begin(); //Init keyboard emulation

  pinMode(ditPin, INPUT_PULLUP);
  pinMode(dahPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ditPin), dit, CHANGE);
  attachInterrupt(digitalPinToInterrupt(dahPin), dah, CHANGE);

}

void loop()
{
  //this loop's execution time is sufficient to debounce the switches.
  //delay(100);

  if (diting) {
    digitalWrite(ledPin, LOW); //inverted - LOW is on, specific to sparkfun pro micro 
    Keyboard.press('.');
  } else {
    digitalWrite(ledPin, HIGH);
    Keyboard.release('.');
  }
  
  if (dahing) {
    digitalWrite(ledPin, LOW); //inverted - LOW is on, specific to sparkfun pro micro 
    Keyboard.press('-');
  } else {
    digitalWrite(ledPin, HIGH);
    Keyboard.release('-');
  }

}

void dit() {
  diting = !digitalRead(ditPin); //inverted because INPUT_PULLUP
}

void dah() {    
  dahing = !digitalRead(dahPin); //inverted because INPUT_PULLUP
}
