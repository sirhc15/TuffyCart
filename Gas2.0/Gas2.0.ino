/*
Gas Version 2.0 uses both PIR sensors and ultrasonic sound sensors
PIR Sensors will interrupt if a change in heat is detected where the ultrasonic sound sensors 
will then be used to see if the object/person has moved out of the carts way 
*/
 
#include <AFMotor.h>

/* Variables */
// DC motor on M2
// m1a m1b ground m2a = black wire m2b = red wire
AF_DCMotor motor(2);
// Adding APMIN
int APMPIN = 13;
int APM_value;

#define echo 11           //Ultrasonic sound sensor echo pin
#define trigger 12        //Ultrasonic sound sensor trigger pin
//#define cont_interrupt 13 
//#define ledpin 14

volatile bool wasStopped = true;
volatile bool fullyExtended = false;
volatile bool fullyRetracted = true;

/* Setup */
void setup() 
{
  attachInterrupt(0, brake, FALLING); //Right PIR sensor
  attachInterrupt(1, brake, FALLING); //Left PIR sensor 
  Serial.begin(9600);                 // set up Serial library at 9600 bps
  Serial.println("Sensing Motor Party Palooza!");
  pinMode(APMPIN, INPUT);
  pinMode(trigger, INPUT);
  pinMode(echo, OUTPUT);
  //pinMode(ledpin, OUTPUT);
  //pinMode(cont_interrupt, OUTPUT);
  motor.setSpeed(200);
  motor.run(RELEASE);
}

/* Loop Function */
void loop()
{
  APM_value = pulseIn(APMPIN, HIGH);
  //Serial.print(APM_value);
  delay(1000);
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

int decrementCount(int counter)
{
  delay(500); /*Delay pauses the program for the amount of time in milliseconds,
              pausing for half a second in order to allow the ultrasonic sound sensor 
              to continue checking for anything in its way */
  return counter--;
}

long microsecsToinches(long microsecs)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microsecs / 74 / 2;
}

void brake()
{
  long soundTime, soundDistance;
  int counter = 10;
  if (!fullyRetracted)
  {
    Serial.print(APM_value);
    motor.run(BACKWARD);
    motor.setSpeed(255);
    for (int i = 0; i < 187; i++)
    {
      delayMicroseconds(16000);
    }
    motor.run(RELEASE);
    wasStopped = true;
    fullyExtended = false;
    fullyRetracted = true;
  }
  
  if(fullyRetracted)
  {
    while((soundDistance <=24) || (counter!=0)) //Will wait for 5 seconds and also check if the object/person is within 2 feet 
    {
      digitalWrite(trigger, LOW); 
      delayMicroseconds(4);
      digitalWrite(trigger, HIGH);
      delayMicroseconds(8);
      digitalWrite(trigger, LOW);
      soundTime = pulseIn(echo, HIGH);
      soundDistance = microsecsToinches(soundTime);
      counter = decrementCount(counter); 
      Serial.print(soundDistance);
      Serial.println(" inches");
    }
  }  
}

void accelerate()
{
  Serial.print(APM_value);
  motor.run(FORWARD);
  motor.setSpeed(255);
  delay(3000);
  motor.run(RELEASE);
  fullyRetracted = false;
}
