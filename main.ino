
#include <dht.h>
#include <Servo.h>

#define ESP Serial1

Servo mServo;


int ledPin = 7;

//Gelen response için
//1. Index led 2. index servor için
//0 ve 3 index ilere kullanılacak
String resArr[4] = {"000","000","000","000"};



dht DHT;
//String'in alloc için dummy daha ile doldurdum
String readString = "foobarfoobarfoobar";
boolean TO = false;

void setup() {
  
  Serial.begin(115200);
  ESP.begin(115200);
  pinMode(7,OUTPUT);
  mServo.attach(10);

}

void loop() {
  
  
  //Sensör Verilerini Oku
  int chk = DHT.read11(11);
  DHT.read11(11);
    
  int sicaklik = DHT.temperature;
  int nem = DHT.humidity;

  Serial.println(sicaklik);     
  Serial.println(nem);
  
  //URL'yi Oluştur
  char url [75];
  sprintf (url, "degerler/%d/%d", sicaklik,nem);


  //İsteği Yolla
  ESP.println(url);

 
  
  TO = false;
  unsigned long send = millis();

  //Cevap Bekle
  while(!TO){
     while (ESP.available() > 0 ) {
       delay(10);  
       char c =   (char) ESP.read();
       readString += c;
       
    }     
    readString.trim();
    if (readString.length() > 0) {
      Serial.println(readString + "res");
    
        //Hata varsa http status coduna göre mesajı printle
      if(readString.charAt(0) == 'H'){
        
        readString.remove(0,6);
        statusCodeKontrol(readString);
      }

      int lastdelim = 0;
      int j = 0;

      //Gelen veriyi /'lara göre böl ve resArr'a yolla
      for (int i = 0 ;i < readString.length() ; i++){
         if(readString.charAt(i) == '/'){
             
             resArr[j] = readString.substring(lastdelim,i);
             
             lastdelim = i+1;
             j++;
         }
      }
       
       Serial.println(resArr[0] + "--" + resArr[1] + "--" + resArr[2]+ "--" + resArr[3]); 


       //LED Kontrol
       //Gelen verinin 1. indexindeki degere göre on/oof
       if(resArr[1].charAt(0) == '1'){
        digitalWrite(ledPin,1);
       }else if (resArr[1].charAt(0) == '0'){
        digitalWrite(ledPin,0);
       }
    

      //Servo Kontrol
      //Gelen verinin 2. indexindeki degere göre on/oof
      mServo.write( resArr[2].toInt());
      
     
      
      //Cevap alındığından loop'tan çık
      TO = true;
      readString ="";
      
    }

    //6000ms Cevap Gelmezse Timeout Olup Loop'tan çık
    unsigned long current = millis();
    if((current - send) > 6000 ){
      TO = true; 
    }

    
  }// while !to
  
   delay(2000);
}//loop





void statusCodeKontrol(String statusCode){
    if(statusCode.equals("404")){
           Serial.println(" Sayfa Bulunamadı ");
         }else if(statusCode.equals("-1")){
           Serial.println(" bağlantı hatası "); 
         }else if(statusCode.equals("400")){
           Serial.println(" Göndirilen veride hata "); 
         }else if(statusCode.equals("500")){
           Serial.println(" Sunucu Hatası "); 
     }
}









