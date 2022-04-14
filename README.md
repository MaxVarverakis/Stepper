# Stepper
Code associated with the stepper motor and arduino


## Background Info

To run this code, you must first have the Arduino IDE downloaded onto 
your machine.  If you're using the computer in Jacks' lab near the 
microscope (not the microscope computer), then it should already be 
installed.  This code was written using Arduino version (1.8.15).
If for some reason the Arduino IDE is not installed, use this link:
https://www.arduino.cc/en/software


## Opening the File

Double clicking on the file should automatically open the Arduino IDE.
If this doesn't happen, click on the Arduino icon to manually open the IDE.
The IDE can be accessed diretly either in the taskbar (dock) or from file searcher.
(You can also click on the Windows button in the bottom left corner and type in 
Arduino, the icon/application should appear there too).
If entering the IDE manually, press ctrl+O (cmd+O on Mac) to bring up the
file search.  Locate the file you want to open and double click on it
(in our case, it would be "GoodStep.ino").
The Arduino IDE should now be showing the code for "GoodStep.ino", and you
can edit/upload/verify the code.



## Understanding the Code

Anything labelled `int` means it can be assigned to an integer
Anything labelled `float` means it can be assigned to a float
Anything labelled `bool` means that it can be assigned `true` or `false`

The first block on text should read something like:

int motorPin1 = 8;
int motorPin2 = 9;
int motorPin3 = 10;
int motorPin4 = 11;
...

This code is initializing everything that we are going to be referencing
from the Arduino board, as well as other references, such as variables (or booleans).
Below is a rough explanation of each part of the code:

motorPin: Corresponds to the pin numbers on the Arduino board that are
associated with specific pins on the L293DNE chip (which drives the motor).

delayTime: Amount of time between each half-step (control rotation speed of motor 
(delay for each half-Step is in miliseconds).

ccwPin and cwPin: Arduino board pin numbers associated with the buttons on the 
breadboard that starts counterclockwise (ccw) and clockwise (cw) rotation.

resetSteps: Arduino board pin number associated with the button on the 
breadboard that resets the counter for the number of steps the motor has taken.

stepCount: Number of steps the motor has taken (negative steps corresponds to 
steps in the clockwise direction).

Step: Value for the step counter.  Each half step of the motor corresponds to 0.5.

ccwCount: Number of times the motor has stepped counterclockwise (used for 
determining when the motor has turned the set number of counterclockwise rotations).
*Should remain 0*

cwCount: Number of times the motor has stepped counter clockwise (used for 
determining when the motor has turned the set number of clockwise rotations).
*Should remain 0*

ccwStep: Number of times the user wants the motor to step counterclockwise/

cwStep: Number of times the user wants the motor to step clockwise.

NOTE: 180 steps per rotation.

manual: Set to `false` if you want to make the motor turn a set number of 
steps per button press.  Set to `true` if you want the motor to turn until 
the corresponding button is released.  To set the mode, write the word 
`true` or `false` in place of the current word.  For instance, if I wanted 
to use manual mode, then I would edit the code so it reads 
`bool manual = true;`.

list: `[8][4]` corresponds to a list of 8 elements each containing 4 elements.
Each of the 8 elements in the list corresponds to one of the 8 motor positions.
The 8 elements of the list will be cycled through to make the motor turn.

setup(): Will only be run once.  This is the initialization section.

pinMode: Initialize the relevant pins of the Arduino.

loop():  This loop will constantly be running to check to see if the buttons
are pressed.

Condition: (function) Determines if the rotation functions should use manual mode.  
    *Args: `ccw` or `cw` depending on which rotation function is using the Condition.
    *Returns: bool 
This shouldn't need to be changed, as it is already implemented in the rotation 
functions.

ccwRotation: (function) 
    *Args: None
    *Returns: None (since it is preceded by a `void`)
This function is called whenever the ccw button is pressed.  This 
is what tells the motor what to do (tells the motor to rotate ccw)

cwRotation: (function) 
    *Args: None
    *Returns: None (since it is preceded by a `void`)
This function is called whenever the cw button is pressed.  This 
is what tells the motor what to do (tells the motor to rotate cw)



## Setting Up the Board/Computer

First make sure that your arduino is connected to the computer via usb.
Then make sure "Board:" is assigned to "'Arduino Uno'".
Also make sure "Port" is set to:
   PC: `COM (Arduino Uno)`
   Mac: `/dev/cu.usbmodem14101`
   Linux: `dev/ttyACM0`

* If you have an error while uploading the code, first check to make sure
the IDE still recognizes the correct port, sometimes the IDE can forget the
port, especially if you're unplugging and plugging back in the board a lot.



## Using the Code

(IF MANUAL IS SET TO TRUE, SKIP STEP 1)
1. Change the values of `ccwStep` and `cwStep` to the desired 
number of steps per button press for ccw and cw directions, respectively.

2. Click on the icon that looks like an arrow pointing to the right 
(in the top left corner of the screen) to upload the code to the 
Arduino.

3. In the bottom right corner of the screen, the word "Uploading"
(or something similar) should appear with a little orange-ish colored
loading bar.  Once this bar is full, it will change to "Upload Complete"
(or something similar).  If no errors appear, then the code has been
successfully uploaded.

4. Press the corresponding buttons on the breadboard to make 
the motor perform the desired actions.
