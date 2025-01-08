#include <WiFi.h>
 
const char* ssid = "TUKKUK1";
const char* password =  "SHX3U21a";
 
const char* ntpServer = "time.google.com";
 
void printTime(){
  
  struct tm time;
   
  if(!getLocalTime(&time)){
    Serial.println("Could not obtain time info");
    return;
  }
 
  Serial.println("\n---------TIME----------");
   
  Serial.print("Number of years since 1900: ");
  Serial.println(time.tm_year);
 
  Serial.print("month, from 0 to 11: ");
  Serial.println(time.tm_mon);
 
  Serial.print("day, from 1 to 31: "); 
  Serial.println(time.tm_mday);
 
  Serial.print("hour, from 0 to 23: ");
  Serial.println(time.tm_hour);
 
  Serial.print("minute, from 0 to 59: ");
  Serial.println(time.tm_min);
   
  Serial.print("second, from 0 to 59: ");
  Serial.println(time.tm_sec);
}
 
void setup()
{
  Serial.begin(115200);
   
  WiFi.begin(ssid, password);
   
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("Connecting...");
  }
   
  Serial.println("Connected with success");
   
  configTime(3600, 3600, ntpServer);
}
 
void loop()
{
  printTime();
  delay(5000);
}
