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
int walkpattern[] = {60, 120, 120, 120, 120, 60, 60, 60};

// int walkleft[] =  {50, 50, 90, 90, 50, 50, 90, 90};

// this backs up and turns to the right
// int walkright[] = {50, 130, 50, 90, 50, 130, 50, 90};
int walkright[] = {90, 150, 90, 90, 90, 150, 90, 90};

//
// int walkleft[] = {130, 50, 130, 90, 130, 50, 130, 90};
int walkleft[] = {90, 30, 90, 90, 90, 30, 90, 90};
// int walkright[] = {130, 130, 90, 90, 130, 130, 90, 90};

int delayT = 200;
bool walking = false;

String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

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

unsigned long StartTime = millis();

void setup() {
  Serial.begin(9600);
  BluePins.begin(9600);

  frontservo.attach(9);
  backservo.attach(10);
 
  // keeping this line here out of respect for GemCode Studios creator
  Serial.println("Ard Object Detection & Tracking - Copyright: 2019");

  Serial.println("Setting servos to default positions.");
  frontservo.write(90);
  backservo.write(90);
}

void loop() {

  bool bObjectFound = false;

  //
  // Handle Object Tracking:
  //
  if (stringComplete) {
    Serial.flush();

    /*
    if (inputString.startsWith("FTF:person:"))
    {
      Serial.println("FTF PERSON DETECTED");

      bObjectFound = true;
      searchCount = 0;

      //Serial.println(inputString);
      inputString.replace("FTF:person:", "");

      int colonPos = inputString.indexOf(":");
      if (colonPos > 0)
      {
        String objID = inputString.substring(0, colonPos);
        inputString.replace(objID + ":", "");

        int commaPos = inputString.indexOf(",");
        if (commaPos > 0)
        {
          sXVal = inputString.substring(0, commaPos);
          xVal = sXVal.toInt();
          int commaPos2 = inputString.indexOf(",", commaPos + 1);
          sYVal = inputString.substring(commaPos + 1, commaPos2);
          yVal = sYVal.toInt();

          Serial.println(sXVal + ":" + sYVal);
        }
      }
    } */
    
    //
    // Standard tensor flow person object detected. If using this note robot may get confused between different people in close proximity:
    // From tests conducted this will however work faster than the above filtered detection. For this just select Tensor Flow Object Detection Only.
    //


    if (inputString.startsWith("person:"))
    {
      Serial.println("PERSON DETECTED");
      Serial.println(inputString);
      inputString.replace("person:", "");
      bObjectFound = true;
      searchCount = 0;

      int colonPos = inputString.indexOf(":");
      if (colonPos > 0)
      {
        String objID = inputString.substring(0, colonPos);  // Could do something with ObjID, but ignored for now.
        inputString.replace(objID + ":", "");

        int commaPos = inputString.indexOf(",");
        if (commaPos > 0)
        {
          sXVal = inputString.substring(0, commaPos);
          xVal = sXVal.toInt();
          int commaPos2 = inputString.indexOf(",", commaPos + 1);
          sYVal = inputString.substring(commaPos + 1, commaPos2);
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
      Serial.print("Target's x-position is: ");
      Serial.println(xVal);

      if (xVal > -100 && xVal < 100)
        forward();
      
      else if (xVal < -100)
      // if (xVal < -100)
        left();
 
      else if (xVal > 100)
        right();     
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
/*
  // Check if turning and control how long we continue turning before stopping.
  if (bTurning && turnCount > maxTurnCount)
  {
    Serial.println("TurnCount=" + String(turnCount));
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
    Serial.println("Searching After=" + String(ElapsedTime));
   // if (bTurningRightLast)
    //  right();
    //else
     // left();
    delay(200);
    stop(1);
    // Reset start time:
    StartTime = CurrentTime;
    searchCount++;
  }
*/
    serialEvent();
}   // end of LOOP *****************************************************************************************************


// MOVEMENT FUNCTIONS - UNNEEDED FOR COMMUNICATION / LED TESTING - fill these functions out later with robot walking movements

void stop(int period)
{}

void left()
{
  
  walking = true;
  Serial.println("Person detected to the LEFT.");
  for (int n = 0; n < 4; n++) {
    frontservo.write(walkleft[2*n]);  
    backservo.write(walkleft[(2*n)+1]);
    delay(delayT);
  }
  walking = false;
  
}

void right()
{
  
  walking = true;
  Serial.println("Person detected to the RIGHT.");
  for (int n = 0; n < 4; n++) {
    frontservo.write(walkright[2*n]);  
    backservo.write(walkright[(2*n)+1]);
    delay(delayT);
  }
  walking = false;
  
}

void forward()
{
  
  walking = true;
  Serial.println("Person detected AHEAD.  Let's move FORWARD.");
  for (int n = 0; n < 4; n++) {
    frontservo.write(walkpattern[2*n]);  
    backservo.write(walkpattern[(2*n)+1]);
    delay(delayT);
  }
  walking = false;
  
}


  /*
    SerialEvent occurs whenever a new data comes in the hardware serial RX. This
    routine is run between each time loop() runs, so using delay inside loop can
    delay response. Multiple bytes of data may be available.
  */
void serialEvent(){
// if (walking == false){
  
    while (BluePins.available()) {
     
      // get the new byte:
      char inChar = (char)BluePins.read();
      // add it to the inputString:
      inputString += inChar;
      //Serial.println(inputString);
      // if the incoming character is a newline, set a flag so the main loop can
      // do something about it:
      if (inChar == '\n') 
        stringComplete = true;
      
    }
  }
