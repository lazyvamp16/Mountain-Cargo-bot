// Arduino Code for following white line using IR sensor
// And initiating server motor to unload cargo up commpleting the track

#include <Servo.h>

#define in1 12
#define in2 8
#define in3 7
#define in4 6
#define enA 11
#define enB 5

int M1_Speed = 250; // speed of motor 1
int M2_Speed = 250; // speed of motor 2
int LeftRotationSpeed = 250; // Left Rotation Speed
int RightRotationSpeed = 250; // Right Rotation Speed

Servo servoMotor;
int servoPin = 3;
int initialAngle = 173;
int finalAngle = 60;
int pauseTime = 2000;
int stopTime = 3000;

unsigned long previousMillis = 0;
boolean stopped = false;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  servoMotor.attach(servoPin);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(A2, INPUT); // initialize Left sensor as an input
  pinMode(A1, INPUT); // initialize Right sensor as an input
}

void loop() {
  int LEFT_SENSOR = digitalRead(A2);
  int RIGHT_SENSOR = digitalRead(A1);

  if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 1) {
    forward(); // FORWARD
    stopped=true;
  } else if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 0) {
    right(); // Move Right
    stopped=true;
  } else if (RIGHT_SENSOR == 0 && LEFT_SENSOR == 1) {
    left(); // Move Left
    stopped=true;
  } else if (RIGHT_SENSOR == 0 && LEFT_SENSOR == 0) {
    Stop(); // STOP
    stopped=false;
  }

  if (!stopped) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= stopTime) {
      stopped = true;
      previousMillis = currentMillis;
      Servorotate();
    }
  } else {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= pauseTime) {
      stopped = false;
      previousMillis = currentMillis;
    }
  }
}

void forward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, M1_Speed);
  analogWrite(enB, M2_Speed);
}

void right() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, LeftRotationSpeed);
  analogWrite(enB, RightRotationSpeed);
}

void left() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, LeftRotationSpeed);
  analogWrite(enB, RightRotationSpeed);
}

void Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void Servorotate() {
  for (int angle = initialAngle; angle >= finalAngle; angle--) {
    servoMotor.write(angle);
    delay(15); // Adjust the delay if needed for smoother rotation
  }

  for (int angle = finalAngle; angle <= initialAngle; angle++) {
    servoMotor.write(angle);
    delay(15); // Adjust the delay if needed for smoother rotation
  }
}
