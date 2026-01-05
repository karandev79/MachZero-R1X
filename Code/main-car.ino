#include <AFMotor.h>

AF_DCMotor motor1(1); 
AF_DCMotor motor2(2); 
AF_DCMotor motor3(3); 
AF_DCMotor motor4(4);

const int leftIR = A0;
const int rightIR = A1;

char command;
int speed = 200;

void setup() {
  Serial.begin(9600);
  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);
  
  setSpeed(speed);
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();
    stopMotors();
  }

  if (command == 'X') {
    obstacleAvoidance();
  } else {
    remoteControl(command);
  }
}

void remoteControl(char cmd) {
  switch (cmd) {
    case 'F': forward();  break;
    case 'B': backward(); break;
    case 'L': left();     break;
    case 'R': right();    break;
    case 'S': stopMotors(); break;
  }
}

void obstacleAvoidance() {
  int leftVal = digitalRead(leftIR);
  int rightVal = digitalRead(rightIR);

  if (leftVal == HIGH && rightVal == HIGH) {
    forward();
  } else if (leftVal == LOW && rightVal == HIGH) {
    right();
    delay(300);
  } else if (leftVal == HIGH && rightVal == LOW) {
    left();
    delay(300);
  } else {
    backward();
    delay(400);
    left();
    delay(300);
  }
}

void forward() {
  motor1.run(FORWARD); motor2.run(FORWARD);
  motor3.run(FORWARD); motor4.run(FORWARD);
}

void backward() {
  motor1.run(BACKWARD); motor2.run(BACKWARD);
  motor3.run(BACKWARD); motor4.run(BACKWARD);
}

void left() {
  motor1.run(BACKWARD); motor2.run(BACKWARD);
  motor3.run(FORWARD);  motor4.run(FORWARD);
}

void right() {
  motor1.run(FORWARD);  motor2.run(FORWARD);
  motor3.run(BACKWARD); motor4.run(BACKWARD);
}

void stopMotors() {
  motor1.run(RELEASE); motor2.run(RELEASE);
  motor3.run(RELEASE); motor4.run(RELEASE);
}

void setSpeed(int s) {
  motor1.setSpeed(s); motor2.setSpeed(s);
  motor3.setSpeed(s); motor4.setSpeed(s);
}