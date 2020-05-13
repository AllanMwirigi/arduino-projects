#include <Servo.h> 
 
Servo elbowServo;  // create servo object to control a servo 
 Servo baseServo;              // twelve servo objects can be created on most boards
  Servo gripperServo; 
  
int pos = 0;    // variables to store the servo position 
int pos1 = 0;    
 int pos2 = 0; 
 

int leftmotor_A=28;
int leftmotor_B=26;
int leftmotor_pwm=2;

int rightmotor_A=22;
int rightmotor_B=24;
int rightmotor_pwm=3;


//connect pins of sensers to the microcontroler
int outer_Left = 42;
int MIDleft_sens=40;
int centr_sens=38;
int MIDright_sens=36;
int outer_Right = 34;

int arm_A=23;
int arm_B=25;
int arm_PWM=7;

int gripper_A = 29;
int gripper_B = 27;
int gripper_PWM = 6;

int arm_LimitSwitch = 52;
int gripper_openswitch = 53;




//digitalpins for counting sensors
int Backright_sens=48;
int Backleft_sens=46;

//variable to store conditions of sensors
int outer_leftsensstate;
int Midleftstate;
int centrState;
int Midrightstate;
int leftsensstate;
int rightsensstate;
int outer_rightsensstate;

int Backrightsensstate;
int Backleftsensstate;

int limitSwitch_state;
int gripperopen_state;


int counter=0;
int currentState=1;
int previousState=1;

int white_junctions;

int forward_speed = 180;
 

 void setup() {
  //figuring out whether output from h_bridge to motors
  
  pinMode(leftmotor_A,OUTPUT);
  pinMode(leftmotor_B,OUTPUT);
  pinMode(leftmotor_pwm,OUTPUT);
  pinMode(rightmotor_A,OUTPUT);
  pinMode(rightmotor_B,OUTPUT);
  pinMode(rightmotor_pwm,OUTPUT);
  
//input from microcontroler to the sensers
//senser midright/midleft used for counting whitelines
  pinMode(outer_Left,INPUT);
  //pinMode(left_sens,INPUT);
  pinMode(MIDleft_sens,INPUT);
  pinMode(centr_sens,INPUT);
  pinMode(MIDright_sens,INPUT);
  //pinMode(right_sens,INPUT);
  pinMode(outer_Right,INPUT);

elbowServo.attach(9);  // attaches the servo on pin 9 to the servo object 
baseServo.attach(8);
gripperServo.attach(10);

// declare the starting angles
 elbowServo.write(90); 
 baseServo.write(90); 
 gripperServo.write(70);
  }

void stop_robot()

{
 digitalWrite(leftmotor_A,HIGH);
 digitalWrite(leftmotor_B,HIGH);
 analogWrite(leftmotor_pwm,100);
 digitalWrite(rightmotor_A,HIGH);
 digitalWrite(rightmotor_B,HIGH);
 analogWrite(rightmotor_pwm,100);
}

void forward_short()
{
 digitalWrite(leftmotor_A,LOW);
 digitalWrite(leftmotor_B,HIGH);
 analogWrite(leftmotor_pwm,180);
 digitalWrite(rightmotor_A,LOW);
 digitalWrite(rightmotor_B,HIGH);
 analogWrite(rightmotor_pwm,180);
}

void checkAll_sensors()
{
  outer_leftsensstate=digitalRead(outer_Left);
  Midleftstate=digitalRead(MIDleft_sens);
  centrState=digitalRead(centr_sens);
  Midrightstate=digitalRead(MIDright_sens);
  outer_rightsensstate=digitalRead(outer_Right);
}



// this subroutine uses all four tacking sensors to track on the white line
void navigate()//move forward while following the white line
{
  //start by checking the state of all tracking sensors
  checkAll_sensors();
//make decisions depending on the state of each sensor
if(
   outer_leftsensstate == LOW &&  Midleftstate == LOW == Midrightstate == LOW && outer_rightsensstate == HIGH)    // extremely lost to the left
{
 digitalWrite(leftmotor_A,LOW);
 digitalWrite(leftmotor_B, HIGH);
 analogWrite(leftmotor_pwm,255);
 digitalWrite(rightmotor_A,HIGH);
 digitalWrite(rightmotor_B,HIGH);
 analogWrite(rightmotor_pwm,0);
}
else
if( outer_leftsensstate == LOW &&  Midleftstate == LOW && Midrightstate == HIGH && outer_rightsensstate == HIGH) // slightly lost to the left
{
 digitalWrite(leftmotor_A,  LOW);
 digitalWrite(leftmotor_B, HIGH);
 analogWrite(leftmotor_pwm,forward_speed + 70);
 digitalWrite(rightmotor_A,LOW);
 digitalWrite(rightmotor_B,HIGH);
 analogWrite(rightmotor_pwm,forward_speed - 70);
}
else
if( outer_leftsensstate == LOW &&  Midleftstate == LOW && Midrightstate == HIGH && outer_rightsensstate == LOW) // lost to the left
{
 digitalWrite(leftmotor_A,  LOW);
 digitalWrite(leftmotor_B, HIGH);
 analogWrite(leftmotor_pwm,forward_speed + 50);
 digitalWrite(rightmotor_A,LOW);
 digitalWrite(rightmotor_B,HIGH);
 analogWrite(rightmotor_pwm,forward_speed - 50);
}

else
if( outer_leftsensstate == LOW &&  Midleftstate ==HIGH && Midrightstate == LOW  && rightsensstate == LOW) // lost to the right
{
 digitalWrite(leftmotor_A,LOW);
 digitalWrite(leftmotor_B, HIGH);
 analogWrite(leftmotor_pwm,forward_speed - 50);
 digitalWrite(rightmotor_A,LOW);
 digitalWrite(rightmotor_B,HIGH);
 analogWrite(rightmotor_pwm,forward_speed + 50);
}

else
if( outer_leftsensstate == HIGH &&  Midleftstate ==HIGH && Midrightstate == LOW  && rightsensstate == LOW) // slightly lost to the right
{
 digitalWrite(leftmotor_A,LOW);
 digitalWrite(leftmotor_B, HIGH);
 analogWrite(leftmotor_pwm,forward_speed - 70);
 digitalWrite(rightmotor_A,LOW);
 digitalWrite(rightmotor_B,HIGH);
 analogWrite(rightmotor_pwm,forward_speed + 70);
}

else
if( outer_leftsensstate == HIGH &&  Midleftstate == LOW && Midrightstate == LOW && outer_rightsensstate == LOW )    // extremely lost to the right
{
 digitalWrite(leftmotor_A,HIGH);
 digitalWrite(leftmotor_B, HIGH);
 analogWrite(leftmotor_pwm,0);
 digitalWrite(rightmotor_A,LOW);
 digitalWrite(rightmotor_B,HIGH);
 analogWrite(rightmotor_pwm,255);
}

else    // any other state, the robot should continue moving straight forward
{
 digitalWrite(leftmotor_A,LOW);
 digitalWrite(leftmotor_B, HIGH);
 analogWrite(leftmotor_pwm,forward_speed);
 digitalWrite(rightmotor_A,LOW);
 digitalWrite(rightmotor_B,HIGH);
 analogWrite(rightmotor_pwm,forward_speed);
}
}



//count the number of white lines or junctions as it moves forward
void countwhitelines()
{     checkAll_sensors();
      if(outer_leftsensstate == LOW && outer_rightsensstate == LOW)
       {currentState = LOW;
         }
          else
      if(outer_leftsensstate == HIGH && outer_rightsensstate == HIGH) 
         {currentState = HIGH;
          }
     if(currentState!=previousState)    
     {
      if(currentState==HIGH)
       {counter +=1;  
       } 
   }
   previousState=currentState;
   }
    

void movecounting()
{counter = 0;
  countwhitelines();
   while (counter !=  white_junctions)
   {
    navigate();
     countwhitelines();
     if (counter ==white_junctions)
      {
        stop_robot();
        delay(200);
        break;
     }
    }
  }
//TURNING THE ROBOT RIGHT
void right_Uturn()
{digitalWrite(leftmotor_A,LOW);
 digitalWrite(leftmotor_B,HIGH);
 analogWrite(leftmotor_pwm,200);
 digitalWrite(rightmotor_A,HIGH);
 digitalWrite(rightmotor_B,LOW);
 analogWrite(rightmotor_pwm,150);
}

//make the robot turn while searching for the white line at 90 degrees
 void right_turn90()
  {
   right_Uturn();
   delay(300);
   checkAll_sensors();
  while ((centrState &&  MIDright_sens)== LOW)
  {right_Uturn();
  checkAll_sensors();
  if ((centrState &&  MIDright_sens)== HIGH){
       stop_robot();
        delay(200);
        break;
     }
    }
  }






//TURNING THE ROBOT LEFT
void left_Uturn()
{digitalWrite(leftmotor_A,HIGH);
 digitalWrite(leftmotor_B,LOW);
 analogWrite(leftmotor_pwm,150);
 digitalWrite(rightmotor_A,LOW);
 digitalWrite(rightmotor_B,HIGH);
 analogWrite(rightmotor_pwm,200);
}

void turnLeft_OneWheel()
{
digitalWrite(leftmotor_A,HIGH);
 digitalWrite(leftmotor_B,LOW);
 analogWrite(leftmotor_pwm,170);
 digitalWrite(rightmotor_A,HIGH);
 digitalWrite(rightmotor_B,HIGH);
 analogWrite(rightmotor_pwm,60);
}


//make the robot turn left while searching for the white line at 90 degrees
 void left_turn90()
  {left_Uturn();
   delay(300);
   checkAll_sensors();
  while ((centrState && Midleftstate)== LOW)
  {left_Uturn();
 checkAll_sensors();
  if ((centrState && Midleftstate)== HIGH){
       stop_robot();
        delay(200);
        break;
     }
    }
  }


// align robot perfect on the track after making a 90 degrees turn on the left
void align_lefttrack()
{ checkAll_sensors();
  while (Midrightstate== LOW)
  {turnLeft_OneWheel();
   checkAll_sensors();
  if ( Midrightstate == HIGH){
       stop_robot();
        delay(200);
        break;
     }
    }
  }


//MAKE THE MOTORS MOVE UNCONDITIONALLY
void reverse_motors()
{
digitalWrite(leftmotor_A,HIGH);
 digitalWrite(leftmotor_B,LOW);
 analogWrite(leftmotor_pwm,180);
 digitalWrite(rightmotor_A,HIGH);
 digitalWrite(rightmotor_B,LOW);
 analogWrite(rightmotor_pwm,180);
}



void baseLeft(int base_angle,  int baseup_angle)
  {
     for(pos1 = base_angle; pos1 <= baseup_angle; pos1 += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    baseServo.write(pos1);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
      }
    }
    
 void baseRight( int baselast_angle, int basedown_angle)
  {
    for(pos1 = baselast_angle; pos1>=basedown_angle; pos1-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    baseServo.write(pos1);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
    }
  }

void elbowUp(int elblast_angle,  int up_angle)
  {
     for(pos = elblast_angle; pos <= up_angle; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    elbowServo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
      }
    }
    
 void elbowDown( int last_angle, int down_angle)
  {
    for(pos = last_angle; pos>=down_angle; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    elbowServo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
    }
  }

void openGripper(int close_angle,  int open_angle)
  {
     for(pos2 = close_angle; pos2 <= open_angle; pos2 += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    gripperServo.write(pos2);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
      }
    }
    
 void closeGripper( int lastopen_angle, int newclose_angle)
  {
    for(pos2 = lastopen_angle; pos2>=newclose_angle; pos2-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    gripperServo.write(pos2);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
    }
  }


void loop ()

{
navigate();




 /* 
 white_junctions = 4; 
movecounting();
stop_robot();
forward_short();
 delay(100);
 stop_robot();
right_turn90();

 white_junctions = 11; 
movecounting();
stop_robot();
forward_short();
 delay(100);
 stop_robot();
right_turn90();

white_junctions = 4; 
movecounting();
stop_robot();
forward_short();
 delay(100);
 stop_robot();
left_turn90();

white_junctions = 5;  // move to the blue position
movecounting();
stop_robot();
forward_short();
 delay(100);
 stop_robot();
 delay(2);


baseRight(90,  0);//pick the blue ballot
elbowDown(90, 5);
closeGripper(70, 5);
elbowUp(5, 90);
baseLeft(0, 80);
elbowUp(90, 175);
openGripper(5, 70);


white_junctions = 1; // move to the yellow position
movecounting();
stop_robot();
forward_short();
 delay(100);
 stop_robot();
 delay(20);

elbowDown(175, 90);//pick the yellow ballot
baseRight(90,  0);
elbowDown(90, 5);
closeGripper(70, 5);
elbowUp(5, 90);
baseLeft(0, 140);
elbowUp(90, 175);
openGripper(5, 70);
 

 white_junctions = 1; //move to the red position
movecounting();
stop_robot();
forward_short();
 delay(100);
 stop_robot();
 delay(20);

elbowDown(175, 90);//pick the red ballot
baseRight(140,  0);
elbowDown(90, 5);
closeGripper(70, 5);
elbowUp(5, 90);
baseLeft(0, 130);

 

 left_turn90();

white_junctions = 7; 
movecounting();
stop_robot();
forward_short();
 delay(100);
 stop_robot();
left_turn90();

white_junctions = 6; 
movecounting();
stop_robot();
forward_short();
 delay(100);
 stop_robot();
right_turn90();
 stop_robot();


white_junctions = 1; 
movecounting();
stop_robot();
forward_short();
 delay(100);
 stop_robot();
left_turn90();

white_junctions =12; 
movecounting();
stop_robot();
reverse_motors();
delay(250);
stop_robot();

elbowDown(90, 20);//drop the red ballot
openGripper(5, 70);


elbowUp(20, 180);//pick and drop yellow ballot
closeGripper(70, 5);
elbowDown(180, 90);
baseRight(130,  98);
elbowDown(90, 20);
openGripper(5, 70);

baseRight(98,  75); //pick and drop blue ballot
elbowUp(20, 180);
closeGripper(70, 5);
elbowDown(180, 20);
baseRight(75,  62);
openGripper(5, 70);

reverse_motors();
delay(100);
left_turn90();
left_turn90();



forward_speed = 80;  //lower the speed to go down the ramp
white_junctions = 6; 
movecounting();
stop_robot();
forward_short();
 delay(100);
 stop_robot();
right_turn90();


forward_speed = 180; //increase the after going down the ramp heading to the parking
 white_junctions = 8; 
movecounting();
stop_robot();
forward_short();
 delay(100);
 stop_robot();
right_turn90();

 white_junctions = 6; 
movecounting();
stop_robot();
forward_short();
 delay(1000);
 
stop_robot();
delay(25000000000);  // park the robot at the starting zone after completing voting
*/
  }
  
