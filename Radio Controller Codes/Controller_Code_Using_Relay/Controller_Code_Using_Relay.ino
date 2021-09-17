#define leftMotF 4
#define leftMotB 5
#define rightMotF 7
#define rightMotB 6

#define channel1 2
#define channel2 3
/*Define Complete*/

int channel1Value;
int channel2Value;

void  setup ()
{
   pinMode (leftMotF, OUTPUT);
   pinMode (leftMotB, OUTPUT);
   pinMode (rightMotF, OUTPUT);
   pinMode (rightMotB, OUTPUT);
   pinMode (channel1, INPUT);
   pinMode (channel2, INPUT);
   Serial.begin (9600);
}

void  loop ()
{
  channel1Value = (pulseIn (channel1, HIGH));
  channel2Value = (pulseIn (channel2, HIGH)); 

{
  if (channel1Value < 1200 && channel2Value > 1700)
  {
          
          digitalWrite(leftMotF , HIGH);
          digitalWrite(leftMotB , LOW);
          digitalWrite(rightMotF , HIGH);
          digitalWrite(rightMotB , HIGH);
          Serial.println("Slight Turn Back Right");
  }

    else if (channel1Value < 1200 && channel2Value < 1200)
  {
          
          digitalWrite(leftMotF , HIGH);
          digitalWrite(leftMotB , HIGH);
          digitalWrite(rightMotF , HIGH);
          digitalWrite(rightMotB , LOW);
          Serial.println("Slight Turn Back Left");
  }

    else if (channel1Value > 1700 && channel2Value > 1700) 
  {
          digitalWrite(leftMotF , LOW);
          digitalWrite(leftMotB , HIGH);
          digitalWrite(rightMotF , HIGH);
          digitalWrite(rightMotB , HIGH);
          Serial.println("Slight Turn Right");
  }

    else if(channel1Value > 1700 && channel2Value < 1200) 
  {
          digitalWrite(leftMotF , HIGH);
          digitalWrite(leftMotB , HIGH);
          digitalWrite(rightMotF , LOW);
          digitalWrite(rightMotB , HIGH);
          Serial.println("Slight Turn Left");
  }

  
  else if (channel1Value < 1200)
  {
          digitalWrite(leftMotF , HIGH);
          digitalWrite(leftMotB , LOW);
          digitalWrite(rightMotF , HIGH);
          digitalWrite(rightMotB , LOW);
          Serial.println("Back");
          
  }

  else if (channel1Value > 1700) 
  {
          digitalWrite(leftMotF , LOW);
          digitalWrite(leftMotB , HIGH);
          digitalWrite(rightMotF , LOW);
          digitalWrite(rightMotB , HIGH);
          Serial.println("Front");
  }
  

  else if (channel2Value < 1200)
  {
          digitalWrite(leftMotF , HIGH);
          digitalWrite(leftMotB , LOW);
          digitalWrite(rightMotF , LOW);
          digitalWrite(rightMotB , HIGH);
          Serial.println("Sharp Left");
  }
  
  else if (channel2Value > 1700) 
  {
        digitalWrite(leftMotF , LOW);
        digitalWrite(leftMotB , HIGH);
        digitalWrite(rightMotF , HIGH);
        digitalWrite(rightMotB , LOW);
        Serial.println("Sharp Right");
  }

  
  else
  {
          digitalWrite(leftMotF , HIGH);
          digitalWrite(leftMotB , HIGH);
          digitalWrite(rightMotF , HIGH);
          digitalWrite(rightMotB , HIGH);
          Serial.println("Stop");
  }
}
}
