#include <SPI.h>
#include <Wire.h> 
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Fingerprint.h>
SoftwareSerial mySerial(24, 22);
#define getPin 9

#define SS_PIN 53
#define RST_PIN 4

#define DataPass 8

int fingerData, masterPass;

MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial1);


void setup() {
  pinMode(getPin, INPUT_PULLUP);
  pinMode(DataPass, OUTPUT);
  Wire.begin();
  Serial.begin(9600);
  Serial1.begin(9600);
  SPI.begin();
  lcd.begin(16, 2);
  mfrc522.PCD_Init();
  while (!Serial);
  delay(100);
  Serial.println("NSU:EVM finger detect test");
  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("NSU:EVM Found fingerprint sensor!");
  } else {
    Serial.println("NSU:EVM Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }
  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");
}

void loop() {
MAINLOOP();
//int temp = getFingerprintIDez();
//Serial.println(temp);
//delay(100);
//Serial.println(digitalRead(getPin));
//delay(200);

}

void MAINLOOP()
{   
  digitalWrite(DataPass, HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan your tags");
  if ( ! mfrc522.PICC_IsNewCardPresent()){return;}
  if ( ! mfrc522.PICC_ReadCardSerial()){return;}
  String content= "";
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  
  /*<-----------------Voter 1----------------->*/
  if (content.substring(1) == "E4 25 57 1E")
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Voter Detected");
    lcd.setCursor(0, 1);
    lcd.print("Mahmudur Rashid");
    delay(2000);
    
    int tempFingerNumber=0;
    int a = 0;
    
    while(a!=1)
    {
      lcd.setCursor(0, 0);
      lcd.print("Put your Thumb");
      lcd.setCursor(0, 1);
      lcd.print("On the scanner");
      if(getFingerprintIDez()==2)
      {
        a=1;
        tempFingerNumber = 2;
      }
   }   
 
 {
     if(tempFingerNumber==2 && digitalRead(getPin)!=1)
    {
      digitalWrite(DataPass, LOW);
      lcd.setCursor(0, 0);
      lcd.print("Correct Finger!");
      delay(3000);
      masterPass = 0;
    }
    else
    {
      lcd.setCursor(1, 0);
      lcd.print("Wrong Finger!");
      delay(1000);
    }
  }
}

/*<-----------------Voter 2----------------->*/

else if (content.substring(1) == "33 3C E0 2B")
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Voter Detected");
    lcd.setCursor(0, 1);
    lcd.print("Md Uaday");
    delay(2000);
    
    int tempFingerNumber=0;
    int a = 0;
    
    while(a!=1)
    {
      lcd.setCursor(0, 0);
      lcd.print("Put your Thumb");
      lcd.setCursor(0, 1);
      lcd.print("On the scanner");
      if(getFingerprintIDez()==1)
      {
        a=1;
        tempFingerNumber = 1;
      }
   }   
 
 {
     if(tempFingerNumber==1 && digitalRead(getPin)!=1)
    {
      lcd.setCursor(0, 0);
      lcd.print("Correct Finger!");
      delay(3000);
    }
    else
    {
      lcd.setCursor(1, 0);
      lcd.print("Wrong Finger!");
      delay(1000);
    }
  }
}

/*<-----------------Voter 3----------------->*/

else if (content.substring(1) == "B4 34 04 1E")
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Voter Detected");
    lcd.setCursor(0, 1);
    lcd.print("Md Sujon");
    delay(2000);
    
    int tempFingerNumber=0;
    int a = 0;
    
    while(a!=1)
    {
      lcd.setCursor(0, 0);
      lcd.print("Put your Thumb");
      lcd.setCursor(0, 1);
      lcd.print("On the scanner");
      if(getFingerprintIDez()==3)
      {
        a=1;
        tempFingerNumber = 3;
      }
   }   
 
 {
     if(tempFingerNumber==3 && digitalRead(getPin)!=1)
    {
      lcd.setCursor(0, 0);
      lcd.print("Correct Finger!");
      delay(3000);
    }
    else
    {
      lcd.setCursor(1, 0);
      lcd.print("Wrong Finger!");
      delay(1000);
    }
  }
}
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wrong Voter");
    lcd.setCursor(0, 1);
    lcd.print("Contact with PO");
    delay(3000);
  }

}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  fingerData = finger.fingerID;
  return fingerData; 
}
