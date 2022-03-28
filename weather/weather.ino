#include <SPI.h> 
#include <WiFi101.h> 


char ssid[] = "UofM-Guest"; //  your network SSID (name) 
char pass[] = "";//  your network PASSWORD () 
//open weather map api key 
String apiKey= "25e6df0596c6377562bef75dbb510754"; 
//the city you want the weather for 
String location= "Minneapolis"; 
int status = WL_IDLE_STATUS; 
char server[] = "api.openweathermap.org";     
WiFiClient client; 

void setup() { 
 //Initialize serial and wait for port to open: 
 Serial.begin(9600); 
 // attempt to connect to Wifi network: 
 while (status != WL_CONNECTED) { 
   Serial.print("Attempting to connect to SSID: "); 
   Serial.println(ssid); 
   status = WiFi.begin(ssid); 
   //use the line below if your network is protected by wpa password  
   //status = WiFi.begin(ssid, pass); 
   // wait 10 seconds for connection: 
   delay(1000); 
 } 
 Serial.println("Connected to wifi"); 
} 

void getWeather() { 
 Serial.println("\nStarting connection to server..."); 
 // if you get a connection, report back via serial: 
 if (client.connect(server, 80)) { 
   Serial.println("connected to server"); 
   // Make a HTTP request: 
   client.print("GET /data/2.5/forecast?"); 
   client.print("q="+location); 
   client.print("&appid="+apiKey); 
   client.print("&cnt=3"); 
   client.println("&units=metric"); 
   client.println("Host: api.openweathermap.org"); 
   client.println("Connection: close"); 
   client.println(); 
 } else { 
   Serial.println("unable to connect"); 
 } 
 delay(1000); 
 String line = ""; 
 while (client.connected()) { 
   line = client.readStringUntil('\n'); 
   Serial.println(line); 
 } 
} 

void loop() { 
 getWeather(); 
 delay(10000); 
}
