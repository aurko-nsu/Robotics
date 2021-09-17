#include <Servo.h>
#include <SPI.h>  
#include <Pixy.h>

Servo rotate_servo;
Servo base_servo;
Servo top_servo;
Servo grip;
Pixy pixy;
 
int x1 = 143, y1 = 20, x2, y2;
int temp = 0;
float distance;
  
void setup() {
  rotate_servo.attach(2);  // attaches the servo on pin 2 to the servo object
  base_servo.attach(3);    // attaches the servo on pin 3 to the servo object
  top_servo.attach(4);    // attaches the servo on pin 4 to the servo object
  grip.attach(5);         // attaches the servo on pin 5 to the servo object
  Serial.begin(9600);
  red_base_top();
  Serial.println("Starting...");
  pixy.init();            //Pixy-Mon initialize this part
}

void loop() {
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32]; 
  
  blocks = pixy.getBlocks();
  
  if (blocks)
  {
    i++;
    if (i%50==0)
    {
      for (j=0; j<blocks; j++)
      {
        if((pixy.blocks[j].signature)==1 || (pixy.blocks[j].signature)==2 || (pixy.blocks[j].signature)==3)
        {
          temp = 0;
          Serial.println("Detected");
          delay(2000);

          if((pixy.blocks[j].signature)==1) temp = 1;
          else if((pixy.blocks[j].signature)==2) temp = 2;
          else if((pixy.blocks[j].signature)==3) temp = 3;
          else{}
          
          sprintf(buf, "  Width: %d mm ", pixy.blocks[j].width-15);
          Serial.print(buf);
          Serial.print(" || ");
          sprintf(buf, "  Height: %d mm", pixy.blocks[j].height-15);
          Serial.println(buf);
          get_distance(j);
        
          if(((pixy.blocks[j].x) > 220) && ((pixy.blocks[j].x) < 250)) 
            {
              Serial.println("----------------------------Left");
              pick_left();
            }
          else if(((pixy.blocks[j].x) > 145) && ((pixy.blocks[j].x) < 165)) 
            {
              Serial.println("----------------------------Center");
              pick_center();
            }
          else if(((pixy.blocks[j].x) > 60) && ((pixy.blocks[j].x) < 90)) 
            {
              Serial.println("----------------------------Right");
              pick_right();
            }
          else 
            {
              Serial.println("----------------------------Base_Inner");
              red_base_top();
            }
        }
        else 
            {
              Serial.println("----------------------------Base_Outer");
              red_base_top();
            }
      }      
    }
  }  
}

void right_top()
{
  rotate_servo.write(37);
  base_servo.write(70);
  top_servo.write(10);
}

void right_down()
{
  rotate_servo.write(37);
  base_servo.write(128);
  top_servo.write(10);
}

void center_top()
{
  rotate_servo.write(50);
  base_servo.write(70);
  top_servo.write(10);
}

void center_down()
{
  rotate_servo.write(50);
  base_servo.write(128);
  top_servo.write(10);
}

void left_top()
{
  rotate_servo.write(64);
  base_servo.write(70);
  top_servo.write(10);
}

void left_down()
{
  rotate_servo.write(64);
  base_servo.write(128);
  top_servo.write(10);
}

void red_base_top()
{
  rotate_servo.write(1);
  base_servo.write(70);
  top_servo.write(10);
}

void green_base_top()
{
  rotate_servo.write(150);
  base_servo.write(70);
  top_servo.write(10);
}

void yellow_base_top()
{
  rotate_servo.write(100);
  base_servo.write(70);
  top_servo.write(10);
}

void pick_right()
{
  right_top();    delay(2000);  Serial.println("Top position hold");
  grip.write(60); delay(1000);  Serial.println("Grip Open");
  right_down();   delay(1000);  Serial.println("Moved to down");
  grip.write(100); delay(1000);  Serial.println("Object has taken");
  right_top();    delay(3000);  Serial.println("Moved back to top");
  
  if(temp==1){ red_base_top();     delay(1000);  Serial.println("Returned to base");}
  else if(temp==2){ yellow_base_top();     delay(1000);  Serial.println("Returned to base");}
  else if(temp==3){ green_base_top();     delay(1000);  Serial.println("Returned to base");}
  else{}
  
  grip.write(60); delay(1000);  Serial.println("Released the object");
}

void pick_center()
{
  center_top();   delay(2000);  Serial.println("Top position hold");
  grip.write(60); delay(1000);  Serial.println("Grip Open");
  center_down();  delay(1000);  Serial.println("Moved to down");
  grip.write(100); delay(1000);  Serial.println("Object has taken");
  center_top();   delay(3000);  Serial.println("Moved back to top");

  if(temp==1){ red_base_top();     delay(1000);  Serial.println("Returned to base");}
  else if(temp==2){ yellow_base_top();     delay(1000);  Serial.println("Returned to base");}
  else if(temp==3){ green_base_top();     delay(1000);  Serial.println("Returned to base");}
  else{}
  
  grip.write(60); delay(1000);  Serial.println("Released the object");
}

void pick_left()
{
  left_top();     delay(2000); Serial.println("Top position hold");
  grip.write(60); delay(2000); Serial.println("Grip Open");
  left_down();    delay(1000); Serial.println("Moved to down");
  grip.write(120); delay(2000); Serial.println("Object has taken");
  left_top();     delay(3000); Serial.println("Moved back to top");

  if(temp==1){ red_base_top();     delay(1000);  Serial.println("Returned to base");}
  else if(temp==2){ yellow_base_top();     delay(1000);  Serial.println("Returned to base");}
  else if(temp==3){ green_base_top();     delay(1000);  Serial.println("Returned to base");}
  else{}
  
  grip.write(60); delay(1000); Serial.println("Released the object");
}

void get_distance(int m)
{
  x2 = (pixy.blocks[m].x); 
  y2 = (pixy.blocks[m].y);
  distance = sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
  
  Serial.print("  Distance ≈ ");
  Serial.print(distance, 2);
  Serial.println("mm");
}
