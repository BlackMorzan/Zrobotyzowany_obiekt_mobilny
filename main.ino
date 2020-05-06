#include <Servo.h>

const int ledPin = 3;

// SERVO
Servo Serwo;

const int ServoPin = 9;
int initSerwoPos = 0;
int currentSerwoPos = 0;

// ENGINES
const int AOutPin1 = A5;
const int AOutPin2 = A4;
const int APwmPin = 5;

const int BOutPin1 = 13;
const int BOutPin2 = 12;
const int BPwmPin = 6;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Engines control
void moveFWD();
void moveBWD();


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  pinMode(ledPin, OUTPUT);

  // Servo
  Serwo.attach(9);

  
  // Engines
  pinMode(APwmPin, OUTPUT);
  pinMode(AOutPin1, OUTPUT);
  pinMode(AOutPin2, OUTPUT);

  pinMode(BPwmPin, OUTPUT);
  pinMode(BOutPin1, OUTPUT);
  pinMode(BOutPin2, OUTPUT);
}

void loop() {

  delay(2000);

  // 98 - middle

  Serwo.write(2);

  delay(2000);
  Serwo.write(89);
  delay(2000);
  Serwo.write(178);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Engines Control
void moveFWD() {
  digitalWrite(APwmPin, HIGH);
  digitalWrite(BPwmPin, HIGH);

  digitalWrite(AOutPin1, HIGH);
  digitalWrite(AOutPin2, LOW);
  digitalWrite(BOutPin1, LOW);
  digitalWrite(BOutPin2, HIGH);
}
//-------------------------------------------------------------------------------------------------------------------------
void moveBWD() {
  digitalWrite(APwmPin, HIGH);
  digitalWrite(BPwmPin, HIGH);

  digitalWrite(AOutPin1, LOW);
  digitalWrite(AOutPin2, HIGH);
  digitalWrite(BOutPin1, HIGH);
  digitalWrite(BOutPin2, LOW);
}