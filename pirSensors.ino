/////////////////////////////
//Variables
//Time given to calibrate sensors should be between 10 - 60 secs
int calibrationTime = 30;        

//the time when the sensor outputs a low impulse
long unsigned int lowInput;         

long unsigned int pause = 5000;  

boolean lock = true;
boolean takeLowTime;  

int pirPin = 12;    //the digital pin connected to the PIR sensor's output
int ledPin = 13;    //the digital pin connected to the LED as output
int pirOut = 11;    //the digital pin used to interrupt the motors


/////////////////////////////
//Initial Setup
////////////////////////////
void setup(){
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(pirOut, OUTPUT);
  digitalWrite(pirOut, LOW);
  digitalWrite(pirPin, LOW);
  digitalWrite(ledPin, LOW);
  //Calibrate sensors
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
  }

////////////////////////////
//LOOP
void loop(){
     if(digitalRead(pirPin) == HIGH){
       digitalWrite(ledPin, HIGH);   
       digitalWrite(pirOut, HIGH);
       if(lock){  
         lock = false;            
         Serial.println("---");
         Serial.print("motion detected at ");
         Serial.print(millis()/1000);
         Serial.println(" sec"); 
         delay(30);
         }         
         takeLowTime = true;
       }

     if(digitalRead(pirPin) == LOW){ 
       digitalWrite(pirOut, LOW);      
       digitalWrite(ledPin, LOW);  

       if(takeLowTime){
        lowInput = millis();         
        takeLowTime = false;     
        }
       if(!lock && millis() - lowInput > pause){  
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           delay(30);
           }
       }
  }
