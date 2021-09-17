#define leftMotF 9
#define leftMotB 6
#define rightMotF 11
#define rightMotB 10


#define UpDownChannel 14
#define LeftRightChannel 17
#define SpeedChannel 15
/*Define Complete*/



int UpDownChannelValue;
int LeftRightChannelValue;
int Speed;



int   up = 1982;
int down = 996;

int left = 988, right = 1974;

int   SpeedUp = 1972;
int SpeedDown = 988;



void  setup ()
{
   pinMode (leftMotF, OUTPUT);
   pinMode (leftMotB, OUTPUT);
   pinMode (rightMotF, OUTPUT);
   pinMode (rightMotB, OUTPUT);
   pinMode (UpDownChannel, INPUT);
   pinMode (LeftRightChannel, INPUT);
   pinMode (SpeedChannel, INPUT);
   Serial.begin (9600);
}

void  loop ()
{
  UpDownChannelValue = (pulseIn (UpDownChannel, HIGH));
  LeftRightChannelValue = (pulseIn (LeftRightChannel, HIGH)); 
          int Temp = (pulseIn (SpeedChannel, HIGH));
          if(Temp>(SpeedUp-100))Speed=255;
     else if(Temp<(SpeedDown+100))Speed=100;
                  else Speed = 150;

{
  if (LeftRightChannelValue > (right-100) && UpDownChannelValue > (up-100))
  {
          analogWrite(leftMotF , Speed);
          digitalWrite(leftMotB , LOW);
          analogWrite(rightMotF , Speed/2);
          digitalWrite(rightMotB , LOW);
          Serial.println("Slight Turn Right");
  }

    else if (UpDownChannelValue > (up-100) && LeftRightChannelValue < (left+100))
  {
          analogWrite(leftMotF , Speed/2);
          digitalWrite(leftMotB , LOW);
          analogWrite(rightMotF , Speed);
          digitalWrite(rightMotB , LOW);
          Serial.println("Slight Turn Left");
  }

    else if (UpDownChannelValue < (down+100) && LeftRightChannelValue < (left+100)) 
  {
          digitalWrite(leftMotF , LOW);
          analogWrite(leftMotB , Speed/2);
          digitalWrite(rightMotF , LOW);
          analogWrite(rightMotB , Speed);
          Serial.println("Slight Turn Back Left");
  }

    else if(UpDownChannelValue < (down+100) && LeftRightChannelValue > (right-100)) 
  {
          digitalWrite(leftMotF , LOW);
          analogWrite(leftMotB , Speed);
          digitalWrite(rightMotF , LOW);
          analogWrite(rightMotB , Speed/2);
          Serial.println("Slight Turn Back Right");
  }

  
  else if (UpDownChannelValue > (up-100))
  {
          analogWrite(leftMotF , Speed);
          digitalWrite(leftMotB , LOW);
          analogWrite(rightMotF , Speed);
          digitalWrite(rightMotB , LOW);
          Serial.println("Front");
  }

  else if (UpDownChannelValue < (down+100)) 
  {
          digitalWrite(leftMotF , LOW);
          analogWrite(leftMotB , Speed);
          digitalWrite(rightMotF , LOW);
          analogWrite(rightMotB , Speed);
          Serial.println("Back");
  }
  

  else if (LeftRightChannelValue < (left+100))
  {
          digitalWrite(leftMotF , LOW);
          analogWrite(leftMotB , Speed);
          analogWrite(rightMotF , Speed);
          digitalWrite(rightMotB , LOW);
          Serial.println("Sharp Left");
  }
  
  else if (LeftRightChannelValue > (right-100)) 
  {
        analogWrite(leftMotF , Speed);
        digitalWrite(leftMotB , LOW);
        digitalWrite(rightMotF , LOW);
        analogWrite(rightMotB , Speed);
        Serial.println("Sharp Right");
  }

  
  else
  {
        digitalWrite(leftMotF , LOW);
        digitalWrite(leftMotB , LOW);
        digitalWrite(rightMotF , LOW);
        digitalWrite(rightMotB , LOW);
        Serial.println("Stop");
  }
}
}
