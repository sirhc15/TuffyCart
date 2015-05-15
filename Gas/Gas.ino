#include <AFMotor.h>
//#include <Servo.h>

// DC motor on M2
// m1a m1b ground m2a = black wire m2b = red wire
AF_DCMotor motor(2);
// Adding APMIN
int APMPIN = 13;
int APM_value;

int i;
volatile bool wasStopped = true;
volatile bool fullyExtended = false;
volatile bool fullyRetracted = true;
void setup() 
{
  //attachInterrupt(0, brake, FALLING); //Right PIR sensor
  //attachInterrupt(1, brake, FALLING); //Left PIR sensor 
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor party!");
  pinMode(APMPIN, INPUT);
  motor.setSpeed(200);
  motor.run(RELEASE);
}

void loop()
{
  APM_value = pulseIn(APMPIN, HIGH);

  if (APM_value > 1550) //Going forward
  {
    if (wasStopped && !fullyExtended)
    {
      Serial.print("Inside accelerate if statment\n");
      accelerate();
      wasStopped = false;
      fullyExtended = true;
    }
  }
  
  if (APM_value < 1550) //Stopping
  {
    Serial.print("inside brake if statement\n");
    brake();
  }
}

void brake()
{
  if (!fullyRetracted)
  {
    Serial.print(APM_value);
    motor.run(BACKWARD);
    Serial.print("AFTER BACKWARD IN BRAKE\n");
    motor.setSpeed(255);
    /*for (i = 0; i < 125; i++)
    {
      delayMicroseconds(16000);
    }*/
    delay(2000);
    Serial.print("BEFORE RELEASE IN BRAKE\n");
    motor.run(RELEASE);
    Serial.print("AFTER RELEASE IN BRAKE\n");

    wasStopped = true;
    fullyExtended = false;
    fullyRetracted = true;
  }
}
void accelerate()
{
  Serial.print(APM_value);
  // Serial.print("Forward function");
  motor.run(FORWARD);
  Serial.print("AFTER FORWARD IN ACCELERATE\n");
  motor.setSpeed(255);
  delay(2000);
  Serial.print("BEFORE RELEASE IN ACCELERATE\n");
  motor.run(RELEASE);
  Serial.print("AFTER RELEASE IN ACCELERATE\n");
  fullyRetracted = false;
}

