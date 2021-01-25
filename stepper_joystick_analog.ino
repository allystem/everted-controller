// Stepper controlled by joystick
// Written by: Allison Raines

#include <Stepper.h> 
#define STEPS 200 //no. of steps per revolution for NEMA 17 is 200

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
Stepper stepper(STEPS, 4, 3); //pins to which the driver module is connected
#define motorInterfaceType 1 //defined the motor interface type as Type1 because the motor is connected through the driver module

// Connections to joystick (change if you use different pins):
const int VERT = 0; // analog
const int HORIZ = 1; // analog
const int SEL = 2; // digital

//initialize variables for analog and digital values
int vertical, horizontal, select;
int increment = 0; // rate control


void setup() {
  // Set the maximum speed in steps per second:
  stepper.setSpeed(20); //max motor speed for NEMA 17 is 4688 RPM, but >1000 RPM torque falls off quickly

   // set up serial port for output
  Serial.begin(9600);
}

void loop() {

 // read all values from the joystick
  vertical = analogRead(VERT); // will be 0-1023, middle position is about 504
  //horizontal = analogRead(HORIZ); // will be 0-1023, middle position is aout 512
  select = digitalRead(SEL); // will be HIGH (1) if not pressed, and LOW (0) if pressed

    
  // rate control- add or subtract proportional to joystick position
    if( vertical > 515){
    increment += 1;
    Serial.print("Steps: ");
    Serial.println(increment);
    }
    if (vertical < 495){
    increment -= 1;
    Serial.print("Steps: ");
    Serial.println(increment);
    }
    stepper.step(increment);
 }
