// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!
// left:1850-1550
// center: 1350-1550
// right: 1000-1350
#include <AFMotor.h>

// DC motor on M2
AF_DCMotor motor(2);

int APMIN = 13;
int APM_value;
//int VCC = 10;
//int GND = 11;
bool left_turn = false;
bool right_turn = false;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor party!");
  pinMode(APMIN, INPUT);//
  //pinMode(VCC, INPUT);
  //pinMode(GND,INPUT);
  motor.setSpeed(200);
  motor.run(RELEASE);
}

void loop()
{
  APM_value = pulseIn(APMIN, HIGH);
  if ( (1550 < APM_value) && (APM_value < 1850) && !left_turn  ) //left turning
  {
    right_turn = false;
    left_turn = true;
    retract();
  }
  if ((1350 < APM_value) && (APM_value< 1550)) // straight
  {
    if (left_turn)
    {
      left_turn = false;
      extend();
    }
    if (right_turn)
    {
      right_turn = false;
      retract();
    }
  }
  if ((1000 < APM_value) && (APM_value < 1350) && !right_turn) //right turning
  {
    left_turn = false;
    right_turn = true;
    extend();
  }
}

void retract()// left turn
{
  Serial.print(APM_value);
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
  Serial.print(APM_value);
  motor.run(FORWARD);
  Serial.print("AFTER FORWARD EXTEND\n");
  motor.setSpeed(255);
  delay(3000);
  Serial.print("BEFORE RELEASE EXTEND\n");
  motor.run(RELEASE);
  Serial.print("AFTER RELEASE EXTEND\n");
}
