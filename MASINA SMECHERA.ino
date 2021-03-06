    
#include <Servo.h>        //add Servo Motor library            
#include <NewPing.h>      //add Ultrasonic sensor library

#define S_PIN1 9
#define S_PIN2 10
#define S_PIN3 11
#define swap(a,b) a ^= b; b ^= a; a ^= b;
#define sort(a,b) if(a>b){ swap(a,b); }

#define MAX_DISTANCE 2600 // sets maximum useable sensor measuring distance to 300cm // NU FOLOESC

#define COLL_DIST 25 // sets distance at which robot stops and reverses to 30cm

NewPing sonarF(S_PIN1, S_PIN1, MAX_DISTANCE); 
NewPing sonarR(S_PIN2, S_PIN2, MAX_DISTANCE); 
NewPing sonarL(S_PIN3, S_PIN3, MAX_DISTANCE); 

/// MOTOR A 
  const int motorA1  = 2;  
  const int motorA2  = 3;  

//// MOTOR B  
  const int motorB1  = 4; 
  const int motorB2  = 5;  

/// MOTOR C
  const int motorC1  = 6;  
  const int motorC2  = 7;  

//// MOTOR D  
  const int motorD1  = 8; 
  const int motorD2  = 12; 
  
Servo myservo;  

int leftDistance, rightDistance; //distances on either side
int curDist = 0;


//-------------------------------------------- SETUP LOOP ----------------------------------------------------------------------------
void setup() {
  myservo.attach(13);  
  myservo.write(90); // tells the servo to position at 90-degrees ie. facing forward.
  delay(1000); // delay for one seconds

    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);

    pinMode(motorC1, OUTPUT);
    pinMode(motorC2, OUTPUT);

    pinMode(motorD1, OUTPUT);
    pinMode(motorD2, OUTPUT);
    Serial.begin(9600);
   
 }
//------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------MAIN LOOP ------------------------------------------------------------------------------
void loop() {
  myservo.write(90);  // move eyes forward
  delay(90);
    
  curDist = readPing();   // read distance
    
  if (curDist < COLL_DIST) {changePath();}  // if forward is blocked change direction
    
  moveForward();  // move forward
 }
//-------------------------------------------------------------------------------------------------------------------------------------

void changePath() { 
  moveStop();   // 
  
  myservo.write(36);  // check distance to the right
    delay(200);
    rightDistance = sonarF.ping(); //set right distance
    delay(200);
    myservo.write(144);  // check distace to the left
    delay(200);
    leftDistance = sonarF.ping(); //set left distance
    moveBackward();
    myservo.write(90); //return to center
    compareDistance(); 
  }

  
void compareDistance()   // CAUTA CEA MAI LUNGA DISTANTA DE LA SENZOR
{
  if (leftDistance>rightDistance) // DACA E AI OK LEFT
  {
    turnLeft();
  }
  else if (rightDistance>leftDistance) // DACA E MAI OK RIGHT
  {
    turnRight();
  }
   else // DACA SUNT LA FEL DE FUCKED
  {
    turnAround();
  }
}

int median(int a, int b, int c, int d, int e)
{
    sort(a,b);
    sort(d,e);  
    sort(a,c);
    sort(b,c);
    sort(a,d);  
    sort(c,d);
    sort(b,e);
    sort(b,c);
    return c;
}

//-------------------------------------------------------------------------------------------------------------------------------------

int readPing() { // read the ultrasonic sensor distance
  delay(70);   
    unsigned int p1, p2,p3, uS,i=0,P1[5], P2[5], P3[5];

  for(i=0; i<5; i++)
  {
   delay(15);
   P1[i]= sonarF.ping();
   P2[i]= sonarL.ping();
   P3[i]= sonarR.ping();
  }
 
  p1 =  median(P1[0], P1[1], P1[2], P1[3], P1[4]);
  p1 =  median(P2[0], P2[1], P2[2], P2[3], P2[4]); 
  p1 =  median(P3[0], P3[1], P3[2], P3[3], P3[4]);
    
  // Serial.println(p3/US_ROUNDTRIP_CM);
   
   if ( p1 < p2 && p1 < p3) 
    uS=p1;
   else if ( p2 < p3 && p2 < p1)
    uS=p2;
   else if (p3 < p1 && p3 < p2)
    uS=p3;
    
  int cm = uS/US_ROUNDTRIP_CM;
  Serial.println(cm);
  return cm;
}
//-------------------------------------------------------------------------------------------------------------------------------------
void moveStop() {

  analogWrite(motorA1, 0); analogWrite(motorA2, 0);
  analogWrite(motorB1, 0); analogWrite(motorB2, 0); 
        
  analogWrite(motorC1, 0); analogWrite(motorC2, 0);
  analogWrite(motorD1, 0); analogWrite(motorD2, 0); 
}

//-------------------------------------------------------------------------------------------------------------------------------------
void moveForward() {

  analogWrite(motorA1, 0); analogWrite(motorA2, 255);
  analogWrite(motorB1, 0); analogWrite(motorB2, 255); 
        
  analogWrite(motorC1, 0); analogWrite(motorC2, 255);
  analogWrite(motorD1, 0); analogWrite(motorD2, 255);

}
//-------------------------------------------------------------------------------------------------------------------------------------
void moveBackward() { 

  analogWrite(motorA1, 255); analogWrite(motorA2, 0);
  analogWrite(motorB1, 255); analogWrite(motorB2, 0); 
        
  analogWrite(motorC1, 255); analogWrite(motorC2, 0);
  analogWrite(motorD1, 255); analogWrite(motorD2, 0); 
   delay(250);  
} 

//-------------------------------------------------------------------------------------------------------------------------------------
void turnRight() { 

  analogWrite(motorA1, 0); analogWrite(motorA2, 255);
  analogWrite(motorB1, 255); analogWrite(motorB2, 0); 
        
  analogWrite(motorC1, 0); analogWrite(motorC2, 255);
  analogWrite(motorD1, 255); analogWrite(motorD2, 0); 
  delay(1500);
}  

//-------------------------------------------------------------------------------------------------------------------------------------
void turnLeft() { 

  analogWrite(motorA1, 255); analogWrite(motorA2, 0);
  analogWrite(motorB1, 0); analogWrite(motorB2, 255); 
        
  analogWrite(motorC1, 255); analogWrite(motorC2, 0);
  analogWrite(motorD1, 0); analogWrite(motorD2, 255); 
  delay(1500); // run motors this way for 1500        
}  

//-------------------------------------------------------------------------------------------------------------------------------------
void turnAround() {

  analogWrite(motorA1, 0); analogWrite(motorA2, 255);
  analogWrite(motorB1, 255); analogWrite(motorB2, 0); 
        
  analogWrite(motorC1, 0); analogWrite(motorC2, 255);
  analogWrite(motorD1, 255); analogWrite(motorD2, 0); 
  delay(2500); // run motors this way for 1500        
}

