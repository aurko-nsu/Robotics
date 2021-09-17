/*Defining Trig and Echo pin of Sonar in Arduino
In v.1 board "Echo" pin is 11 and "Trig" pin is 12*/

#define echo 3
#define trig 2

long duration;
int distance;

void setup() {
pinMode(trig, OUTPUT);
pinMode(echo, INPUT);
Serial.begin(9600); 
}

void loop() {

digitalWrite(trig, LOW);
delayMicroseconds(2);
digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);
duration = pulseIn(echo, HIGH);
distance = duration*0.034/2;

Serial.print("Distance: ");
Serial.print(distance);
Serial.println(" cm");
}
