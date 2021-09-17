#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#define pulsePin 8

File myFile;
String LastValue1, LastValue2, LastValue3;
int lastVote1, lastVote2, lastVote3,x,a;

void setup() {
  pinMode(pulsePin, INPUT_PULLUP);
  Wire.begin(1);
  Serial.begin(9600);
  while (!Serial){;}
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  Read();
  Wire.onReceive(receiveEvent);
}

void loop() {  
//Serial.println(digitalRead(pulsePin));
//delay(200);

MAINLOOP();
}

void MAINLOOP()
{
    
  if(x==1)
  {
    myFile = SD.open("voter1.txt", FILE_WRITE);
      if (myFile) {
        Serial.print("Voting 1...");
        int tempVote = lastVote1++;
        myFile.println(lastVote1++);
        myFile.close();
        delay(1500);
        Serial.println("Voting 1 Done.");
      }else {
      Serial.println("error opening test.txt");
    }
    x=0;
  }
  
  if(x==2)
  {
    myFile = SD.open("voter2.txt", FILE_WRITE);
      if (myFile) {
        Serial.print("Voting 2...");
        int tempVote = lastVote2++;
        myFile.println(lastVote2++);
        myFile.close();
        delay(1500);
        Serial.println("Voting 2 Done.");
      }else {
      Serial.println("error opening test.txt");
    }
    x=0;
  }

  if(x==3)
  {
    myFile = SD.open("voter3.txt", FILE_WRITE);
      if (myFile) {
        Serial.print("Voting 3...");
        int tempVote = lastVote3++;
        myFile.println(lastVote3++);
        myFile.close();
        delay(1500);
        Serial.println("Voting 3 Done.");
      }else {
      Serial.println("error opening test.txt");
    }
    x=0;
  }

  if(digitalRead(pulsePin)==0)
  {
    Read();
    Serial.println("\n\n\n");
    Serial.print("\t\t");
    Serial.println("#############################################");
    Serial.println("");Serial.println("");
    Serial.print("\t\t");
    Serial.print("          ");
    Serial.print("(1) Alif :: ");
    Serial.print(LastValue1);
    Serial.println("Votes");
    
    Serial.print("\t\t");
    Serial.print("          ");
    Serial.print("(2) Sumon :: ");
    Serial.print(LastValue2);
    Serial.println("Votes");

    Serial.print("\t\t");
    Serial.print("          ");
    Serial.print("(3) Ridoy :: ");
    Serial.print(LastValue3);
    Serial.println("Votes");
    Serial.println("");Serial.println("");
    Serial.print("\t\t");
    Serial.println("#############################################");
    Serial.print("\n\n");
  }

}

void Read()
{
   {
    myFile = SD.open("voter1.txt");
    if (myFile) {
      while (myFile.available()) {
        LastValue1 = myFile.readStringUntil('\n');
      }
      Serial.print("Final Data: ");
      Serial.println(LastValue1);
      myFile.close();
      lastVote1 = LastValue1.toInt();
      Serial.print("Voter 1: ");
      Serial.println(lastVote1);
    } else {
      Serial.println("error opening test.txt");
    }
  }

  {
    myFile = SD.open("voter2.txt");
    if (myFile) {
      while (myFile.available()) {
        LastValue2 = myFile.readStringUntil('\n');
      }
      Serial.print("Final Data: ");
      Serial.println(LastValue2);
      myFile.close();
      lastVote2 = LastValue2.toInt();
      Serial.print("Voter 2: ");
      Serial.println(lastVote2);
    } else {
      Serial.println("error opening test.txt");
    }
  }

  {
    myFile = SD.open("voter3.txt");
    if (myFile) {
      while (myFile.available()) {
        LastValue3 = myFile.readStringUntil('\n');
      }
      Serial.print("Final Data: ");
      Serial.println(LastValue3);
      myFile.close();
      lastVote3 = LastValue3.toInt();
      Serial.print("Voter 3: ");
      Serial.println(lastVote3);
    } else {
      Serial.println("error opening test.txt");
    }
  }
}

void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
  return x;
}
