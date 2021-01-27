// Stepper controlled by joystick
// Written by: Allison Raines

byte directionPin = 3;
byte stepPin = 2;


const int VERT = 0; // analog connection to joystick
unsigned long curMillis; // milliseconds
unsigned long prevStepMillis = 0;
unsigned long customDelay; // microseconds
boolean input = false; // is there an input to the joystick?

void setup() {
   
  Serial.begin(9600);
  pinMode(directionPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  
}

void loop() {
  
  curMillis = millis();
  getDelay();
  singleStep();
  
 }

// compute the time in usec of the next output pulse
// ie. convert pps (pulse per second) to uspp (microsecond per pulse)
void getDelay(){
  int pulseRate = getPulseRate();
  customDelay = (int)( 1 / ( pulseRate * pow(10,-6)));
  // does not include microsecond delays in hardware
}

//function converting joystick degrees to pulse rate (pulses/sec)
//the speed of the stepper motor is determined by the frequency of pulses to STEP pin
//DRV8825 requires a minimum STEP pulse duration of 1.9 us
int getPulseRate(){
  int angle = getJoystickAngle(); //greater angle = greater speed

  int maxPulseRate = 4000; //(pulse/sec) ***max no load
  int minPulseRate = 1400; //(pulse/sec)
  int noPulse = 0;
  int maxAngle = 90;
  int minAngle = 0;
  int upperBuffer = 45;
  int lowerBuffer = 43;
  int pulseRate;

  if (angle >= lowerBuffer and angle <= upperBuffer) {// buffer section where motor does not move
    input = false;
    return noPulse;
  }
  else if (angle > upperBuffer){
    input = true;
    pulseRate = (int)((double(angle-(upperBuffer + 1)) / (maxAngle - upperBuffer - 1)) * (maxPulseRate - minPulseRate)) + minPulseRate;
    return pulseRate;
    //digitalWrite(directionPin, HIGH);
  }
  else{
    input = true;
    pulseRate = (int)((double(angle-(lowerBuffer - 1)) / (minAngle - lowerBuffer + 1)) * (maxPulseRate - minPulseRate)) + minPulseRate;
    return pulseRate;
    //digitalWrite(directionPin, LOW);
  }
}

//relate dac value to theta
//return angle in degrees
int getJoystickAngle() {
  /* Read Joystick
   * UP:     1023-523
   * CENTER: 522-500
   * DOWN:   0-499
   */
  int dac = analogRead(VERT); // will be 0-1023, middle position is about 504
  int dacMax = 1023;

  /* Convert to degrees
   * UP:     46-90 degrees
   * CENTER: 43-45 degrees
   * DOWN:   0-42 degrees
   */
  int theta = (int)((double(dac) / dacMax) * 90); //arduino may be slow with floating point 
  return theta;
}

void singleStep() {
  if ( input == true )
  {
    if (curMillis - prevStepMillis >= (customDelay/100)) { //divide by 10 for slow, 100 for quicker speeds, 1000 converts to millis
        prevStepMillis = curMillis;
        digitalWrite(stepPin, HIGH);
        //delayMicroseconds(100); //may need delay, 100 us
        digitalWrite(stepPin, LOW);
    }
  }
}
