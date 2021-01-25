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
int startMillis; // start time
int currentMillis = 0; // time in milliseconds
int period = 1000; // time lapse between increments


void setup() {
  // Set the maximum speed in steps per second:
  stepper.setSpeed(20); //max motor speed for NEMA 17 is 4688 RPM, but >1000 RPM torque falls off quickly

   // set up serial port for output
  Serial.begin(9600);

  //startMillis = millis();
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
//  // record time 
//  // millis() is an alternative to delay() that doesn't stop loop activity
//  if (vertical > 515 or vertical < 495){
//    currentMillis = millis();
//  }
//  else
//    currentMillis = 0;
//
//    
//  // rate control- add or subtract proportional to joystick position
//  if ( (currentMillis % startMillis) > period){
//    startMillis = millis();
//    if( vertical > 515){
//    increment += 1;
//    Serial.print("Steps: ");
//    Serial.println(increment);
//    }
//    else if (vertical < 495){
//    increment -= 1;
//    Serial.print("Steps: ");
//    Serial.println(increment);
//    }
//  }

//  stepper.step(increment);
  
//  if (vertical > 515) // vertical is high = clockwise
//      stepper.step(increment);
//  if (vertical < 495) // vertical is low = counterclockwise
//      stepper.step(increment);
//  //if (select == LOW) // button pressed = turn off motor
//}
//void loop() {
//
// // read all values from the joystick
//
//  vertical = analogRead(VERT); // will be 0-1023, middle position is about 504
//  horizontal = analogRead(HORIZ); // will be 0-1023, middle position is aout 512
//  select = digitalRead(SEL); // will be HIGH (1) if not pressed, and LOW (0) if pressed
//  int last_sig_x;
//  
//  if (vertical > 600 or vertical < 400)
//      last_sig_x = vertical;
//  if (last_sig_x > 600) // vertical is high = clockwise
//      stepper.step(1);
//  if (last_sig_x < 400) // vertical is low = counterclockwise
//      stepper.step(-1);
//  //if (select == LOW) // button pressed = turn off motor
//}
