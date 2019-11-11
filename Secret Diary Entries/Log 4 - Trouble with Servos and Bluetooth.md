## Trouble with Servos and Bluetooth


### I.
I'm having a strange issue that I can't quite wrap my head around.


For testing, I send the character "W" from my phone to the HC-05.\
This gets the robot walking.  Both servos work fine.  Hurray!


Another victory:  The code from GemCode Studios does indeed detect humans.\
I was able to get an LED to light up on detection of a human.


**The problem?**\
For some reason, combining the human detection with the two servos causes the Bluetooth connection to drop.\
The robot starts to take its first step and then stops, i.e. the servos stop when the Bluetooth drops.\
This might be the biggest obstacle I will have to overcome for this project.



### II.
I did some research and there are a few possible causes for the Bluetooth to keep dropping.\
**One possibility:** the servos are taking too much power when they kick in, causing the HC-05 to drop its Bluetooth connection.\
But how can this be the case?  In an earlier experiment, I was able to send "W" to get both servos moving alongside Bluetooth.


**Another possibility:** My code causes the problem.\
I've done about 5 different sketches, each with varying levels of complexity, and the problem still happens.  The code should be fine.


Somehow, the Frankensteining-together of the human detection and the servos seems to cause the problem.  Really weird.


**A third possible cause** of the Bluetooth dropping out: Maybe the HC-05 has a buffer which is being overwhelmed by all the incoming data.\
Again, the counterpoint to this argument is that it was working fine with human detection before (turning an LED on and off).


### III.
**I thought of a possible solution which might work**, based on a really rudimentary sketch.\
It's such an awkward, clumsy fix - but if it works, it works.


The Bluetooth only seems to fail when two servos are operating.  When using "frontservo" only, the connection was maintained.\
Adding the second servo ("backservo") immediately reproduced this ongoing annoying problem.


I was looking at the line "frontservo.attach(9)" and thought: What if I just keep reattaching "frontservo" to different pins?\
In effect, we would trick the Arduino into thinking there is only one servo.\
In reality, we would be constantly switching between frontservo and backservo, i.e. bouncing between pin 9 and 10.\
If this works, I'll be very pleased.


As is often the case, I might find out the real cause of the problem and a proper solution at a much later date.\
However, I've already spent a lot of time trying to figure out this problem.  Maybe a weird work-around is the best course of action.
