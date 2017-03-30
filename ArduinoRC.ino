/*
(c) Elan Bustos and Miles Fleisher

This is the code for the Arduino in the Arduino RC.

*/

// The Led Pins
const int ledPin =  7;
const int ledPin1 = 8;



unsigned long previousMillis = 0;        // will store last time LED was up
const int interval = 1000;           // interval at which to blink (milliseconds)

//pins connected to RX
int throttleInput = A5;
int steeringInput = A4;

//each value will also have a value from 0 to 255 with the map() function
int throttle;
int steering;

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
  pinMode(ledPin, OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  //setting all the inputs from the RX
  pinMode(throttleInput, INPUT);
  pinMode(steeringInput, INPUT);
  
  //setting the outputs for the H-Bridge
  pinMode(m1Forward, OUTPUT);
  pinMode(m1Reverse, OUTPUT);
  pinMode(m2Forward, OUTPUT);
  pinMode(m2Reverse, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (digitalRead(ledPin) == LOW) {
      digitalWrite(ledPin, HIGH);
      digitalWrite(ledPin1, LOW);
    } else {
      digitalWrite(ledPin, LOW);
      digitalWrite(ledPin1, HIGH);
    }
  }
  // put your main code here, to run repeatedly:
  
  //mapping the values from 0 to 255(CHANGE VALUES WHEN GET CONTROLER!!!!!)
  throttle = map(pulseIn(throttleInput, HIGH), 1070, 1700, 0, 180);
  steering = map(pulseIn(steeringInput, HIGH), 1100, 1850, 0, 255);
  
  //make sure the values are >= 0 and <= 255
  throttle = constrain(throttle, 0, 180);
  aileron = constrain(steering, 0, 255);
  
  //set speeds for the motors
  if(throttle > 135) {
    motor1val = map(throttle, 135, 255, 0, 255);
    motor2val = map(throttle, 135, 255, 0, 255);
  }
  
  else if(throttle < 115) {
    motor1val = map(throttle, 115, 0, 0, 255);
    motor2val = map(throttle, 115, 0, 0, 255);
  }
  
  if(steering > 135) {
    if(throttle > 135) {
      motor2val = motor2val - map(steering, 135, 255, 0, throttle - 135);
    }
    else if(throttle < 115) {
      motor2val = motor2val - map(steering, 135, 255, 0, throttle + 135);
    }
  }
  
  
  else if(steering < 115) {
    if(throttle > 135) {
      motor1val = motor1val - map(steering, 115, 0, 0, throttle - 115);
    }
    else if(throttle < 115) {
      motor1val = motor1val - map(steering, 115, 0, 0, throttle + 115);
    }
  }
  
  //spin the motors
  if(throttle > 135) {
    spinMotor1(1, motor1val);
    spinMotor2(1, motor2val);
  }
  else if(throttle < 115){
    spinMotor1(2, motor1val);
    spinMotor2(2, motor2val);
  }
  else {
    spinMotor1(1, 0);
    spinMotor2(1, 0);
  }
  
}
