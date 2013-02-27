/*
  PureData example
  
*/

#include <PureData.h>

// constants won't change. They're used here to 
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

void setup() 
{ 
  // Have the PureData library setup
  PureData.begin(); 

  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(ledPin, OUTPUT);     

  // initialize the pushbutton pin as an input (with pull-up):
  pinMode(buttonPin, INPUT);     
  digitalWrite(buttonPin, HIGH);
} 

void loop() 
{ 
  float receivedValue;

  // check for a value from PD tagged testx and then
  // send it back to PD on testy
  if(PureData.receive("testx", &receivedValue)) {
    PureData.send("testy", receivedValue);
  }

  // check for a value from PD tagged LED
  if(PureData.receive("led", &receivedValue)) {
    if(receivedValue == 0.0) {
      // turn LED off
      digitalWrite(ledPin, LOW);
    } else {
      // turn LED on
      digitalWrite(ledPin, HIGH);
    }
  }

  // have a static variable for
  // remembering buttonstate between
  // calls to this loop method
  static int lastState = LOW;

  // send the button as a value
  const int buttonState = digitalRead(buttonPin);
  if(buttonState != lastState) {
    if(buttonState == HIGH) {
      PureData.send("button", 1.0);
    } else {
      PureData.send("button", 0.0);
    }
  
    // keep track of button state changes
    // so we only send a new value on change
    lastState = buttonState;
  }

  // tick a send every second
  if(!(millis() & 1023)) {
    PureData.send("tick", (float)millis() / 1000.0);
  }
}

