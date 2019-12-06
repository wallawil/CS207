## Hello, reader! ##

This Readme file will attempt to walk you through my Human-Tracking Creepy Robot project.

You will find two different guides below.

The quick-start guide is appropriate for advanced users who have built the robot and just want to get it running.

The in-depth guide is a complete walkthrough for beginners who are starting out from scratch.



## Quick-start Guide:

#### Preliminary work:
* Build the robot and circuit
* Pair the HC-05 with your smartphone
* Upload the Human-Tracking Creepy Robot sketch to your Arduino
* Install the Arduino Object Tracking app to your phone

#### Activating the robot:
* Supply power to your Arduino
* Open ArdObject Tracking app on your phone
* Attach the phone to the cell phone holder

The robot will now follow humans.  If you want to stop the robot, remove the phone from its head and close the app.  This will sever the Bluetooth communication.



## In-depth Guide:

Use your material of choice to create the robot's body and legs.  For this project, a 3D printer was used.  You may use another material if you prefer.

Blueprint (click for full size)    |  Printed Parts
:-------------------------:|:-------------------------:
![](/Images/walker.png)  |  ![](/Images/printedparts.png)

* Slot the pieces together.  Slot your servos into the rectangular holes.  
* You will need M2 and M3 screws where indicated on the blueprint.

* Attach your Arduino and breadboard to the robot.  I used zip ties.  Elastic bands can be used as a temporarily solution.
* Build the following circuit on your Arduino breadboard.  

![](/Images/bready.png)
![](/Images/IMG_20191206_103548.jpg)
* Supply two power sources to your robot.  This will allow both the HC-05 and servos to operate simultaneously.
* Note that providing two 5V sources will likely be insufficient.  One of your sources should be at least 7.5V, and it would be best to provide 9V to the barrel jack on the Arduino.

