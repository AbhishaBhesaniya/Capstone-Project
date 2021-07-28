import serial
import datetime
from time import time, ctime
import requests

sp = serial.Serial('/dev/ttyUSB0')

while 1:
       #for x in range(0, 100):
           #requests.delete('http://esdserver:3000/api/c520d388d3438a8b12053f62c0deef6f/data')
                    
       rdata = sp.readline()
       print(rdata)
              
       if(rdata[0] == 36):
       
           fdata = rdata.decode().split(',', 8)
          
           sensor_type = fdata[1]
           #print(sensor_type)
           sensor_no = fdata[2]
           #print(sensor_no)
           sensor_data1 = fdata[4]
           #print(sensor_data1)
           sensor_data2 = fdata[5]
           #print(sensor_data2)
           
           t = datetime.datetime.now();
           time = t.strftime("%I:%M:%S %p")
           year = t.year
           date = t.day
           month = t.strftime("%B")
           day = t.strftime("%A")
           
           if (int(fdata[1]) == 1):
               data={'Day':day,'Date':int(date),'Month':month, 'Year':int(year),'time':time,'sensor Type': 'Soil Moisture','Sensor No': int(sensor_no), 'Soil Moisture Level':float(sensor_data1)}
               #print(data)
               
           elif (int(fdata[1]) == 2):
                 data={'Day':day,'Date':int(date),'Month':month, 'Year':int(year),'time':time,'sensor Type': 'DHT11','Sensor No': int(sensor_no), 'Temperature':float(sensor_data2),'Humidity':float(sensor_data1)}
                 #print(data)
                 
           elif (int(fdata[1]) == 3):
                 data={'Day':day,'Date':int(date),'Month':month, 'Year':int(year),'time':time,'sensor Type': 'DC Motor','Sensor No': int(sensor_no), 'DC PUMP Status':int(sensor_data1)}
                 #print(data)
                 
           requests.put('http://esdserver:3000/api/c520d388d3438a8b12053f62c0deef6f/data',json=data)
           #r=requests.get('http://esdserver:3000/api/c520d388d3438a8b12053f62c0deef6f/data')
           #print(r.json())
       
       
        
       
       