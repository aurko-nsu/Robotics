#include <ESP8266WiFi.h>

String apiKey = "8USANABEIAF4TKD0";     //API key from ThingSpeak
const char *ssid =  "Appnap";           //wifi ssid
const char *pass =  "Appnap@2016";      //wifi password
const char* server = "api.thingspeak.com";
WiFiClient client;

int received;
int temp, student, mask;
char buffer[50];
char arr[5];
char arr2[5];

char nam[20];
char id[10];
char phone[20];
char tempStat[10];
char maskStat[10];

int a=0 , b=0, c=0 , i=0;
void setup() 
{
  Serial.begin(9600);
  Serial.println("Connecting to ");
   Serial.println(ssid); 
   WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) 
 {
        delay(500);
        Serial.print(".");
 }
  Serial.println("");
  Serial.println("WiFi connected");
    while (!Serial) {;}
}

void loop() 
{ 
 temp = 0;
 i = 0;
  if(Serial.available()) 
    {
      arr[i] = Serial.read();
      i++;
      temp = 1;
    }      

    if(temp == 1)
      {
        arr2[a] = arr[0];
        a++;

        if(a==4)
        {
          for(i=0 ; i<4 ; i++)
            Serial.print(arr2[i]);
        Serial.println();
        a=0;

        received = atoi(arr2);
        mask = received % 10; 
        received = received / 10;
        student = received % 10;
        temp = received / 10;

        if (client.connect(server,80)) 
          {          
                 String postStr = apiKey;
                 if(student == 1)
                  {
                     postStr +="&field1=";
                     postStr += String("Fuad Rahman");
                     postStr +="&field2=";
                     postStr += String("1731482643");
                     postStr +="&field3=";
                     postStr += String("01723677755");
                     postStr +="&field4=";
                     postStr += String(temp);
                     postStr +="&field5=";
                     if(mask==1)
                     postStr += String("Ok");
                     else
                     postStr += String("Not Ok");
                     postStr +="&field6=";
                     postStr += String("SNS1, PNG, SYE, KSS");
                     postStr += "\r\n\r\n\r\n\r\n\r\n\r\n";
                  }
                  else if(student == 2)
                  {
                     postStr +="&field1=";
                     postStr += String("Parika Samawat");
                     postStr +="&field2=";
                     postStr += String("1711617043");
                     postStr +="&field3=";
                     postStr += String("01711431781");
                     postStr +="&field4=";
                     postStr += String(temp);
                     postStr +="&field5=";
                     if(mask==1)
                     postStr += String("Ok");
                     else
                     postStr += String("Not Ok");
                     postStr +="&field6=";
                     postStr += String("SRB, IQR, HZR, MHK3");
                     postStr += "\r\n\r\n\r\n\r\n\r\n\r\n";
                  }
                  else if(student == 3)
                  {
                     postStr +="&field1=";
                     postStr += String("Binoy Saha");
                     postStr +="&field2=";
                     postStr += String("1722073642");
                     postStr +="&field3=";
                     postStr += String("01689832150");
                     postStr +="&field4=";
                     postStr += String(temp);
                     postStr +="&field5=";
                     if(mask==1)
                     postStr += String("Ok");
                     else
                     postStr += String("Not Ok");
                     postStr +="&field6=";
                     postStr += String("ATA, SSU, DRS, ABO, SBS");
                     postStr += "\r\n\r\n\r\n\r\n\r\n\r\n";
                  }
                  else if(student == 4)
                  {
                     postStr +="&field1=";
                     postStr += String("MD. Naeem Sana");
                     postStr +="&field2=";
                     postStr += String("1721088042");
                     postStr +="&field3=";
                     postStr += String("01793447018");
                     postStr +="&field4=";
                     postStr += String(temp);
                     postStr +="&field5=";
                     if(mask==1)
                     postStr += String("Ok");
                     else
                     postStr += String("Not Ok");
                     postStr +="&field6=";
                     postStr += String("EVM, SR3, FKR");
                     postStr += "\r\n\r\n\r\n\r\n\r\n\r\n";
                  }
                  else if(student == 5)
                  {
                     postStr +="&field1=";
                     postStr += String("Afrida Jahan");
                     postStr +="&field2=";
                     postStr += String("1711251642");
                     postStr +="&field3=";
                     postStr += String("01720802672");
                     postStr +="&field4=";
                     postStr += String(temp);
                     postStr +="&field5=";
                     if(mask==1)
                     postStr += String("Ok");
                     else
                     postStr += String("Not Ok");
                     postStr +="&field6=";
                     postStr += String("SRB, SBS, MFJ, PNG, KLQ");
                     postStr += "\r\n\r\n\r\n\r\n\r\n\r\n";
                  }else{}
                 client.print("POST /update HTTP/1.1\n");
                 client.print("Host: api.thingspeak.com\n");
                 client.print("Connection: close\n");
                 client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                 client.print("Content-Type: application/x-www-form-urlencoded\n");
                 client.print("Content-Length: ");
                 client.print(postStr.length());
                 client.print("\n\n");
                 client.print(postStr);
        
                 Serial.println("Send to Online Cloud.");
            }
                  client.stop();
         
                  Serial.println("Waiting...");
          
          // thingspeak needs minimum 15 sec delay between updates
          delay(1000);
        }
        
      }
      for(i=0 ; i<6 ; i++)
          arr[i] = 0;

}
