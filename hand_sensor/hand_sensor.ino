/*
=====================
 DESCRIPTION:
 Serial sender for SICK DS60 sensor for Gut Feelings Entry Experience
 ====================
 */

// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce2

#include <Bounce2.h>


#define LED_PIN 13

//int buttonPin[2] = {7, 8};
int buttonPin[2] = {2, 3};

// Instantiate a Bounce object
Bounce debouncer[2] = Bounce();

int handHold = 0;

void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);
  
  for (int i=0; i<2; i++)  {

    // Setup button with an internal pull-up :
    pinMode(buttonPin[i],INPUT);
    digitalWrite(buttonPin[i],LOW);

    // After setting up the button, setup the Bounce instance :
    debouncer[i].attach(buttonPin[i]);
    debouncer[i].interval(5); // interval in ms
  }

  //Setup the LED :
  pinMode(LED_PIN,OUTPUT);

}

void loop() {
  delay(10);
  // Update the Bounce instances :
  while (!Serial) {
    delay(10);
  }
  for (int i=0; i<2; i++)  {
      debouncer[i].update();
  }

  // Get the updated value :
  int value[2] = {debouncer[0].read(), debouncer[1].read()};

  // Check that hand is within range (Q1 active, Q2 inactive)
  if ( value[0] == HIGH && value[1] == LOW ) {
    handHold++;
    delay(10);
  } else {
    handHold = 0;
    digitalWrite(LED_PIN, LOW );
  }
// Hand has been held in the correct position for a moment
  if ( handHold >= 5 ) {
    digitalWrite(LED_PIN, HIGH );
    Serial.println('1');
    delay(10);
  } else {
    digitalWrite(LED_PIN, LOW );
    Serial.println('0');
  }
}
