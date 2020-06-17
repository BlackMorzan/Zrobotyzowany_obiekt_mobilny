
#include <Servo.h>

const int ledPin = 3;

// ENCODERS INPUTS
const int ECLeftA = 7;
const int ECLeftB = 8;
const int ECRightA = A3;
const int ECRightB = A0;

int leftEngineCounter = 0;
int rightEngineCounter = 0;

// tests
int leftEncoderState = 0;
int rightEncoderState = 0;


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
int detectObstacle();

// Engines control
void moveFWD();
void moveBWD();
void moveLeft();
void moveRight();
void turnAround();
void stopMotors();

// Encoders control
void countLeftEngine();
void countRightEngine();

// Avoiding obstacles
char getObstacleSide();
int detectObstacle();

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

  // ENCODERS:
  pinMode(ECLeftA, INPUT);
  pinMode(ECLeftB, INPUT);
  pinMode(ECRightA, INPUT);
  pinMode(ECRightB, INPUT);

  // Interrupts
  attachInterrupt(digitalPinToInterrupt(ECLeftB), countLeftEngine, RISING);
  attachInterrupt(digitalPinToInterrupt(ECRightB), countRightEngine, RISING);
}

void loop() {

  Serwo.write(89);
  
  // Oczekiwanie na włączenie
  while (getDistance() > 20) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }

  delay(2000);
  
  while (1) {

    int distance;
    char obstacleSide = 'o';

    // Jazda do przodu, do czasu wykrycia przeszkody
    while (getDistance() > 20) {
      moveFWD();
    }

    // Wykrycie przeszkody - zatrzymanie silnikow
    stopMotors();

    // Wykrycie strony po ktrej jest przeszkoda
    obstacleSide = getObstacleSide();

    // Jesli po prawej -> obrot w lewo i ustawienie czujnika w prawo
    if(obstacleSide == 'r'){
      moveLeft();
      Serwo.write(178);
      delay(200);
    }
    else if(obstacleSide == 'l'){ // Jesli po lewej -> Obrot w prawo i ustawienie czujnika w lewo
      moveRight();
      Serwo.write(2);
      delay(200);
    }


    // Jazda do przodu i monitorowanie czy przeszkoda o lewej/prawej stronie sie nie skonczyla
    // Jednoczenie monitorowany jest czas jazdy
    while (getDistance() < 20) {
      moveFWD();
      distance++; // Zliczenie czasu, ktory jest potrzebny na ominiecie przeszkody
      Serial.println(distance);
    }

    // Gdy przeszkoda sie skonczy: wyrownanie serwa, odczekanie 300ms, wylaczenie silnikow
    Serwo.write(89);
    delay(100);
    stopMotors();
    delay(5000);

    
    // Powrot na prosta droge, obok przeszkody
    if(obstacleSide == 'l'){
      moveLeft();
      Serwo.write(2);
    }
    else if(obstacleSide == 'r'){
      moveRight();
      Serwo.write(178);
    }

    delay(1000);

    // Jazda do przodu wzdluz przeszkody
    while (getDistance() < 20) {
      moveFWD();
    }

    delay(500);

    // Przeszkoda sie skonczyla
    // Gdy przeszkoda sie skonczy: wyrownanie serwa, odczekanie 300ms, wylaczenie silnikow
    Serwo.write(89);
    delay(300);
    stopMotors();
    delay(2000);

    //Obrot, wjazd za prszeszkode
    if(obstacleSide == 'l'){
      moveLeft();
      Serwo.write(2);
    }
    else if(obstacleSide == 'r'){
      moveRight();
      Serwo.write(178);
    }
    delay(500);


    // Jazda do przod, tyle czasu ile wczesniej przy omijaniu preszkody
    while(distance >= 0){
      distance--;
      moveFWD;
    }

    stopMotors();

    // Dojazd na ta sama sciezke
    // Obrot by jechac w tej samej linii
    if(obstacleSide == 'l'){
      moveLeft();
      Serwo.write(2);
    }
    else if(obstacleSide == 'r'){
      moveRight();
      Serwo.write(178);
      }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Avoiding obstacles
char getObstacleSide(){

    Serwo.write(2); // Ustawienie czujnika w lewo
    delay(1000);
    if(getDistance() < 20){
      return 'l';
    }
    Serwo.write(178);
    delay(1000);
    if(getDistance() < 20){
      return 'r';
    }
}

// Encoders control
void countLeftEngine(){
  Serial.println("Wywolane przerwanie");
  
  if(digitalRead(ECLeftA)){
    leftEngineCounter++;
  }
  else{
    leftEngineCounter--;
  }
}

void countRightEngine(){

  Serial.println("Wywolane przerwanie");
  
  if(digitalRead(ECRightB)){
    rightEngineCounter++;
  }
  else{
    rightEngineCounter--;
  }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Engines Control
void moveFWD() {
  analogWrite(APwmPin, 100);
  analogWrite(BPwmPin, 100);

  digitalWrite(AOutPin1, LOW);
  digitalWrite(AOutPin2, HIGH);
  digitalWrite(BOutPin1, LOW);
  digitalWrite(BOutPin2, HIGH);
}
//-------------------------------------------------------------------------------------------------------------------------
void moveBWD() {
  analogWrite(APwmPin, 100);
  analogWrite(BPwmPin, 100);

  digitalWrite(AOutPin1, HIGH);
  digitalWrite(AOutPin2, LOW);
  digitalWrite(BOutPin1, HIGH);
  digitalWrite(BOutPin2,  LOW);
}

//-------------------------------------------------------------------------------------------------------------------------
void moveLeft(){
  analogWrite(APwmPin, 100);
  analogWrite(BPwmPin, 100);

  digitalWrite(AOutPin1, LOW);
  digitalWrite(AOutPin2, HIGH);
  digitalWrite(BOutPin1, HIGH);
  digitalWrite(BOutPin2, LOW);

  delay(300);
}

void moveRight(){
  analogWrite(APwmPin, 100);
  analogWrite(BPwmPin, 100);

  digitalWrite(AOutPin1, HIGH);
  digitalWrite(AOutPin2, LOW);
  digitalWrite(BOutPin1, HIGH);
  digitalWrite(BOutPin2, LOW);

  delay(300);
}


void turnAround(){
  analogWrite(APwmPin, 100);
  analogWrite(BPwmPin, 100);

  digitalWrite(AOutPin1, HIGH);
  digitalWrite(AOutPin2, LOW);
  digitalWrite(BOutPin1, HIGH);
  digitalWrite(BOutPin2, LOW);

  delay(1000);
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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///*
int detectObstacle() {
  Serwo.write(2);
  if (getDistance() < 20) {
    delay(200);
    Serwo.write(89);
    return 1;
  }
  else {
    delay(200);
    Serwo.write(89);
  }

  Serwo.write(178);
  if (getDistance() < 20) {
    delay(200);
    Serwo.write(89);
    return 2;
  }
  else {
    delay(200);
    Serwo.write(89);
  }

  return -1;
}
