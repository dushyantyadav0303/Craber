#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <ESP32Servo.h>




#define TRIG1 13
#define ECHO1 12
#define TRIG2 14
#define ECHO2 27
#define TRIG3 15
#define ECHO3 16


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
Servo servo17;
Servo servo18;




void setup() {
  Serial.begin(115200);

  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);

  Wire.begin(21, 22);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);

  servo17.setPeriodHertz(50);
  servo18.setPeriodHertz(50);
  servo17.attach(19, 500, 2500);
  servo18.attach(18, 500, 2500);

  delay(500);
  standUp();
}



void loop() {
  float d1 = getDistance(TRIG1, ECHO1);
  float d2 = getDistance(TRIG2, ECHO2);
  Serial.println(d1);
  Serial.println(d2);

  if (d1 < 20 || d2 < 20) {
    standUp();
    turnRight();
  } else {
    walkForward();
  }
}








void setServo(int number, int angle) {
  if (number <= 16) {
    int pulse = map(angle, 0, 180, 500, 2500);
    pwm.writeMicroseconds(number - 1, pulse);
  }
  if (number == 17) {
    servo17.write(angle);
  }
  if (number == 18) {
    servo18.write(angle);
  }
}




float getDistance(int trig, int echo) {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);



  long time = pulseIn(echo, HIGH, 30000);
  if (time == 0) {
    return 999;
  }
  return time * 0.034 / 2;
}



void standUp() {
  for (int i = 1; i <= 18; i++) {
    setServo(i, 90);
  }
  delay(500);
}



void walkForward() {
  for (int leg = 0; leg < 6; leg += 2) {
    setServo(leg * 3 + 2, 60);
    setServo(leg * 3 + 1, 110);
  }
  for (int leg = 1; leg < 6; leg += 2) {
    setServo(leg * 3 + 1, 70);
  }
  delay(300);
  for (int leg = 0; leg < 6; leg += 2) {
    setServo(leg * 3 + 2, 90);
  }
  delay(300);

  for (int leg = 1; leg < 6; leg += 2) {
    setServo(leg * 3 + 2, 60);
    setServo(leg * 3 + 1, 110);
  }
  for (int leg = 0; leg < 6; leg += 2) {
    setServo(leg * 3 + 1, 70);
  }
  delay(300);
  for (int leg = 1; leg < 6; leg += 2) {
    setServo(leg * 3 + 2, 90);
  }
  delay(300);
}




void turnRight() {
  for (int leg = 0; leg < 6; leg += 2) {
    setServo(leg * 3 + 2, 60);
    setServo(leg * 3 + 1, 120);
  }
  delay(300);
  for (int leg = 0; leg < 6; leg += 2) {
    setServo(leg * 3 + 2, 90);
  }
  delay(300);

  for (int leg = 1; leg < 6; leg += 2) {
    setServo(leg * 3 + 2, 60);
    setServo(leg * 3 + 1, 120);
  }
  delay(300);
  for (int leg = 1; leg < 6; leg += 2) {
    setServo(leg * 3 + 2, 90);
  }
  delay(300);

  standUp();
}


