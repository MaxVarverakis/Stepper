//Alternative to setup pinModes:
/*#include <Stepper.h>

  initialize the Stepper library on pins 8 through 11:
  Stepper myStepper(StepsPerRevolution, 8, 10, 9, 11);*/

#include <Arduino.h> // Not needed if using standard Arduino IDE
#include "HX711.h"
//#include "string.h"
//#include <string> // for string class
//using namespace std;

#define DOUT  A0
#define CLK  A1

HX711 scale;

// Load cell initialization
float calibration_factor = 200000; // this calibration factor must be adjusted according to your load cell
float units;

// Motor initialization
int motorPin1 = 8;
int motorPin2 = 9;
int motorPin3 = 10;
int motorPin4 = 11;
int delayTime = 2; // Control rotation speed of motor (delay for each half-Step is in miliseconds)
int ccwPin = 13; // Start counter clockwise rotation (button pin)
int cwPin = 7; // Start clockwise rotation (button pin)
int resetSteps = 12; // Reset the step count (button pin)
float stepCount = 0; // Number of Steps the motor has taken
float Step = .5;
float ccwCount = 0; // Number of times the motor has stepped counter clockwise
float cwCount = 0; // Number of times the motor has stepped clockwise
float ccwStep = 100; // Number of times the user wants the motor to step counter clockwise
float cwStep = 1500; // Number of times the user wants the motor to step clockwise
// Note: 180 steps per rotation
bool manual = true; // Set to false if you want to make the motor turn a set number of steps.
bool list[8][4] = {
  {HIGH, LOW, LOW, LOW},
  {HIGH, HIGH, LOW, LOW},
  {LOW, HIGH, LOW, LOW},
  {LOW, HIGH, HIGH, LOW},
  {LOW, LOW, HIGH, LOW},
  {LOW, LOW, HIGH, HIGH},
  {LOW, LOW, LOW, HIGH},
  {HIGH, LOW, LOW, HIGH}
};
char ccw[4] = "ccw", cw[3] = "cw";

void setup() {

  Serial.begin(19200); // initialize the serial port (for printing the number of Steps)

  // Initializing all of the pins with the Arduino
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(ccwPin, INPUT_PULLUP);
  pinMode(cwPin, INPUT_PULLUP);
  pinMode(resetSteps, INPUT_PULLUP);

  /*
    Not suggested, but:
    Alternatively, you can uncomment the "#include <Stepper.h>..."
    code to initialize the motor pins with the arduino.  This allows the user to utilize the functions
    "myStepper" followed by ".Stepper()", ".setSpeed()", and ".Step()".  Documentation for what these
    functions do is under the methods portion of:
    https://www.arduino.cc/reference/en/libraries/Stepper/
  */

  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  scale.tare();  //Reset the scale to 0
  // Serial.println("HX711 calibration sketch");
  // Serial.println("Remove all weight from scale");
  // Serial.println("Press T to tare");
  // Serial.println("After readings begin, place known weight on scale");
  // Serial.println("Press + or a to increase calibration factor");
  // Serial.println("Press - or z to decrease calibration factor");



  //  long zero_factor = scale.read_average(); //Get a baseline reading
  //  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  //  Serial.println(zero_factor);
}

void loop() {

  // Motor loop
  if (digitalRead(ccwPin) == LOW) {
    ccwRotation(); // Rotate motor counter clockwise
  }
  else if (digitalRead(cwPin) == LOW) {
    cwRotation(); // Rotate motor clockwise
  }
  else if (digitalRead(resetSteps) == LOW) {
    stepCount = 0; // Reset step count to zero
  }

  // Load cell loop
  measure();

}

float measure() {
  // Function to throw into loop for load cell
  // Serial.print("Reading ");
  units = scale.get_units(), 5;
  // if (units < 0)
  // {
  //   units = 0.00;
  // }
  Serial.print("Force: ");
  Serial.println(units, 10);
  // delay(50);
  
  // Serial.print(" N");
  // Serial.print("Steps:");
  //  Serial.print(" calibration_factor: ");
  //  Serial.print(calibration_factor);
  // Serial.println();

  // commands to type into serial monitor for calibration

  // if (Serial.available())
  // {
  //   char temp = Serial.read(); //to adjust zero
  //   if (temp == 't' || temp == 'T') //Type in
  //     scale.tare();  //Resets the scale to zero
  // }


  // if (Serial.available())
  // {
  //   char temp = Serial.read(); //to adjust calibration factor
  //   if (temp == '+' || temp == 'a') //Type in
  //     calibration_factor += 1;
  //   else if (temp == '-' || temp == 'z') //Type in
  //     calibration_factor -= 1;
  // }

  // return units;
}

bool Condition(char *x) {
  /* Function that determines if the rotation functions should use manual mode.
      Args: "ccw" or "cw" depending on which rotation function is using the Condition.
      Returns: bool
    This shouldn't need to be used, as it is already implemented in the
    rotation functions. */
//  int ccwBool = strcmp(x, ccw), cwBool = strcmp(x, cw);
  
  if (manual == false) {
    if (strcmp(x, ccw) == 0) {
      return (ccwCount < ccwStep);
    }
    else if (strcmp(x, cw) == 0) {
      return (cwCount < cwStep);
    }
  }
  else if (manual == true) {
    if (strcmp(x, ccw) == 0) {
      return (digitalRead(ccwPin) == LOW);
    }
    else if (strcmp(x, cw) == 0) {
      return (digitalRead(cwPin) == LOW);
    }
  }
}

void ccwRotation() {

//  char x[] = "ccw";
  char *x = ccw;
  int i = 0;
  while (Condition(x)) {

    digitalWrite(motorPin4, list[i][0]);
    digitalWrite(motorPin3, list[i][1]);
    digitalWrite(motorPin2, list[i][2]);
    digitalWrite(motorPin1, list[i][3]);
    delay(delayTime);

    // Serial.print("Steps:");
    stepCount += Step;
    ccwCount += Step;
    // Serial.println(stepCount);

    measure();

    i++;
    if (i == 7) {
      i = 0;
    }
  }
  ccwCount = 0;
}

void cwRotation() {

//  char x[] = "cw";
  char *x = cw;
  int i = 0;
  while (Condition(x)) {

    digitalWrite(motorPin4, list[i][3]);
    digitalWrite(motorPin3, list[i][2]);
    digitalWrite(motorPin2, list[i][1]);
    digitalWrite(motorPin1, list[i][0]);
    delay(delayTime);

    // Serial.print("Steps:");
    stepCount -= Step;
    cwCount += Step;
    // Serial.println(stepCount);

    measure();

    i++;
    if (i == 7) {
      i = 0;
    }
  }
  cwCount = 0;
}
