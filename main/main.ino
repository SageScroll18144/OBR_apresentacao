 
#include <Servo.h>

Servo garra;  

#define IR_F A3
//MOTORES
const int dir[] = {51,53,45,43,41,39,47,49};//pinos de direção dos motores
const int motores[] = {A1,A2,A6,A7};
//ULTRASSONICO
//int trig = 5;
//int echo = 6;
const int ultPin[] = {5,34,0,6,36,0};//trig;trig;trig;echo;echo;echo

//RGB
//s0; s1; s2; s3; out -> Pino digital || gnd -> gnd || vcc -> 5v
const int rgbs[] = {2,3,26,24,28,8,9,11,12,10}; //s0 s1 s2 s3 out 

const int irs[] = {A8,A9,A10,A11,A12,A13,A14,A15};

int red = 0;
int green = 0;
int blue = 0;

int red1 = 0;
int green1 = 0;
int blue1 = 0;
/*
 M0  ####  M3.
    ######       -> chassi do robô
    ######       -> M(motor)[número do motor]
 M1  ####  M2
*/
//CONSTANTES
#define RB 600 // Valor lido pelo sensor analógico

void setup(){
  garra.attach(30);
  for(int i = 0; i < sizeof(irs)/sizeof(int); i++){
      pinMode(irs[i], INPUT);
  }
  for(int i = 0; i < sizeof(motores)/sizeof(int); i++){
      analogWrite(motores[i], 1023);
  }
  for(int i = 0; i < sizeof(dir)/sizeof(int); i++){
      pinMode(dir[i], OUTPUT);
  }
  Serial.begin(2000000);
 
  for(int i = 0; i < sizeof(ultPin)/sizeof(int); i++){
      if (i > 2)
        pinMode(ultPin[i], INPUT);
      else
        pinMode(ultPin[i], OUTPUT);
  }
  
}

void loop(){

  if(readRGBRight()==3&&readRGBLeft()==3){
     while(true){
      if(Serial.available() > 0){
        auto input = Serial.readString();
        if(input == "G"){//get ball
          resgate();
          here();
        }else if(input == "F"){//giro
          forward();
        }else if(input == "B"){//giro
          backward();
        }else if(input == "SL"){//giro
          spinRobot('L');
        }else if(input == "SR"){//giro
          spinRobot('R');
        }else if(input == "L"){//esquerda
          go_left();
        }else if(input == "R"){//direita
          go_right();
        }
        
      }
     }
  }else{
    if(ultrassonicRead(0) < 2){
      desvio();
    }else if(readRGBRight()==2&&readRGBLeft()==2){
      giro180('R');
    }else if(readRGBRight()==2&&readRGBLeft()!=2){
      
    }else if(readRGBRight()!=2&&readRGBLeft()==2){
      
    }else{
      PID(5);
    }
   }
  
  Serial.println(ultrassonicRead(0));
}
