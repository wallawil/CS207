/*
Note from Will:  This code is only for testing BlueTooth communication and human tracking.
Depending on a human's position, 3 possible LEDs will turn on and off.
Example:  If human is standing to the left of center, leftPin LED will be turned on.

This code is based on work by Sohail Shah of GemCode Studios.
However, his code was meant for a wheeled vehicle with sonar/echo.

This is a heavily modified, simplified version which is only for testing.  No robot/walker required.
*/

#include <Servo.h>
#include <SoftwareSerial.h> 

SoftwareSerial BluePins(2, 3); // RX | TX 
Servo frontservo,backservo;

String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

int leftPin = 13;
int midPin = 7;
int rightPin = 4;


int maxFOV = 600;             // Field of view in pixels from centre

int minSpeed = 120;           // Motors will starting turning around 120 value. Change to suit your motors.
int turnCount = 0;            // Count of how many times we have turned.
int forwardCount = 0;         // Forward count
int searchCount = 0;          // How many times have we searched.
int maxSearchWaitTime = 3000; // How long before searching people. (3 seconds)
int maxSearchCount = 10;
int maxForwardCount = 25;
int maxTurnCount = 5;
bool bGoForward = false;
bool bTurning = false;
bool bTurningRightLast = true;


int xVal = -2000;
int yVal = -2000;
String sXVal = "";            // Horizontal x value of target from centre 0,0
String sYVal = "";            // Vertical y value of target from centre 0,0
int distance = 1;             // Used to hold distance from sonar reading.

unsigned long StartTime = millis();

void setup() {

  Serial.begin(9600);
  BluePins.begin(9600);

  pinMode(leftPin, OUTPUT);
  pinMode(midPin, OUTPUT);
  pinMode(rightPin, OUTPUT);
  
  Serial.println("Ard Object Detection & Tracking - Copyright: 2019");  
}

void loop() {

  bool bObjectFound = false;
  
  //
  // Handle Object Tracking:
  //
  if (stringComplete) {

    if (inputString.startsWith("FTF:person:"))
    {
      Serial.println("FTF PERSON DETECTED");

      bObjectFound = true;
      searchCount = 0;
      
      //Serial.println(inputString);
      inputString.replace("FTF:person:", "");

      int colonPos = inputString.indexOf(":");
      if (colonPos>0)
      {
        String objID = inputString.substring(0, colonPos);
        inputString.replace(objID+":", "");

        int commaPos = inputString.indexOf(",");
        if (commaPos>0)
        {
          sXVal = inputString.substring(0, commaPos);
          xVal = sXVal.toInt();
          int commaPos2 = inputString.indexOf(",", commaPos+1);
          sYVal = inputString.substring(commaPos+1, commaPos2);
          yVal = sYVal.toInt();

          Serial.println(sXVal + ":" + sYVal);
        }
      } 
    }
    //
    // Standard tensor flow person object detected. If using this note robot may get confused between different people in close proximity:
    // From tests conducted this will however work faster than the above filtered detection. For this just select Tensor Flow Object Detection Only.
    //
    else if (inputString.startsWith("person:")) 
    {
      Serial.println("PERSON DETECTED");
      Serial.println(inputString);
      inputString.replace("person:", "");
      bObjectFound = true;
      searchCount = 0;
      
      int colonPos = inputString.indexOf(":");
      if (colonPos>0)
      {
        String objID = inputString.substring(0, colonPos);  // Could do something with ObjID, but ignored for now.
        inputString.replace(objID+":", "");

        int commaPos = inputString.indexOf(",");
        if (commaPos>0)
        {
          sXVal = inputString.substring(0, commaPos);
          xVal = sXVal.toInt();
          int commaPos2 = inputString.indexOf(",", commaPos+1);
          sYVal = inputString.substring(commaPos+1, commaPos2);
          yVal = sYVal.toInt();

          Serial.println(sXVal + ":" + sYVal);
        }
      }
    }
    
    // Is object detected if so now track it:
    if (bObjectFound)
    {
      searchCount = 0;    // Resets the search count so we can try search in case we lose the object during subsequent frames.
      
      xVal = constrain(xVal, -maxFOV, maxFOV);  
      
      // turn on LED corresponding to where human is standing (mid, left, or right)
      if (xVal > -100 && xVal < 100)
      {
        digitalWrite(midPin, HIGH);
        digitalWrite(leftPin, LOW);
        digitalWrite(rightPin, LOW);
      }
      else if (xVal < -100)
      {
        digitalWrite(leftPin, HIGH);
        digitalWrite(midPin, LOW);
        digitalWrite(rightPin, LOW);
      }
      else if (xVal > 100)
      {
        digitalWrite(midPin, LOW);
        digitalWrite(rightPin, HIGH);
        digitalWrite(leftPin, LOW);
      }    
    }
    else 
    {
      // Object Not Found:
      StartTime = millis(); // Start wait process until max wait time has elapsed before searching.
    }
      
     
    // clear the string:
    inputString = "";
    stringComplete = false;
  } 

  // Check if turning and control how long we continue turning before stopping.
  if (bTurning && turnCount > maxTurnCount)
  {
    Serial.println("TurnCount="+String(turnCount));
    bTurning = false;
    stop(1);
    turnCount = 0;
  }
  else
  {
    turnCount++;
  }

  // Check if going forward and control how long we continue going forward before stopping.
  if (bGoForward && forwardCount > maxForwardCount)
  {
    bGoForward = false;
    stop(1);
    forwardCount = 0;
  }
  else
  {
    forwardCount++;
    delay(10);
  }

  unsigned long CurrentTime = millis();
  unsigned long ElapsedTime = CurrentTime - StartTime;
  if (ElapsedTime > maxSearchWaitTime && searchCount < maxSearchCount)
  {
    // Do search:
    bTurning = false;
    bGoForward = false;
    Serial.println("Searching After="+String(ElapsedTime));
    if (bTurningRightLast)
      right(255);
    else 
      left(255);  
    delay(200);
    stop(1);
    // Reset start time:
    StartTime = CurrentTime;
    searchCount++;
  }

 serialEvent();
}   // end of LOOP *****************************************************************************************************


// MOVEMENT FUNCTIONS - UNNEEDED FOR COMMUNICATION / LED TESTING - fill these functions out later with robot walking movements

void stop(int period)
{}

void left(int speed)
{}

void right(int speed)
{}

void forward(int speed)
{}

void reverse(int speed)
{}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {

  while (BluePins.available()) {

    // get the new byte:
       char inChar = (char)BluePins.read();
    // add it to the inputString:
    inputString += inChar;
    //Serial.println(inputString);
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
