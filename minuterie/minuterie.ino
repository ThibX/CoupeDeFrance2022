#define go 2

int digit1=11;
int digit2=10;
int digit3=9;
int digit4=8;

int data=7;
int output=6;
int memo=5;

int trigger=0, cmp=0, centaine, dizaine, unite;

long previous,current,tmp,Init;

int tab1[8],tab2[8],tab3[8],tab4[8];

void setup() {

  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(go),lancer,RISING);

  pinMode(go,INPUT);
  
  pinMode(digit1,OUTPUT);
  pinMode(digit2,OUTPUT);
  pinMode(digit3,OUTPUT);
  pinMode(digit4,OUTPUT);

  pinMode(data,OUTPUT);
  pinMode(output,OUTPUT);
  pinMode(memo,OUTPUT);
  previous=millis();
}

void loop() {
  if(trigger==1){
    tmp=millis();
    if(tmp-Init>=1000){
      cmp++;
      Init=tmp;
    }
    decomposition(cmp);
    commande();
    if(cmp==100)trigger=0;
  }
  else{
    decomposition(cmp);
    commande();
  }
  
  
}

void lancer(){
  trigger=1;
  Init=millis();
}

void decomposition(int nombre){
  unite=nombre%10;
  nombre=nombre-unite;
  centaine=nombre/100;
  nombre%=100;
  dizaine=nombre/10;
}

void commande(){
  current=millis();

  //digit1  
  if(current-previous<5){
    digitalWrite(digit1,HIGH);
    digitalWrite(output,LOW);
    affiche(0,tab1);    //dans notre cas le digit1 sera toujours à 0
    for(int i=0;i<8;i++){
      digitalWrite(data,tab1[i]);
      digitalWrite(memo,HIGH);
      digitalWrite(memo,LOW);
    }
    digitalWrite(output,HIGH);
    digitalWrite(digit1,LOW);
  }
  
  //digit2
  if(current-previous>=5 && current-previous<10){
    digitalWrite(digit2,HIGH);
    digitalWrite(output,LOW);
    affiche(centaine,tab2);   //chiffre des centaine
    for(int i=0;i<8;i++){
      digitalWrite(data,tab2[i]);
      digitalWrite(memo,HIGH);
      digitalWrite(memo,LOW);
    }
    digitalWrite(output,HIGH);
    digitalWrite(digit2,LOW);
    
  }

  //digit3
  if(current-previous>=10 && current-previous<15){
    digitalWrite(digit3,HIGH);
    digitalWrite(output,LOW);
    affiche(dizaine,tab3);  //chiffre des dizaines
    for(int i=0;i<8;i++){
      digitalWrite(data,tab3[i]);
      digitalWrite(memo,HIGH);
      digitalWrite(memo,LOW);
    }
    digitalWrite(output,HIGH);
    digitalWrite(digit3,LOW);
    
  }

  //digit4
  if(current-previous>=15 && current-previous<20){
    digitalWrite(digit4,HIGH);
    digitalWrite(output,LOW);
    affiche(unite,tab4);  //chiffre des unités
    for(int i=0;i<8;i++){
      digitalWrite(data,tab4[i]);
      digitalWrite(memo,HIGH);
      digitalWrite(memo,LOW);
    }
    digitalWrite(output,HIGH);
    digitalWrite(digit4,LOW);
    
  }
  if(current-previous>=20){
      Serial.println(millis());
      Serial.println(millis());
      previous=millis();
  }
}

void affiche(int a, int* tab){
  //int tab[8];
  switch(a){
    case 0:tab[0]=0;//H
           tab[1]=0;//G
           tab[2]=255;//F
           tab[3]=255;//E
           tab[4]=255;//D
           tab[5]=255;//C
           tab[6]=255;//B
           tab[7]=255;//A
           break;
    case 1:tab[0]=0;
           tab[1]=0;
           tab[2]=0;
           tab[3]=0;
           tab[4]=0;
           tab[5]=255;
           tab[6]=255;
           tab[7]=0;
           break;
     case 2:tab[0]=0;
           tab[1]=1;
           tab[2]=0;
           tab[3]=1;
           tab[4]=1;
           tab[5]=0;
           tab[6]=1;
           tab[7]=1;
           break;
     case 3:tab[0]=0;
           tab[1]=1;
           tab[2]=0;
           tab[3]=0;
           tab[4]=1;
           tab[5]=1;
           tab[6]=1;
           tab[7]=1;
           break;
     case 4:tab[0]=0;//H
           tab[1]=1;//G
           tab[2]=1;//F
           tab[3]=0;//E
           tab[4]=0;//D
           tab[5]=1;//C
           tab[6]=1;//B
           tab[7]=0;//A
           break;
     case 5:tab[0]=0;//H
           tab[1]=1;//G
           tab[2]=1;//F
           tab[3]=0;//E
           tab[4]=1;//D
           tab[5]=1;//C
           tab[6]=0;//B
           tab[7]=1;//A
           break;
     case 6:tab[0]=0;//H
           tab[1]=1;//G
           tab[2]=1;//F
           tab[3]=1;//E
           tab[4]=1;//D
           tab[5]=1;//C
           tab[6]=0;//B
           tab[7]=1;//A
           break;
     case 7:tab[0]=0;//H
           tab[1]=0;//G
           tab[2]=0;//F
           tab[3]=0;//E
           tab[4]=0;//D
           tab[5]=1;//C
           tab[6]=1;//B
           tab[7]=1;//A
           break;
     case 8:tab[0]=0;//H
           tab[1]=1;//G
           tab[2]=1;//F
           tab[3]=1;//E
           tab[4]=1;//D
           tab[5]=1;//C
           tab[6]=1;//B
           tab[7]=1;//A
           break;
     case 9:tab[0]=0;//H
           tab[1]=1;//G
           tab[2]=1;//F
           tab[3]=0;//E
           tab[4]=1;//D
           tab[5]=1;//C
           tab[6]=1;//B
           tab[7]=1;//A
           break;
     default:for(int i=0; i<8;i++){
                tab[i]=1;
                break;
     }
     
    }

}
