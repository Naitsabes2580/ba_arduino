/*
  Serial Event example
 
 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and 
 clears it.
 
 A good test for this is to try it with a GPS receiver 
 that sends out NMEA 0183 sentences. 
 
 Created 9 May 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/SerialEvent
 
 */

#include <Servo.h>
Servo myservo;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int led = 13;
int i = 100;
int pos = 0;

void setup() {
  // initialize serial:
  Serial.begin(9600);
    pinMode(led, OUTPUT);     
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  myservo.attach(9);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(">" + inputString); 
    char inputChars[inputString.length()];
    inputString.toCharArray(inputChars,inputString.length()+1);
    pos = atoi(inputChars);
    Serial.println(pos);
    if (pos > 0 && pos < 270)
    {
      myservo.write(pos);
    }

    // clear the string:
    inputString = "";
    stringComplete = false;
    Serial.flush();
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString if it's not a line ending
    if (inChar != '\n')
    {
      inputString += inChar;
    }
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}


