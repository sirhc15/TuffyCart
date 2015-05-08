//HC-SR04 - Ultrasonic Sound Sensor
/* To be used after motion has been detected by PIR sensor which will send a signal if the 
ultrasonic sound sensor detects something/someone within 2 feet */

#define echo 11
#define trigger 12
#define cont_interrupt 13
#define ledpin 14

void setup() 
{
  Serial.begin (9600);
  pinMode(echo, OUTPUT);
  pinMode(ledpin, OUTPUT);
  pinMode(cont_interrupt, OUTPUT);
  pinMode(trigger, INPUT);
}

void loop() 
{
  long time, soundDistance;
  digitalWrite(trigger, LOW); 
  delayMicroseconds(4);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(8);
  digitalWrite(trigger, LOW);
  time = pulseIn(echo, HIGH);
  soundDistance = microsecsToinches(time);
  
  if (soundDistance <= 24) 
  {
    digitalWrite(cont_interrupt,HIGH);
    digitalWrite(ledpin, HIGH);
  }
  if (soundDistance > 24 || soundDistance <= 0)
  {
    Serial.println("Out of range");
  }
  else 
  {
    Serial.print(soundDistance);
    Serial.println(" inches");
  }
  delay(500);
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