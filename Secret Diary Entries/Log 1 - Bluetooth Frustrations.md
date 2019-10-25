## Bluetooth Frustrations
### I.
My first milestone is set to be achieved by October 31st.\
The goal is to get my smartphone communicating with the Arduino via Bluetooth.


If I can turn an LED on and off remotely using my smartphone, I'll be satisfied.\
It will prove that more elaborate instructions can be given once the project is more... mature.


I've already acquired an HC-05 Bluetooth receiver from Amazon.


Amazon:  Monolithic and soulless, like an undead titan.\
Say what you will about the undead; they are convenient.  The component got here quick!


### II.
There seem to be an abundance of tutorials and apps for Arduino + Bluetooth communication.\
This is reassuring.


However, my inexperience is a big obstacle.\
I've installed three Bluetooth apps now and have yet to successfully communicate any information to my Arduino.


**The apps in question:**\
Bluetooth Terminal:  https://play.google.com/store/apps/details?id=project.bluetoothterminal&hl=en  
Bluetooth Terminal (uhh, another variety, I guess)\
BlueTerm


I also need to be careful with the testing.\
There are six pins on the HC-05 receiver.\
**One of the pins on the receiver is fine with 5V, but the other needs 3.3V.**\
I need to use voltage division with the limited types of resistors I have.\
Otherwise, damage may occur.


### III.
I still have not communicated **TO** the Arduino, but to my surprise received serial output **FROM** the Arduino.\
My smartphone screen was suddenly covered with output from a preexisting sketch from our lab-work.\
So, at least **SOME** communication is occurring.


I found out the old BlueTerm app is unusable on my phone.\
It was designed in an ancient time (2012 - 2013).\
My phone needs to have physical buttons to access BlueTerm's menu.\
My phone does not have physical buttons.\
My phone cannot access BlueTerm's menu.


The app has failed me.  I was too quick to turn my back on the others.\
I will find another app.  A new apprentice.  One far younger and more powerful.


### IV.
Still no communication **TO** the Arduino.\
I attempted uploading some tutorial sketches.\
Unfortunately, the Arduino IDE on my laptop said that an error occurred.\
No details were given as to the origin of this error.

On a more positive note, voltage division is clearer in my brain.\
A helpful tutorial provided a formula for dropping from 5V to 3.3V.\
As long as I keep a 2:1 ratio in mind, things will be fine.

Oh, my little HC-05.\
I won't let the evil USB cable burn you out.
