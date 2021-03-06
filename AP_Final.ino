/* 
 * 
 *  Configure the ESP8266 unit as a Wi-Fi access point
 */

//#include <ESP8266WiFi.h>
#include <WiFi.h>
#include <string.h>
//#include <SPI.h>

#define     MAXSC     10           // MAXIMUM NUMBER OF CLIENTS
 
WiFiServer  server(1010);      // THE SERVER AND THE PORT NUMBER
WiFiClient  serverClients[MAXSC];     // THE SERVER CLIENTS (Devices)
  

/* Your WiFi Soft Access Point settings */
const char* ssid = "TechFarm";          //this will be the network name
const char* password = "Techfarm@123";  //this will be the network password
String str;
int data1 = 0;
String reply; 
char st1[100];
int sensor_type = 0;

void setup() {
  Serial.begin(9600); 
   // Setting The Wifi Mode
   WiFi.mode(WIFI_AP);
   Serial.println("WIFI Mode : AccessPoint");
    
   
    // Starting The Access Point
    IPAddress Ip(192, 168, 4, 1);
    IPAddress NMask(255, 255, 255, 0);
    WiFi.softAPConfig(Ip, Ip, NMask);
    WiFi.softAP(ssid, password, 6, 0, 10);
    Serial.println("WIFI < " + String(ssid) + " > ... Started");
    
    // Wait For Few Seconds
    delay(1000);
   // WiFi.onEvent(WiFiStationConnected, SYSTEM_EVENT_AP_STACONNECTED);
    //WiFi.onEvent(WiFiStationDisconnected, SYSTEM_EVENT_AP_STADISCONNECTED);
        // Getting Server IP
    IPAddress IP = WiFi.softAPIP();
    
    // Printing The Server IP Address
    Serial.print("AccessPoint IP : ");
    Serial.println(IP);

    // Printing MAC Address
    Serial.print("AccessPoint MC : ");
    Serial.println(String(WiFi.softAPmacAddress()));

    // Starting Server
    server.begin();
    server.setNoDelay(true);
    Serial.println("Server Started");
}



void loop() {
  //Serial.printf("Number of connected devices (stations) = %d\n", WiFi.softAPgetStationNum());
  AvailableClients();
  AvailableMessage();
 
}



void AvailableClients()
  {   
    
    if (server.hasClient())
    {

     for(uint8_t i = 1; i < MAXSC; i++)
    {
        //find free/disconnected spot
       // Serial.println("start");
        if (!serverClients[i] || !serverClients[i].connected())
        {
          // Checks If Previously The Client Is Taken
          if(serverClients[i])
          {
            serverClients[i].stop();
          }

          // Checks If Clients Connected To The Server
          if(serverClients[i] = server.available())
          {
            Serial.println("New Client: " + String(i));
          }

          // Continue Scanning
          continue;
        }
      }
      
      
    }
    
  }
  //***************************************************************************************
   void AvailableMessage()
  {
    //check clients for data
    for(uint8_t i = 1; i < MAXSC; i++)
    {
      if (serverClients[i] && serverClients[i].connected() && serverClients[i].available())
      {
          while(serverClients[i].available())
          {
            // Use WiFiClient class to create TCP connections
                  static float SoilMoisture_level = 0;                   
                  reply = serverClients[i].readStringUntil('\r');
                  
                  if(reply[2] == '1')
                  {
                                    
                    reply.toCharArray(st1,100);
                    int i = 0;
                    char* a = st1;
                    char* b = strtok(a, ",");
                    while(b != NULL)
                    {
                         //Serial.println(b);
                         i++;
                         b++;
                         b = strtok(NULL, ",");
                         if(i == 4)
                         {
                           // char soil =(char)b;
                            SoilMoisture_level = atof(b);
                            
                         }
                    }
                                        
                    i = 0;
                    //Serial.println(SoilMoisture_level);
                    
                    
                  }
                  
                  if(reply[2] == '3')
                  {
                    
                    //Serial.println (reply);
                   // Serial.println (reply[8]);
                    if(SoilMoisture_level > 700)
                    {
                      data1 = 1;
                    }
                    else
                    {
                      data1 = 0;
                    }
                    
                    str = String("$") + "," + String("3") + "," + String("1") + "," + String("1") + "," + String(data1) + "," + String("0") + "," + String("#") + "\r";
                    //Serial.println (reply);
                    serverClients[i].print(str);
                    serverClients[i].flush();
                    Serial.println (str);
                    
                  }
                  else
                  {
                      Serial.println (reply);
                  }
                  
           
            //delay(3000);
          }
      }
    }
  }
