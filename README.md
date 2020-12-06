# Remote Greenhouse ( Arduino )

## Nedir ?

    Arduino ve ESP8266 ile sensör verileri okuyup servera yollayan ve sonrasıdan gelen bilgilere göre seradaki aygıtları yöneten bir uygulama.

## Nasıl Çalışır ?

    Arduino loop fonksiyonunda belirli aralıklarla sensör verilerilerini okuyor. Bu verileri toplayıp espye gönderiyor. ESP gelen verileri http call ile servera yolluyor. Server her bir birim için gerekli değerlerin olduğu bir cevabı ESP'ye geri dönüyor ve bu değerleri kullana-
    rak aygıtları yönetiyor.

## Eklenmesi Gereken Özellikler

### Gönderilen Verinin Çeşitlendirilmesi

    Mevcut uygulamada tek bir istek yolluyor ve sadece sensör verilerini yolluyor. Serverın durumunu, hataları ve herhangi bir acil durumu yollamamızı sağlayacak birden fazla iste,
    ğin yollanmasını. 

### Data Validation

    ESP ve Arduinonun veri aktarımı çok güvenilir değil üstüne bunun üzeri bir WiFi iletişim var bu yüzden için aktarılan verilerde
    daha sağlam bir validation sistemi gerekli.

### Offline Mode

    Herhangi bir internet bağlantısı sorununda arduinonun bağlantı gelen kadar kendi kendine yönetecebileği sistem şart. En azında ekstrem sıcaklık, nem vb durumlarında serverdan bağım-
    sız kendi kararlarını verebileciği bir sistem şart.

