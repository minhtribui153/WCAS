#include <AFMotor.h>
#include <OneButton.h>

#define STABLE 0
#define UP 1
#define DOWN 2


// Components
AF_DCMotor pulleyMotorUp(1);
AF_DCMotor pulleyMotorDown(2);
OneButton moveButton(A1);
OneButton resetButton(A2);


// Variables
bool railMovementState = STABLE;
bool done = false;
bool forwardDirection = false;
bool reachedTop = false;
bool reachedBottom = false;

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(9600);

	pinMode(A3, INPUT_PULLUP); // Bottom reach detector
	pinMode(A4, INPUT_PULLUP); // Top reach detector
	
	// Functions
	moveButton.attachClick([]() 
	{
		forwardDirection = !forwardDirection;
		canMove = true;
	});
	resetButton.attachClick([]()
	{
		canMove = false;
	});
}


void loop()
{
	reachedTop = digitalRead(A4) == LOW;
	reachedBottom = digitalRead(A3) == LOW;
	Serial.println(reachedBottom);
	// put your main code here, to run repeatedly:
	pulleyMotorUp.setSpeed(movementState == STABLE ? 0 : 80);
	pulleyMotorDown.setSpeed(movementState == STABLE ? 0 : 80);

	
	updateButtons();
}

void updateCanopy()
{
	if (isMoving == UP) 
	{
		
	}
	else if (isMoving == DOWN) 
	{
		
	}
}

void updateButtons() 
{
	moveButton.tick();
	resetButton.tick();
}