// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!
// left:1850-1550
// center: 1350-1550
// right: 1000-1350
#include <AFMotor.h>
#include <Servo.h>

// DC motor on M2
AF_DCMotor motor(2);

int APMIN = 13;
//int VCC = 10;
//int GND = 11;
bool left_turn = false;
bool right_turn = false;

void setup() {
  //attachInterrupt(0, brakeToNotKill, FALLING);
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor party!");
  pinMode(APMIN, INPUT);//
  //pinMode(VCC, INPUT);
  //pinMode(GND,INPUT);

  motor.setSpeed(200);
  motor.run(RELEASE);
}

int i;
int steer;//variable to determine direction
void loop()
{
  Serial.print("Inside LOOP before digitalwrite");

  Serial.print("Inside LOOP AFTER digitalwrite");
  if( 1550 < APMIN < 1850 && !left_turn )// turn left if  
  {
    right_turn = false;
    left_turn = true;
    steer = 0;
  }
  if ( 1350 < APMIN < 1550)//go straight
  {
    if(left_turn)
    {
      steer = 1;
      left_turn = false;
    }
    if(right_turn)
    {
      steer = 0;
      right_turn = false;
    }
  }
  if( 1550 < APMIN < 1850 && !right_turn )
  {
    left_turn = false;
    right_turn = true;
    steer = 1;
  }
  switch (steer)//chooses which direction to go
  {
    case 0:
      retract();
      break;
    case 1:
     extend();
     break; 
    default:
      break;
  }
  steer = 2;//used to hold position
}

void retract()// left turn
{
  motor.run(BACKWARD);
  Serial.print("AFTER BACKWARD RETRACT\n");
  motor.setSpeed(255);
  delay(3000);
  Serial.print("BEFORE RELEASE RETRACT\n");
  motor.run(RELEASE);
  Serial.print("AFTER RELEASE RETRACT\n");
}

void extend()//right turn
{
  // Serial.print("Forward function");
  motor.run(FORWARD);
  Serial.print("AFTER FORWARD EXTEND\n");
  motor.setSpeed(255);
  delay(3000);
  Serial.print("BEFORE RELEASE EXTEND\n");
  motor.run(RELEASE);
  Serial.print("AFTER RELEASE EXTEND\n");
}
