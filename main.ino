#include <AFMotor.h>
#include <Servo.h>
#include <OneButton.h>

// Enums
#define STABLE 0
#define UP 1
#define DOWN 2
#define EXTEND 3
#define RETRACT 4

// Pin]s
int topDctPin = A4;           // Top Detection Pin
int botDctPin = A5;           // Bottom Detection Pin
int statusSensorPin = 25;     // Status Sensor Pin

// Components
AF_DCMotor railMtr1(1);       // Rail Motor 1
AF_DCMotor railMtr2(2);       // Rail Motor 2
Servo extServo;               // Extension Servo Motor
OneButton actvBtn(A1);        // Activate/Deactivate Canopy Button
OneButton rstBtn(A2);         // Reset Button
OneButton extdBtn(A3);        // Extend/Retract Button

// Variables
int currCnpMov = RETRACT;      // Current Canopy Movement
int currRailDir = STABLE;     // Current Rail Direction
bool rchdTop = false;         // Canopy Has Reached Top
bool rchdBot = false;         // Canopy Has Reached Bottom
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);
  actvBtn.attachClick(handleActvBtn);
  rstBtn.attachClick(handleRstBtn);
  extdBtn.attachClick(handleExtdBtn);
  extServo.attach(10);
  pinMode(topDctPin, INPUT_PULLUP);
  pinMode(botDctPin, INPUT_PULLUP);
  previousMillis = millis();
  extServo.write(0);
}

void loop() {
  rchdTop = digitalRead(topDctPin) == LOW;
  rchdBot = digitalRead(botDctPin) == LOW;
  actvBtn.tick();
  rstBtn.tick();
  extdBtn.tick();
  handleRailMovement();
  handleCanopyExtension();
}

void handleRailMovement() {
  if (currRailDir != STABLE) {
    railMtr1.setSpeed(200);
    railMtr2.setSpeed(200);
    if (currRailDir == UP && !rchdTop) {
      railMtr1.run(FORWARD);
      railMtr2.run(FORWARD);
    } else if (currRailDir == DOWN && !rchdBot) {
      railMtr1.run(BACKWARD);
      railMtr2.run(BACKWARD);
    } else {
      railMtr1.setSpeed(0);
      railMtr2.setSpeed(0);
      currRailDir = STABLE;
    }
  } else {
    railMtr1.setSpeed(0);
    railMtr2.setSpeed(0);
  }
}

void handleCanopyExtension() {
  if (currCnpMov != STABLE) {
      extServo.write(currCnpMov == EXTEND ? 180 : 0);
  } else {
    currCnpMov = RETRACT;
    extServo.write(0);
  }
}

void handleActvBtn() {
  currRailDir = (currRailDir != UP && !rchdTop) ? UP : DOWN;
}

void handleRstBtn() {
  currRailDir = STABLE;
  currCnpMov = RETRACT;
}

void handleExtdBtn() {
  currCnpMov = (currCnpMov != EXTEND && rchdTop) ? EXTEND : RETRACT;
}