#define leftMotF 11
#define leftMotB 10
#define rightMotF 5
#define rightMotB 3
#define flipperF 6
#define flipperB 9


#define UpDownChannel 15
#define LeftRightChannel 14
#define FlipperDown 17
#define FlipperChannel 16
#define SpeedChannel 19
/*Define Complete*/



int UpDownChannelValue;
int LeftRightChannelValue;
int FlipperChannelValue;
int FlipperDownValue;
int SpeedChannelValue;


int MaxSpeed=255 ;
int MinSpeed=150 ;

int FlipTemp;


void  setup ()
{
   pinMode (leftMotF, OUTPUT);
   pinMode (leftMotB, OUTPUT);
   pinMode (rightMotF, OUTPUT);
   pinMode (rightMotB, OUTPUT); 
   pinMode (flipperF, OUTPUT); 
   pinMode (flipperB, OUTPUT);
   pinMode (UpDownChannel, INPUT);
   pinMode (LeftRightChannel, INPUT);
   pinMode (FlipperDown, INPUT); 
   pinMode (FlipperChannel, INPUT);
   pinMode(SpeedChannel, INPUT);
   Serial.begin (9600);
}

void  loop ()
{
  UpDownChannelValue    = (pulseIn (UpDownChannel, HIGH));
  FlipperChannelValue   = (pulseIn (FlipperChannel, HIGH));
  LeftRightChannelValue = (pulseIn (LeftRightChannel, HIGH));
  FlipperDownValue = (pulseIn (FlipperDown, HIGH));
  SpeedChannelValue = (pulseIn (SpeedChannel, HIGH));
   
  

{
  if(SpeedChannelValue<1300){
    if ((UpDownChannelValue > 1700) && (LeftRightChannelValue > 1800))
  {
          analogWrite(leftMotF , MaxSpeed);
          digitalWrite(leftMotB , LOW);
          analogWrite(rightMotF , MaxSpeed/2);
          digitalWrite(rightMotB , LOW);
          Serial.println("Slight Front-Right in Maximum Speed");
  }
  else if ((UpDownChannelValue > 1700) && (LeftRightChannelValue < 1150))
  {
          analogWrite(leftMotF , MaxSpeed/2);
          digitalWrite(leftMotB , LOW);
          analogWrite(rightMotF , MaxSpeed);
          digitalWrite(rightMotB , LOW);
          Serial.println("Slight Front-Left in Maximum Speed");
  }
  else if ((UpDownChannelValue < 1200) && (LeftRightChannelValue > 1800)) 
  {
          digitalWrite(leftMotF , LOW);
          analogWrite(leftMotB , MaxSpeed);
          digitalWrite(rightMotF , LOW);
          analogWrite(rightMotB , MaxSpeed/2);
          Serial.println("Slight Right-Back in Maximum Speed");
  }
  else if ((UpDownChannelValue < 1200) && (LeftRightChannelValue < 1150)) 
  {
          digitalWrite(leftMotF , LOW);
          analogWrite(leftMotB , MaxSpeed/2);
          digitalWrite(rightMotF , LOW);
          analogWrite(rightMotB , MaxSpeed);
          Serial.println("Slight Left-Back in Maximum Speed");
  }
  else if (UpDownChannelValue > 1700)
  {
          analogWrite(leftMotF , MaxSpeed);
          digitalWrite(leftMotB , LOW);
          analogWrite(rightMotF , MaxSpeed);
          digitalWrite(rightMotB , LOW);
          Serial.println("Front in Maximum Speed");
  }
  else if (UpDownChannelValue < 1200) 
  {
          digitalWrite(leftMotF , LOW);
          analogWrite(leftMotB , MaxSpeed);
          digitalWrite(rightMotF , LOW);
          analogWrite(rightMotB , MaxSpeed);
          Serial.println("Back in Maximum Speed");
  }
  else if (LeftRightChannelValue < 1150)
  {
          digitalWrite(leftMotF , LOW);
          analogWrite(leftMotB , MaxSpeed);
          analogWrite(rightMotF , MaxSpeed);
          digitalWrite(rightMotB , LOW);
          Serial.println("Sharp Left in Maximum Speed");
  }
  else if (LeftRightChannelValue > 1800) 
  {
        analogWrite(leftMotF , MaxSpeed);
        digitalWrite(leftMotB , LOW);
        digitalWrite(rightMotF , LOW);
        analogWrite(rightMotB , MaxSpeed);
        Serial.println("Sharp Right in Maximum Speed");
  }
  else
  {
          digitalWrite(leftMotF , LOW);
          digitalWrite(leftMotB , LOW);
          digitalWrite(rightMotF , LOW);
          digitalWrite(rightMotB , LOW);
          Serial.println("Stop in Whatever Damn Speed!!");
  }
 }
  else{
    if ((UpDownChannelValue > 1700) && (LeftRightChannelValue > 1800))
  {
          analogWrite(leftMotF , MinSpeed);
          digitalWrite(leftMotB , LOW);
          analogWrite(rightMotF , MinSpeed/2);
          digitalWrite(rightMotB , LOW);
          Serial.println("Slight Front-Right in Minumum Speed");
  }
  else if ((UpDownChannelValue > 1700) && (LeftRightChannelValue < 1150))
  {
          analogWrite(leftMotF , MinSpeed/2);
          digitalWrite(leftMotB , LOW);
          analogWrite(rightMotF , MinSpeed);
          digitalWrite(rightMotB , LOW);
          Serial.println("Slight Front-Left in Minumum Speed");
  }
  else if ((UpDownChannelValue < 1200) && (LeftRightChannelValue > 1800)) 
  {
          digitalWrite(leftMotF , LOW);
          analogWrite(leftMotB , MinSpeed);
          digitalWrite(rightMotF , LOW);
          analogWrite(rightMotB , MinSpeed/2);
          Serial.println("Slight Right-Back in Minumum Speed");
  }
  else if ((UpDownChannelValue < 1200) && (LeftRightChannelValue < 1150)) 
  {
          digitalWrite(leftMotF , LOW);
          analogWrite(leftMotB , MinSpeed/2);
          digitalWrite(rightMotF , LOW);
          analogWrite(rightMotB , MinSpeed);
          Serial.println("Slight Left-Back in Minumum Speed");
  }
  else if (UpDownChannelValue > 1700)
  {
          analogWrite(leftMotF , MinSpeed);
          digitalWrite(leftMotB , LOW);
          analogWrite(rightMotF , MinSpeed);
          digitalWrite(rightMotB , LOW);
          Serial.println("Front in Minumum Speed");
  }
  else if (UpDownChannelValue < 1200) 
  {
          digitalWrite(leftMotF , LOW);
          analogWrite(leftMotB , MinSpeed);
          digitalWrite(rightMotF , LOW);
          analogWrite(rightMotB , MinSpeed);
          Serial.println("Back in Minumum Speed");
  }
  else if (LeftRightChannelValue < 1150)
  {
          digitalWrite(leftMotF , LOW);
          analogWrite(leftMotB , MinSpeed);
          analogWrite(rightMotF , MinSpeed);
          digitalWrite(rightMotB , LOW);
          Serial.println("Sharp Left in Minumum Speed");
  }
  else if (LeftRightChannelValue > 1800) 
  {
        analogWrite(leftMotF , MinSpeed);
        digitalWrite(leftMotB , LOW);
        digitalWrite(rightMotF , LOW);
        analogWrite(rightMotB , MinSpeed);
        Serial.println("Sharp Right in Minumum Speed");
  }
  else
  {
          digitalWrite(leftMotF , LOW);
          digitalWrite(leftMotB , LOW);
          digitalWrite(rightMotF , LOW);
          digitalWrite(rightMotB , LOW);
          Serial.println("Stop in Whatever Damn Speed!!");
  }
 }
}
{
  if(FlipperChannelValue > 1700 && FlipTemp!=0)
  {
    digitalWrite(flipperF , HIGH);
    digitalWrite(flipperB , LOW);
    delay(300);
    digitalWrite(flipperF , LOW);
    digitalWrite(flipperB , LOW);
    FlipTemp=0;
    Serial.println("----------->Flipper Up");
  }
  else if(FlipperChannelValue < 1200 && FlipTemp!=1)
  {
    digitalWrite(flipperF , LOW);
    digitalWrite(flipperB , HIGH);
    delay(300);
    digitalWrite(flipperF , LOW);
    digitalWrite(flipperB , LOW);
    FlipTemp=1;
    Serial.println("----------->Flipper Down");
  }
  else if(FlipperDownValue>1750)
  {
    digitalWrite(flipperF , LOW);
    analogWrite(flipperB , 100);
    Serial.println("------------------------------->Flipper Slow Down");
    delay(100);
  }
  else
  {
    digitalWrite(flipperF , LOW);
    digitalWrite(flipperB , LOW);
  }
}
digitalWrite(flipperF , LOW);
digitalWrite(flipperB , LOW);
}
