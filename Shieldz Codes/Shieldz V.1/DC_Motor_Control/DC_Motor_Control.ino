
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
}


void loop()
{
      analogWrite(leftMotorPWM, leftMotorSpeed);
      analogWrite(rightMotorPWM, rightMotorSpeed);
      digitalWrite(leftMotForward , HIGH);
      digitalWrite(leftMotBackward , LOW);
      digitalWrite(rightMotForward , HIGH);
      digitalWrite(rightMotBackward , LOW);

      delay(5000);

      analogWrite(leftMotorPWM, leftMotorSpeed);
      analogWrite(rightMotorPWM, rightMotorSpeed);
      digitalWrite(leftMotForward , LOW);
      digitalWrite(leftMotBackward , HIGH);
      digitalWrite(rightMotForward , LOW);
      digitalWrite(rightMotBackward , HIGH);

      delay(5000);

      analogWrite(leftMotorPWM, leftMotorSpeed);
      analogWrite(rightMotorPWM, rightMotorSpeed);
      digitalWrite(leftMotForward , HIGH);
      digitalWrite(leftMotBackward , LOW);
      digitalWrite(rightMotForward , LOW);
      digitalWrite(rightMotBackward , HIGH);

      delay(5000);

      analogWrite(leftMotorPWM, leftMotorSpeed);
      analogWrite(rightMotorPWM, rightMotorSpeed);
      digitalWrite(leftMotForward , LOW);
      digitalWrite(leftMotBackward , HIGH);
      digitalWrite(rightMotForward , HIGH);
      digitalWrite(rightMotBackward , LOW);

      delay(5000);
}
