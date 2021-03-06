#include <ESP8266WiFi.h>
#include <DHT.h>

#define DHTTYPE DHT22
String str ;
float Temp = 0;
float humi = 0;
int sensor_type = 02;
int sensor_no = 01;
int no_of_data = 02;
uint8_t DHTPin = 5;

void data(float data1, float data2);
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);

const char* ssid = "TechFarm";         
const char* password = "Techfarm@123";  

int             serverPort  = 1010;
IPAddress       server(192,168,4,1);
WiFiClient      client;

void setup() {
  
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(9600);
 
  pinMode(DHTPin, INPUT);
  dht.begin();
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
      int chk = dht.read(DHTPin);
      humi = dht.readHumidity(); // store data in variable
      Temp = dht.readTemperature();
      data(humi, Temp);
      client.print(str);
      Serial.print("Humidity : "); 
      Serial.println(humi); 
      Serial.print("Temperature : ");
      Serial.println(Temp); 
      
     delay(1000);
     client.flush(); 
      
   }
   else
   {
   
     (client.connect(server, serverPort));
     Serial.println("."); 
   } 

}

void data( float data1, float data2)
{
   str = String("$") + "," + String(sensor_type) + "," + String(sensor_no) + "," + String(no_of_data) + "," + String(data1) + "," + String(data2) + "," + String("#") + "\r";

}
