// RedBoard üzerindeki pinlerin fonksiyonlarını tanımla
#define stp 2  // 2. pini step pini olarak tanımla
#define dir 3  // 3. pini yön pini olarak tanımla
#define MS1 4  // 4. pini 1. mikroadım kontrol pini olarak tanımla
#define MS2 5  // 5. pini 2. mikroadım kontrol pini olarak tanımla
#define MS3 7  // 7. pini 3. mikroadım kontrol pini olarak tanımla
#define EN 6   // 6. pini enable (etkinleştirme) pini olarak tanımla

// Fonksiyonlar için kullanılacak değişkenleri tanımla
char user_input;  // Seri iletişimden gelen kullanıcı girişini tutmak için değişken
int x;            // Döngüler için değişken
int y;            // Döngüler için değişken
int state;        // Yön durumunu tutmak için değişken

void setup() {
  pinMode(stp, OUTPUT);  // step pinini çıkış olarak ayarla
  pinMode(dir, OUTPUT);  // yön pinini çıkış olarak ayarla
  pinMode(MS1, OUTPUT);  // MS1 pinini çıkış olarak ayarla
  pinMode(MS2, OUTPUT);  // MS2 pinini çıkış olarak ayarla
  pinMode(MS3, OUTPUT);
  pinMode(EN, OUTPUT);                        // enable pinini çıkış olarak ayarla
  resetEDPins();                              // tüm pinleri varsayılan değerlerine sıfırla
  Serial.begin(9600);                         // seri iletişimi 9600 baud hızında başlat
  Serial.println("Motor kontrolü başlıyor");  // seri monitöre mesaj yazdır
  Serial.println();
  // Kullanıcı için seçim menüsünü yazdır
  Serial.println("Motor kontrol seçeneği için numara girin:");
  Serial.println("1. full step modunda dönüş.");
  Serial.println("2. full step modunda yönü ters çevir.");
  Serial.println("3. 1/8 mikroadım modunda dönüş.");
  Serial.println("4. İleri ve geri adımlama.");
  Serial.println("5. 1/4 mikroadım modunda dönüş");
  Serial.println("6. 1/16 mikroadım modunda dönüş");
  Serial.println("7. 1/2 mikroadım modunda dönüş");
  Serial.println();
}

//Main loop
void loop() {
  while (Serial.available()) {   // Seri monitörden giriş olup olmadığını kontrol et
    user_input = Serial.read();  // Kullanıcı girişini oku
    digitalWrite(EN, LOW);       // Motor sürücüsünü etkinleştir
    if (user_input == '1') {
      StepForwardDefault();  // Varsayılan full step modunda ileri adımlama fonksiyonunu çağır
    }
     else if (user_input == '2') {
      ReverseStepDefault();  // Varsayılan full step modunda geri adımlama fonksiyonunu çağır
    }
     else if (user_input == '3') {
      SmallStepMode();  // 1/8 mikroadım modunda adımlama fonksiyonunu çağır
    }
     else if (user_input == '4') {
      ForwardBackwardStep();  // İleri ve geri adımlama fonksiyonunu çağır
    } 
      else if(user_input == '5') {
        QuarterStepMode(); // 1/4 mikroadım modunda adımlama fonksiyonunu çağır
    }
     else if(user_input == '6') {
        SixteenthStepMode(); // 1/16 mikroadım modunda adımlama fonksiyonunu çağır
    }
     else if(user_input == '7') {
        HalfStepMode(); // 1/2 mikroadım modunda adımlama fonksiyonunu çağır
     }
    else {
      Serial.println("Geçersiz seçenek girdiniz.");
    }
    resetEDPins();  // Pin durumlarını varsayılan değerlerine sıfırla
  }
}

void StepForwardDefault() {
  Serial.println("Varsayılan adım modunda ileri hareket ediliyor.");  // Konsol ekranına mesaj yazdırılıyor

  digitalWrite(dir, HIGH);  // Motoru ileri hareket ettirmek için yön pini (saat yönü ) HIGH yap

  for (x = 0; x < 120000; x++)  // 4 dk boyunca motor hareket etsin
  {
    digitalWrite(stp, HIGH);  // Bir adım ileri tetikle

    delay(1);  // 1 milisaniye bekle

    digitalWrite(stp, LOW);  // Yeniden tetiklenebilmesi için adım pinini LOW yap

    delay(1);  // 1 milisaniye bekle
  }

  Serial.println("Yeni seçenek girin");  // Konsol ekranına mesaj yazdırılıyor
  Serial.println();
}

void ReverseStepDefault() {
  Serial.println("Varsayılan adım modunda geri hareket ediliyor.");  // Konsol ekranına mesaj yazdırılıyor

  digitalWrite(dir, LOW);  // Motoru geri hareket ettirmek için yön pinini(saat yönü tersi) LOW yap

  for (x = 0; x < 120000; x++)  // 4 dk boyunca motor hareket etsin
  {
    digitalWrite(stp, HIGH);  // Bir adım tetikle

    delay(1);  // 1 milisaniye bekle

    digitalWrite(stp, LOW);  // Yeniden tetiklenebilmesi için adım pinini LOW yap

    delay(1);  // 1 milisaniye bekle
  }

  Serial.println("Yeni seçenek girin");  // Konsol ekranına mesaj yazdırılıyor
  Serial.println();
}

void SmallStepMode() {
  Serial.println("1/8 mikro adım modunda hareket ediliyor.");  // Konsol ekranına mesaj yazdırılıyor

  digitalWrite(dir, HIGH);  // Motoru ileri hareket ettirmek için yön pinini (saat yönü) HIGH yap

  digitalWrite(MS1, HIGH);   // 1/8 mikro adım çözünürlüğüne ayarlamak için MS1  pinini HIGH yap
  digitalWrite(MS2, HIGH);  // 1/8 mikro adım çözünürlüğüne ayarlamak için  MS2 pinini HIGH yap
  digitalWrite(MS3, LOW);  // 1/8 mikro adım çözünürlüğüne ayarlamak için  MS3 pinini LOW yap

  for (x = 0; x < 120000; x++)  // 4 dk boyunca motor hareket etsin
  {
    digitalWrite(stp, HIGH);  // Bir adım ileri tetikle

    delay(1);  // 1 milisaniye bekle

    digitalWrite(stp, LOW);  // Yeniden tetiklenebilmesi için adım pinini LOW yap

    delay(1);  // 1 milisaniye bekle
  }

  Serial.println("Yeni seçenek girin");  // Konsol ekranına mesaj yazdırılıyor
  Serial.println();
}

void ForwardBackwardStep() {
  Serial.println("İleri ve geri hareket arasında geçiş yapılıyor.");  // Konsol ekranına mesaj yazdırılıyor

  for (x = 1; x < 5; x++)  // Hareketin görülebilmesi için yeterli adım atılması sağlanıyor (5 kez)
  {
    state = digitalRead(dir);  // Yön pininin durumunu oku ve değiştir

    if (state == HIGH)  // Eğer yön HIGH ise LOW yap, LOW ise HIGH yap (yönü tersine çevir)
    {
      digitalWrite(dir, LOW);
    } else if (state == LOW) {
      digitalWrite(dir, HIGH);
    }

    for (y = 0; y < 120000; y++)  // 120000 adım at
    {
      digitalWrite(stp, HIGH);  // Bir adım tetikle

      delay(1);  // 1 milisaniye bekle

      digitalWrite(stp, LOW);  // Yeniden tetiklenebilmesi için adım pinini LOW yap

      delay(1);  // 1 milisaniye bekle
    }
  }

  Serial.println("Yeni seçenek girin:");  // Konsol ekranına mesaj yazdırılıyor
  Serial.println();
}

void QuarterStepMode() {
  Serial.println("1/4 mikro adım modunda hareket ediliyor.");  // Konsol ekranına mesaj yazdırılıyor

  digitalWrite(dir, HIGH);  // Motoru ileri hareket ettirmek için yön pinini (saat yönü) HIGH yap

  digitalWrite(MS1, LOW);   // 1/4 mikro adım çözünürlüğüne ayarlamak için MS1  pinini LOW yap
  digitalWrite(MS2, HIGH);  // 1/4 mikro adım çözünürlüğüne ayarlamak için  MS2 pinini HIGH yap
  digitalWrite(MS3, LOW);  // 1/4 mikro adım çözünürlüğüne ayarlamak için  MS3 pinini LOW yap

  for (x = 0; x < 120000; x++)  // 4 dk boyunca motor hareket etsin
  {
    digitalWrite(stp, HIGH);  // Bir adım ileri tetikle

    delay(1);  // 1 milisaniye bekle

    digitalWrite(stp, LOW);  // Yeniden tetiklenebilmesi için adım pinini LOW yap

    delay(1);  // 1 milisaniye bekle
  }

  Serial.println("Yeni seçenek girin");  // Konsol ekranına mesaj yazdırılıyor
  Serial.println();

}

void SixteenthStepMode() {
 Serial.println("1/16 mikro adım modunda hareket ediliyor.");  // Konsol ekranına mesaj yazdırılıyor

  digitalWrite(dir, HIGH);  // Motoru ileri hareket ettirmek için yön pinini (saat yönü) HIGH yap

  digitalWrite(MS1, HIGH);   // 1/16 mikro adım çözünürlüğüne ayarlamak için MS1  pinini HIGH yap
  digitalWrite(MS2, HIGH);  // 1/16 mikro adım çözünürlüğüne ayarlamak için  MS2 pinini HIGH yap
  digitalWrite(MS3, HIGH);  // 1/16 mikro adım çözünürlüğüne ayarlamak için  MS3 pinini HIGH yap

  for (x = 0; x < 120000; x++)  // 4 dk boyunca motor hareket etsin
  {
    digitalWrite(stp, HIGH);  // Bir adım ileri tetikle

    delay(1);  // 1 milisaniye bekle

    digitalWrite(stp, LOW);  // Yeniden tetiklenebilmesi için adım pinini LOW yap

    delay(1);  // 1 milisaniye bekle
  }

  Serial.println("Yeni seçenek girin");  // Konsol ekranına mesaj yazdırılıyor
  Serial.println();
}

void HalfStepMode() {
  Serial.println("1/2 mikro adım modunda hareket ediliyor.");  // Konsol ekranına mesaj yazdırılıyor

  digitalWrite(dir, HIGH);  // Motoru ileri hareket ettirmek için yön pinini (saat yönü) HIGH yap

  digitalWrite(MS1, HIGH);   // 1/2 mikro adım çözünürlüğüne ayarlamak için MS1  pinini HIGH yap
  digitalWrite(MS2, LOW);  // 1/2 mikro adım çözünürlüğüne ayarlamak için  MS2 pinini LOW yap
  digitalWrite(MS3, LOW);  // 1/2 mikro adım çözünürlüğüne ayarlamak için  MS3 pinini LOW yap

  for (x = 0; x < 120000; x++)  // 4 dk boyunca motor hareket etsin
  {
    digitalWrite(stp, HIGH);  // Bir adım ileri tetikle

    delay(1);  // 1 milisaniye bekle

    digitalWrite(stp, LOW);  // Yeniden tetiklenebilmesi için adım pinini LOW yap

    delay(1);  // 1 milisaniye bekle
  }

  Serial.println("Yeni seçenek girin");  // Konsol ekranına mesaj yazdırılıyor
  Serial.println();
}

void resetEDPins() {
  // Tüm pinleri varsayılan değerlerine ayarla
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(MS3, LOW);
  digitalWrite(EN, HIGH);
}
