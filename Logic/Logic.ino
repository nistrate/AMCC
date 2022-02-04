#include <Servo.h>
#include <myDCMotorLibrary.h>

int Echo = A0;
int Trig = A1;
#define LeftBackIO  6 
#define LeftBackA  4 
#define LeftBackB  5 


#define RightBackIO 3
#define RightBackA 2
#define RightBackB 10

#define FrontIO 7
#define FrontA 12
#define FrontB 13

myDCMotorLibrary car(LeftBackIO, LeftBackA, LeftBackB, RightBackIO, RightBackA, RightBackB, FrontIO, FrontA, FrontB);


int rightDistance = 0, leftDistance = 0, middleDistance =0;

int posLow = 8;    // variable to store the servo position
int servoPosition;
int newServoPosition;
Servo myservo;  // create servo object to control a servo
#define ServoPin 9  // servo pin


//SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN); // create distance sensor object
long a;         // variable to store the distance in cm
int speed = 100;
int thresholdDistance = 35; //cm

///////////////////////////////

/////////////////////////////////////
//////  Servo Functions

void moveFromToAngle(int pos0, int pos1)
{
  if (pos0 < pos1)
  {
    for (int pos = pos0; pos <= pos1; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15 ms for the servo to reach the position
    }
  }
    
  if (pos0 > pos1)
  {
    for (int pos = pos0; pos >= pos1; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15 ms for the servo to reach the position
    }
  }

}


//////////////////////
//// Ultrasonic Function

int Distance_test()
{
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);
  float Fdistance = pulseIn(Echo, HIGH);
  Fdistance = Fdistance / 58;
  return (int)Fdistance;
}

////////////////////////////////

void setup() {

  //Servo
  myservo.attach(ServoPin);  // attaches the servo on pin 9 to the servo object
  myservo.write(posLow);

   Serial.begin(9600); // spiecfies the output channel
   delay(500);

  // Ultrasound HC04
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);

  car.PowerFront(HIGH);
  car.PowerBack(HIGH,HIGH);
}


void loop() {
 
   servoPosition = 90;
   myservo.write(servoPosition);
   delay(500);

   middleDistance = Distance_test();
   Serial.print("Measurement at angle: ");
   Serial.print(servoPosition);
   Serial.print(" degrees - ");
   Serial.print(middleDistance);
   Serial.println(" cm");


   if (middleDistance <= thresholdDistance){
    car.PowerOff();
    delay(500);
    newServoPosition = posLow;
    moveFromToAngle(servoPosition, newServoPosition);
    servoPosition = newServoPosition;
    delay(1000);
    rightDistance = Distance_test();
    Serial.print("Measurement at angle: ");
    Serial.print(servoPosition);
   Serial.print(" degrees - ");
   Serial.print(rightDistance);
   Serial.println(" cm");

    delay(500);
    newServoPosition = 180;
    moveFromToAngle(servoPosition, newServoPosition);
    servoPosition = newServoPosition;
    delay(1000);
    leftDistance = Distance_test();
    Serial.print("Measurement at angle: ");
    Serial.print(servoPosition);
   Serial.print(" degrees - ");
   Serial.print(leftDistance);
   Serial.println(" cm");

    delay(500);
    newServoPosition = 90;
    moveFromToAngle(servoPosition, newServoPosition);
    servoPosition = newServoPosition;
    delay(1000);

    if ( (rightDistance > leftDistance) || (rightDistance > thresholdDistance) )
    {
      car.PowerFront(HIGH);
      car.PowerBack(HIGH,HIGH);
      car.rightForwardTurn(1000);
    }
    else if ((rightDistance < leftDistance)||(leftDistance > thresholdDistance)){
      car.PowerFront(HIGH);
      car.PowerBack(HIGH,HIGH);
      car.leftForwardTurn(1000);
    }
    else if ( (rightDistance <= thresholdDistance) || (leftDistance <= thresholdDistance)){
      car.PowerBack(HIGH,HIGH);
      car.backward(1000, speed);
    }

    else {
      car.PowerBack(HIGH,HIGH);
      car.forward(speed);
    }
    
   }
   else {
    car.PowerBack(HIGH,HIGH);
    car.forward(speed);
   }

    // car.PowerBack(100,100);
    // delay(100);
    // car.forward(speed);
    // delay(1000);
    // car.backward(1000, speed);
    // car.PowerOff();
    // delay(1000);
    // leftForwardTurn(1000);
    // delay(1000);
    // leftForwardTurn(1000);
    
}