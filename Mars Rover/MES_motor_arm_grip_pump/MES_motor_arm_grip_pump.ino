//---------------------------Radio Controller Channel Pins Start
#define motorControlChannel 58
#define controlChannel 56
#define opChannelUpDown 55
#define opChannelRightLeft 54
#define gripRotateChannel 57
//---------------------------Radio Controller Channel Pins End


//-------------------------------Motor Pins Start
#define LFfront 38
#define LFback 40
#define LBfront 44
#define LBback 42
#define RFfront 48
#define RFback 46
#define RBfront 50
#define RBback 52
//-------------------------------Motor Pins End


//---------------------------Actuator Pins Start
#define ABaseFront 27
#define ABaseBack 29
#define ATopFront 23
#define ATopBack 25
#define AFrontFront 35
#define AFrontBack 37
#define ASoilFront 39
#define ASoilBack 41
//---------------------------Actuator Pins End


//---------------------------Gripping and Pump Pins Start
#define pump 5
#define rotateRightMotor 33
#define rotateLeftMotor 31
#define gripCloseMotor 43
#define gripOpenMotor 45
//---------------------------Gripping and Pump Pins End


//---------------------------Base Motor Pins Start
#define baseMotorRight 2
#define baseMotorLeft 3
//---------------------------Base Motor Pins End

int motorControlChannelValue;
int controlChannelValue;
int opChannelUpDownValue;
int opChannelRightLeftValue;
int gripRotateChannelValue;

bool top, down, right, left, motor;
bool Position[10];

void setup() {
  Serial.begin(9600);
  Serial.println("NSU Mars Ex------>");
  delay(500);
  pinMode(motorControlChannel, INPUT);
  pinMode(controlChannel, INPUT);
  pinMode(opChannelRightLeft, INPUT);
  pinMode(opChannelUpDown, INPUT);
  pinMode(gripRotateChannel, INPUT);
  
  pinMode(LFfront, OUTPUT);
  pinMode(LFback, OUTPUT);
  pinMode(LBfront, OUTPUT);
  pinMode(LBback, OUTPUT);
  pinMode(RFfront, OUTPUT);
  pinMode(RFback, OUTPUT);
  pinMode(RBfront, OUTPUT);
  pinMode(RBback, OUTPUT);

  pinMode(ABaseFront,OUTPUT);
  pinMode(ABaseBack,OUTPUT);
  pinMode(ATopFront,OUTPUT);
  pinMode(ATopBack,OUTPUT);
  pinMode(AFrontFront,OUTPUT);
  pinMode(AFrontBack,OUTPUT);
  pinMode(ASoilFront,OUTPUT);
  pinMode(ASoilBack,OUTPUT);

  pinMode(pump,OUTPUT);
  pinMode(rotateRightMotor,OUTPUT);
  pinMode(rotateLeftMotor,OUTPUT);
  pinMode(gripCloseMotor,OUTPUT);
  pinMode(gripOpenMotor,OUTPUT);

  pinMode(baseMotorRight, OUTPUT);
  pinMode(baseMotorLeft, OUTPUT);
  Serial.println("Rover Initialization Complete------>");
  delay(500);
  Serial.println("Ready to Go!------>");
  //delay(2000);
}

void loop() {
  motorControlChannelValue = (pulseIn (motorControlChannel, HIGH));
  controlChannelValue = (pulseIn (controlChannel, HIGH));
  opChannelUpDownValue = (pulseIn (opChannelUpDown, HIGH));
  opChannelRightLeftValue = (pulseIn (opChannelRightLeft, HIGH));
  gripRotateChannelValue = (pulseIn (gripRotateChannel, HIGH));

  top = opChannelUpDownValue>1700;
  down = opChannelUpDownValue<1350;
  right = opChannelRightLeftValue>1600;
  left = opChannelRightLeftValue<1250;
  motor = motorControlChannelValue>1500;
  Position[1] = controlChannelValue>1900;
  Position[2] = (controlChannelValue>1800 && controlChannelValue<1880);
  Position[3] = (controlChannelValue>1700 && controlChannelValue<1800);
  Position[4] = (controlChannelValue>1240 && controlChannelValue<1300);
  Position[5] = (controlChannelValue>1150 && controlChannelValue<1240);
  Position[6] = (controlChannelValue>1000 && controlChannelValue<1150);
  
  //Serial.println(opChannelRightLeftValue);
  
  if(motor)   //top toggle switch triggred and motor controlling here
  {
    if(top)        roverGo();    
    else if(down)  roverBack();  
    else if(right) roverRight();     
    else if(left)  roverLeft();
    else           roverStop();
    Serial.print("Position 0   :   Rover Motor     ||   ");
  }

  else if(!motor && Position[1])        //base actuator operation
  {
    if(top)       baseActuatorExtend();
    else if(down) baseActuatorNarrow();
    else          baseActuatorStop();
    Serial.print("Position 1   :   Base Actuator   ||   ");
  }

  else if(!motor && Position[2])        //top actuator operation
  {
    if(top)       topActuatorExtend();
    else if(down) topActuatorNarrow();
    else          topActuatorStop();
    Serial.print("Position 2   :   Top Actuator    ||   ");
  }

  else if(!motor && Position[3])        //front actuator operation
  {
    if(top)       frontActuatorExtend();
    else if(down) frontActuatorNarrow();
    else          frontActuatorStop();
    Serial.print("Position 3   :   Front Actuator  ||   ");
  }

  else if(!motor && Position[4])        //grip actuator operation
  {
    if(top)       gripClose();
    else if(down) gripOpen();
    else if(right)rotateRight();
    else if(left) rotateLeft();
    else          {gripStop(); rotateStop();}
    Serial.print("Position 4   :   Grip Operation  ||   ");
  }

  else if(!motor && Position[5])        //Pump operation
  {
    if(top)       pumpStart();
    else          pumpStop();
    Serial.print("Position 5   :   Pump Operation  ||   ");
  }

  else if(!motor && Position[6])        //Base operation
  {
    if(right)     baseRight();
    else if(left) baseLeft();
    else baseStop();
    Serial.print("Position 6   :   Rover Arm Base  ||   ");
  }
  
}

void roverGo(){
  digitalWrite(LFfront,LOW);      digitalWrite(RFfront,LOW);
  digitalWrite(LFback,HIGH);      digitalWrite(RFback,HIGH);

  digitalWrite(LBfront,LOW);      digitalWrite(RBfront,LOW);
  digitalWrite(LBback,HIGH);      digitalWrite(RBback,HIGH);
  Serial.println("Go");
}

void roverBack(){
  digitalWrite(LFfront,HIGH);     digitalWrite(RFfront,HIGH);
  digitalWrite(LFback,LOW);       digitalWrite(RFback,LOW);

  digitalWrite(LBfront,HIGH);     digitalWrite(RBfront,HIGH);
  digitalWrite(LBback,LOW);       digitalWrite(RBback,LOW);
  Serial.println("Back");
}

void roverRight(){
  digitalWrite(LFfront,LOW);      digitalWrite(RFfront,HIGH);
  digitalWrite(LFback,HIGH);      digitalWrite(RFback,LOW);

  digitalWrite(LBfront,LOW);      digitalWrite(RBfront,HIGH);
  digitalWrite(LBback,HIGH);      digitalWrite(RBback,LOW);
  Serial.println("Right");
}

void roverLeft(){
  digitalWrite(LFfront,HIGH);     digitalWrite(RFfront,LOW);
  digitalWrite(LFback,LOW);       digitalWrite(RFback,HIGH);

  digitalWrite(LBfront,HIGH);     digitalWrite(RBfront,LOW);
  digitalWrite(LBback,LOW);       digitalWrite(RBback,HIGH);
  Serial.println("Left");
}

void roverStop(){
  digitalWrite(LFfront,HIGH);     digitalWrite(RFfront,HIGH);
  digitalWrite(LFback,HIGH);       digitalWrite(RFback,HIGH);

  digitalWrite(LBfront,HIGH);     digitalWrite(RBfront,HIGH);
  digitalWrite(LBback,HIGH);       digitalWrite(RBback,HIGH);
  Serial.println("Stop");
}

//-----------------------------------------------Base Actuator Operations Start
void baseActuatorExtend(){
  digitalWrite(ABaseFront, HIGH);
  digitalWrite(ABaseBack, LOW);
  Serial.println("Extending");
}
void baseActuatorNarrow(){
  digitalWrite(ABaseFront, LOW);
  digitalWrite(ABaseBack, HIGH);
  Serial.println("Narrowing");
}
void baseActuatorStop(){
  digitalWrite(ABaseFront, LOW);
  digitalWrite(ABaseBack, LOW);
  Serial.println("Stop");
}
//-----------------------------------------------Base Actuator Operations End

//-----------------------------------------------Top Actuator Operations Start
void topActuatorExtend(){
  digitalWrite(ATopFront, HIGH);
  digitalWrite(ATopBack, LOW);
  Serial.println("Extending");
}
void topActuatorNarrow(){
  digitalWrite(ATopFront, LOW);
  digitalWrite(ATopBack, HIGH);
  Serial.println("Narrowing");
}
void topActuatorStop(){
  digitalWrite(ATopFront, LOW);
  digitalWrite(ATopBack, LOW);
  Serial.println("Stop");
}
//-----------------------------------------------Top Actuator Operations End

//-----------------------------------------------Front Actuator Operations Start
void frontActuatorExtend(){
  digitalWrite(AFrontFront, HIGH);
  digitalWrite(AFrontBack, LOW);
  Serial.println("Extending");
}
void frontActuatorNarrow(){
  digitalWrite(AFrontFront, LOW);
  digitalWrite(AFrontBack, HIGH);
  Serial.println("Narrowing");
}
void frontActuatorStop(){
  digitalWrite(AFrontFront, LOW);
  digitalWrite(AFrontBack, LOW);
  Serial.println("Stop");
}
//-----------------------------------------------Front Actuator Operations End

//-----------------------------------------------Gripping Operations Start
void gripClose(){
  digitalWrite(gripCloseMotor, HIGH);
  digitalWrite(gripOpenMotor, LOW);
  Serial.println("Closing  ");
}
void gripOpen(){
  digitalWrite(gripCloseMotor, LOW);
  digitalWrite(gripOpenMotor, HIGH);
  Serial.println("Opening  ");
}
void gripStop(){
  digitalWrite(gripCloseMotor, LOW);
  digitalWrite(gripOpenMotor, LOW);
  Serial.print("Stop  ");
}
//--------------------------------------------------------------
void rotateRight(){
  digitalWrite(rotateRightMotor, HIGH);
  digitalWrite(rotateLeftMotor, LOW);
  Serial.println("Rotating Right");
}
void rotateLeft(){
  digitalWrite(rotateRightMotor, LOW);
  digitalWrite(rotateLeftMotor, HIGH);
  Serial.println("Rotating Left");
}
void rotateStop(){
  digitalWrite(rotateRightMotor, LOW);
  digitalWrite(rotateLeftMotor, LOW);
  Serial.println("Rotating Off");
}
//-----------------------------------------------Gripping Operations End


//-----------------------------------------------Base Motor Operation Start
void baseRight(){
  digitalWrite(baseMotorRight, HIGH);
  digitalWrite(baseMotorLeft, LOW);
  Serial.println("Going Right");
}
void baseLeft(){
  digitalWrite(baseMotorRight, LOW);
  digitalWrite(baseMotorLeft, HIGH);
  Serial.println("Going Left");
}
void baseStop(){
  digitalWrite(baseMotorRight, LOW);
  digitalWrite(baseMotorLeft, LOW);
  Serial.println("Remain Stop");
}
//-----------------------------------------------Base Motor Operation End


//-----------------------------------------------Pump Operation Start
void pumpStart(){
  digitalWrite(pump, HIGH);
  Serial.println("Start");
}
void pumpStop(){
  digitalWrite(pump, LOW);
  Serial.println("Stop");
}
//-----------------------------------------------Pump Operation End
