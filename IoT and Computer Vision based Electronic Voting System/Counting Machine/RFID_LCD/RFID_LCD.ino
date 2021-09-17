#include <SPI.h>
#include <Wire.h> 
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9
#define pulsePin 2

MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

int x,a,v1,v2,v3;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  lcd.begin(16, 2);
  mfrc522.PCD_Init();
  pinMode(pulsePin, OUTPUT);
}

void loop() {
 MAINLOOP();
}

void MAINLOOP()
{  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("<---NSU:EVM--->");
  if ( ! mfrc522.PICC_IsNewCardPresent()){return;}
  if ( ! mfrc522.PICC_ReadCardSerial()){return;}
  String content= "";
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }  
  content.toUpperCase();
  
  /*<-----------------Authorization----------------->*/
  if (content.substring(1) == "1D D4 5E 83")
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Granted");
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("Wait a moment...");
    delay(2000);
    digitalWrite(pulsePin, LOW); 
    delay(200);  
  }
  
  else
  {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Unauthorized");
    lcd.setCursor(5, 1);
    lcd.print("Access!");
    delay(3000);
  }
  digitalWrite(pulsePin, HIGH);
}



/*
 
  if(x>0 && v1==0 && v2==0)
  {
    int temp1 = x;
    Serial.println("\n\n\n");
    Serial.print("\t\t");
    Serial.println("#############################################");
    Serial.println("");Serial.println("");
    Serial.print("\t\t");
    Serial.print("          ");
    Serial.print("Voter 1 :: ");
    Serial.print(temp1);
    Serial.println("Votes");
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Vote 1");
    x=0;
    v1=1;
  }
  if(x>0 && v1==1 && v2==0)
  {
    int temp1 = x;
    Serial.print("\t\t");
    Serial.print("          ");
    Serial.print("Voter 2 :: ");
    Serial.print(temp1);
    Serial.println("Votes");
    x=0;
    v2=1;
    v3=0;    
  }
  if(x>0 && v3==0)
  {
    int temp1 = x;
    Serial.print("\t\t");
    Serial.print("          ");
    Serial.print("Voter 3 :: ");
    Serial.print(temp1);
    Serial.println("Votes");
    Serial.println("");Serial.println("");
    Serial.print("\t\t");
    Serial.println("#############################################");
    Serial.print("\n\n");
    x=0; 
    v3=1;
    v2=0;v1=0;   
  }


*/
 
