#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


const char* ssid = "Bahadir";
const char* password = "bahadir234";
String readString;

void setup () {

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  //Wait while connecting to wifi 
  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.print("Connecting to WiFi ");

  }
  Serial.println("Connectted");

}




void loop() {

while (Serial.available()) {
  
    delay(3);  //Okumanın daha güvenilir olması için 3mslik delay
    char c = Serial.read();
    readString += c; 
  }

  if (readString.length() >0) {
    
    readString.trim();
    httpCall(readString);
    readString="";
    
   }
}

void httpCall(String url){
if (WiFi.status() == WL_CONNECTED) { //WiFi durumunu kontrol et

        HTTPClient http;  

        http.begin("http://mysera.herokuapp.com:80/"+url);  
        int httpCode = http.GET();                                                               
        
        if (httpCode == 200) { //Status code'u kontrol et

           String payload = http.getString();           
           Serial.println(payload);                  //Veriyi al ve arduinoya yolla   

        }else{
           Serial.println("Hata :"+String(httpCode));  //Kod 200 değilse gelen kodu arduinoya yolla
        }

       http.end();   

     }

     return;
}
  
//Veri varsa alarak serial portu temizle
void flushRecieve(){
      while(Serial.available())
        Serial.read();
}


