#include <Wire.h> 
#include <SoftwareSerial.h>

#define slaveAddress 1
#define slaveESP 2
SoftwareSerial mySerial(7, 6);    // RX, TX
SoftwareSerial espSerial(8, 9);   // RX, TX

char dataArray[5];
char arr[5];
char buffer[50];
char tempo[5];
char stud[4];
char m[4];

int text_delay = 7000;
float temperature;
int student;
int mask;
int person = 0;

float temperaturef;
int temp_f;
    
void setup() {
  Wire.begin(slaveAddress);
  Serial.begin(9600);
  Wire.onReceive(receiveEvent);
  mySerial.begin(9600);
  Serial.println("Initializing..."); 
  delay(1000);
  mySerial.println("AT");
  updateSerial();
  espSerial.begin(9600);  
}

void loop() {
    if(person==1)
      {
        updateSerial();
        mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
        updateSerial();
        sprintf(buffer, "Fuad Rahman(1731482643) has signed in, Temperature is %d dg.F", temp_f);
        mySerial.println("AT+CMGS=\"+8801767467405\"");
        updateSerial();
        mySerial.print(buffer); //text content
        updateSerial();
        mySerial.write(26);

        delay(text_delay);
        updateSerial();

        mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
        updateSerial();
        mySerial.println("AT+CMGS=\"+8801723677755\"");
        updateSerial();
        sprintf(buffer, "Fuad Rahman(1731482643) has signed in, Temperature is %d dg.F", temp_f);
        mySerial.print(buffer); //text content
        updateSerial();
        mySerial.write(26);
        person = 0;
      }
   else if(person==2)
      {
        updateSerial();
        mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
        updateSerial();
        sprintf(buffer, "Parika Samawat(1711617043) has signed in, Temperature is %d dg.F", temp_f);
        mySerial.println("AT+CMGS=\"+8801767467405\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
        updateSerial();
        mySerial.print(buffer);
        updateSerial();
        mySerial.write(26);
                
        delay(text_delay);
        updateSerial();
        
        mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
        updateSerial();
        mySerial.println("AT+CMGS=\"+8801711431781\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
        updateSerial();
        sprintf(buffer, "Parika Samawat(1711617043) has signed in, Temperature is %d dg.F", temp_f);
        mySerial.print(buffer); //text content
        updateSerial();
        mySerial.write(26);

        person = 0;
      }
  else if(person==3)
      {
        updateSerial();
        mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
        updateSerial();
        sprintf(buffer, "Binoy Saha(1722073642) has signed in, Temperature is %d dg.F", temp_f);
        mySerial.println("AT+CMGS=\"+8801767467405\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
        updateSerial();
        mySerial.print(buffer); //text content
        updateSerial();
        mySerial.write(26);

        delay(text_delay);
        updateSerial();

        mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
        updateSerial();
        mySerial.println("AT+CMGS=\"+8801689832150\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
        updateSerial();
        sprintf(buffer, "Binoy Saha(1722073642) has signed in, Temperature is %d dg.F", temp_f);
        mySerial.print(buffer); //text content
        updateSerial();
        mySerial.write(26);

        person = 0;
      }
    else if(person==4)
      {
        updateSerial();
        mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
        updateSerial();
        sprintf(buffer, "MD.Naeem Sana(1721088042) has signed in, Temperature is %d dg.F", temp_f);
        mySerial.println("AT+CMGS=\"+8801767467405\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
        updateSerial();
        mySerial.print(buffer); //text content
        updateSerial();
        mySerial.write(26);

        delay(text_delay);
        updateSerial();

        mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
        updateSerial();
        mySerial.println("AT+CMGS=\"+8801793447018\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
        updateSerial();
        sprintf(buffer, "MD.Naeem Sana(1721088042) has signed in, Temperature is %d dg.F", temp_f);
        mySerial.print(buffer); //text content
        updateSerial();
        mySerial.write(26);

        person = 0;
      }
   else if(person==5)
      {
        updateSerial();
        mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
        updateSerial();
        sprintf(buffer, "Afrida Jahan(1711251642) has signed in, Temperature is %d dg.F", temp_f);
        mySerial.println("AT+CMGS=\"+8801767467405\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
        updateSerial();
        mySerial.print(buffer); //text content
        updateSerial();
        mySerial.write(26);
        
        delay(text_delay);
        updateSerial();
        
        mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
        updateSerial();
        mySerial.println("AT+CMGS=\"+8801720802672\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
        sprintf(buffer, "Afrida Jahan(1711251642) has signed in, Temperature is %d dg.F", temp_f);
        updateSerial();        
        mySerial.print(buffer); //text content
        updateSerial();
        mySerial.write(26);

        person = 0;
      }else{}
}


void receiveEvent(int howmany) //howmany = Wire.write()executed by Master
{
  for(int i=0; i<howmany; i++)
  {
    dataArray[i] = Wire.read();
  }  
  
  if(dataArray[4] == 'a')
    {
      for(int i=0 ; i<4 ; i++)
        tempo[i] = dataArray[i];
      
      int temp = atoi(tempo);
      temperature = temp/100.00;
      temperaturef = ((temperature*1.8)+32.00);
      temp_f = 0;
      temp_f = temperaturef;
    }
    
  else if(dataArray[4] == 'b')
    {
        stud[0] = dataArray[0];
      
      int temp = atoi(stud);
      student = temp;
    }
    
  else if(dataArray[4] == 'c')
    {
        m[0] = dataArray[0];
      
      int temp = atoi(m);
      mask = temp;
      
      int data = temp_f*10;
      data = data+student;
      data = data*10;
      data = data+mask;
      
      person = student;
      espSerial.print(data);delay(500);
      
    }else{}
}   




void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
