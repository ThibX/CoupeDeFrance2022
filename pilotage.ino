#include<SharpIR.h>; 

#define ENCODEROUTPUT 663

const byte pinSensor=2;
SharpIR mySensor(SharpIR::GP2Y0A21YK0F,A0);
unsigned int distance=0;

const int HALLSEN_A = 19; // Hall sensor A connected to pin 3 (external interrupt)
const int MOTOR1A = 8; //en1
const int MOTOR1B = 9;  //en2
const int ENA=24;

const int HALLSEN_2A = 18; // Hall sensor A connected to pin 3 (external interrupt)
const int MOTOR2A = 10;  //en3
const int MOTOR2B = 11;  //en4
const int ENB=25;

//The sample code for driving one way motor encoder
volatile long encoderValue = 0;
volatile long encoderValue2 = 0;

int interval = 1000;
int marche=0;
long previousMillis = 0;
long currentMillis = 0;

int rpm = 0, rpm2=0;
byte speed=200, speed2=190;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(HALLSEN_A), niv1, RISING);
  attachInterrupt(digitalPinToInterrupt(HALLSEN_2A), niv2, RISING);
 attachInterrupt(digitalPinToInterrupt(pinSensor),verification,FALLING);

   pinMode( MOTOR1A , OUTPUT);
   pinMode( MOTOR1B , OUTPUT);
   pinMode( MOTOR2A , OUTPUT);
   pinMode( MOTOR2B , OUTPUT);
   pinMode(ENB,OUTPUT);
   digitalWrite(ENB,HIGH);
   pinMode(ENA,OUTPUT);
   digitalWrite(ENA,HIGH);
}

void loop() {
  while(Serial.available()>0){
    Serial.println(mySensor.getDistance());
    char a=Serial.read();
    Serial.println(a); 
    switch(a){
      case 'z':avancer();
            Serial.println(encoderValue);
            Serial.println(encoderValue2);
            Serial.println(speed);
            Serial.println(speed2);
            break;
      case 's':reculer(); break;
      case 'q':left();break;
      case 'd':right();break;
      case 'a':arret();break; 
    } 
  }
}
void niv1(){
  encoderValue++;
 /* if(encoderValue>encoderValue2){
    if(speed==150){speed2=+5;}
    else{speed=-5;}
  }
  if(encoderValue<encoderValue2){
    if(speed==255){speed2=-5;}
    else{speed=+5;  }
  }*/
}
void niv2(){
  encoderValue2++;
  /*if(encoderValue2>encoderValue){
    if(speed2==150){speed=+5;}
    else{speed2=-5;}
  }
  if(encoderValue2<encoderValue){
    if(speed2==255){speed=-5;}
    else{speed2=+5;  }
  }*/
}

void avancer(){
  analogWrite(MOTOR1A,250);
  analogWrite(MOTOR2B,speed2);

  analogWrite(MOTOR1B,0);
  analogWrite(MOTOR2A,0);
}

void reculer(){
  analogWrite(MOTOR1A,0);
  analogWrite(MOTOR2B,0);

  analogWrite(MOTOR1B,speed);
  analogWrite(MOTOR2A,speed2);
}

void left(){
  analogWrite(MOTOR1A,speed);
  analogWrite(MOTOR2B,0);

  analogWrite(MOTOR1B,0);
  analogWrite(MOTOR2A,speed2);
}

void right(){
  analogWrite(MOTOR1A,0);
  analogWrite(MOTOR2B,speed2);

  analogWrite(MOTOR1B,speed);
  analogWrite(MOTOR2A,0);
}

void arret(){
  analogWrite(MOTOR1A,0);
  analogWrite(MOTOR2B,0);

  analogWrite(MOTOR1B,0);
  analogWrite(MOTOR2A,0);
}

void verification(){
  distance=mySensor.getDistance();
  Serial.print("la distance");
  Serial.println(distance);
  if(distance<12){arret();};  
}
