/**
* @file    serialtest2.ino
* @author  Sebastian Krösche
* @version V0.0.1
* @date    28 April 2013
* @brief   Processing file for arduino parsing program
* @details Processing file for arduino parsing program
*
*
*/
#define SERVO_PAN_MIN 0
#define SERVO_PAN_MAX 180
#define SERVO_TILT_MIN 0
#define SERVO_TILT_MAX 180

#include <Servo.h>
Servo servoPan;
Servo servoTilt;

int led = 13;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

int pos = 0;

void setup() {
  // initialize serial:
  Serial.begin(9600);
    pinMode(led, OUTPUT);     
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  servoPan.attach(9);
  servoTilt.attach(10);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) 
  {
    parseCBInput(inputString);  
     // clear the input string:
    inputString = "";
    stringComplete = false;
    Serial.flush();
  }
}

void parseCBInput ( String strInput )
{
    Serial.println("> Input: " + strInput); 
    
    //Command for pan servo received
    if ( strInput.startsWith("*0:") )
    {
      char inputChars[strInput.length()];
      strInput.substring(3).toCharArray(inputChars , strInput.length()+1);
      pos = atoi(inputChars);
      
      if (pos >= SERVO_PAN_MIN && pos <= SERVO_PAN_MAX ) 
      {
        Serial.println("--> Pan Servo: ");
        Serial.println(pos);
        servoPan.write(pos);
      }
      else if (pos < SERVO_PAN_MIN || pos > SERVO_PAN_MAX )
      {
        Serial.println("--> Pan Servo: angle out of range");
      }
    }
    
    //Command for tilt servo received
    else if ( strInput.startsWith("*1:") )
    {
      char inputChars[strInput.length()];
      strInput.substring(3).toCharArray(inputChars , strInput.length()+1);
      pos = atoi(inputChars);
      
      if (pos >= SERVO_PAN_MIN && pos <= SERVO_PAN_MAX ) 
      {
        Serial.println("--> Tilt Servo: ");
        Serial.println(pos);
        servoTilt.write(pos);
      }
      else if (pos < SERVO_PAN_MIN || pos > SERVO_PAN_MAX )
      {
        Serial.println("--> Tilt Servo: angle out of range");
      }
    }
    
    //Command for VISCA control received
    else if ( strInput.startsWith("*2:") )
    {
      Serial.println("--> VISCA: " + strInput.substring(3));
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


