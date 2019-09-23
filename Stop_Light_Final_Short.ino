#include <Servo.h>              //includes servo functions' library

int NSRed=13;                 //assigns NS hardware
int NSYellow=12;
int NSGreen=11;
int NSTurn=10;
int NSSensor=9;

int angle=0;                  //assigns cross bar hardware
Servo cBar;
int cLight=7;
int cBuzzer=A5;

int EWRed=6;                  //assigns EW hardware
int EWYellow=5;
int EWGreen=4;
int EWTurn=3;
int EWSensor=2;

void setup() {
  pinMode(NSRed, OUTPUT);    
  pinMode(NSYellow, OUTPUT);    
  pinMode(NSGreen, OUTPUT);    
  pinMode(NSTurn, OUTPUT);
  pinMode(NSSensor, INPUT);

  cBar.attach(8);
  cBar.write(0);
  pinMode(cLight, OUTPUT);
  pinMode(cBuzzer, OUTPUT);
  noTone(cBuzzer);

  pinMode(EWRed, OUTPUT);     
  pinMode(EWYellow, OUTPUT);  
  pinMode(EWGreen, OUTPUT);   
  pinMode(EWTurn, OUTPUT);    
  pinMode(EWSensor, INPUT);   
}

/*------------------------------------------------------------------------------------------------------------------------------------*/
//north-south left turn subfunction

  void NSLeftTurn(){                        
    digitalWrite(NSTurn, HIGH);    
    delay(6000);
    digitalWrite(NSTurn, LOW);
    delay(1500);
  }
/*------------------------------------------------------------------------------------------------------------------------------------*/
//east-west left turn subfunction

  void EWLeftTurn(){                        
    digitalWrite(EWTurn, HIGH);    
    delay(6000);
    digitalWrite(EWTurn, LOW);
    delay(1500);
  }
/*------------------------------------------------------------------------------------------------------------------------------------*/
//warning for cross bar down

  void cBarWarning(){                       
    digitalWrite(cLight, HIGH);                         //cross light flashes and buzzer sounds
    tone(cBuzzer, 330);                                 //330 Hz = frequency for e
    delay(1000);                  
    digitalWrite(cLight, LOW);
    noTone(cBuzzer);
    delay(1000);  
    digitalWrite(cLight, HIGH);
    tone(cBuzzer, 330);
    delay(1000);                  
    digitalWrite(cLight, LOW);
    noTone(cBuzzer);
    delay(1000);
    digitalWrite(cLight, HIGH);
    tone(cBuzzer, 330);
    delay(1000);
  }
/*------------------------------------------------------------------------------------------------------------------------------------*/
//cross bar up subfuncion

  void cBarUp(){                          
    tone(cBuzzer, 330);
    for(angle=0; angle<90; angle+=1){                 //cross bar up, cross light off
    cBar.write(angle);             
    delay(30);                          //should take ~ 2.7 seconds to go up
    }
    noTone(cBuzzer);
    digitalWrite(cLight, LOW);  
  }
/*------------------------------------------------------------------------------------------------------------------------------------*/
//cross bar down subfunction

  void cBarDown(){        
    for(angle=90; angle>=0; angle-=1){                //cross bar down
    cBar.write(angle);             
    delay(30);                          //should take ~ 2.7 seconds to go down
    }
    noTone(cBuzzer);
  }
  
/*------------------------------------------------------------------------------------------------------------------------------------*/
//loop function

void loop() {
    digitalWrite(cLight, HIGH);                     //cross light & both reds on
    digitalWrite(EWRed, HIGH);   
    digitalWrite(NSRed, HIGH);  
    
  cBarUp();
  
    digitalWrite(NSRed, LOW);                       //NS red off, green on 10 sec, yellow on 5 sec, red on
    digitalWrite(NSGreen, HIGH);   
    delay(10000);                  
    digitalWrite(NSGreen, LOW);    
    digitalWrite(NSYellow, HIGH);   
    
  cBarWarning();  
    
    digitalWrite(NSYellow, LOW);    
    digitalWrite(NSRed, HIGH);   
  
    delay(1500);

  cBarDown();
  
  if(digitalRead(NSSensor) == HIGH){                //check NS sensor, NSLeftTurn subfunction
    NSLeftTurn();
    }
  else if(digitalRead(NSSensor) == LOW){ 
    digitalWrite(NSTurn, LOW);
    delay(1500);
  }
  
  cBarUp(); 
    
    digitalWrite(EWRed, LOW);                       //EW red off, green on 10 sec, yellow on 5 sec, red on
    digitalWrite(EWGreen, HIGH);    
    delay(10000);                 
    digitalWrite(EWGreen, LOW);     
    digitalWrite(EWYellow, HIGH);    
    
  cBarWarning();
    
    digitalWrite(EWYellow, LOW);     
    digitalWrite(EWRed, HIGH);    
  
    delay(1500);
  
  cBarDown();
  
  if(digitalRead(EWSensor) == HIGH){              //check EW sensor, if needed light on 4 sec
    EWLeftTurn();
  }
  else if(digitalRead(EWSensor) == LOW){
    digitalWrite(EWTurn, LOW);
    delay(1500);
  } 
}
