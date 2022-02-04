//Alternative to setup pinModes:
/*#include <Stepper.h>

initialize the Stepper library on pins 8 through 11:
Stepper myStepper(StepsPerRevolution, 8, 10, 9, 11);*/

#include <Arduino.h> // Not needed if using standard Arduino IDE

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
bool manual = false; // Set to false if you want to make the motor turn a set number of steps.
bool list[8][4] = {
    {HIGH,LOW,LOW,LOW},
    {HIGH,HIGH,LOW,LOW},
    {LOW,HIGH,LOW,LOW},
    {LOW,HIGH,HIGH,LOW},
    {LOW,LOW,HIGH,LOW},
    {LOW,LOW,HIGH,HIGH},
    {LOW,LOW,LOW,HIGH},
    {HIGH,LOW,LOW,HIGH}
    };

void setup() {
  Serial.begin(9600); // initialize the serial port (for printing the number of Steps)
  
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
}

void loop() {
  if(digitalRead(ccwPin) == LOW){
    ccwRotation(); // Rotate motor counter clockwise
  }
  else if(digitalRead(cwPin) == LOW){
    cwRotation(); // Rotate motor clockwise
  }
  else if(digitalRead(resetSteps) == LOW){
    stepCount = 0; // Reset step count to zero
  }
}

bool Condition(String x){
/* Function that determines if the rotation functions should use manual mode. 
  *Args: "ccw" or "cw" depending on which rotation function is using the Condition.
  *Returns bool
This shouldn't need to be used, as it is already implemented in the 
rotation functions. */
  if(manual == false){
    if(x == "ccw"){
      return (ccwCount < ccwStep);   
    }
    else if(x == "cw"){
      return (cwCount < cwStep);  
    }
  }
  else if(manual == true){
    if(x == "ccw"){
      return (digitalRead(ccwPin) == LOW);
    }
    else if(x == "cw"){
      return (digitalRead(cwPin) == LOW);
    }
  }
}

void ccwRotation(){

  int i = 0;
  while(Condition("ccw")){
    
    digitalWrite(motorPin4, list[i][0]);
    digitalWrite(motorPin3, list[i][1]);
    digitalWrite(motorPin2, list[i][2]);
    digitalWrite(motorPin1, list[i][3]);
    delay(delayTime);
    
    Serial.print("Steps:");
    stepCount+=Step;
    ccwCount+=Step;
    Serial.println(stepCount);
    i++;
    if(i == 7){
      i = 0;
    }
  }
  ccwCount = 0;
}

void cwRotation(){

  int i = 0;
  while(Condition("cw")){
    
    digitalWrite(motorPin4, list[i][3]);
    digitalWrite(motorPin3, list[i][2]);
    digitalWrite(motorPin2, list[i][1]);
    digitalWrite(motorPin1, list[i][0]);
    delay(delayTime);
    
    Serial.print("Steps:");
    stepCount-=Step;
    cwCount+=Step;
    Serial.println(stepCount);
    i++;
    if(i == 7){
      i = 0;
    }
  }
  cwCount = 0;
}
