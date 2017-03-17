/*
(c) 2016 Reuben Lewis, Gigi Mancuso-Jackson and Elan Bustos

This is the code for the Arduino in the BB8

Links for instructions:

*/

//pins connected to RX
int throttleInput = A5;
int aileronInput = A4;
int elevatorInput = A3;

//each value will also have a value from 0 to 255 with the map() function
int throttle;
int aileron;
int elevator;


//pins connected to H-Bridge
int m1Forward = 5;
int m1Reverse = 3;
int m2Forward = 11;
int m2Reverse = 6;

int motor1val;
int motor2val;

//1 is forward, 2 is backwards
void spinMotor1(int fwdback, int pwm) {
  if(fwdback == 1){
    analogWrite(m1Forward, pwm);
    analogWrite(m1Reverse, LOW);
  }
  else if(fwdback == 2){
    analogWrite(m1Forward, LOW);
    analogWrite(m1Reverse, pwm);
  }
  else {
    analogWrite(m1Forward, LOW);
    analogWrite(m1Reverse, LOW);
  }
}

void spinMotor2(int fwdback, int pwm) {
  if(fwdback == 1){
    analogWrite(m2Forward, pwm);
    analogWrite(m2Reverse, LOW);
  }
  else if(fwdback == 2){
    analogWrite(m2Forward, LOW);
    analogWrite(m2Reverse, pwm);
  }
  else {
    analogWrite(m2Forward, LOW);
    analogWrite(m2Reverse, LOW);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  //setting all the inputs from the RX
  pinMode(throttleInput, INPUT);
  pinMode(aileronInput, INPUT);
  pinMode(elevatorInput, INPUT);
  
  
  //setting the outputs for the H-Bridge
  pinMode(m1Forward, OUTPUT);
  pinMode(m1Reverse, OUTPUT);
  pinMode(m2Forward, OUTPUT);
  pinMode(m2Reverse, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //mapping the values from 0 to 255
  throttle = map(pulseIn(throttleInput, HIGH), 1070, 1700, 0, 180);
  aileron = map(pulseIn(aileronInput, HIGH), 1100, 1850, 0, 255);
  elevator = map(pulseIn(elevatorInput, HIGH), 1280, 1660, 0, 255);
  rudder = map(pulseIn(rudderInput, HIGH), 970, 1820, 0, 180);
  
  //make sure the values are >= 0 and <= 255
  throttle = constrain(throttle, 0, 180);
  aileron = constrain(aileron, 0, 255);
  elevator = constrain(elevator, 0, 255);

  
  
  //set speeds for the motors
  if(elevator > 135) {
    motor1val = map(elevator, 135, 255, 0, 255);
    motor2val = map(elevator, 135, 255, 0, 255);
  }
  
  else if(elevator < 115) {
    motor1val = map(elevator, 115, 0, 0, 255);
    motor2val = map(elevator, 115, 0, 0, 255);
  }
  
  if(aileron > 135) {
    if(elevator > 135) {
      motor2val = motor2val - map(aileron, 135, 255, 0, elevator - 135);
    }
    else if(elevator < 115) {
      motor2val = motor2val - map(aileron, 135, 255, 0, elevator + 135);
    }
  }
  
  
  else if(aileron < 115) {
    if(elevator > 135) {
      motor1val = motor1val - map(aileron, 115, 0, 0, elevator - 115);
    }
    else if(elevator < 115) {
      motor1val = motor1val - map(aileron, 115, 0, 0, elevator + 115);
    }
  }
  
  //spin the motors
  if(elevator > 135) {
    spinMotor1(1, motor1val);
    spinMotor2(1, motor2val);
  }
  else if(elevator < 115){
    spinMotor1(2, motor1val);
    spinMotor2(2, motor2val);
  }
  else {
    spinMotor1(1, 0);
    spinMotor2(1, 0);
  }
  
}
