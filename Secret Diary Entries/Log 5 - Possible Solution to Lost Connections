## Possible Solution to Lost Connections


### I.
Okay, so my clumsy work-around was technically successful, in so far as it got the robot moving without losing the Bluetooth connection, but as far as performance and practicality went, it was a failure.

I continually switched the servo variable from one pin to another so that only one servo was being used at a time.

However, this also made the robot awkward and slow.  It could only move one servo at a time.

Also, there was a danger of interrupting one servo's action by switching to the other.


### II.  The **Real** Solution
Evidence suggests I should have listened to the experts.

Our lab notes, the Arduino forums, and Stack Overflow all suggested that it was a bad idea to have two servos running on the same power source as the Arduino itself.

So, realizing that I hadn't yet used the ARDX's supplied battery pack (five AAs), I plugged these into the barrel jack.

I then searched in vain for about an hour to find the code responsible for switching power sources, e.g. designating the USB as the Arduino's power and the AAs as the servos' power.

D'oh!  It does it itself.  No code needed.  Just plug in the power.

I tested some old code and found that the Bluetooth did not drop this time.  The robot walked - and more importantly, stopped when told to.


### III.
Ah, I mentioned that the robot walked.  It would be good to note that the chassis is assembled.  Otherwise, no walking.

The servos fit pretty tightly and blend in well.


### IV.
I had to buy one extra part, a USB to 2.1 mm barrel jack adapter.  This special cable may change the world.

I have another goofy plan, you see.  My big battery bank for charging my cell phone has two USB ports.

Can I use this single battery to power both ports of the Arduino (both USB and barrel jack)?

If so, I can avoid giving the robot extra batteries to carry, while still supplying enough juice for both the board and the servos.

Stay tuned...
