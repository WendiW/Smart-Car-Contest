
/*****************Smart Car Contest*******************************/
#include <Servo.h> 
int Leftspeed;
int Rightspeed;
int metal_flag1=0;
int metal_flag2=0;
int first=0;
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
 
float a[6]={};    
float distance; //CJ_data_b,CJ_data_c;    

int hw_L=1;
int hw_R=1;
 
int distance1=15;
int distance0=10;
int cishu=0;

#define IN1 9
#define IN2 8
#define IN3 12
#define IN4 13
#define EN1 5
#define EN2 11
        	 
#define Left_moto_go      {analogWrite(EN1,Leftspeed);digitalWrite(IN1, LOW);digitalWrite(IN2, HIGH);}
#define Left_moto_back    {analogWrite(EN1,Leftspeed);digitalWrite(IN2, LOW);digitalWrite(IN1, HIGH);} 	
#define Left_moto_Stop    {digitalWrite(IN1, HIGH);digitalWrite(IN2, HIGH);}   
    
#define Right_moto_back     {analogWrite(EN2,Rightspeed);digitalWrite(IN3, HIGH);digitalWrite(IN4,LOW);}	
#define Right_moto_go   {analogWrite(EN2,Rightspeed);digitalWrite(IN4, HIGH);digitalWrite(IN3,LOW);}
#define Right_moto_Stop   {digitalWrite(IN3, HIGH);digitalWrite(IN4, HIGH);}	
      
#define TrigPin  6
#define EchoPin  7
    
#define Ltrack 2
#define Rtrack 3
      
#define hongwai_left 4
#define hongwai_right 1
      
#define Metal 0
#define duoji 10
#define fengmingqi 16

void Stop(void){ 
  Right_moto_Stop;  
	Left_moto_Stop; 
  delay(300);
}

void run(void){        
  Rightspeed=60;
  Leftspeed=80;
	Left_moto_go;  
	Right_moto_go; 
}

void backrun(void){       
  Rightspeed=70;
  Leftspeed=70;
	Left_moto_back;   
	Right_moto_back; 
}

void leftrun(void){
  Rightspeed=70;
  Leftspeed=70;
  Right_moto_go;
  Left_moto_Stop;
}

void rightrun(void){
  Leftspeed=70;
  Rightspeed=70;
  Left_moto_go;
  Right_moto_Stop;
}

void xunji_leftrun(){
  Rightspeed=60;
  Right_moto_go;
  Left_moto_back;
}

void xunji_rightrun(){
  Leftspeed=60;
  Right_moto_Stop;
  Left_moto_go;
}

void turn_left(void){
  Rightspeed=70;
  Leftspeed=70;
  Right_moto_go;
  Left_moto_back;
  delay(300);
}

void turn_right(void){
  Leftspeed=70;
  Rightspeed=70;
  Right_moto_back;
  Left_moto_go;
  delay(300);
}

void disceret_run(){
  run();
  delay(200);
  Stop();
}
   
void slowrun(){
  Rightspeed=60;
  Leftspeed=60;
	Left_moto_go ;  
	Right_moto_go ; 
}

void xiao_leftrun(void){
  Rightspeed=70;
  Leftspeed=30;
  Right_moto_go;
  Left_moto_go;
}

void xiao_rightrun(void){
  Rightspeed=30;
  Leftspeed=70;
  Right_moto_go;
  Left_moto_go;
}

//Obstacle avoidance program
void read_csb(){  
  //generate a 10us high pulse to trigger TrigPin
  digitalWrite(TrigPin, LOW);    //pin 2 low
  delayMicroseconds(2);          //delay
  digitalWrite(TrigPin, HIGH);   //pin 3 high
  delayMicroseconds(10);          
  digitalWrite(TrigPin, LOW); 
  distance = pulseIn(EchoPin, HIGH) / 58.00;   //calulate the distance and store the result
  delay(10);
}

//Infrared photomultiplier tube program (for obstacle avoidance)
void hongwai_bizhang(){
  hw_L=digitalRead(hongwai_left);
  hw_R=digitalRead(hongwai_right);
}


void judge(){
  if(distance>distance1){
    if(hw_R==1&&hw_L==1){
      run();
    }
    if(hw_R==1&&hw_L==0){
      Stop();
      turn_right();
      Stop();
      delay(200);
    }
    if(hw_R==0&&hw_L==1){
      Stop();
      turn_left();
      Stop();
      delay(200);
      
    }
    if(hw_R==0&&hw_L==0){
      Stop();
      backrun();
      delay(300);
    }
  }
  else if(distance<distance1&&distance>distance0){
    if(hw_R==1&&hw_L==1){
         Stop();
         disceret_run();
         turn_left();      
    }
    if(hw_R==1&&hw_L==0){
      Stop();
      backrun();
      delay(300);
      Stop();
      turn_right();
      Stop();
      delay(200);
    }
    if(hw_R==0&&hw_L==1){
      Stop();
      backrun();
      delay(300);
      Stop();
      turn_left();
      Stop();
      delay(200);
    }
    if(hw_R==0&&hw_L==0){
      Stop();
      backrun();
      delay(300);
    }
  }
  else{
    Stop();
    backrun();
    delay(300);
    Stop();
  }
}

void track(){
  if(digitalRead(Ltrack)==0 && digitalRead(Rtrack)==1){
    xunji_rightrun();
  }	
  if(digitalRead(Rtrack)==0 && digitalRead(Ltrack)==1){	  
    xunji_leftrun();
  }  
  else{
    slowrun();
  }	
}
void metal_search(){
  if(digitalRead(Metal)==0){
    if(metal_flag1==1){
      metal_flag2=1;
    }
    else{
      metal_flag1=1;
      Stop();
      disceret_run();      
    }  
  }
}

void sweep(){
  //steering engine control program
  for(pos = 0; pos < 180; pos += 10)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=1; pos-=10)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
}

void qiqiu(){
  if(cishu<=3){
  if(metal_flag2==1){
    Stop();
    delay(200);
    delay(200);
    sweep();
    metal_flag2=0;
    cishu++;
  }
  }
  else{
    run();
    delay(300);
    Stop();
    cishu=0;
  }
}
void setup() {                
  //initialize the digital pin as an output.
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(Ltrack, INPUT);
  pinMode(Rtrack, INPUT);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(hongwai_left, INPUT);
  pinMode(hongwai_right, INPUT);
  pinMode(Metal, INPUT);
  pinMode(fengmingqi,OUTPUT);
  myservo.attach(duoji);  // attaches the servo on pin duoji to the servo object 
}


void loop(){
  if(first==0){
    delay(2000);
    first=1;
  }
  metal_search();
  if(metal_flag1==0){
    track();
  }
  else{
    read_csb();
    hongwai_bizhang();
    judge();
    qiqiu();
  }
}
