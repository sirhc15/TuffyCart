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
bool straight = false;

void setup() {
  //attachInterrupt(0, brakeToNotKill, FALLING);
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor party!");
  //pinMode(FLAG, INPUT); // turn on motor #2
  pinMode(APMIN, INPUT);//
  //pinMode(VCC, INPUT);
  //pinMode(GND,INPUT);

  motor.setSpeed(200);
  motor.run(RELEASE);
}

int i;
void loop()
{
  Serial.print("Inside LOOP before digitalwrite");

  Serial.print("Inside LOOP AFTER digitalwrite");
  if ( 1550 < APMIN < 1850  ) //left turning
  {
    right_turn = false;
    straight = false;
    if (!left_turn)
    {
      left_turn = true;
      //right_turn = false;
      retract();
    }
  }
  if (1350 < APMIN < 1550) // straight
  {
    if (!straight)
    {
      if (left_turn)
      {
        left_turn = false;
        straight = true;
        extend();
      }
      if (right_turn)
      {
        right_turn = false;
        straight =  true;
        retract();
      }
    }
  }
  if (1000 < APMIN < 1350) //right turning
  {
    left_turn = false;
    if (!right_turn)
    {
      right_turn = true;
      extend();
    }
  }
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
