#include "Stepper.h"
#include "HX711.h"

#define DOUT  A0
#define CLK  A1

HX711 scale;
// Load cell initialization
int calibration_factor = 200000; // this calibration factor must be adjusted according to your load cell
float units;

int ccwPin = 13; // Start counter clockwise rotation (button pin)
int cwPin = 7; // Start clockwise rotation (button pin)

int StepsPerRevolution = 200; // Number of steps per revolution
Stepper myStepper(StepsPerRevolution, 8, 10, 9, 11);

void setup(){
    Serial.begin(19200); // initialize the serial port (for printing the number of Steps)

    scale.begin(DOUT, CLK);
    scale.set_scale(calibration_factor); //Adjust to this calibration factor
    scale.tare();  //Reset the scale to 0

    myStepper.setSpeed(60); // Set the speed of the motor (in RPM)
}

void loop(){
    if (digitalRead(ccwPin) == LOW) {
        // myStepper.step(-10);
        // measure();
    }
    else if (digitalRead(cwPin) == LOW) {
        // myStepper.step(10);
        // measure();
    }

}

float measure() {
  // Function to throw into loop for load cell measurement
    units = scale.get_units(), 5;
    Serial.print("Force: ");
    Serial.println(units, 10);
//  delay(50);
}