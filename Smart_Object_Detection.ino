#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

#define TRIG_PIN_MOVING A0 
#define ECHO_PIN_MOVING A1 
#define TRIG_PIN_FIXED 2  
#define ECHO_PIN_FIXED 3  
#define MAX_DISTANCE 500
#define MAX_SPEED 190 // sets speed of DC motors
#define MAX_SPEED_OFFSET 20

NewPing sonarMoving(TRIG_PIN_MOVING, ECHO_PIN_MOVING, MAX_DISTANCE); 
NewPing sonarFixed(TRIG_PIN_FIXED, ECHO_PIN_FIXED, MAX_DISTANCE); 

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
Servo myservo; 

boolean goesForward = false;
int distanceMoving = 500;
int distanceFixed = 500;
int speedSet = 0;
int servoPos = 155; 

void setup() {
  myservo.attach(10); 
  myservo.write(servoPos); 
  delay(2000);

  distanceMoving = readMovingPing();
  distanceFixed = readFixedPing();
}

void loop() {
  int distanceR = 0;
  int distanceL = 0;
  delay(40);
  distanceMoving=readMovingPing();
  distanceFixed=readFixedPing();

  if (distanceMoving<=100){
    moveStop();
    delay(100);
    distanceR=lookRight();
    delay(200);
    distanceL=lookLeft();
    delay(200);
    
    if (distanceR>=distanceL){
      turnRight();
      moveStop();
    } 
    else{
      turnLeft();
      moveStop();
    }
  } 
  else{
    moveForward();
  }
}

int lookRight() {
  myservo.write(120); 
  delay(500);
  int distance=readMovingPing();
  myservo.write(155); 
  servoPos=155;
  return distance;
}

int lookLeft() {
  myservo.write(180); 
  delay(500);
  int distance = readMovingPing();
  myservo.write(155); 
  servoPos=155; 
  return distance;
}

int readMovingPing() { 
  delay(70);
  int cm=sonarMoving.ping_cm();
  if (cm == 0) {
    cm=250;
  }
  return cm;
}

int readFixedPing() { 
  delay(70);
  int cm=sonarFixed.ping_cm();
  if (cm==0) {
    cm=250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
} 

void moveForward() {
  goesForward=true;
  motor1.run(FORWARD); 
  motor2.run(FORWARD);
  motor3.run(FORWARD); 
  motor4.run(FORWARD); 
  for (speedSet= 0;speedSet < MAX_SPEED;speedSet+=2) {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}

void turnRight()
{
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD); 
  delay(500);
  motor1.run(FORWARD); 
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD); 
} 

void turnLeft()
{
  motor1.run(BACKWARD); 
  motor2.run(BACKWARD); 
  motor3.run(FORWARD);
  motor4.run(FORWARD); 
  delay(500);
  motor1.run(FORWARD); 
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
