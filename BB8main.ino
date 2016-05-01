//pins connected to RX
int throttle = A5;
int aileron = A4;
int elevator = A3;
int rudder = A2;
int gear = A1;

//aux1 doesn't work
int aux1 = A0;

//pins connected to H-Bridge
int m1Forward = 5;
int m1Reverse = 6;
int m2Forward = 10;
int m2Reverse = 11;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  //setting all the inputs from the RX
  pinMode(throttle, INPUT);
  pinMode(aileron, INPUT);
  pinMode(elevator, INPUT);
  pinMode(rudder, INPUT);
  pinMode(gear, INPUT);
  pinMode(aux1, INPUT);
  
  //setting the outputs for the H-Bridge
  pinMode(m1Forward, OUTPUT);
  pinMode(m1Reverse, OUTPUT);
  pinMode(m2Forward, OUTPUT);
  pinMode(m2Reverse, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
