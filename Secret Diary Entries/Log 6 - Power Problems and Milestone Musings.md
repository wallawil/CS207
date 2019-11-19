## Power Problems and Milestone Musings


### I.  Milestone 3 was met on time
I mentioned last time that the robot was assembled and walking.



### II.  Power Problems
I bought a USB-to-barrel jack adapter cable but unfortunately the power to the Bluetooth is still lost.

For example, when using two cell phone battery banks (one to the USB and one to the barrel jack) to power the Arduino, the connection is lost.

However, when I use the ARDX's battery pack with five AAs, there is no problem.  (I mentioned this in my last log.)

I'm not totally sure why this would be.  

It's worth noting that the ARDX's battery pack seems to handle its own grounding.
There's no guarantee that my adapter cable from Amazon would be Arduino-friendly in that regard.

*Wait*, I just remembered the barrel jack prefers to handle 7V and higher.  
I suppose the five AAs would be giving 7.5V, while my USB battery pack would only deliver 5V.

It's not really a problem if I have to use the AAs, and the robot works fine with them.
It's just I like how easy it is to recharge the USB battery banks.
As well, for aesthetic reasons, it would be cool if the robot had two matching banks.  
They would balance it more easily, too.



### III.  Milestone 4 somewhat met
As long as I use 1 battery bank + five AAs, the power needs are met and the Bluetooth connection is not lost.

I held my smartphone in my hand and pointed it at a picture of a person, and the robot responded to this.

Swiveling the phone in my hand caused the robot to think that it needed to turn to the left and right, which is great.

However, I still have to attach the phone to the front of the robot and use it with an actual person (likely myself).



### IV.  To-Do list:
- Possibly keep experimenting with battery banks, although the 5V USB connections can't cut it alone, it seems.
- Get a better walking rhythm between front and back legs.  This needs to be done for forward, left, and right directions.
- Measure the top part of the robot, where a scary alien model could potentially be fitted over top (stretch milestone).
- Create a "good copy" .ino file which we will adapt to the final version.  
