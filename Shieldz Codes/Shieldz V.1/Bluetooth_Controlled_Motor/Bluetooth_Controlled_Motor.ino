#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);   // (RX_Pin, TX_Pin)


/*Defining Arduino Pins*/
#define leftMotorPWM 5
#define leftMotForward 6
#define leftMotBackward 7
#define rightMotForward 8
#define rightMotBackward 9
#define rightMotorPWM 10


/*Motor Speed defines this two variable. Value of these two variables varies 0~255 */
int leftMotorSpeed = 255;
int rightMotorSpeed = 255;

void setup()
{
  pinMode(leftMotorPWM, OUTPUT);
  pinMode(leftMotForward, OUTPUT);
  pinMode(leftMotBackward, OUTPUT);
  pinMode(rightMotForward, OUTPUT);
  pinMode(rightMotBackward, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
}


void loop()
{
  if (mySerial.available() > 0)
  {
    char x = mySerial.read();

    if (x == 'f') //front
    {
      Serial.println("Front");
      analogWrite(leftMotorPWM, leftMotorSpeed);
      analogWrite(rightMotorPWM, rightMotorSpeed);
      digitalWrite(leftMotForward , HIGH);
      digitalWrite(leftMotBackward , LOW);
      digitalWrite(rightMotForward , HIGH);
      digitalWrite(rightMotBackward , LOW);
      delay(100);
    }

    if (x == 'b') //back
    {
      Serial.println("Back");
      analogWrite(leftMotorPWM, leftMotorSpeed);
      analogWrite(rightMotorPWM, rightMotorSpeed);
      digitalWrite(leftMotForward , LOW);
      digitalWrite(leftMotBackward , HIGH);
      digitalWrite(rightMotForward , LOW);
      digitalWrite(rightMotBackward , HIGH);
      delay(100);
    }

    if (x == 'r') //right
    {
      Serial.println("Right");
      analogWrite(leftMotorPWM, leftMotorSpeed);
      analogWrite(rightMotorPWM, rightMotorSpeed);
      digitalWrite(leftMotForward , HIGH);
      digitalWrite(leftMotBackward , LOW);
      digitalWrite(rightMotForward , LOW);
      digitalWrite(rightMotBackward , HIGH);
      delay(100);
    }

    if (x == 'l') //left
    {
      Serial.println("Left");
      analogWrite(leftMotorPWM, leftMotorSpeed);
      analogWrite(rightMotorPWM, rightMotorSpeed);
      digitalWrite(leftMotForward , LOW);
      digitalWrite(leftMotBackward , HIGH);
      digitalWrite(rightMotForward , HIGH);
      digitalWrite(rightMotBackward , LOW);
      delay(100);
    }

    if (x == '0') //stop(default)
    {
      Serial.println("Stop");
      analogWrite(leftMotorPWM, leftMotorSpeed);
      analogWrite(rightMotorPWM, rightMotorSpeed);
      digitalWrite(leftMotForward , LOW);
      digitalWrite(leftMotBackward , LOW);
      digitalWrite(rightMotForward , LOW);
      digitalWrite(rightMotBackward , LOW);
      delay(100);
    }

  }


}
