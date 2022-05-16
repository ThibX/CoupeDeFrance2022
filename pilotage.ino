#include<SharpIR.h>;
#include<PID_v2.h>;

#define trigger 24
#define demarrage 48

byte pinSensor=18;  //Avant
byte pinSensor2=19;  //Arrière
SharpIR mySensorAv1(SharpIR::GP2Y0A21YK0F,A0);
SharpIR mySensorAv2(SharpIR::GP2Y0A21YK0F,A1);
SharpIR mySensorAr(SharpIR::GP2Y0A21YK0F,A2);
unsigned int distanceAr=0, distanceAv1=0, distanceAv2=0;

const int HALLSEN_A = 2; // Hall sensor A connected to pin 3 (external interrupt)
const int HALLSEN_B=4;// jaune_1
const int MOTOR1A = 8; //en1
const int MOTOR1B = 9;  //en2
const int ENA=24;

const int HALLSEN_2A = 3; // Hall sensor A connected to pin 3 (external interrupt)
const int HALLSEN_2B=7;// jaune_2
const int MOTOR2A = 10;  //en3
const int MOTOR2B = 11;  //en4
const int ENB=25;

//The sample code for driving one way motor encoder
volatile long encoderValueA = 0, encoderValueB=0;
volatile long encoderValue2A = 0, encoderValue2B;

long rpm = 0;
byte speed=40, speed2=40;

int sens=-1;
long previousMillis;
int tour; //=180;  //1500 maximum
int tmp=50;

// Asservissement
  double SetPoints, input, output;

PID myPID(&input,&output,&SetPoints,2,5,1,DIRECT);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(HALLSEN_A), niv1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(HALLSEN_2A), niv2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinSensor),verification,HIGH);
  attachInterrupt(digitalPinToInterrupt(pinSensor2),verification2,HIGH);

   pinMode( MOTOR1A , OUTPUT);
   pinMode( MOTOR1B , OUTPUT);
   pinMode( MOTOR2A , OUTPUT);
   pinMode( MOTOR2B , OUTPUT);

   pinMode(HALLSEN_A,INPUT);
   pinMode(HALLSEN_B,INPUT);
   pinMode(HALLSEN_2A,INPUT);
   pinMode(HALLSEN_2B,INPUT);
   
   pinMode(ENB,OUTPUT);
   digitalWrite(ENB,HIGH);
   pinMode(ENA,OUTPUT);
   digitalWrite(ENA,HIGH);

   pinMode(trigger, INPUT_PULLUP);
   pinMode(demarrage,INPUT);
   
   previousMillis=millis();

}

void loop() {
  /*if(digitalRead(demarrage)==HIGH){
    Serial.println("GOOOOOO");
  }
  else{
    Serial.println("NONNNNNNN");
  }*/

  /*distanceAv2=mySensorAv2.getDistance();
  Serial.print("la distanceAv2 ");
  Serial.println(distanceAv2);*/
  
  /*while(Serial.available()>0){
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
  }*/

  /*
  if(digitalRead(trigger)==LOW){
    Serial.println("err");
    //essaie();
    //reglage_vitesse(150);
  }
   else{
    
    Serial.println(digitalRead(trigger));
    //arret();
   }*/
   //delay(3000);
 essaie();
//avancer();
//reglage_vitesse(150);
   
   //if(rpm>=3200){   //IL FAUT 3200 IMPULSIONS POUR UN TOUR DE ROUES
     // while(true){arret();}
   //}
}

void essaie(){
  if(rpm<=32000){
    avancer();
    reglage_vitesse(180);    
    //Serial.println(rpm);
  }
  if(rpm>32000 && rpm<=64000){
    right();
    reglage_vitesse(80); 
  }
  if(rpm>64000 && rpm<=96000){
    reculer();
    reglage_vitesse(180);
    Serial.print("je suis à ");
    Serial.println(rpm);   
  }
  if(rpm>96000 && rpm<=128000){
    left();
    reglage_vitesse(40);  
  }
  if(rpm>128000){
    arret(); 
    Serial.print("je suis dans le dernier cas ");
    Serial.println(rpm);
  }
}

void niv1(){
  int a=digitalRead(HALLSEN_A);
  int b=digitalRead(HALLSEN_B);
  if(a!=b){
    encoderValueA++;
  }
  else{
    encoderValueB++;  
  }
  rpm=rpm+1;
}
void niv2(){
  int a=digitalRead(HALLSEN_2A);
  int b=digitalRead(HALLSEN_2B);
  //Serial.println("aze");
  if(a!=b){
    encoderValue2B++;
  }
  else{
    encoderValue2A++;  
  }
}

void avancer(){
  analogWrite(MOTOR1B,speed);
  analogWrite(MOTOR2B,speed2);

  analogWrite(MOTOR2A,0);
  analogWrite(MOTOR1A,0);
  sens=0;
}

void reculer(){
  analogWrite(MOTOR1B,0);
  analogWrite(MOTOR2B,0);

  analogWrite(MOTOR1A,speed);
  analogWrite(MOTOR2A,speed2);
  sens=1;
}

void left(){
  //speed=100;
  //speed2=105;
  analogWrite(MOTOR1B,speed);
  analogWrite(MOTOR2B,0);

  analogWrite(MOTOR1A,0);
  analogWrite(MOTOR2A,speed2);
  sens=2;
}

void right(){
  //speed=100;
  //speed2=105;
  analogWrite(MOTOR1B,0);
  analogWrite(MOTOR2B,speed2);

  analogWrite(MOTOR1A,speed);
  analogWrite(MOTOR2A,0);
  sens=3;
}

void arret(){
  speed=10;
  speed2=10;
  analogWrite(MOTOR1A,speed);
  analogWrite(MOTOR2B,speed2);

  analogWrite(MOTOR1B,speed);
  analogWrite(MOTOR2A,speed2);
  sens=-1;
}

void verification(){
  distanceAv1=mySensorAv1.getDistance();
  Serial.print("la distanceAv1 ");
  Serial.println(distanceAv1);

  distanceAv2=mySensorAv2.getDistance();
  Serial.print("la distanceAv2 ");
  Serial.println(distanceAv2);

  
  //if(distance<12){arret();delay(500);}  
}

void verification2(){
  distanceAr=mySensorAr.getDistance();
  Serial.print("la distanceAr ");
  Serial.println(distanceAr);
  //if(distance<12){arret();delay(500);}  
}

void reglage_vitesse(int vtse){
  tour=vtse;
  long currentMillis=millis();
  //Arrière
  if(sens==1){
    if(currentMillis-previousMillis>=tmp){
      if(encoderValue2B>tour){
        speed2=speed2-5;  
      }
      else if(encoderValue2B<tour-10){speed2=speed2+5;}
      Serial.print("outB=");
      Serial.println(speed2);
      Serial.println(encoderValue2B);
      encoderValue2B=0;
  
      if(encoderValueB>tour){
        speed=speed-5;  
      }
      else if(encoderValueB<tour-10){speed=speed+5;}
      Serial.print("outA=");
      Serial.println(speed);
      Serial.println(encoderValueB);
      encoderValueB=0;
      
      previousMillis=currentMillis;
     }
  }

  //Avant
  if(sens==0){
    if(currentMillis-previousMillis>=tmp){
      if(encoderValue2A>tour){
        speed2=speed2-5;  
      }
      else if(encoderValue2A<tour-10){speed2=speed2+5;}
      Serial.print("outB=");
      Serial.println(speed2);
      Serial.println(encoderValue2A);
      encoderValue2A=0;
  
      if(encoderValueA>tour){
        speed=speed-5;  
      }
      else if(encoderValueA<tour-10){speed=speed+5;}
      Serial.print("outA=");
      Serial.println(speed);
      Serial.println(encoderValueA);
      encoderValueA=0;
      
      previousMillis=currentMillis;
     }
  }
  //Left
  if(sens==2){
    if(currentMillis-previousMillis>=tmp){
      if(encoderValue2B>tour){
        speed2=speed2-5;  
      }
      else if(encoderValue2B<tour-10){speed2=speed2+5;}
      Serial.print("outB=");
      Serial.println(speed2);
      Serial.println(encoderValue2B);
      encoderValue2B=0;
  
      if(encoderValueA>tour){
        speed=speed-5;  
      }
      else if(encoderValueA<tour-10){speed=speed+5;}
      Serial.print("outA=");
      Serial.println(speed);
      Serial.println(encoderValueA);
      encoderValueA=0;
      
      previousMillis=currentMillis;
     }
  }

  //right
  if(sens==3){
    if(currentMillis-previousMillis>=tmp){
      if(encoderValue2A>tour){
        speed2=speed2-5;  
      }
      else if(encoderValue2A<tour-10){speed2=speed2+5;}
      Serial.print("outB=");
      Serial.println(speed2);
      Serial.println(encoderValue2A);
      encoderValue2A=0;
  
      if(encoderValueB>tour){
        speed=speed-5;  
      }
      else if(encoderValueB<tour-10){speed=speed+5;}
      Serial.print("outA=");
      Serial.println(speed);
      Serial.println(encoderValueB);
      encoderValueB=0;
      
      previousMillis=currentMillis;
     }
  }
  
}
