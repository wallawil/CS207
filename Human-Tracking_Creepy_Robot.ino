/*
  Human-Tracking Creepy Robot
  Will Wallace
  2019

  The human-tracking code is based on work by Sohail Shah of GemCode Studios.
  It also uses a portion of code from edwindertien's 4-legged 2-servo Instructables robot.
*/

#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial BluePins(2, 3); // RX | TX
Servo frontservo, backservo;

// servo pattern for walking in a straight line
int walkforward[] = {60, 120, 130, 120, 130, 50, 60, 50};

// servo position patterns to control steering
int turnleft[] = {90, 150, 90, 90, 90, 150, 90, 90};
int turnright[] = {90, 30, 90, 90, 90, 30, 90, 90};

int delayT = 200;             // increase this number to make the robot walk more slowly
bool walking = false;

String inputString = "";      // used to receive data, e.g. object names
bool stringComplete = false;  // used to check if a complete object name was received, e.g. "person"

int maxFOV = 600;             // field of view of screen

int xVal = -2000;
int yVal = -2000;
String sXVal = "";            // X position of object
String sYVal = "";            // Y position of object

unsigned long StartTime = millis();

void setup() {
  Serial.begin(9600);
  BluePins.begin(9600);

  // keeping this line here out of respect for GemCode Studios creator
  Serial.println("Ard Object Detection & Tracking - Copyright: 2019");

  attachServos();
  
  frontservo.write(90);
  backservo.write(90);

  detachServos();
}

void loop() {

  bool bObjectFound = false;

  // check if we received a new string for a detected object
  // (these new strings come from the serialEvent function)
  if (stringComplete) {
    Serial.flush();

    // check if person was detected
    if (inputString.startsWith("person:"))
    {
      inputString.replace("person:", "");
      bObjectFound = true;

      int colonPos = inputString.indexOf(":");
      if (colonPos > 0)
      {
        String objID = inputString.substring(0, colonPos);  
        inputString.replace(objID + ":", "");

        // get coordinates of image from incoming bytes
        int commaPos = inputString.indexOf(",");
        if (commaPos > 0)
        {
          sXVal = inputString.substring(0, commaPos);
          xVal = sXVal.toInt();
          int commaPos2 = inputString.indexOf(",", commaPos + 1);
          sYVal = inputString.substring(commaPos + 1, commaPos2);
          yVal = sYVal.toInt();
        }
      }
    }

    if (bObjectFound)
    {

      xVal = constrain(xVal, -maxFOV, maxFOV);
      Serial.print("Target's x-position is: ");
      Serial.println(xVal);

      // if target is in center of screen, walk forward
      if (xVal > -100 && xVal < 100)
        walk(walkforward);

      // if target is to the left
      else if (xVal < -100)
        walk(turnleft);

      // if target is to the right
      else if (xVal > 100) 
        walk(turnright); 
    }
    else
    {
      // Object Not Found:
      StartTime = millis(); // Start wait process until max wait time has elapsed before searching.
    }

    // make the string empty so it is ready for new data
    inputString = "";
    stringComplete = false;
  }
    serialEvent();
}  


// MAIN MOVEMENT FUNCTION; depending on the input array, walk forward or turn left/right
void walk(int pattern[])
{
  attachServos();

  Serial.println("Person detected to the LEFT.");
  for (int n = 0; n < 4; n++) {
    frontservo.write(pattern[2*n]);  
    backservo.write(pattern[(2*n)+1]);
    delay(delayT);
  }

  detachServos();
}

// this function runs at the end of each loop and checks for new incoming data
void serialEvent(){

    while (BluePins.available()) {
     
      // get next data from Bluetooth
      char inChar = (char)BluePins.read();
      inputString += inChar;

      // check if we've reached the end of an incoming string
      if (inChar == '\n') 
        stringComplete = true;
    }
  }
  

// functions for attaching/detaching servos 
void attachServos()
{
  frontservo.attach(9);
  backservo.attach(10);
}

void detachServos()
{
  frontservo.detach();
  backservo.detach();
}
