int leftmotor_A=13;
int leftmotor_B=12;
int leftmotor_pwm=11;
int rightmotor_A=8;
int rightmotor_B=7;
int rightmotor_pwm=10;
int left_sens=A0;
int centr_sens=A1;
int right_sens=A2;
int obstacle_sens=A3;
int gripper_A=5;
int gripper_B=4;
int gripper_pwm=9;
int gipperOpen_sens=A4;
int arm_A=3;
int arm_B=2;
int arm_pwm=6;
int armlower_sens=A5;
int state1;
int state2;
int obstacle;
int obstacleState;
int sensStateL;
int sensStateC;
int sensStateR;
int gripper_openLimit;
int arm_lowerLimit;
int objects=0;
//Varibles for all the speed constants are defined here
int max_speed=240;
int valx,valy,val, val2;
int val1=max_speed;

void setup()
//Declare the pins as either inputs or outputs.
{pinMode(leftmotor_A,OUTPUT);
 pinMode(leftmotor_B,OUTPUT);
 pinMode(leftmotor_pwm,OUTPUT);
 pinMode(rightmotor_A,OUTPUT);
 pinMode(rightmotor_B,OUTPUT);
 pinMode(rightmotor_pwm,OUTPUT);
 pinMode(left_sens,INPUT);
 pinMode(centr_sens,INPUT);
 pinMode(right_sens,INPUT);
 pinMode(gripper_A,OUTPUT);
 pinMode(gripper_B,OUTPUT);
 pinMode(gripper_pwm,OUTPUT);
 pinMode(gipperOpen_sens,INPUT);
 pinMode(arm_A,OUTPUT);
 pinMode(arm_B,OUTPUT);
 pinMode(arm_pwm,OUTPUT);
 pinMode(armlower_sens,INPUT);
}




int read_sensors()
{
  obstacleState= digitalRead(obstacle_sens);
  sensStateL= digitalRead(left_sens);
  sensStateC= digitalRead(centr_sens);
  sensStateR= digitalRead(right_sens);
  gripper_openLimit= digitalRead(gipperOpen_sens);
  arm_lowerLimit = digitalRead(armlower_sens);
}

void move_forward(){
  analogWrite(leftmotor_pwm,60);
  analogWrite(rightmotor_pwm,80);
  digitalWrite(leftmotor_A,HIGH);
  digitalWrite(leftmotor_B,LOW);
  digitalWrite(rightmotor_A,HIGH);
  digitalWrite(rightmotor_B,LOW);
  }
  
  void TURNRIGHT()
  {
  analogWrite(leftmotor_pwm,120);
  analogWrite(rightmotor_pwm,20);
  digitalWrite(leftmotor_A,HIGH);
  digitalWrite(leftmotor_B,LOW);
  digitalWrite(rightmotor_A,HIGH);
  digitalWrite(rightmotor_B,LOW);
  }
  void TURNLEFT()
  {analogWrite(leftmotor_pwm,20);
  analogWrite(rightmotor_pwm,150);
  digitalWrite(leftmotor_A,HIGH);
  digitalWrite(leftmotor_B,LOW);
  digitalWrite(rightmotor_A,HIGH);
  digitalWrite(rightmotor_B,LOW);
  }
  
  void align_robot(){
    if((sensStateL ==LOW)&& (sensStateR ==LOW))
    { stop_moving();//don't move.
    }
    else
    {
    if((sensStateL==HIGH) && (sensStateR==LOW))//if the robot gets off the track towards the right side.
 {
    TURNLEFT();//turn it to the left.
 }
  if((sensStateL==LOW) && (sensStateR==HIGH))//if the robot gets off the track towards the left side.
 {
   TURNRIGHT();//turn it to the right.
 }
 if((sensStateL==HIGH) && (sensStateR==HIGH))//if the robot is on track.
 {
  move_forward(); //continue moving forward.
 }  
 }
 }
 
   void stop_moving()
  {
            analogWrite(leftmotor_pwm,10);
            analogWrite(rightmotor_pwm,10);
            digitalWrite(leftmotor_A,LOW);
            digitalWrite(leftmotor_B,LOW);
            digitalWrite(rightmotor_A,LOW);
            digitalWrite(rightmotor_B,LOW);
        
    }
  
  
  void reverse(unsigned long duration)
  {
     unsigned long start = millis();

        while (millis() - start <= duration) 
          {
            analogWrite(leftmotor_pwm,60);
            analogWrite(rightmotor_pwm,80);
            digitalWrite(leftmotor_A,LOW);
            digitalWrite(leftmotor_B,HIGH);
            digitalWrite(rightmotor_A,LOW);
            digitalWrite(rightmotor_B,HIGH);
          }
    }
  
  
   void left_Uturn()
  {
   
   analogWrite(leftmotor_pwm,70);
   analogWrite(rightmotor_pwm,70);
   digitalWrite(leftmotor_A,LOW);
   digitalWrite(leftmotor_B,HIGH);
   digitalWrite(rightmotor_A,HIGH);
   digitalWrite(rightmotor_B,LOW);
          
    }
  
  void find_track()
  {read_sensors();
  while ((sensStateR && sensStateC)== LOW)
  {left_Uturn();
  read_sensors();
  if ((sensStateR && sensStateC) == HIGH){
        stop_moving();
        delay(200);
        break;
     }
    }
  }
  
  void armUp(unsigned long duration)
  {
     unsigned long start = millis();

        while (millis() - start <= duration) 
          {
          digitalWrite(arm_A, HIGH);
          digitalWrite(arm_B, LOW);
           analogWrite(arm_pwm, val1);
          }
    }
    
 void armDown(unsigned long duration)
  {
     unsigned long start = millis();

        while (millis() - start <= duration) 
          {
          digitalWrite(arm_A, LOW);
          digitalWrite(arm_B, HIGH);
         analogWrite(arm_pwm, val1);
         }
    }
 void armDown_max(){
 while (arm_lowerLimit==HIGH) 
          {
           digitalWrite(arm_A, LOW);
           digitalWrite(arm_B, HIGH);
           analogWrite(arm_pwm, val1);
           read_sensors(); 
      if (arm_lowerLimit== LOW){
         stopArm(100);
        break;
         }
    }
  }
    
 void stopArm(unsigned long duration)
   {
     unsigned long start = millis();

        while (millis() - start <= duration) 
          {
           digitalWrite(arm_A, LOW);
           digitalWrite(arm_B, LOW);
      
        }
    }
 
  void openGripper(){
    while (gripper_openLimit==HIGH) 
          {
           digitalWrite(gripper_A, LOW);
           digitalWrite(gripper_B, HIGH);
           analogWrite(gripper_pwm, val1);
           read_sensors(); 
      if (gripper_openLimit == LOW){
         stopGripper();
        delay(100);
        break;
         }
    }
  }
    
 void closeGripper(unsigned long duration)
  {
     unsigned long start = millis();

        while (millis() - start <= duration) 
          {
         digitalWrite(gripper_A, HIGH);
         digitalWrite(gripper_B, LOW);
         analogWrite(gripper_pwm, val1);
       }
    }
  
  void stopGripper() {
     digitalWrite(gripper_A, LOW);
     digitalWrite(gripper_B, LOW); 
          
    }
  
  
  
  
  
    void loop(){
   read_sensors();
   armDown_max();
   armUp(1300);
   stopArm(100);
   openGripper();
    for (int object=0; object <= 2; object++){   
    read_sensors(); 
    while(obstacleState != LOW){
     align_robot();
      read_sensors(); 
      if (obstacleState == LOW){
        stop_moving();
        delay(200);
        break;
      }
   } 
  closeGripper(4000);
  stopGripper();
  delay(100);
  armUp(3000);
  stopArm(100);
  reverse(500);
  read_sensors();
  left_Uturn();
  delay(1500);
  read_sensors();
  find_track();
  
  read_sensors();
  
    while(obstacleState != LOW){
      align_robot();
      read_sensors(); 
      if (obstacleState == LOW){
        stop_moving();
        delay(200);
        break;
      }
   }
   
   openGripper();
   stopGripper();
   delay(100);
   reverse(1000);
   stop_moving();
   read_sensors();
   left_Uturn();
   delay(1400);
   read_sensors();
   find_track();
   stop_moving();
   delay(100);
    if (object == 2){
        stop_moving();
        delay(20000);  
      }
   armUp(10000);
  stopArm(100);
    }
  
}
  
