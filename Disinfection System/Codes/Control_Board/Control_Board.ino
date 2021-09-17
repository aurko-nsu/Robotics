#include <NewPing.h>
#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MLX90614.h>
#include <SPI.h>
#include <MFRC522.h>

const int LDR = A4;

#define leftMotF 6
#define leftMotB 7

#define slaveAddress 1
#define box_led 4
#define servo_pin 8
#define trig 3
#define echo 2
#define row 20
#define column 4
#define SS_PIN 10
#define RST_PIN 9
#define I2C_ADDR 0x27

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
NewPing sonar(trig, echo, 200);
Servo myservo;
LiquidCrystal_I2C lcd(0x26, row, column);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
int servo_angle=180;
long duration = 0, distance = 0;
float ambient = 0, temp = 0 , tempf = 0;
float tempStore = 0;
int student = 0;
int mask = 0 ;
char job;
char arr[] = "";
int ldr_val = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  myservo.attach(servo_pin);
  myservo.write(180);
  mlx.begin();
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(((row-8)/2),0);
  lcd.print("Starting");
  delay(1000);
  lcd.clear();
  SPI.begin();
  rfid.PCD_Init();
  pinMode(box_led, OUTPUT);
  pinMode(leftMotF,OUTPUT);
  pinMode(leftMotB,OUTPUT);
}

void loop() {
  student = 0;

  lcd.setCursor(((row-12)/2),0); lcd.print("Swap Your ID");
  lcd.setCursor(((row-13)/2),1); lcd.print("on the reader");
  card_check();

  if(student!=0)
  {
    lcd.clear();
    lcd.setCursor(((row-14)/2),0);
    lcd.print("Wash Your Hand");
    digitalWrite(box_led , HIGH);
    Sonar();
//------------------------------------------------------------------from here
    ldr_val = analogRead(LDR);
    Serial.print("Distance 1:  ");  Serial.println(distance);
    while(!((ldr_val<825) && (distance<5)))
    {
      Serial.println("In loop");
      Sonar();
      ldr_val = analogRead(LDR);
      Serial.print("Distance: ");  Serial.print(distance);
      Serial.print("|| LDR: ");  Serial.println(ldr_val);
    }
    Sonar();
    
      Serial.print("Distance: ");  Serial.print(distance);
      Serial.print("|| LDR:");  Serial.println(ldr_val);
    
    lcd.clear();
    lcd.setCursor(((row-11)/2),0);
    lcd.print("Spraying...");
    digitalWrite(leftMotF , LOW);
    digitalWrite(leftMotB , HIGH);
    delay(1000);
    digitalWrite(leftMotF , LOW);
    digitalWrite(leftMotB , LOW);
    lcd.clear();
    lcd.setCursor(((row-8)/2),0);
    lcd.print("Complete"); delay(3000); lcd.clear();
    digitalWrite(box_led , LOW);


//------------------------------------------------------------------till here
      float tempT = Temp();
      int count = 0;
      tempT = tempT + 2.00;
      
      lcd.setCursor(((row-15)/2),0); lcd.print("Place Your Hand");
      lcd.setCursor(((row-13)/2),1); lcd.print("To Check Temp");
        
      while(!(tempT < temp))
      {
        Temp();
      }
      lcd.clear();
      for(int i = 0 ; i < 5 ; i++)
      {
        lcd.setCursor(((row-8)/2),1); lcd.print("Checking");
        lcd.setCursor(((row-2)/2),2); lcd.print(5-i);
        delay(1000);
        lcd.clear();
        tempStore = Temp();
      }
        tempf = ((tempStore*1.8)+32.00);
        
        lcd.setCursor(((row-9)/2),0); lcd.print("Your Temp");
        lcd.setCursor(((row-5)/2),1); lcd.print(tempf);
        lcd.setCursor(13,1); lcd.print("F");
        delay(5000);
        lcd.clear();

      mask = get_mask_status();
      
      Send(temp , student , mask);
      
        Serial.print("Mask  "); Serial.println(mask);
        Serial.print("Temperature  ");  Serial.println(temp);
        
      if((mask==1) && (temp < 38.00))
        {
          lcd.setCursor(((row-12)/2),0); lcd.print("Gate Opening");
          myservo.write(90);
          delay(5000);
          lcd.clear();
          myservo.write(180);
        }
      else
      {
        lcd.setCursor(((row-5)/2),0); lcd.print("Sorry");
        if(temp > 38.00)
          {
            lcd.setCursor(((row-14)/2),1); lcd.print("Your Temp High");
            lcd.setCursor(((row-14)/2),2); lcd.print("Check Covid-19");
            delay(5000);
          }
        else
          {
            lcd.setCursor(((row-16)/2),1); lcd.print("No Mask Detected");
            lcd.setCursor(((row-14)/2),2); lcd.print("Please Mask On");
            delay(5000);
          }
          lcd.clear();
      }
      
  }  

}

void Sonar()
{
  distance=0;
  distance = sonar.ping_cm();
  return distance;
}

float Temp()
{
  ambient = 0;
  temp = 0;
  ambient = mlx.readAmbientTempC();
  temp = mlx.readObjectTempC();
  return temp;
}

void card_check()
{
  if ( ! rfid.PICC_IsNewCardPresent()) return;
  if ( ! rfid.PICC_ReadCardSerial()) return;

//-------------------------------------------Student 1
  if ((rfid.uid.uidByte[0]== 82) && 
      (rfid.uid.uidByte[1]== 13) && 
      (rfid.uid.uidByte[2]== 218) && 
      (rfid.uid.uidByte[3]== 26)) 
  {
    student = 1;
    lcd.clear();
    lcd.setCursor(((row-5)/2),0);
    lcd.print("Hello");
    lcd.setCursor(((row-11)/2),1);
    lcd.print("Fuad Rahman"); delay(3000); lcd.clear();
  }

//-------------------------------------------Student 2
  else if ((rfid.uid.uidByte[0]== 151) && 
      (rfid.uid.uidByte[1]== 91) && 
      (rfid.uid.uidByte[2]== 74) && 
      (rfid.uid.uidByte[3]== 228)) 
  {
    student = 2;
    lcd.clear();
    lcd.setCursor(((row-5)/2),0);
    lcd.print("Hello");
    lcd.setCursor(((row-14)/2),1);
    lcd.print("Parika Samawat"); delay(3000); lcd.clear();
  }

//-------------------------------------------Student 3
  else if ((rfid.uid.uidByte[0]== 71) && 
      (rfid.uid.uidByte[1]== 158) && 
      (rfid.uid.uidByte[2]== 75) && 
      (rfid.uid.uidByte[3]== 228)) 
  {
    student = 3;
    lcd.clear();
    lcd.setCursor(((row-5)/2),0);
    lcd.print("Hello");
    lcd.setCursor(((row-10)/2),1);
    lcd.print("Binoy Saha"); delay(3000); lcd.clear();
  }

//-------------------------------------------Student 4
  else if ((rfid.uid.uidByte[0]== 135) && 
      (rfid.uid.uidByte[1]== 81) && 
      (rfid.uid.uidByte[2]== 26) && 
      (rfid.uid.uidByte[3]== 228)) 
  {
    student = 4;
    lcd.clear();
    lcd.setCursor(((row-5)/2),0);
    lcd.print("Hello");
    lcd.setCursor(((row-14)/2),1);
    lcd.print("MD. Naeem Sana"); delay(3000); lcd.clear();
  }


//-------------------------------------------Student 5
  else if ((rfid.uid.uidByte[0]== 242) && 
      (rfid.uid.uidByte[1]== 202) && 
      (rfid.uid.uidByte[2]== 127) && 
      (rfid.uid.uidByte[3]== 12)) 
  {
    student = 5;
    lcd.clear();
    lcd.setCursor(((row-5)/2),0);
    lcd.print("Hello");
    lcd.setCursor(((row-12)/2),1);
    lcd.print("Afrida Jahan"); delay(3000); lcd.clear();
  }


//-------------------------------------------Wrong 
  else 
  { 
    lcd.clear();   
    lcd.setCursor(((row-5)/2),0);
    lcd.print("Sorry");
    lcd.setCursor(((row-8)/2),1);
    lcd.print("Wrong ID"); delay(3000); lcd.clear();
  }
  
  rfid.PICC_HaltA(); rfid.PCD_StopCrypto1();
}
bool get_mask_status(){}

//Send(temp , student , mask);
void Send(float t1 , int st , int m)
{
  {
    for(int i=0 ; i<6 ; i++)
      arr[i] = '0';
    int temp = t1*100;
    snprintf(arr , 5 , "%d" , temp);
    arr[4] = 'a';

    Wire.beginTransmission(slaveAddress); 
    for (int i=0; i<5; i++)
    {
      Wire.write(arr[i]);  
    }
    Wire.endTransmission();
  }
  delay(100);

  {
    for(int i=0 ; i<6 ; i++)
      arr[i] = '0';
    int temp = st;
    snprintf(arr , 2 , "%d" , temp);
    arr[4] = 'b';

    Wire.beginTransmission(slaveAddress); 
    for (int i=0; i<5; i++)
    {
      Wire.write(arr[i]);  
    }
    Wire.endTransmission();
  }
  delay(100);

  {
    for(int i=0 ; i<6 ; i++)
      arr[i] = '0';
    int temp = m;
    snprintf(arr , 2 , "%d" , temp);
    arr[4] = 'c';

    Wire.beginTransmission(slaveAddress); 
    for (int i=0; i<5; i++)
    {
      Wire.write(arr[i]);  
    }
    Wire.endTransmission();
  }
  delay(100);
}
