#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Bahadir";
const char* password = "bahadir234";
String readString;

void setup () {

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.print("Connecting to WiFi ");

  }
  Serial.println("Connectted");

}

void loop() {


while (Serial.available()) {
    delay(3);  
    char c = Serial.read();
    readString += c; 
  }

  if (readString.length() >0) {
  
    
    readString.trim();
    denemeCall(readString);
    readString="";
    
   }



}





void denemeCall(String url){
if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

        HTTPClient http;  //Declare an object of class HTTPClient

        http.begin("http://fuzzysera.herokuapp.com:80/"+url);  //Specify request destination
        int httpCode = http.GET();                                                                  //Send the request
        
        if (httpCode == 200) { //Check the returning code

           String payload = http.getString();
                  //Get the request response payload
           Serial.println(payload);                     //Print the response payload

        }else{
           Serial.println("Hata :"+String(httpCode)); 
        }

       http.end();   //Close connection

     }

     return;
}
  

void flushRecieve(){
      while(Serial.available())
        Serial.read();
}


