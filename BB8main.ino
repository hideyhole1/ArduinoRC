/*
(c) 2016 Reuben Lewis, Gigi Mancuso-Jackson and Elan Bustos

This is the code for the Arduino in the BB8

Links for instructions:

*/


//pins connected to RX
int throttleInput = A5;
int aileronInput = A4;
int elevatorInput = A3;
int rudderInput = A2;
int gearInput = A1;

//aux1 doesn't work
int aux1 = A0;

//each value will also have a value from 0 to 255 with the map() function
int throttle;
int aileron;
int elevator;
int rudder;
int gear;

//pins connected to H-Bridge
int m1Forward = 5;
int m1Reverse = 6;
int m2Forward = 10;
int m2Reverse = 11;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  //setting all the inputs from the RX
  pinMode(throttleInput, INPUT);
  pinMode(aileronInput, INPUT);
  pinMode(elevatorInput, INPUT);
  pinMode(rudderInput, INPUT);
  pinMode(gearInput, INPUT);
  pinMode(aux1, INPUT);
  
  //setting the outputs for the H-Bridge
  pinMode(m1Forward, OUTPUT);
  pinMode(m1Reverse, OUTPUT);
  pinMode(m2Forward, OUTPUT);
  pinMode(m2Reverse, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //mapping the values from 0 to 255
  throttle = map(pulseIn(throttleInput, HIGH), 1070, 1880, 0, 255);
  aileron = map(pulseIn(aileronInput, HIGH), 1337, 1650, 0, 255);
  elevator = map(pulseIn(elevatorInput, HIGH), 1300, 1660, 0, 255);
  rudder = map(pulseIn(rudderInput, HIGH), 970, 1820, 0, 255);
  
  
}
