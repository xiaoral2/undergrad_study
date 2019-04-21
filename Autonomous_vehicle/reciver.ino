#define FRONT_Echo 4 // front ultrasonic receive 前超音波信号接收脚位
#define FRONT_Trig 2 // fornt ultrasonic send    前超音波信号发射脚位
#define LEFT_Echo  6  // LEFT ULTRASONIC  RECEIVE 左超音波信号接收脚位  
#define LEFT_Trig  5  // LEFT ULTRASONIC SEND 左超音波信号发射脚位
#define RIGHT_Echo  10  // RIGHT ULTRASONIC RECEIVE 右定义超音波信号接收脚位  
#define RIGHT_Trig  7  // RIGHT ULTRASONIC SEND 右定义超音波信号发射脚位
#include <Wire.h>
long int df=0,dl=0,dr=0;
int value;
void MOTOR_GO_FORWARD(){
  //Motor right
  digitalWrite(12, HIGH); // DIRECTION CONTROL
  digitalWrite(9, LOW);   //BRAKE CONTROL LOW IF DISABLE
  digitalWrite(3, HIGH);   // SPEED

  //Motor left
  digitalWrite(13, HIGH);  
  digitalWrite(8, LOW);   
  digitalWrite(11, HIGH);    
  }                  

void MOTOR_GO_BACK(){
  //Motor right
  digitalWrite(12, LOW); 
  digitalWrite(9, LOW);   
  digitalWrite(3, HIGH);   

  //Motor left
  digitalWrite(13, LOW);  
  digitalWrite(8, LOW);   
  digitalWrite(11, HIGH);    
  }    

void MOTOR_GO_RIGHT(){
  //Motor right
  digitalWrite(12, LOW); 
  digitalWrite(9, LOW);   
  digitalWrite(3, HIGH);   

  //Motor left
  digitalWrite(13, HIGH);  
  digitalWrite(8, LOW);  
  digitalWrite(11, HIGH);     
  }  

void MOTOR_GO_LEFT(){
  //Motor RIGHT
  digitalWrite(12, HIGH); 
  digitalWrite(9, LOW);   
  digitalWrite(3, HIGH);   

  //Motor left
  digitalWrite(13, LOW);  
  digitalWrite(8, LOW);  
  digitalWrite(11, HIGH);
  }    

void MOTOR_GO_STOP(){
  //Motor left
  digitalWrite(9, HIGH);     

  //Motor right
  digitalWrite(8, HIGH);  
  }  

/*void TURN_LEFT_ANGLE(float angle){
  int t;
  t=angle/360*1500;
  MOTOR_GO_LEFT();
  delay(t);
  MOTOR_GO_FORWARD();
  delay(100);
  MOTOR_GO_RIGHT();
  delay(t);
  }   //输入角度决定转向时间

void TURN_RIGHT_ANGLE(float angle){
  int t;
  t=angle/360*1500;
  MOTOR_GO_RIGHT();
  delay(t);
  MOTOR_GO_FORWARD();
  delay(100);
  MOTOR_GO_LEFT();
  delay(t);
  }   //输入角度决定转向时间 */

long Get_Front_Distance(){
      long Ldistance=0;
      pinMode(FRONT_Trig, OUTPUT); 
      digitalWrite(FRONT_Trig, LOW);   // 让超声波发射低电压2μs  
      delayMicroseconds(2);  
      digitalWrite(FRONT_Trig, HIGH);  // 让超声波发射高电压10μs，这里至少是10μs  
      delayMicroseconds(10);  
      digitalWrite(FRONT_Trig, LOW);    // 维持超声波发射低电压  
      pinMode(FRONT_Echo,INPUT);
      Ldistance = pulseIn(FRONT_Echo, HIGH);  // 读差相差时间  
      Ldistance= Ldistance/5.8/10;      // 将时间转为距离距离（单位：公分）    
      Serial.print("Frontdistance=");
      Serial.println(Ldistance);      //显示距离  
      
      return Ldistance;
      
  }    //MEASURE FRONT DISTANCE

long Get_Left_Distance(){  
      long Ldistance=0;
      pinMode(LEFT_Trig,OUTPUT);
      digitalWrite(LEFT_Trig, LOW);   // 让超声波发射低电压2μs  
      delayMicroseconds(2);  
      digitalWrite(LEFT_Trig, HIGH);  // 让超声波发射高电压10μs，这里至少是10μs  
      delayMicroseconds(10);  
      digitalWrite(LEFT_Trig, LOW);    // 维持超声波发射低电压  
      pinMode(LEFT_Echo,INPUT);
      Ldistance = pulseIn(LEFT_Echo, HIGH);  // 读差相差时间  
      Ldistance= Ldistance/5.8/10;      // 将时间转为距离距离（单位：公分） 
      Serial.print("leftdistance=");   
      Serial.println(Ldistance);      //显示距离  
      return Ldistance;
      
  }    //MEASURE LEFT DISTANCE

long Get_Right_Distance(){  
      long Ldistance=0;
      pinMode(RIGHT_Trig,OUTPUT);
      digitalWrite(RIGHT_Trig, LOW);   // 让超声波发射低电压2μs  
      delayMicroseconds(2);  
      digitalWrite(RIGHT_Trig, HIGH);  // 让超声波发射高电压10μs，这里至少是10μs  
      delayMicroseconds(10);  
      digitalWrite(RIGHT_Trig, LOW);    // 维持超声波发射低电压  
      pinMode(RIGHT_Echo,INPUT);
      Ldistance = pulseIn(RIGHT_Echo, HIGH);  // 读差相差时间  
      Ldistance= Ldistance/5.8/10;      // 将时间转为距离距离（单位：公分）
      Serial.print("rightdistance=");    
      Serial.println(Ldistance);      //显示距离  
      return Ldistance;
      
  }    //MEASURE RIGHT DISTANCE  


      
void setup() {
  
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin
  pinMode(3,OUTPUT);
  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin
  pinMode(11,OUTPUT);
  
 Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void receiveEvent(int howMany) {

   value = Wire.read();    // receive byte as an integer
 // Serial.println(value);         // print the integer
}

void loop(){
  Serial.println(value);
    delay(1000); //allows all serial sent to be received together
   
   
  MOTOR_GO_FORWARD();
  //df=Get_Front_Distance();
  //dr=Get_Right_Distance();
  //dl=Get_Left_Distance(); 
  if (value>120 && value != 0){
  MOTOR_GO_STOP();
  delay(3000);
  }
  /*else if(df < 20){
    MOTOR_GO_STOP();
    delay(1000);
    
    }
   else if(dr < 6 && dl > 6){
    MOTOR_GO_LEFT();
    delay(800);
    MOTOR_GO_FORWARD();
    delay(1000);
    MOTOR_GO_RIGHT();
    delay(800);
    MOTOR_GO_FORWARD();
    }
  else if(dr > 6 && dl < 6){
    MOTOR_GO_RIGHT();
    delay(800);
    MOTOR_GO_FORWARD();
    delay(1000);
    MOTOR_GO_LEFT();
    delay(800);
    MOTOR_GO_FORWARD();
    }
   else {
   MOTOR_GO_FORWARD();
   
   delay(100);
   }
   
// ULTRASONIC AVOID FUNCTION

*/
}

