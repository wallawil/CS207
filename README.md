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

* The left side of the board takes care of the HC-05.
* The right side of the board takes care of the servos.
* Make sure you implement voltage division so that only 3.3V is reaching the RX pin on the HC-05.

![](/Images/IMG_20191206_103548.jpg)

* Supply two power sources to your robot.  This will allow both the HC-05 and servos to operate simultaneously.
* Note that providing two 5V sources will likely be insufficient.  One of your sources should be at least 7.5V, and it would be best to provide 9V to the barrel jack on the Arduino.
* In the image below, I am using a USB power bank which is sitting on top of five AAs.

![](/Images/IMG_20191206_131620.jpg)

* From this repository, grab the Human-Tracking Creepy Robot Arduino sketch.
* If you don't have it already, download the [Arduino IDE](https://www.arduino.cc/en/main/software) so you can upload the code to your board.


* With power supplied to your Arduino, your HC-05 will be ready to establish a Bluetooth connection.  But first, you must have Bluetooth enabled on your phone, and you must pair with the HC-05.  Use the password "1234" if prompted; this is a default code.
* On an Android smartphone, download the free app called [Arduino Object Detection Tracking](https://play.google.com/store/apps/details?id=com.studios.code.gem.ardobjecttracker&hl=en).
* Open the Arduino Object Detection Tracking app.  Your phone will begin classifying nearby objects (e.g. bottle, TV, person).
* Attach the phone to your robot.  If there are no people nearby, use yourself as a guinea pig and stand a few paces in front of your robot.  
* Congratulations!  You have trained your robot to follow people!

## Facehugger tutorial ##
* If you have access to a 3D printer and want to make your robot look scary, find a 3D model to print!
* I recommend this [life-size facehugger model from Thingiverse!](https://www.thingiverse.com/thing:1116392)
* Be warned that several prints must be done for this big 40" model.  Here is just a portion:
![](/Images/facelegs.png)

* Paint it whatever colour you like, or leave it the same as it came out of the printer.  It's entirely up to you!

![](/Images/facepaint.jpg)

* Snap the limbs and tail together.  The articulated joints might be a tight fit.  
* If things don't fit together quite right, improvise!I had to use crazy glue and tape at times.  It's better than having a leg fall off in the middle of an experiment.  (Trust me!)

![](/Images/facehugger.jpg)
