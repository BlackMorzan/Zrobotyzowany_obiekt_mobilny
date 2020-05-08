#include <Servo.h>

const int ledPin = 3;

// Ultrasocnic sesor
const int HCTrigPin = 11;
const int HCEchoPin = 10;

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
// Ultrasonic sensor control
int getDistance();

// Engines control
void moveFWD();
void moveBWD();
void stopMotors();


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  // Ultrasonic sensor
  pinMode(HCTrigPin, OUTPUT);
  pinMode(HCEchoPin, INPUT);


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
  while (getDistance() > 20) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }

  delay(2000);

  while (getDistance() > 20) {
    //moveFWD();
  }
  //stopMotors();
  delay(2000);

  

  

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Engines Control
void moveFWD() {
  analogWrite(APwmPin, 50);
  analogWrite(BPwmPin, 50);

  digitalWrite(AOutPin1, HIGH);
  digitalWrite(AOutPin2, LOW);
  digitalWrite(BOutPin1, LOW);
  digitalWrite(BOutPin2, HIGH);
}
//-------------------------------------------------------------------------------------------------------------------------
void moveBWD() {
  analogWrite(APwmPin, 50);
  analogWrite(BPwmPin, 50);

  digitalWrite(AOutPin1, LOW);
  digitalWrite(AOutPin2, HIGH);
  digitalWrite(BOutPin1, HIGH);
  digitalWrite(BOutPin2, LOW);
}

//-------------------------------------------------------------------------------------------------------------------------
void stopMotors() {
  analogWrite(APwmPin, 50);
  analogWrite(BPwmPin, 50);

  digitalWrite(AOutPin1, LOW);
  digitalWrite(AOutPin2, LOW);
  digitalWrite(BOutPin1, LOW);
  digitalWrite(BOutPin2, LOW);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ultrasonic sensor
int getDistance() {
  long time_p, distance;

  digitalWrite(HCTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(HCTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(HCTrigPin, LOW);

  time_p = pulseIn(HCEchoPin, HIGH);
  distance = time_p / 58;

  return distance;
}