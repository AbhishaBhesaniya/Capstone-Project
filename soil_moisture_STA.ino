#include <ESP8266WiFi.h>
#include <SPI.h>


float soilMoistureValue = 0;
char myData[] = {}; 
String str;
const int SensorPin = A0;
int sensor_type = 01;
int sensor_no = 01;
int no_of_data = 01;

const char* ssid = "TechFarm";          
const char* password = "Techfarm@123";  

int             serverPort  = 1010;
IPAddress       server(192,168,4,1);
WiFiClient      client;

void data( float data1, float data2);


void setup() {
  
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(9600);
 
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

void loop() 
{
  // put your main code here, to run repeatedly:
   if(client.connected())
   {

    soilMoistureValue = analogRead(SensorPin);  //put Sensor insert into soil
    //Serial.print("Analog Value : "); 
    //Serial.println(soilMoistureValue);
    //str = String(soilMoistureValue);
    //str = str +"\r";
   // Serial.println(str);
    
    data(soilMoistureValue, 0);
    client.print(str);
    Serial.println(str); 
     delay(60000);
    client.flush(); 
   }
   else
   {
     (client.connect(server, serverPort));
     Serial.println("connection failed"); 
  } 

}

void data( float data1, float data2)
{
   str = String("$") + "," + String(sensor_type) + "," + String(sensor_no) + "," + String(no_of_data) + "," + String(data1) + "," + String(data2) + "," + String("#") + "\r";

}
