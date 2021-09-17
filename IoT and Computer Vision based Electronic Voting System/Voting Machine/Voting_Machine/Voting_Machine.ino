#include <Wire.h>
#define alwaysHott 10
#define vote1 2
#define vote2 3
#define vote3 4
#define ledGreen 8
#define ledRed 7
#define dataIn 9
#define getIn 11

int getData, temp;
byte x = 0;

void setup() {
  Wire.begin();
  pinMode(alwaysHott, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(vote1, INPUT_PULLUP);
  pinMode(vote2, INPUT_PULLUP);
  pinMode(vote3, INPUT_PULLUP);
  pinMode(dataIn, INPUT_PULLUP);
  pinMode(getIn, INPUT_PULLUP);
  digitalWrite(alwaysHott, LOW);
  Serial.begin(9600);  
}

void loop() {
MAINLOOP();
}

void MAINLOOP()
{
      getData = 0;
    temp=1;
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, LOW);
    
    getData = digitalRead(dataIn);
    Serial.println(getData);

    while(getData==0 && temp==1)
    {
      if(digitalRead(vote1)==0)             //For Voter 1
        {
          x=1;
          Wire.beginTransmission(1);
          Wire.write(x);
          Wire.endTransmission();               
          digitalWrite(ledGreen, HIGH);
          delay(2000);
          temp=0;
        }
      if(digitalRead(vote2)==0)
        {
          x=2;
          Wire.beginTransmission(1);
          Wire.write(x);
          Wire.endTransmission();           //For Voter 2
          digitalWrite(ledGreen, HIGH);
          delay(2000);
          temp=0;
        }
      if(digitalRead(vote3)==0)
        {
          x=3;
          Wire.beginTransmission(1);
          Wire.write(x);
          Wire.endTransmission();           //For Voter 3
          digitalWrite(ledGreen, HIGH);
          delay(2000);
          temp=0;
        }
     }

     
     {
       if(digitalRead(vote1)==0)
        {
          digitalWrite(ledRed, HIGH);
          delay(2000);
        }
      if(digitalRead(vote2)==0)
        {
          digitalWrite(ledRed, HIGH);
          delay(2000);
        }
      if(digitalRead(vote3)==0)
        {
          digitalWrite(ledRed, HIGH);
          delay(2000);
        }
     }
}

