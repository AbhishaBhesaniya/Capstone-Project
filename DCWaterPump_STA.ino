#include <ESP8266WiFi.h>



String str ;
int sensor_type = 03;
int sensor_no = 01;
int no_of_data = 01;
uint8_t DCPin = 5;
int DCPump_State = 0;
void data(int data1, int data2);
// Initialize DHT sensor.


const char* ssid = "TechFarm";
const char* password = "Techfarm@123";

int             serverPort  = 1010;
IPAddress       server(192,168,4,1);
WiFiClient      client;

void setup() {
  
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(9600);
 
  pinMode(DCPin, OUTPUT);
  digitalWrite(DCPin,HIGH);
  Serial.println("\nI/O Pins Modes Set .... Done");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); //

  Serial.println();
  Serial.print("connecting....");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("success!");
  Serial.println("IP adress is:");
  Serial.println(WiFi.localIP());
  client.connect(server, serverPort);
  
}

void loop() {
  // put your main code here, to run repeatedly:
   if(client.connected())
   {
      // If Sucessfully Connected Send Connection Message
         
      String reply = client.readStringUntil('\r');
      DCPump_State = int(reply[8]);
      if(reply[8]  == '0')
      {
        digitalWrite(DCPin, HIGH);
        data(0, 0);
        
      }
      else if(reply[8]  == '1')
      {
        digitalWrite(DCPin, LOW);
        data(1, 0);
      }
      else
      {
        data(0,0);
      }
      
      client.print(str);
      Serial.println(str);
      delay(10000);
      client.flush(); 
      
   }
   else
   {
   
     (client.connect(server, serverPort));
     Serial.println("."); 
   } 

}

void data( int data1, int data2)
{
   str = String("$") + "," + String(sensor_type) + "," + String(sensor_no) + "," + String(no_of_data) + "," + String(data1) + "," + String(data2) + "," + String("#") + "\r";

}
