# Metin Arama Sistemi (Text Search Engine)

Bu proje, İzmir Bakırçay Üniversitesi **BIL1203 Mühendislikte Proje Yönetimi** dersi kapsamında geliştirilmiş bir metin arama motorudur. C programlama dili kullanılarak tasarlanan bu uygulama, kullanıcıdan alınan bir kelimeyi bir veya birden fazla metin dosyası içerisinde arar, frekansını hesaplar ve bulunduğu satır numaralarını raporlar.

## 🚀 Özellikler

- **Modüler Mimari:** Proje; `main.c`, `search_engine.c` ve `search_engine.h` olmak üzere modüler bir yapıda tasarlanmıştır.
- **Çoklu Dosya Desteği:** Aynı anda birden fazla `.txt` dosyası üzerinde arama yapılabilir.
- **Gelişmiş Arama Modları:** - *Normal Arama:* Aranan kelimeyi diğer kelimelerin içinde geçse dahi (örn. "el" araması "elma"yı kapsar) bulur.
  - *Tam Eşleşme (Exact Match):* Sadece bağımsız olarak yazılmış kelimeleri tespit eder.
- **Bellek Dostu Okuma:** Büyük boyutlu dosyalar bellek taşmasına (overflow) yol açmaması için `fgets` ile satır satır okunur.
- **Hata Kontrolü ve Güvenlik:** Kullanıcının menü seçimlerinde hatalı giriş yapmasına (örn. harf girmesine) karşı buffer temizleme ve varsayılan atama kontrolleri içerir.
- **Performans Ölçümü:** Arama işleminin ne kadar sürdüğü milisaniye (ms) cinsinden hesaplanarak raporlanır.
- **Renkli Terminal Çıktısı:** ANSI renk kodları kullanılarak okunabilirliği yüksek, kullanıcı dostu bir terminal arayüzü sunulur.

## 📂 Proje Yapısı

- `search_engine.h`: Fonksiyon prototipleri, sabit değerler ve renk kodlarını içeren başlık dosyası.
- `search_engine.c`: Dosya okuma, string manipülasyonu ve arama algoritmalarının bulunduğu kaynak dosya.
- `main.c`: Kullanıcı arayüzünü (CLI) yöneten ve temel akışı sağlayan ana dosya.

## 🛠️ Kurulum ve Derleme

Proje standart C kütüphanelerini kullanmaktadır ve GCC/Clang gibi bir C derleyicisine ihtiyaç duyar. 

Mac/Linux terminalinde veya Windows ortamındaki uygun bir terminalde (PowerShell/CMD) projeyi derlemek için proje dizininde şu komutu çalıştırın:

bash
gcc main.c search_engine.c -o arama_motoru


**Çalıştırmak için:**

Windows ortamında:
bash
.\arama_motoru.exe


Mac/Linux ortamında:
bash
./arama_motoru
