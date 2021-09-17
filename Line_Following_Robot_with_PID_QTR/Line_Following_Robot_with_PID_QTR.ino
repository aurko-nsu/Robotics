#include <QTRSensors.h>
#define P 40
#define D          //40
#define I 2

#define Kp 20       //20
#define Ki 1500
#define Kd 11/9

#define leftMotF A4
#define leftMotB A5
#define leftMotRPM 10

#define rightMotF A2
#define rightMotB A1
#define rightMotRPM 11

#define qtrLed 8
#define NUM_SENSORS 8
#define TIMEOUT 2500

int leftMaxSpeed = 200;      //calibrated speeed left 109, right 65  difference = 44
int rightMaxSpeed = 200;
int rightBaseSpeed= 200; 

int leftBaseSpeed =114;
int rightMaxSpeed_loop=60;

int leftMaxSpeed_loop=60;
int rightBaseSpeed_loop=90;

int leftBaseSpeed_loop=90;
int reverseSpeed = 200;

int turnSpeed = 150;
int setPoint = 0;

int readsensorAnalog = 0;        //to get sensor read initialize 1
int readsensorDigital = 0;

int mainLoop = 0;
int DEBUG=0;                        //to get sensor read initialize 1

QTRSensorsRC qtrrc((unsigned char[]) {2,3,4,5,6,7,8,9} ,NUM_SENSORS, TIMEOUT,qtrLed);

unsigned int sensorValues[NUM_SENSORS];
unsigned int sensors[NUM_SENSORS];

void readSensor();
void straight_slight_turns();
void reverse();
void PID_control();
void pid_control_loop();
void readSensor();
void manual_calibration();
void set_point();
void straight();
void center_Reverse();
void sharp_turn_right();
void  sharp_turn_left();

void setup()
{
Serial.begin(9600);
  pinMode(leftMotF,OUTPUT);
  pinMode(leftMotB,OUTPUT);
  pinMode(leftMotRPM,OUTPUT);
  pinMode(rightMotF,OUTPUT);
  pinMode(rightMotB,OUTPUT);
  pinMode(rightMotRPM,OUTPUT);
  //digitalWrite(qtrLed, HIGH);
   manual_calibration();
    set_point();
}

int blackValue = 1500;
boolean lff,lf,ln,lc,rc,rn,rf,rff;
int lastError = 0;


void loop(){
  readSensor();
  PID_control(); 
  }

void set_point(){
for(int i=0;i<100;i++){
setPoint=qtrrc.readLine(sensors);
delay(50);
  }  
}


void pid_control_loop()
{
  Serial.println("pid_control_loop");

   int position = qtrrc.readLine(sensors); // get calibrated readings along with the line position, refer to the QTR Sensors Arduino Library for more details on line position.
  Serial.print(position);
  Serial.print("  ");
  int error = position - setPoint;
  Serial.print(error);
  Serial.print(" ");
  
  int integral=0;
  integral=integral+error;
  
  int motorSpeed = error*P+(error - lastError)*D+(integral)*I;
  lastError = error;

  int rightMotorSpeed = rightBaseSpeed_loop + motorSpeed;
  int leftMotorSpeed = leftBaseSpeed_loop - motorSpeed;
  
    if (rightMotorSpeed > rightMaxSpeed_loop ) rightMotorSpeed = rightMaxSpeed_loop; // prevent the motor from going beyond max speed
  if (leftMotorSpeed > leftMaxSpeed_loop ) leftMotorSpeed = leftMaxSpeed_loop; // prevent the motor from going beyond max speed
  if (rightMotorSpeed < 0) rightMotorSpeed = 0; // keep the motor speed positive
  if (leftMotorSpeed < 0) leftMotorSpeed = 0; // keep the motor speed positive
  
   {
// move forward with appropriate speeds
  digitalWrite(rightMotF, HIGH);
  digitalWrite(rightMotB, LOW);
  Serial.print(rightMotRPM);
 
  Serial.print(" ");
  Serial.print(leftMotRPM);
  Serial.println();
  analogWrite(rightMotRPM, rightMotorSpeed);
  digitalWrite(leftMotF, HIGH);
  digitalWrite(leftMotB, LOW);
  analogWrite(leftMotRPM, leftMotorSpeed);
}   
}



void Stop(){
  analogWrite(leftMotRPM, 0);
  analogWrite(rightMotRPM, 0);
  digitalWrite(leftMotF , HIGH);
  digitalWrite(leftMotB , LOW);
  digitalWrite(rightMotF , HIGH);
  digitalWrite(rightMotB , LOW); 
}

void sharp_turn_right(){
  
  int position = qtrrc.readLine(sensors); 
  Serial.print(position);
  boolean tc = position == setPoint;
 
  while (!(!lff && !rff && (lf || ln || lc || rc)))
  {
  analogWrite(leftMotRPM, turnSpeed);
  analogWrite(rightMotRPM, turnSpeed);
  digitalWrite(leftMotF , LOW);
  digitalWrite(leftMotB , HIGH);
  digitalWrite(rightMotF , HIGH);
  digitalWrite(rightMotB , LOW); 
  position = qtrrc.readLine(sensors);
  tc = position == setPoint;
  readSensor();
  }

}

void sharp_turn_left(){
  int position = qtrrc.readLine(sensors);
  Serial.print(position);
  boolean tc = position == setPoint;
  while (!(!lff && !rff && (lf || ln || lc || tc)))
  {
  analogWrite(leftMotRPM, turnSpeed);
  analogWrite(rightMotRPM, turnSpeed);
  digitalWrite(leftMotF , HIGH);
  digitalWrite(leftMotB , LOW);
  digitalWrite(rightMotF , LOW);
  digitalWrite(rightMotB , HIGH); 
  readSensor();
  position = qtrrc.readLine(sensors);
  tc = position == setPoint;
  }
}

void reverse(){
  while(!(!rff&&!lff)){
  analogWrite(leftMotRPM, 0);
  analogWrite(rightMotRPM, reverseSpeed);
  digitalWrite(leftMotF , HIGH);
  digitalWrite(leftMotB , LOW);
  digitalWrite(rightMotF , HIGH);
  digitalWrite(rightMotB , LOW); 
   readSensor(); 
}
//Stop();
//delay(20);
  
}

void straight_slight_turns(){
  if(!lc||!rc){
    pid_control_loop();}
  else{
    pid_control_loop();}
}

 void PID_control(){
  Serial.println("PID_control");

   int position = qtrrc.readLine(sensors); // get calibrated readings along with the line position, refer to the QTR Sensors Arduino Library for more details on line position.
  Serial.print(position);
  Serial.print("  ");
  int error = position - setPoint;
  Serial.print(error);
  Serial.print(" ");
  
  int integral=0;
  integral=integral+error;
  
  int motorSpeed = error/Kp +(error - lastError)/Kd+(integral)/Ki;
  lastError = error;

  int rightMotorSpeed = rightBaseSpeed + motorSpeed;
  int leftMotorSpeed = leftBaseSpeed - motorSpeed;
  
    if (rightMotorSpeed > rightMaxSpeed ) rightMotorSpeed = rightMaxSpeed; // prevent the motor from going beyond max speed
  if (leftMotorSpeed > leftMaxSpeed ) leftMotorSpeed = leftMaxSpeed; // prevent the motor from going beyond max speed
  if (rightMotorSpeed < 0) rightMotorSpeed = 0; // keep the motor speed positive
  if (leftMotorSpeed < 0) leftMotorSpeed = 0; // keep the motor speed positive
  
   {
// move forward with appropriate speeds
  digitalWrite(rightMotF, HIGH);
  digitalWrite(rightMotB, LOW);
  Serial.print(rightMotorSpeed);
 
  Serial.print(" ");
  Serial.print(leftMotorSpeed);
  Serial.println();
  analogWrite(rightMotRPM, rightMotorSpeed);
  digitalWrite(leftMotF, HIGH);
  digitalWrite(leftMotB, LOW);
  analogWrite(leftMotRPM, leftMotorSpeed);
}

 }




void readSensor()
{
   
   
  
  qtrrc.read(sensorValues);
  lff=sensorValues[7]>=blackValue;
  lf=sensorValues[6]>=blackValue;
  ln=sensorValues[5]>=blackValue;
  lc=sensorValues[4]>=blackValue;
  rc=sensorValues[3]>=blackValue;
  rn=sensorValues[2]>=blackValue;
  rf=sensorValues[1]>=blackValue;
  rff=sensorValues[0]>=blackValue;

if(readsensorDigital==1){
    Serial.print('\t');
        Serial.print("lff-");
    Serial.print(lff);
    Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
    Serial.print("lf-");
    Serial.print(lf);
    Serial.print('\t');
    Serial.print("ln-");
    Serial.print(ln);
    Serial.print('\t');
    Serial.print("lc-");
    Serial.print(lc);
    Serial.print('\t');
    Serial.print("rc-");
    Serial.print(rc);
    Serial.print('\t');
    Serial.print("rn-");
    Serial.print(rn);
    Serial.print('\t');
    Serial.print("rf-");
    Serial.print(rf);
    Serial.print('\t');
    Serial.print("rff-");
    Serial.print(rff);
    Serial.print('\t');

    
    delay(200);
    Serial.print('\n');
    
  }

  if(readsensorAnalog==1){
//      Serial.print("lfff-");
//    Serial.print(analogRead(A4));
//    Serial.print('\t');
    Serial.print("lff-");
    Serial.print(sensorValues[7]);
    Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
    Serial.print("lf-");
    Serial.print(sensorValues[6]);
    Serial.print('\t');
    Serial.print("ln-");
    Serial.print(sensorValues[5]);
    Serial.print('\t');
    Serial.print("lc-");
    Serial.print(sensorValues[4]);
    Serial.print('\t');
    Serial.print("rc-");
    Serial.print(sensorValues[3]);
    Serial.print('\t');
    Serial.print("rn-");
    Serial.print(sensorValues[2]);
    Serial.print('\t');
    Serial.print("rf-");
    Serial.print(sensorValues[1]);
    Serial.print('\t');
    Serial.print("rff-");
    Serial.print(sensorValues[0]);
//    Serial.print('\t');
//    Serial.print("rfff-");
//    Serial.print(analogRead(A5));
    
    delay(200);
    Serial.print('\n');
    
  }
}
void manual_calibration() {
 
int i;
for (i = 0; i < 100; i++)
{
qtrrc.calibrate(QTR_EMITTERS_ON);
delay(20);
}
 
if (DEBUG) {
Serial.begin(9600);
for (int i = 0; i < NUM_SENSORS; i++)
{
Serial.print(qtrrc.calibratedMinimumOn[i]);
Serial.print(' ');
}
Serial.println();
 
for (int i = 0; i < NUM_SENSORS; i++)
{
Serial.print(qtrrc.calibratedMaximumOn[i]);
Serial.print(' ');
}
Serial.println();
Serial.println();
}
}

void center_Reverse(){
  
  while(!(lf || ln || lc || rc || rn || rf)){
  analogWrite(leftMotRPM, reverseSpeed);
  analogWrite(rightMotRPM, reverseSpeed);
  digitalWrite(leftMotF , HIGH);
  digitalWrite(leftMotB , LOW);
  digitalWrite(rightMotF , LOW);
  digitalWrite(rightMotB , HIGH); 
   readSensor(); 
   }  
}

void straight(){
  while(!(!lff && !rff)){
  analogWrite(leftMotRPM, leftMaxSpeed);
  analogWrite(rightMotRPM, rightMaxSpeed);
  digitalWrite(leftMotF , HIGH);
  digitalWrite(leftMotB , LOW);
  digitalWrite(rightMotF , HIGH);
  digitalWrite(rightMotB , LOW); 
   readSensor();
  }
}



