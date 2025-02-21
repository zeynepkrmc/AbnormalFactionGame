////#include <windows.h>
////#include "icb_gui.h"
////#include <thread>
////#include <atomic>
////#include <chrono>
////#include <mutex>
////
////#include <mmsystem.h>  // Windows için ses fonksiyonları (PlaySound için)
////#pragma comment(lib, "winmm.lib")  // PlaySound fonksiyonu için gerekli kütüphane
////
////
////int F1;
////ICBYTES arkaplanilk, arkaplandevam, Character, Bird, Fish, Bat, Gold, Yuzme;
////ICBYTES CharacterRun[3], CharacterSwim[4], BirdFly[4], FishSwim[2], BatFly[2];
////
////ICBYTES arkaplan2; // arkaplan2
////bool oyunCalisiyor = true;
////bool yuzmedenCikti = false; // Yüzmeden çıkış durumu
////int arkaPlanX = 0;  // Arka planın X ekseninde kaymasını kontrol eden değişken
////const int arkaPlanGecisBaslangici = 500; // Arka planın kaymaya başlayacağı X noktası
////const int maksimumKayma = 100; // Arka planın en fazla ne kadar kayacağını belirler
////bool gecisBasladi = false;  // Arka plan geçişi başladı mı?
////int gecisKaymaMiktari = 0;  // Arkaplan2'nin kayma miktarı
////const int gecisHizi = 10;   // Her güncellemede kaç birim kayacak
////const int gecisTamamlanmaMiktari = 200; // Geçiş tamamlanınca toplam kayma miktarı
////
////
////
////
////bool oyunBasladi = false; // Oyun başlama durumu
////ICBYTES enterScreen;       // Giriş ekranı için resim
////
////int MouseLogBox;
////
////bool ikinciArkaplanAktif = false; // arka plan
////
////// Karakter değişkenleri
////int karakterX = 66, karakterY = 280;
////const int hareketMesafesi = 10;
////bool yuzmede = false;
////bool ziplamaAktif = false;
////int animasyonKare = 0;
////
////// Kuş, balık ve yarasa için animasyon kareleri
////int birdAnimasyonKare = 0;
////int fishAnimasyonKare = 0;
////int batAnimasyonKare = 0;
////
////// Merdiven koordinatları
////const int merdivenSolX = 116, merdivenSagX = 130;
////const int merdivenUstY = 280, merdivenAltY = 370;
////
////// Yüzme alanı koordinatları
////const int yuzmeAlaniX = 175, yuzmeAlaniY = 415;
////const int yuzmeAlaniGenislik = 424, yuzmeAlaniYukseklik = 84;
////
////// Objelerin başlangıç konumları
////int birdX = 440, birdY = 247, birdYon = -1;
////int fishX = 546, fishY = 432, fishYon = -1;
////int batX = 309, batY = 160, batYon = -1;
////const int hareketHizi = 5;
////
////// Altın konumu
////int goldX = 500, goldY = 400;
////bool goldGorunur = true;
////
////int loadAssetsButton, startGameButton; // Butonları kontrol etmek için ID'ler
////bool assetsYuklendi = false; // Varlıkların yüklenip yüklenmediğini takip eder
////
////
////// Yüzme alanı
//////int yuzmeAlaniX = 175;
//////int yuzmeAlaniY = 415;
//////int yuzmeAlaniGenislik = 424;
//////int yuzmeAlaniYukseklik = 84;
////
////
////// Merdivende mi?
////bool GoldCarpistiMi() {
////    if (!goldGorunur) return false;
////
////    // ✅ *Tam olarak X=516, Y=416 olduğunda altını al!*
////    if (abs(karakterX - 526) <= 2 && abs(karakterY - 460) <= 2)
////    {
////        goldGorunur = false;
////        ICG_printf(MouseLogBox, "✅ ALTIN ALINDI! Karakter X=%d, Y=%d | Altın X=%d, Y=%d\n",
////            karakterX, karakterY, goldX, goldY);
////        return true;
////    }
////    return false;
////}
////
////
////
////bool merdivendeMi(int x, int y) {
////    // 🎯 Eğer karakter en altta (Y=370) ise artık merdivende değil
////    if (y >= merdivenAltY) return false;
////
////    return (x >= merdivenSolX && x <= merdivenSagX && y >= merdivenUstY && y <= merdivenAltY);
////}
////
////
////// Yüzme alanında mı?
////bool yuzmeAlaniIcindeMi(int x, int y) {
////    return (x >= yuzmeAlaniX && x <= yuzmeAlaniX + yuzmeAlaniGenislik &&
////        y >= yuzmeAlaniY && y <= yuzmeAlaniY + yuzmeAlaniYukseklik);
////}
////
////
////// Balık su alanında hareket etmeli
////const int fishMinX = 250;  // Su içindeki minimum X koordinatı
////const int fishMaxX = 500;  // Su içindeki maksimum X koordinatı
////const int fishMinY = 430;  // Su seviyesine uygun minimum Y
////const int fishMaxY = 450;  // Su içinde hafif yukarı aşağı hareket
////
////void ICGUI_Create() {
////    ICG_MWSize(800, 600);
////    ICG_MWTitle("Abnormal Faction Game");
////}
////
////void LoadGameAssets() {
////    ReadImage("enter.bmp", enterScreen);
////    ReadImage("dene.bmp", arkaplanilk);
////    ReadImage("arkaplandevamdene.bmp", arkaplandevam);
////    ReadImage("girl.bmp", Character);
////    ReadImage("girl.bmp", Yuzme);
////    ReadImage("kus.bmp", Bird);
////    ReadImage("fishh.bmp", Fish);
////    ReadImage("batt.bmp", Bat);
////    ReadImage("gold1.bmp", Gold);
////
////    // Koşma Animasyonu
////    ICBYTES charRunCoords{ {8, 9, 40, 60}, {58, 10, 40, 60}, {110, 10, 40, 60} };
////    for (int i = 0; i < 3; i++) {
////        Copy(Character, charRunCoords.I(1, i + 1), charRunCoords.I(2, i + 1),
////            charRunCoords.I(3, i + 1), charRunCoords.I(4, i + 1), CharacterRun[i]);
////    }
////
////    // Yüzme Animasyonu
////    ICBYTES swimCoords{ {8, 85, 52, 30}, {66, 85, 56, 33}, {130, 85, 53, 31}, {187, 85, 57, 32} };
////    for (int i = 0; i < 4; i++) {
////        Copy(Yuzme, swimCoords.I(1, i + 1), swimCoords.I(2, i + 1),
////            swimCoords.I(3, i + 1), swimCoords.I(4, i + 1), CharacterSwim[i]);
////    }
////
////    // Kuş Animasyonu
////    ICBYTES birdCoords{ {6, 2, 39, 24}, { 55,11,39,23 }, { 9,35,38,26 }, { 49,61,40,30 } };
////    for (int i = 0; i < 4; i++) {
////        Copy(Bird, birdCoords.I(1, i + 1), birdCoords.I(2, i + 1),
////            birdCoords.I(3, i + 1), birdCoords.I(4, i + 1), BirdFly[i]);
////    }
////
////    // Balık Animasyonu
////    ICBYTES fishCoords{ {16,30,53,37},{16,73,53,39},{84,30,51,37},{84,74,49,39} };
////    for (int i = 0; i < 4; i++) {
////        Copy(Fish, fishCoords.I(1, i + 1), fishCoords.I(2, i + 1),
////            fishCoords.I(3, i + 1), fishCoords.I(4, i + 1), FishSwim[i]);
////    }
////
////    // Yarasa Animasyonu
////    ICBYTES batCoords{ {5, 24, 49, 43}, {56, 24, 41, 27} };
////    for (int i = 0; i < 2; i++) {
////        Copy(Bat, batCoords.I(1, i + 1), batCoords.I(2, i + 1),
////            batCoords.I(3, i + 1), batCoords.I(4, i + 1), BatFly[i]);
////    }
////
////    DisplayImage(F1, enterScreen);
////
////    ICG_DestroyWidget(loadAssetsButton);
////
////    assetsYuklendi = true;
////}
////void UpdateScreen() {
////    // Eğer karakter X=350’ye ulaştıysa, arka plan kaymaya başlasın
////    if (karakterX >= 350) {
////        gecisBasladi = true;
////    }
////
////    // Eğer geçiş başladıysa, arka plan karakterin ilerlemesine bağlı olarak kaymaya devam etmeli
////    if (gecisKaymaMiktari > 700) {
////        gecisKaymaMiktari = 700;  // Maksimum 700 kayabilir (tam ekran boyutu kadar)
////    }
////    else if (gecisBasladi) {
////        gecisKaymaMiktari = karakterX - 350;
////    }
////
////    // *🔥 İlk ve ikinci arka planı yükle*
////    ReadImage("dene.bmp", arkaplanilk);
////    ReadImage("arkaplan2.bmp", arkaplan2);
////
////    // *🔥 Geçici bir buffer oluştur (tamamen siyah bir arka plan başlat)*
////    ICBYTES geciciArkaPlan;
////    Copy(arkaplanilk, 0, 0, 700, 500, geciciArkaPlan);  // İlk arka planı geçici buffer olarak kopyala
////    FillRect(geciciArkaPlan, 0, 0, 700, 500, 0); // Buffer'ı tamamen siyah yap (arka planı temizle)
////
////    // *🔥 Eğer ilk arka plan tamamen kaybolmadıysa, sola kaydırarak ekleyelim*
////    if (gecisKaymaMiktari < 700) {
////        PasteNon0(arkaplanilk, -gecisKaymaMiktari, 0, geciciArkaPlan);
////    }
////
////    // *🔥 İkinci arka planı sağdan içeri kaydır ve üstüne ekle*
////    PasteNon0(arkaplan2, 700 - gecisKaymaMiktari, 0, geciciArkaPlan);
////
////    // *🔥 Güncellenmiş arka planı ekrana koy*
////    DisplayImage(F1, geciciArkaPlan);
////
////    // *Karakterin ekran konumunu belirle (arka plan kayarken bile hareket etmeli)*
////    int karakterEkranX = karakterX - gecisKaymaMiktari;
////
////    // *Karakteri ekrana çiz*
////    if (yuzmede) {
////        PasteNon0(CharacterSwim[animasyonKare % 4], karakterEkranX, karakterY, geciciArkaPlan);
////    }
////    else {
////        PasteNon0(CharacterRun[animasyonKare % 3], karakterEkranX, karakterY, geciciArkaPlan);
////    }
////
////    // *Diğer objeleri ekrana çiz (arka plan kaymasını hesaba kat)*
////    PasteNon0(BirdFly[birdAnimasyonKare % 4], birdX - gecisKaymaMiktari, birdY, geciciArkaPlan);
////    PasteNon0(FishSwim[fishAnimasyonKare % 2], fishX - gecisKaymaMiktari, fishY, geciciArkaPlan);
////    PasteNon0(BatFly[batAnimasyonKare % 2], batX - gecisKaymaMiktari, batY, geciciArkaPlan);
////
////    if (goldGorunur) {
////        PasteNon0(Gold, goldX - gecisKaymaMiktari, goldY, geciciArkaPlan);
////    }
////
////    // *🔥 Güncellenmiş ekranı göster*
////    DisplayImage(F1, geciciArkaPlan);
////}
////
////void yuzmeModuGuncelle() {
////    if (yuzmede && karakterX >= 566 && karakterY == 410) {
////        yuzmede = false;
////        yuzmedenCikti = true;
////        karakterY = 370;
////
////        gecisBasladi = true; // 🎯 İkinci arka planı kaydırmayı başlat!
////        UpdateScreen(); // 🎯 Ekranı güncelle!
////
////        ICG_printf(MouseLogBox, "🚶 Karakter yüzmeden çıktı ve yürümeye başladı! X=%d, Y=%d\n", karakterX, karakterY);
////    }
////
////    if (yuzmedenCikti) return;
////
////    if (!yuzmede && karakterY >= 370 && karakterX >= yuzmeAlaniX + 10) {
////        yuzmede = true;
////        karakterY = yuzmeAlaniY + 5;
////        animasyonKare = 0;
////    }
////
////    if (yuzmede && !yuzmeAlaniIcindeMi(karakterX, karakterY)) {
////        yuzmede = false;
////        karakterY = merdivenAltY;
////    }
////}
////
////
////
////void StartGame(void*) {
////    
////    
////    if (!assetsYuklendi) return; // Eğer varlıklar yüklenmediyse oyunu başlatma
////    
////    // 🎯 "Start Game" butonunu kaldır
////    ICG_DestroyWidget(startGameButton);
////
////    oyunBasladi = true; // Oyun başladı
////    fishX = 574;
////    fishY = 440;
////    
////    while (oyunCalisiyor) {
////
////        
////
////        // 🎯 Animasyon karesi değiştir (sadece kuş, balık ve yarasa için)
////        static int frameCounter = 0;
////        frameCounter++;
////        if (frameCounter % 5 == 0) {
////            birdAnimasyonKare = (birdAnimasyonKare + 1) % 4;
////            fishAnimasyonKare = (fishAnimasyonKare + 1) % 2;
////            batAnimasyonKare = (batAnimasyonKare + 1) % 2;
////        }
////
////        // Kuş hareketi
////        birdX += birdYon * hareketHizi;
////        if (birdX <= 100 || birdX >= 700) birdYon *= -1;
////
////        // Balık hareketi
////        fishX += fishYon * hareketHizi;
////        if (fishX <= 202) fishYon = 1;
////        if (fishX >= 574) fishYon = -1;
////
////        // Balık Y ekseninde hafif dalgalanmalı
////        fishY += (rand() % 3 - 1);
////        if (fishY < 420) fishY = 420;
////        if (fishY > 473) fishY = 473;
////
////        // Yarasa hareketi
////        batX += batYon * hareketHizi;
////        if (batX <= 100 || batX >= 700) batYon *= -1;
////
////        // 🎯 Ekranı yenile
////        UpdateScreen();
////
////        Sleep(100);
////    }
////}
////void KeyboardInput(int key) {
////    bool hareketEtti = false;
////
////    // 🎯 Eğer karakter yüzmeden çıkmışsa, tekrar yüzmesini engelle
////    if (yuzmedenCikti) {
////        yuzmede = false;
////    }
////
////    // 🎯 Eğer yüzme modundan çıkması gerekiyorsa
////    if (karakterX >= 576 && karakterY == 370) {
////        yuzmede = false;
////    }
////
////    // 🎯 Karakter ilerlerken 400’e ulaştığında arka plan kaymaya başlasın
////    if (karakterX >= 400) {
////        gecisBasladi = true;
////    }
////
////    yuzmeModuGuncelle(); // 🎯 Her girişte yüzme modunu kontrol et
////
////    if (merdivendeMi(karakterX, karakterY)) {
////        // 🎯 Merdivenden aşağı inme ve çıkma
////        if (key == 38 && karakterY > merdivenUstY) { // Yukarı çıkma
////            karakterY -= hareketMesafesi;
////            hareketEtti = true;
////        }
////        else if (key == 40 && karakterY < merdivenAltY) { // Aşağı inme
////            karakterY += hareketMesafesi;
////            hareketEtti = true;
////        }
////
////        // 🎯 Eğer karakter Y = 370 olduysa artık merdivende değil
////        if (karakterY >= 370) {
////            karakterX += 10;  // Karakteri biraz ileri taşı (merdivenden çıkmış gibi)
////        }
////    }
////    else if (yuzmede && !yuzmedenCikti) { // 🎯 Eğer karakter yüzmeden çıkmadıysa yüzmeye izin ver
////        // 🎯 Yüzme Alanı İçinde Hareket Etme
////        switch (key) {
////        case 37: // Sol
////            if (karakterX > yuzmeAlaniX) {
////                karakterX -= hareketMesafesi;
////                hareketEtti = true;
////            }
////            break;
////        case 39: // Sağ
////            if (karakterX < yuzmeAlaniX + yuzmeAlaniGenislik - 40) {
////                karakterX += hareketMesafesi;
////                hareketEtti = true;
////            }
////            break;
////        case 38: // Yukarı
////            if (karakterY > yuzmeAlaniY) {
////                karakterY -= hareketMesafesi;
////                hareketEtti = true;
////            }
////            break;
////        case 40: // Aşağı
////            if (karakterY < yuzmeAlaniY + yuzmeAlaniYukseklik - 40) {
////                karakterY += hareketMesafesi;
////                hareketEtti = true;
////            }
////            break;
////        }
////    }
////    else { // 🎯 Normal yürüyüş işlemleri (yüzmede değilse buraya girer)
////        if (key == 37 && karakterX > 50) { // Sol
////            karakterX -= hareketMesafesi;
////            hareketEtti = true;
////        }
////        else if (key == 39) { // Sağ
////            karakterX += hareketMesafesi;
////            hareketEtti = true;
////
////            // 🎯 Eğer geçiş başladıysa, kayma miktarını artır
////            if (gecisBasladi && gecisKaymaMiktari < 800) {
////                gecisKaymaMiktari += hareketMesafesi;
////            }
////        }
////    }
////
////    if (hareketEtti) {
////        animasyonKare = (animasyonKare + 1) % 4;
////        ICG_printf(MouseLogBox, "Karakter Konum: X=%d, Y=%d, Yüzme: %d\n", karakterX, karakterY, yuzmede);
////        UpdateScreen();
////    }
////}
////
////
////void ICGUI_main() {
////    PlaySound("Remembrance.wav", NULL, SND_ASYNC);
////    F1 = ICG_FrameThin(5, 5, 800, 600);
////    ICG_Button(270, 250, 150, 45, "Load Assets", LoadGameAssets);
////    ICG_TButton(270, 295, 150, 45, "Start Game", StartGame, NULL);
////    
////    LoadGameAssets(); // İlk olarak giriş ekranını yükle
////    DisplayImage(F1, enterScreen); // Giriş ekranını göster
////
////    MouseLogBox = ICG_MLEditSunken(10, 700, 600, 80, "", SCROLLBAR_V);
////
////    ICG_SetOnKeyPressed(KeyboardInput);
////}
//
////
////#include <windows.h>
////#include "icb_gui.h"
////#include <thread>
////#include <atomic>
////#include <chrono>
////#include <mutex>
////
////#include <mmsystem.h>  // Windows için ses fonksiyonları (PlaySound için)
////#pragma comment(lib, "winmm.lib")  // PlaySound fonksiyonu için gerekli kütüphane
////
////bool ucusAktif = false;  // Karakter uçuş modunda mı?
////int hedefX = 66, hedefY = 280; // Karakterin başlangıç noktası
////float ucusHizX = 0, ucusHizY = 0;
////const float ucusHizCarpani = 0.1; // Hız katsayısı
////
////int F1;
////ICBYTES arkaplanilk, arkaplandevam, Character, Bird, Fish, Bat, Gold, Yuzme;
////ICBYTES CharacterRun[3], CharacterSwim[4], BirdFly[4], FishSwim[2], BatFly[2];
////
////ICBYTES arkaplan2; // arkaplan2
////bool oyunCalisiyor = true;
////bool yuzmedenCikti = false; // Yüzmeden çıkış durumu
////int arkaPlanX = 0;  // Arka planın X ekseninde kaymasını kontrol eden değişken
////const int arkaPlanGecisBaslangici = 500; // Arka planın kaymaya başlayacağı X noktası
////const int maksimumKayma = 100; // Arka planın en fazla ne kadar kayacağını belirler
////bool gecisBasladi = false;  // Arka plan geçişi başladı mı?
////int gecisKaymaMiktari = 0;  // Arkaplan2'nin kayma miktarı
////const int gecisHizi = 10;   // Her güncellemede kaç birim kayacak
////const int gecisTamamlanmaMiktari = 200; // Geçiş tamamlanınca toplam kayma miktarı
////
////bool oyunBasladi = false; // Oyun başlama durumu
////ICBYTES enterScreen;       // Giriş ekranı için resim
////
////int MouseLogBox;
////
////bool ikinciArkaplanAktif = false; // arka plan
////
////// Karakter değişkenleri
////int karakterX = 66, karakterY = 280;
////const int hareketMesafesi = 10;
////bool yuzmede = false;
////bool ziplamaAktif = false;
////int animasyonKare = 0;
////
////// Kuş, balık ve yarasa için animasyon kareleri
////int birdAnimasyonKare = 0;
////int fishAnimasyonKare = 0;
////int batAnimasyonKare = 0;
////
////// Merdiven koordinatları
////const int merdivenSolX = 116, merdivenSagX = 130;
////const int merdivenUstY = 280, merdivenAltY = 370;
////
////// Yüzme alanı koordinatları
////const int yuzmeAlaniX = 175, yuzmeAlaniY = 415;
////const int yuzmeAlaniGenislik = 424, yuzmeAlaniYukseklik = 84;
////
////// Objelerin başlangıç konumları
////int birdX = 440, birdY = 247, birdYon = -1;
////int fishX = 546, fishY = 432, fishYon = -1;
////int batX = 309, batY = 160, batYon = -1;
////const int hareketHizi = 5;
////
////// Altın konumu
////int goldX = 500, goldY = 400;
////bool goldGorunur = true;
////
////int loadAssetsButton, startGameButton; // Butonları kontrol etmek için ID'ler
////bool assetsYuklendi = false; // Varlıkların yüklenip yüklenmediğini takip eder
////
////
////// Yüzme alanı
//////int yuzmeAlaniX = 175;
//////int yuzmeAlaniY = 415;
//////int yuzmeAlaniGenislik = 424;
//////int yuzmeAlaniYukseklik = 84;
////
////// Merdivende mi?
////void BaslangicaUcusBaslat() {
////    ucusAktif = true;
////
////    float deltaX = hedefX - karakterX;
////    float deltaY = hedefY - karakterY;
////
////    // Hareket hızını hesapla (daha yavaş ve kontrollü olacak)
////    ucusHizX = deltaX * ucusHizCarpani;
////    ucusHizY = deltaY * ucusHizCarpani;
////
////    ICG_printf(MouseLogBox, "🚀 Uçuş Başladı! Karakter X=%d, Y=%d -> Hedef X=%d, Y=%d\n", karakterX, karakterY, hedefX, hedefY);
////}
////
////
////void BaslangicaUcusGuncelle() {
////    if (!ucusAktif) return;
////
////    // 🎯 Karakteri yavaşça başlangıca doğru hareket ettir
////    karakterX += ucusHizX;
////    karakterY += ucusHizY;
////
////    // 🚀 Başlangıç noktasına ulaştığında uçuşu bitir
////    if (abs(karakterX - hedefX) < 2 && abs(karakterY - hedefY) < 2) {
////        karakterX = hedefX;
////        karakterY = hedefY;
////        ucusAktif = false;
////
////        // 🎯 Oyun başlangıç konumuna döndü
////        yuzmede = false;
////        animasyonKare = 0;
////        ICG_printf(MouseLogBox, "✅ Karakter Başlangıca Döndü!\n");
////    }
////}
////
////bool BaliklaCarpistiMi() {
////    int karakterGenislik = 20;  // Daha küçük hitbox
////    int karakterYukseklik = 20; // Daha küçük hitbox
////    int balikGenislik = 40;     // Balık için küçültülmüş hitbox
////    int balikYukseklik = 25;    // Balık için küçültülmüş hitbox
////
////    int karakterMerkezX = karakterX + karakterGenislik / 2;
////    int karakterMerkezY = karakterY + karakterYukseklik / 2;
////
////    int balikMerkezX = fishX + balikGenislik / 2;
////    int balikMerkezY = fishY + balikYukseklik / 2;
////
////    int carpismaMesafesiX = (karakterGenislik + balikGenislik) / 2 - 10; // Daraltılmış çarpışma alanı
////    int carpismaMesafesiY = (karakterYukseklik + balikYukseklik) / 2 - 10; // Daraltılmış çarpışma alanı
////
////    bool carpisti = abs(karakterMerkezX - balikMerkezX) < carpismaMesafesiX &&
////        abs(karakterMerkezY - balikMerkezY) < carpismaMesafesiY;
////
////    if (carpisti) {
////        BaslangicaUcusBaslat(); // 🚀 Uçuş başlat
////        ICG_printf(MouseLogBox, "⚠ BALIKLA ÇARPIŞMA! Karakter uçuyor...\n");
////    }
////
////    return carpisti;
////}
////
////
////bool GoldCarpistiMi() {
////    if (!goldGorunur) return false;
////
////    // ✅ Tam olarak X=516, Y=416 olduğunda altını al!
////    if (abs(karakterX - 526) <= 2 && abs(karakterY - 460) <= 2)
////    {
////        goldGorunur = false;
////        ICG_printf(MouseLogBox, "✅ ALTIN ALINDI! Karakter X=%d, Y=%d | Altın X=%d, Y=%d\n",
////            karakterX, karakterY, goldX, goldY);
////        return true;
////    }
////    return false;
////}
////
////
////// Merdivende mi?
////bool merdivendeMi(int x, int y) {
////    // 🎯 Eğer karakter en altta (Y=370) ise artık merdivende değil
////    if (y >= merdivenAltY) return false;
////
////    return (x >= merdivenSolX && x <= merdivenSagX && y >= merdivenUstY && y <= merdivenAltY);
////}
////
////
////// Yüzme alanında mı?
////bool yuzmeAlaniIcindeMi(int x, int y) {
////    return (x >= yuzmeAlaniX && x <= yuzmeAlaniX + yuzmeAlaniGenislik &&
////        y >= yuzmeAlaniY && y <= yuzmeAlaniY + yuzmeAlaniYukseklik);
////}
////
////
////// Balık su alanında hareket etmeli
////const int fishMinX = 250;  // Su içindeki minimum X koordinatı
////const int fishMaxX = 500;  // Su içindeki maksimum X koordinatı
////const int fishMinY = 430;  // Su seviyesine uygun minimum Y
////const int fishMaxY = 450;  // Su içinde hafif yukarı aşağı hareket
////
////void ICGUI_Create() {
////    ICG_MWSize(800, 600);
////    ICG_MWTitle("Abnormal Faction Game");
////}
////
////void LoadGameAssets() {
////    ReadImage("enter.bmp", enterScreen);
////    ReadImage("dene.bmp", arkaplanilk);
////    ReadImage("arkaplandevamdene.bmp", arkaplandevam);
////    ReadImage("girl.bmp", Character);
////    ReadImage("girl.bmp", Yuzme);
////    ReadImage("kus.bmp", Bird);
////    ReadImage("fishh.bmp", Fish);
////    ReadImage("batt.bmp", Bat);
////    ReadImage("gold1.bmp", Gold);
////
////    // Koşma Animasyonu
////    ICBYTES charRunCoords{ {8, 9, 40, 60}, {58, 10, 40, 60}, {110, 10, 40, 60} };
////    for (int i = 0; i < 3; i++) {
////        Copy(Character, charRunCoords.I(1, i + 1), charRunCoords.I(2, i + 1),
////            charRunCoords.I(3, i + 1), charRunCoords.I(4, i + 1), CharacterRun[i]);
////    }
////
////    // Yüzme Animasyonu
////    ICBYTES swimCoords{ {8, 85, 52, 30}, {66, 85, 56, 33}, {130, 85, 53, 31}, {187, 85, 57, 32} };
////    for (int i = 0; i < 4; i++) {
////        Copy(Yuzme, swimCoords.I(1, i + 1), swimCoords.I(2, i + 1),
////            swimCoords.I(3, i + 1), swimCoords.I(4, i + 1), CharacterSwim[i]);
////    }
////
////    // Kuş Animasyonu
////    ICBYTES birdCoords{ {6, 2, 39, 24}, { 55,11,39,23 }, { 9,35,38,26 }, { 49,61,40,30 } };
////    for (int i = 0; i < 4; i++) {
////        Copy(Bird, birdCoords.I(1, i + 1), birdCoords.I(2, i + 1),
////            birdCoords.I(3, i + 1), birdCoords.I(4, i + 1), BirdFly[i]);
////    }
////
////    // Balık Animasyonu
////    ICBYTES fishCoords{ {16,30,53,37},{16,73,53,39},{84,30,51,37},{84,74,49,39} };
////    for (int i = 0; i < 4; i++) {
////        Copy(Fish, fishCoords.I(1, i + 1), fishCoords.I(2, i + 1),
////            fishCoords.I(3, i + 1), fishCoords.I(4, i + 1), FishSwim[i]);
////    }
////
////    // Yarasa Animasyonu
////    ICBYTES batCoords{ {5, 24, 49, 43}, {56, 24, 41, 27} };
////    for (int i = 0; i < 2; i++) {
////        Copy(Bat, batCoords.I(1, i + 1), batCoords.I(2, i + 1),
////            batCoords.I(3, i + 1), batCoords.I(4, i + 1), BatFly[i]);
////    }
////
////    DisplayImage(F1, enterScreen);
////
////    ICG_DestroyWidget(loadAssetsButton);
////
////    assetsYuklendi = true;
////}
////void UpdateScreen() {
////    // ✈ Uçuşu güncelle
////    BaslangicaUcusGuncelle();
////
////    // Eğer karakter X=350’ye ulaştıysa, arka plan kaymaya başlasın
////    if (karakterX >= 350) {
////        gecisBasladi = true;
////    }
////
////    // Eğer geçiş başladıysa, arka plan karakterin ilerlemesine bağlı olarak kaymaya devam etmeli
////    if (gecisKaymaMiktari > 700) {
////        gecisKaymaMiktari = 700;  // Maksimum 700 kayabilir (tam ekran boyutu kadar)
////    }
////    else if (gecisBasladi) {
////        gecisKaymaMiktari = karakterX - 350;
////    }
////
////    // *🔥 İlk ve ikinci arka planı yükle*
////    ReadImage("dene.bmp", arkaplanilk);
////    ReadImage("arkaplan2.bmp", arkaplan2);
////
////    // *🔥 Geçici bir buffer oluştur (tamamen siyah bir arka plan başlat)*
////    ICBYTES geciciArkaPlan;
////    Copy(arkaplanilk, 0, 0, 700, 500, geciciArkaPlan);  // İlk arka planı geçici buffer olarak kopyala
////    FillRect(geciciArkaPlan, 0, 0, 700, 500, 0); // Buffer'ı tamamen siyah yap (arka planı temizle)
////
////    // *🔥 Eğer ilk arka plan tamamen kaybolmadıysa, sola kaydırarak ekleyelim*
////    if (gecisKaymaMiktari < 700) {
////        PasteNon0(arkaplanilk, -gecisKaymaMiktari, 0, geciciArkaPlan);
////    }
////
////    // *🔥 İkinci arka planı sağdan içeri kaydır ve üstüne ekle*
////    PasteNon0(arkaplan2, 700 - gecisKaymaMiktari, 0, geciciArkaPlan);
////
////    // *🔥 Güncellenmiş arka planı ekrana koy*
////    DisplayImage(F1, geciciArkaPlan);
////
////    // *Karakterin ekran konumunu belirle (arka plan kayarken bile hareket etmeli)*
////    int karakterEkranX = karakterX - gecisKaymaMiktari;
////
////    // *Karakteri ekrana çiz*
////    if (yuzmede) {
////        PasteNon0(CharacterSwim[animasyonKare % 4], karakterEkranX, karakterY, geciciArkaPlan);
////    }
////    else {
////        PasteNon0(CharacterRun[animasyonKare % 3], karakterEkranX, karakterY, geciciArkaPlan);
////    }
////
////    // *Diğer objeleri ekrana çiz (arka plan kaymasını hesaba kat)*
////    PasteNon0(BirdFly[birdAnimasyonKare % 4], birdX - gecisKaymaMiktari, birdY, geciciArkaPlan);
////    PasteNon0(FishSwim[fishAnimasyonKare % 2], fishX - gecisKaymaMiktari, fishY, geciciArkaPlan);
////    PasteNon0(BatFly[batAnimasyonKare % 2], batX - gecisKaymaMiktari, batY, geciciArkaPlan);
////
////    if (goldGorunur) {
////        PasteNon0(Gold, goldX - gecisKaymaMiktari, goldY, geciciArkaPlan);
////    }
////
////    // *🔥 Güncellenmiş ekranı göster*
////    DisplayImage(F1, geciciArkaPlan);
////}
////
////void yuzmeModuGuncelle() {
////    // 🎯 Karakter belirlenen Y ve X pozisyonlarına ulaştığında yüzme moduna geçsin
////    if (!yuzmede && karakterY >= 370 && karakterX >= yuzmeAlaniX + 10) {
////        yuzmede = true;
////        karakterY = yuzmeAlaniY + 5; // Karakter suyun içine girsin
////        animasyonKare = 0; // Animasyonu baştan başlat
////    }
////
////    // 🎯 Karakter yüzme alanından çıkarsa normal moda geri dön
////    if (yuzmede && !yuzmeAlaniIcindeMi(karakterX, karakterY)) {
////        yuzmede = false;
////        karakterY = merdivenAltY; // Karakteri tekrar merdivenin altına koy
////    }
////}
////
////void StartGame(void*) {
////    if (!assetsYuklendi) return; // Eğer varlıklar yüklenmediyse oyunu başlatma
////
////    // 🎯 "Start Game" butonunu kaldır
////    ICG_DestroyWidget(startGameButton);
////
////    oyunBasladi = true; // Oyun başladı
////    fishX = 574;
////    fishY = 440;
////
////    while (oyunCalisiyor) {
////        // 🎯 Animasyon karesi değiştir (sadece kuş, balık ve yarasa için)
////        static int frameCounter = 0;
////        frameCounter++;
////        if (frameCounter % 5 == 0) {
////            birdAnimasyonKare = (birdAnimasyonKare + 1) % 4;
////            fishAnimasyonKare = (fishAnimasyonKare + 1) % 2;
////            batAnimasyonKare = (batAnimasyonKare + 1) % 2;
////        }
////
////        // Kuş hareketi
////        birdX += birdYon * hareketHizi;
////        if (birdX <= 100 || birdX >= 700) birdYon *= -1;
////
////        // Balık hareketi
////        fishX += fishYon * hareketHizi;
////        if (fishX <= 202) fishYon = 1;
////        if (fishX >= 574) fishYon = -1;
////
////        // Balık Y ekseninde hafif dalgalanmalı
////        fishY += (rand() % 3 - 1);
////        if (fishY < 420) fishY = 420;
////        if (fishY > 473) fishY = 473;
////
////        // Yarasa hareketi
////        batX += batYon * hareketHizi;
////        if (batX <= 100 || batX >= 700) batYon *= -1;
////
////        // 🎯 Ekranı yenile
////        UpdateScreen();
////
////        Sleep(100);
////    }
////}
////void KeyboardInput(int key) {
////    bool hareketEtti = false;
////
////    // 🎯 Eğer karakter yüzmeden çıkmışsa, tekrar yüzmesini engelle
////    if (yuzmedenCikti) {
////        yuzmede = false;
////    }
////
////    // 🎯 Eğer yüzme modundan çıkması gerekiyorsa
////    if (karakterX >= 576 && karakterY == 370) {
////        yuzmede = false;
////    }
////
////    // 🎯 Karakter ilerlerken 400’e ulaştığında arka plan kaymaya başlasın
////    if (karakterX >= 400) {
////        gecisBasladi = true;
////    }
////
////    yuzmeModuGuncelle(); // 🎯 Her girişte yüzme modunu kontrol et
////
////    if (merdivendeMi(karakterX, karakterY)) {
////        // 🎯 Merdivenden aşağı inme ve çıkma
////        if (key == 38 && karakterY > merdivenUstY) { // Yukarı çıkma
////            karakterY -= hareketMesafesi;
////            hareketEtti = true;
////        }
////        else if (key == 40 && karakterY < merdivenAltY) { // Aşağı inme
////            karakterY += hareketMesafesi;
////            hareketEtti = true;
////        }
////
////        // 🎯 Eğer karakter Y = 370 olduysa artık merdivende değil
////        if (karakterY >= 370) {
////            karakterX += 10;  // Karakteri biraz ileri taşı (merdivenden çıkmış gibi)
////        }
////    }
////    else if (yuzmede && !yuzmedenCikti) { // 🎯 Eğer karakter yüzmeden çıkmadıysa yüzmeye izin ver
////        // 🎯 Yüzme Alanı İçinde Hareket Etme
////        switch (key) {
////        case 37: // Sol
////            if (karakterX > yuzmeAlaniX) {
////                karakterX -= hareketMesafesi;
////                hareketEtti = true;
////            }
////            break;
////        case 39: // Sağ
////            if (karakterX < yuzmeAlaniX + yuzmeAlaniGenislik - 40) {
////                karakterX += hareketMesafesi;
////                hareketEtti = true;
////            }
////            break;
////        case 38: // Yukarı
////            if (karakterY > yuzmeAlaniY) {
////                karakterY -= hareketMesafesi;
////                hareketEtti = true;
////            }
////            break;
////        case 40: // Aşağı
////            if (karakterY < yuzmeAlaniY + yuzmeAlaniYukseklik - 40) {
////                karakterY += hareketMesafesi;
////                hareketEtti = true;
////            }
////            break;
////        }
////    }
////    else { // 🎯 Normal yürüyüş işlemleri (yüzmede değilse buraya girer)
////        if (key == 37 && karakterX > 50) { // Sol
////            karakterX -= hareketMesafesi;
////            hareketEtti = true;
////        }
////        else if (key == 39) { // Sağ
////            karakterX += hareketMesafesi;
////            hareketEtti = true;
////
////            // 🎯 Eğer geçiş başladıysa, kayma miktarını artır
////            if (gecisBasladi && gecisKaymaMiktari < 800) {
////                gecisKaymaMiktari += hareketMesafesi;
////            }
////        }
////    }
////
////    if (hareketEtti) {
////        animasyonKare = (animasyonKare + 1) % 4;
////        ICG_printf(MouseLogBox, "Karakter Konum: X=%d, Y=%d, Yüzme: %d\n", karakterX, karakterY, yuzmede);
////        UpdateScreen();
////    }
////}
////
////
////void ICGUI_main() {
////    PlaySound("Remembrance.wav", NULL, SND_ASYNC);
////    F1 = ICG_FrameThin(5, 5, 800, 600);
////    ICG_Button(270, 250, 150, 45, "Load Assets", LoadGameAssets);
////    ICG_TButton(270, 295, 150, 45, "Start Game", StartGame, NULL);
////
////    LoadGameAssets(); // İlk olarak giriş ekranını yükle
////    DisplayImage(F1, enterScreen); // Giriş ekranını göster
////
////    MouseLogBox = ICG_MLEditSunken(10, 700, 600, 80, "", SCROLLBAR_V);
////
////    ICG_SetOnKeyPressed(KeyboardInput);
////}
////
////#include <windows.h>
////#include "icb_gui.h"
////#include <thread>
////#include <atomic>
////#include <chrono>
////#include <mutex>
////#include <mmsystem.h>  // Windows için ses fonksiyonları (PlaySound için)
////#pragma comment(lib, "winmm.lib")  // PlaySound fonksiyonu için gerekli kütüphane
////bool ucusAktif = false;  // Karakter uçuş modunda mı?
////int hedefX = 66, hedefY = 280; // Karakterin başlangıç noktası
////float ucusHizX = 0, ucusHizY = 0;
////const float ucusHizCarpani = 0.1; // Hız katsayısı
////
////int F1;
////ICBYTES arkaplanilk, arkaplandevam, Character, Bird, Fish, Bat, Gold, Yuzme;
////ICBYTES CharacterRun[3], CharacterSwim[4], BirdFly[4], FishSwim[2], BatFly[2];
////
////bool oyunCalisiyor = true;
////bool yuzmedenCikti = false; // Yüzmeden çıkış durumu
////
////bool oyunBasladi = false; // Oyun başlama durumu
////ICBYTES enterScreen;       // Giriş ekranı için resim
////
////int MouseLogBox;
////
////// Karakter değişkenleri
////int karakterX = 66, karakterY = 280;
////const int hareketMesafesi = 10;
////bool yuzmede = false;
////bool ziplamaAktif = false;
////int animasyonKare = 0;
////
////// Kuş, balık ve yarasa için animasyon kareleri
////int birdAnimasyonKare = 0;
////int fishAnimasyonKare = 0;
////int batAnimasyonKare = 0;
////
////// Merdiven koordinatları
////const int merdivenSolX = 116, merdivenSagX = 130;
////const int merdivenUstY = 280, merdivenAltY = 370;
////
////// Yüzme alanı koordinatları
////const int yuzmeAlaniX = 175, yuzmeAlaniY = 415;
////const int yuzmeAlaniGenislik = 424, yuzmeAlaniYukseklik = 84;
////
////// Objelerin başlangıç konumları
////int birdX = 440, birdY = 247, birdYon = -1;
////int fishX = 546, fishY = 432, fishYon = -1;
////int batX = 309, batY = 160, batYon = -1;
////const int hareketHizi = 5;
////
////// Altın konumu
////int goldX = 500, goldY = 390;
////bool goldGorunur = true;
////
////int loadAssetsButton, startGameButton; // Butonları kontrol etmek için ID'ler
////bool assetsYuklendi = false; // Varlıkların yüklenip yüklenmediğini takip eder
////
////
////bool altinAlindi = false;
////bool oyunDurdu = false; // Oyun durdu mu?
////
////bool mesajGorunur = false; // "One Life Extra!" mesajı aktif mi?
////int mesajGorunurSuresi = 2000; // Mesajın görünme süresi (milisaniye)
////std::chrono::steady_clock::time_point mesajBaslangicZamani;
////
////const int ekranGenisligi = 700; // Oyun penceresinin genişliği
////const int toplamArkaplanGenisligi = 1400; // İki arkaplanın birleşimi (700px + 700px)
////
////int arkaPlanX = 0;  // Arka planın X ekseninde kaymasını kontrol eden değişken
////const int arkaPlanGecisBaslangici = 500; // Arka planın kaymaya başlayacağı X noktası
////const int maksimumKayma = 100;
////
////bool gecisBasladi = false;  // Arka plan geçişi başladı mı?
////int gecisKaymaMiktari = 0;  // Arkaplan2'nin kayma miktarı
////const int gecisHizi = 10;   // Her güncellemede kaç birim kayacak
////const int gecisTamamlanmaMiktari = 200; // Geçiş tamamlanınca toplam kayma miktarı
////bool ikinciArkaplanAktif = false; // arka plan
////
////
////void ShowOneLifeExtraMessage() {
////    ICG_SLEdit(300, 400, 200, 50, "One Life Extra!");
////}
////
////// Merdivende mi?
////void BaslangicaUcusBaslat() {
////    ucusAktif = true;
////
////    // 🚀 Eğer ekran kayıyorsa, başlangıca dönüşte bu kaymayı iptal et
////    int gercekKarakterX = karakterX + (karakterX >= 356 ? gecisKaymaMiktari : 0);
////
////    // 🚀 SABİT BİR HIZ BELİRLE (YAVAŞ UÇMASINI ENGELLE)
////    ucusHizX = (hedefX - gercekKarakterX) * 0.1; // X hızını hedefe göre ayarla
////    ucusHizY = (hedefY - karakterY) * 0.1; // Y hızını hedefe göre ayarla
////
////    ICG_printf(MouseLogBox, "🚀 Uçuş Başladı! Karakter X=%d (Gerçek: %d), Y=%d -> Hedef X=%d, Y=%d\n",
////        karakterX, gercekKarakterX, karakterY, hedefX, hedefY);
////}
////
////
////void BaslangicaUcusGuncelle() {
////    if (!ucusAktif) return;
////
////
////
////    // 🚀 Karakteri başlangıca doğru hızlı hareket ettir
////    karakterX += ucusHizX;
////    karakterY += ucusHizY;
////
////    // 🚀 Başlangıç noktasına ulaştığında dur
////    if (karakterX <= hedefX || karakterY <= hedefY) {
////        karakterX = hedefX;
////        karakterY = hedefY;
////        ucusAktif = false;  // Uçuşu kapat
////
////        // 🚀 Düzgün şekilde durdur ve sıfırla
////        yuzmede = false;
////        animasyonKare = 0;
////        ICG_printf(MouseLogBox, "✅ Karakter Başlangıca Ulaştı! X=%d, Y=%d\n", karakterX, karakterY);
////    }
////
////    // 🚨 Ekranın dışına çıkmasını önleyelim
////    if (karakterX < 0) karakterX = 0;
////    if (karakterX > 800) karakterX = 800;
////    if (karakterY < 0) karakterY = 0;
////    if (karakterY > 600) karakterY = 600;
////}
////
////
////
////bool BaliklaCarpistiMi() {
////    int karakterGenislik = 20;
////    int karakterYukseklik = 20;
////    int balikGenislik = 40;
////    int balikYukseklik = 25;
////
////    // 🚀 Eğer ekran kayması başladıysa karakterin gerçek X konumunu hesapla
////    int gercekKarakterX = karakterX + (karakterX >= 356 ? gecisKaymaMiktari : 0);
////    int gercekBalikX = fishX - gecisKaymaMiktari; // Balığın kaymasını da hesaba kat
////
////    int karakterMerkezX = gercekKarakterX + karakterGenislik / 2;
////    int karakterMerkezY = karakterY + karakterYukseklik / 2;
////    int balikMerkezX = gercekBalikX + balikGenislik / 2;
////    int balikMerkezY = fishY + balikYukseklik / 2;
////
////    int carpismaMesafesiX = (karakterGenislik + balikGenislik) / 2 + 5;
////    int carpismaMesafesiY = (karakterYukseklik + balikYukseklik) / 2 + 5;
////
////
////    bool carpisti = abs(karakterMerkezX - balikMerkezX) < carpismaMesafesiX &&
////        abs(karakterMerkezY - balikMerkezY) < carpismaMesafesiY;
////
////
////
////    if (carpisti) {
////        BaslangicaUcusBaslat();
////        ICG_printf(MouseLogBox, "⚠ BALIKLA ÇARPIŞMA! Karakter başlangıca uçuyor... Karakter X=%d (Gerçek: %d), Y=%d\n",
////            karakterX, gercekKarakterX, karakterY);
////    }
////
////    ICG_printf(MouseLogBox, "fishX: %d, gercekBalikX: %d\n", fishX, gercekBalikX);
////
////
////    return carpisti;
////}
////
////bool GoldCarpistiMi() {
////    if (!goldGorunur) return false;
////
////    // ✅ Tam olarak X=516, Y=416 olduğunda altını al!
////    if (abs(karakterX - 526) <= 2 && abs(karakterY - 460) <= 2)
////    {
////        goldGorunur = false;
////        ICG_printf(MouseLogBox, "✅ ALTIN ALINDI! Karakter X=%d, Y=%d | Altın X=%d, Y=%d\n",
////            karakterX, karakterY, goldX, goldY);
////        return true;
////    }
////    return false;
////}
////
////bool merdivendeMi(int x, int y) {
////    // 🎯 Eğer karakter en altta (Y=370) ise artık merdivende değil
////    if (y >= merdivenAltY) return false;
////
////    return (x >= merdivenSolX && x <= merdivenSagX && y >= merdivenUstY && y <= merdivenAltY);
////}
////
////
////// Yüzme alanında mı?
////bool yuzmeAlaniIcindeMi(int x, int y) {
////    return (x >= yuzmeAlaniX && x <= yuzmeAlaniX + yuzmeAlaniGenislik &&
////        y >= yuzmeAlaniY && y <= yuzmeAlaniY + yuzmeAlaniYukseklik);
////}
////
////
////// Balık su alanında hareket etmeli
////const int fishMinX = 250;  // Su içindeki minimum X koordinatı
////const int fishMaxX = 500;  // Su içindeki maksimum X koordinatı
////const int fishMinY = 430;  // Su seviyesine uygun minimum Y
////const int fishMaxY = 450;  // Su içinde hafif yukarı aşağı hareket
////
////void ICGUI_Create() {
////    ICG_MWSize(800, 600);
////    ICG_MWTitle("Abnormal Faction Game");
////}
////
////void LoadGameAssets() {
////    ReadImage("enter.bmp", enterScreen);
////    ReadImage("dene.bmp", arkaplanilk);
////    ReadImage("arkaplan2.bmp", arkaplandevam);
////    ReadImage("karakter.bmp", Character);
////    ReadImage("karakter.bmp", Yuzme);
////    ReadImage("kus.bmp", Bird);
////    ReadImage("fishh.bmp", Fish);
////    ReadImage("batt.bmp", Bat);
////    ReadImage("gold1.bmp", Gold);
////
////    // Koşma Animasyonu
////    ICBYTES charRunCoords{ {8, 9, 40, 60}, {58, 10, 40, 60}, {110, 10, 40, 60} };
////    for (int i = 0; i < 3; i++) {
////        Copy(Character, charRunCoords.I(1, i + 1), charRunCoords.I(2, i + 1),
////            charRunCoords.I(3, i + 1), charRunCoords.I(4, i + 1), CharacterRun[i]);
////    }
////
////    // Yüzme Animasyonu
////    ICBYTES swimCoords{ {8, 85, 52, 30}, {66, 85, 56, 33}, {130, 85, 53, 31}, {187, 85, 57, 32} };
////    for (int i = 0; i < 4; i++) {
////        Copy(Yuzme, swimCoords.I(1, i + 1), swimCoords.I(2, i + 1),
////            swimCoords.I(3, i + 1), swimCoords.I(4, i + 1), CharacterSwim[i]);
////    }
////
////    // Kuş Animasyonu
////    ICBYTES birdCoords{ {6, 2, 39, 24}, { 55,11,39,23 }, { 9,35,38,26 }, { 49,61,40,30 } };
////    for (int i = 0; i < 4; i++) {
////        Copy(Bird, birdCoords.I(1, i + 1), birdCoords.I(2, i + 1),
////            birdCoords.I(3, i + 1), birdCoords.I(4, i + 1), BirdFly[i]);
////    }
////
////    // Balık Animasyonu
////    ICBYTES fishCoords{ {16,30,53,37},{16,73,53,39},{84,30,51,37},{84,74,49,39} };
////    for (int i = 0; i < 4; i++) {
////        Copy(Fish, fishCoords.I(1, i + 1), fishCoords.I(2, i + 1),
////            fishCoords.I(3, i + 1), fishCoords.I(4, i + 1), FishSwim[i]);
////    }
////
////    // Yarasa Animasyonu
////    ICBYTES batCoords{ {5, 24, 49, 43}, {56, 24, 41, 27} };
////    for (int i = 0; i < 2; i++) {
////        Copy(Bat, batCoords.I(1, i + 1), batCoords.I(2, i + 1),
////            batCoords.I(3, i + 1), batCoords.I(4, i + 1), BatFly[i]);
////    }
////
////    DisplayImage(F1, enterScreen);
////
////    ICG_DestroyWidget(loadAssetsButton);
////
////    assetsYuklendi = true;
////}
////
////
////void UpdateScreen() {
////
////    BaslangicaUcusGuncelle();
////
////    if (karakterX >= 356) {
////        gecisBasladi = true;
////    }
////
////    if (gecisKaymaMiktari > 700) {
////        gecisKaymaMiktari = 700;
////    }
////    else if (gecisBasladi) {
////        gecisKaymaMiktari = karakterX - 356;
////    }
////
////    ReadImage("dene.bmp", arkaplanilk);
////    ReadImage("arkaplan2.bmp", arkaplandevam);
////
////    ICBYTES geciciArkaPlan;
////    Copy(arkaplanilk, 0, 0, 700, 500, geciciArkaPlan);
////    FillRect(geciciArkaPlan, 0, 0, 700, 500, 0);
////
////    if (gecisKaymaMiktari < 700) {
////        PasteNon0(arkaplanilk, -gecisKaymaMiktari, 0, geciciArkaPlan);
////    }
////
////    PasteNon0(arkaplandevam, 700 - gecisKaymaMiktari, 0, geciciArkaPlan);
////
////    int karakterEkranX = karakterX - gecisKaymaMiktari;
////
////    if (yuzmede) {
////        PasteNon0(CharacterSwim[animasyonKare % 4], karakterEkranX, karakterY, geciciArkaPlan);
////    }
////    else {
////        PasteNon0(CharacterRun[animasyonKare % 3], karakterEkranX, karakterY, geciciArkaPlan);
////    }
////
////    PasteNon0(BirdFly[birdAnimasyonKare % 4], birdX - gecisKaymaMiktari, birdY, geciciArkaPlan);
////    PasteNon0(FishSwim[fishAnimasyonKare % 2], fishX - gecisKaymaMiktari, fishY, geciciArkaPlan);
////    PasteNon0(BatFly[batAnimasyonKare % 2], batX - gecisKaymaMiktari, batY, geciciArkaPlan);
////
////    if (goldGorunur) {
////        PasteNon0(Gold, goldX - gecisKaymaMiktari, goldY, geciciArkaPlan);
////    }
////
////    if (BaliklaCarpistiMi()) {
////        ICG_printf(MouseLogBox, "Karakter başlangıca uçuyor!\n");
////    }
////    if (GoldCarpistiMi()) {
////        ICG_printf(MouseLogBox, "✅ Altın alındı!\n");
////        ICG_SLEdit(500, 400, 100, 25, "One Life Extra!");
////    }
////    // Altını ekrana yerleştir
////    if (goldGorunur) {
////        PasteNon0(Gold, goldX - gecisKaymaMiktari, goldY, geciciArkaPlan);
////
////    }
////    DisplayImage(F1, geciciArkaPlan);
////}
////
////void yuzmeModuGuncelle() {
////    // 🎯 Gerçek karakter X konumunu hesaba kat
////    int gercekKarakterX = karakterX + gecisKaymaMiktari;
////
////    // 🎯 Yüzmeden çıkış noktasını doğru hesapla
////    int yuzmeCikisNoktasi = yuzmeAlaniX + yuzmeAlaniGenislik + 10; // +10 çıkış gecikmesi için
////
////    // 🎯 Eğer karakter yüzmeden çıkması gerekiyorsa
////    if (yuzmede && gercekKarakterX >= yuzmeCikisNoktasi - 10 && karakterY >= yuzmeAlaniY) {
////        yuzmede = false;
////        yuzmedenCikti = true;
////        karakterY = 370; // Karakteri yürüyüş moduna al
////        gecisBasladi = true; // 🎯 İkinci arka planı kaydırmayı başlat!
////        UpdateScreen();
////        ICG_printf(MouseLogBox, "🚶 Karakter yüzmeden çıktı ve yürümeye başladı! X=%d (Gerçek: %d), Y=%d\n", karakterX, gercekKarakterX, karakterY);
////    }
////
////    if (yuzmedenCikti) return;
////
////    // 🎯 Eğer karakter yüzme alanında ise yüzme modunda kalmalı
////    if (!yuzmede && karakterY >= 370 && gercekKarakterX >= yuzmeAlaniX + 10) {
////        yuzmede = true;
////        karakterY = yuzmeAlaniY + 5; // Karakter suyun içine girsin
////        animasyonKare = 0; // Animasyonu baştan başlat
////    }
////
////    // 🎯 Eğer karakter yüzme alanından çıktıysa, tekrar yürümeye geçmeli
////    if (yuzmede && !yuzmeAlaniIcindeMi(gercekKarakterX, karakterY)) {
////        yuzmede = false;
////        karakterY = merdivenAltY; // Karakteri tekrar merdivenin altına koy
////    }
////}
////
////
////
////void StartGame(void*) {
////    if (!assetsYuklendi) return; // Eğer varlıklar yüklenmediyse oyunu başlatma
////
////    // 🎯 "Start Game" butonunu kaldır
////    ICG_DestroyWidget(startGameButton);
////
////    oyunBasladi = true; // Oyun başladı
////    fishX = 574;
////    fishY = 440;
////
////    while (oyunCalisiyor) {
////
////        // 🎯 Animasyon karesi değiştir (sadece kuş, balık ve yarasa için)
////        static int frameCounter = 0;
////        frameCounter++;
////        if (frameCounter % 5 == 0) {
////            birdAnimasyonKare = (birdAnimasyonKare + 1) % 4;
////            fishAnimasyonKare = (fishAnimasyonKare + 1) % 2;
////            batAnimasyonKare = (batAnimasyonKare + 1) % 2;
////        }
////
////        // Kuş hareketi
////        birdX += birdYon * hareketHizi;
////        if (birdX <= 100 || birdX >= 700) birdYon *= -1;
////
////        // Balık hareketi
////        fishX += fishYon * hareketHizi;
////        if (fishX <= 202) fishYon = 1;
////        if (fishX >= 574) fishYon = -1;
////
////        // Balık Y ekseninde hafif dalgalanmalı
////        fishY += (rand() % 3 - 1);
////        if (fishY < 420) fishY = 420;
////        if (fishY > 473) fishY = 473;
////
////        // Yarasa hareketi
////        batX += batYon * hareketHizi;
////        if (batX <= 100 || batX >= 700) batYon *= -1;
////
////        // 🎯 Ekranı yenile
////        UpdateScreen();
////
////        Sleep(100);
////    }
////}
////
////// Klavye Girişi
////void KeyboardInput(int key) {
////    if (mesajGorunur) {
////        return; // Mesaj ekrandayken girişleri engelle
////    }
////
////    // 🛑 Eğer oyun durduysa herhangi bir tuşa basınca devam et
////    if (oyunDurdu) {
////        oyunDurdu = false;  // Oyunu devam ettir
////        ICG_printf(MouseLogBox, "▶ Oyun devam ediyor!\n");
////        UpdateScreen();
////        return;
////    }
////
////    bool hareketEtti = false;
////
////    if (GoldCarpistiMi()) {
////        ICG_SLEdit(300, 400, 100, 25, "One Life Extra!");
////    }
////
////    // 🎯 Space tuşuna basıldığında karakter zıplasın
////    if (key == 32 && !ziplamaAktif) { // 32 -> Space tuşu ASCII kodu
////        ziplamaAktif = true;
////        int ziplamaYuksekligi = 50; // Zıplama yüksekliği
////        int ziplamaHizi = 5; // Her karede ne kadar yukarı çıksın
////
////        for (int i = 0; i < ziplamaYuksekligi / ziplamaHizi; i++) {
////            karakterY -= ziplamaHizi;
////            UpdateScreen();
////            Sleep(30); // Küçük bir gecikme ekleyerek animasyonu sağla
////        }
////
////        // Karakter tekrar aşağı insin
////        for (int i = 0; i < ziplamaYuksekligi / ziplamaHizi; i++) {
////            karakterY += ziplamaHizi;
////            UpdateScreen();
////            Sleep(30);
////        }
////
////        ziplamaAktif = false;
////    }
////
////
////    // 🎯 Eğer karakter yüzme alanından çıkarsa yürümeye devam etmeli
////    if (yuzmede && karakterX >= 576 && karakterY == 370) {
////        yuzmede = false;
////        yuzmedenCikti = true;
////        karakterY = 370; // Karakteri yürüyüş moduna al
////        ICG_printf(MouseLogBox, "🚶 Karakter yüzmeden çıktı ve yürümeye başladı! X=%d, Y=%d\n", karakterX, karakterY);
////    }
////
////    if (karakterX >= 400) {
////        gecisBasladi = true;
////    }
////
////    yuzmeModuGuncelle(); // 🎯 Yüzme modunu kontrol et
////
////    // 🎯 Merdivende mi?
////    if (merdivendeMi(karakterX, karakterY)) {
////        if (key == 38 && karakterY > merdivenUstY) {
////            karakterY -= hareketMesafesi;
////            hareketEtti = true;
////        }
////        else if (key == 40 && karakterY < merdivenAltY) {
////            karakterY += hareketMesafesi;
////            hareketEtti = true;
////        }
////
////        if (karakterY >= 370) {
////            karakterX += 10;
////        }
////    }
////    // 🎯 Eğer yüzmede ise yüzme hareketlerini uygula
////    else if (yuzmede && !yuzmedenCikti) {
////        switch (key) {
////        case 37: if (karakterX > yuzmeAlaniX) { karakterX -= hareketMesafesi; hareketEtti = true; } break;
////        case 39: if (karakterX < yuzmeAlaniX + yuzmeAlaniGenislik - 40) { karakterX += hareketMesafesi; hareketEtti = true; } break;
////        case 38: if (karakterY > yuzmeAlaniY) { karakterY -= hareketMesafesi; hareketEtti = true; } break;
////        case 40: if (karakterY < yuzmeAlaniY + yuzmeAlaniYukseklik - 40) { karakterY += hareketMesafesi; hareketEtti = true; } break;
////        }
////    }
////    // 🎯 Eğer karakter yürümeye geçtiyse, ikinci arkaplana doğru ilerlemesini sağla
////    else {
////        if (key == 37 && karakterX > 50) { // Sol
////            karakterX -= hareketMesafesi;
////            hareketEtti = true;
////        }
////        else if (key == 39) { // Sağ
////            karakterX += hareketMesafesi;
////            hareketEtti = true;
////
////            // 🎯 Eğer ikinci arkaplana geçtiyse, arkaplanı kaydır
////            if (gecisBasladi && gecisKaymaMiktari < 800) {
////                gecisKaymaMiktari += hareketMesafesi;
////            }
////        }
////    }
////
////    if (hareketEtti) {
////        animasyonKare = (animasyonKare + 1) % 4;
////        ICG_printf(MouseLogBox, "Karakter Konum: X=%d, Y=%d, Yüzme: %d\n", karakterX, karakterY, yuzmede);
////        UpdateScreen();
////    }
////
////    if (BaliklaCarpistiMi()) {
////        ICG_printf(MouseLogBox, "⚠ Balıkla Çarpışma Algılandı!\n");
////    }
////
////}
////
////void ICGUI_main() {
////    PlaySound("Remembrance.wav", NULL, SND_ASYNC);
////    F1 = ICG_FrameThin(5, 5, 800, 600);
////    ICG_Button(270, 250, 150, 45, "Load Assets", LoadGameAssets);
////    ICG_TButton(270, 295, 150, 45, "Start Game", StartGame, NULL);
////
////    LoadGameAssets(); // İlk olarak giriş ekranını yükle
////    DisplayImage(F1, enterScreen); // Giriş ekranını göster
////
////    MouseLogBox = ICG_MLEditSunken(10, 700, 600, 80, "", SCROLLBAR_V);
////
////    ICG_SetOnKeyPressed(KeyboardInput);
////}
//
//#include <windows.h>
//#include "icb_gui.h"
//#include <thread>
//#include <atomic>
//#include <chrono>
//#include <mutex>
//#include <mmsystem.h>  // Windows için ses fonksiyonları (PlaySound için)
//#pragma comment(lib, "winmm.lib")  // PlaySound fonksiyonu için gerekli kütüphane
//
//bool ucusAktif = false;
//int hedefX = 66, hedefY = 280;
//float ucusHizX = 0, ucusHizY = 0;
//const float ucusHizCarpani = 0.1; // Hız katsayısı
//
//// Balık su alanında hareket etmeli
//const int fishMinX = 250;  // Su içindeki minimum X koordinatı
//const int fishMaxX = 500;  // Su içindeki maksimum X koordinatı
//const int fishMinY = 430;  // Su seviyesine uygun minimum Y
//const int fishMaxY = 450;  // Su içinde hafif yukarı aşağı hareket
//
//
//int F1;
//ICBYTES arkaplanilk, arkaplandevam, Character, Bird, Fish, Bat, Gold, Yuzme;
//ICBYTES CharacterRun[3], CharacterSwim[4], BirdFly[4], FishSwim[2], BatFly[2];
//
//ICBYTES arkaplan2; // arkaplan2
//bool oyunCalisiyor = true;
//bool yuzmedenCikti = false; // Yüzmeden çıkış durumu
//int arkaPlanX = 0;  // Arka planın X ekseninde kaymasını kontrol eden değişken
//const int arkaPlanGecisBaslangici = 500; // Arka planın kaymaya başlayacağı X noktası
//const int maksimumKayma = 100; // Arka planın en fazla ne kadar kayacağını belirler
//bool gecisBasladi = false;  // Arka plan geçişi başladı mı?
//int gecisKaymaMiktari = 0;  // Arkaplan2'nin kayma miktarı
//const int gecisHizi = 10;   // Her güncellemede kaç birim kayacak
//const int gecisTamamlanmaMiktari = 200; // Geçiş tamamlanınca toplam kayma miktarı
//
//
//bool oyunBasladi = false; // Oyun başlama durumu
//ICBYTES enterScreen;       // Giriş ekranı için resim
//
//int MouseLogBox;
//
//bool ikinciArkaplanAktif = false; // arka plan
//
//// Karakter değişkenleri
//int karakterX = 66, karakterY = 280;
//const int hareketMesafesi = 10;
//bool yuzmede = false;
//bool ziplamaAktif = false;
//int animasyonKare = 0;
//
//// Kuş, balık ve yarasa için animasyon kareleri
//int birdAnimasyonKare = 0;
//int fishAnimasyonKare = 0;
//int batAnimasyonKare = 0;
//
//// Merdiven koordinatları
//const int merdivenSolX = 116, merdivenSagX = 130;
//const int merdivenUstY = 280, merdivenAltY = 370;
//
//// Yüzme alanı koordinatları
//const int yuzmeAlaniX = 175, yuzmeAlaniY = 415;
//const int yuzmeAlaniGenislik = 424, yuzmeAlaniYukseklik = 84;
//
//// Objelerin başlangıç konumları
//int birdX = 440, birdY = 247, birdYon = -1;
//int fishX = 546, fishY = 432, fishYon = -1;
//int batX = 309, batY = 160, batYon = -1;
//const int hareketHizi = 5;
//
//// Altın konumu
//int goldX = 500, goldY = 400;
//bool goldGorunur = true;
//
//int loadAssetsButton, startGameButton; // Butonları kontrol etmek için ID'ler
//bool assetsYuklendi = false; // Varlıkların yüklenip yüklenmediğini takip eder
//
//int mesajGorunurSuresi = 4000; // Mesajın görünme süresi (milisaniye) - 4 saniye
//std::chrono::steady_clock::time_point mesajBaslangicZamani;
//bool mesajGorunur = false;
//
//// Yüzme alanı
////int yuzmeAlaniX = 175;
////int yuzmeAlaniY = 415;
////int yuzmeAlaniGenislik = 424;
////int yuzmeAlaniYukseklik = 84;
//
//// Merdivende mi?
//void BaslangicaUcusBaslat() {
//    // Ekran kayma miktarını sıfırla, uçuş başlamadan önce kayma miktarını hesaba katma
//    gecisKaymaMiktari = 0;
//
//    ucusAktif = true;
//    float deltaX = hedefX - karakterX;
//    float deltaY = hedefY - karakterY;
//    ucusHizX = deltaX * ucusHizCarpani;
//    ucusHizY = deltaY * ucusHizCarpani;
//    ICG_printf(MouseLogBox, "Uçuş Başladı! Karakter X=%d, Y=%d -> Hedef X=%d, Y=%d\n", karakterX, karakterY, hedefX, hedefY);
//}
//
//bool GoldCarpistiMi() {
//    if (!goldGorunur) return false;
//
//    // ✅ Tam olarak X=516, Y=416 olduğunda altını al!
//    if (abs(karakterX - 526) <= 2 && abs(karakterY - 460) <= 2)
//    {
//        goldGorunur = false;
//        mesajGorunur = true;  // Mesajı aktif et
//        mesajBaslangicZamani = std::chrono::steady_clock::now();  // Başlangıç zamanını kaydet
//
//        ICG_printf(MouseLogBox, "ALTIN ALINDI! Karakter X=%d, Y=%d | Altın X=%d, Y=%d\n",
//            karakterX, karakterY, goldX, goldY);
//        return true;
//    }
//    return false;
//}
//
////void BalikHareketi() {
////    // Balık Y ekseninde hafif dalgalanmalı hareket eder
////    fishY += (rand() % 3 - 1);  // Balık, y ekseninde rastgele hareket eder
////    if (fishY < fishMinY) fishY = fishMinY;
////    if (fishY > fishMaxY) fishY = fishMaxY;
////
////    // Balık X ekseninde sınırlı hareket eder
////    fishX += fishYon * hareketHizi;
////    if (fishX <= fishMinX) fishYon = 1;
////    if (fishX >= fishMaxX) fishYon = -1;
////}
//
//void BalikHareketi() {
//    // Balık Y ekseninde hafif dalgalanmalı hareket eder
//    fishY += (rand() % 3 - 1);  // Balık, y ekseninde rastgele hareket eder
//    if (fishY < fishMinY) fishY = fishMinY;
//    if (fishY > fishMaxY) fishY = fishMaxY;
//
//    // Balık X ekseninde sınırlı hareket eder
//    fishX += fishYon * hareketHizi;
//    if (fishX <= fishMinX) fishYon = 1;
//    if (fishX >= fishMaxX) fishYon = -1;
//
//}
//bool merdivendeMi(int x, int y) {
//    // 🎯 Eğer karakter en altta (Y=370) ise artık merdivende değil
//    if (y >= merdivenAltY) return false;
//
//    return (x >= merdivenSolX && x <= merdivenSagX && y >= merdivenUstY && y <= merdivenAltY);
//}
//
////// Yüzme alanında mı?
////bool yuzmeAlaniIcindeMi(int x, int y) {
////    return (x >= yuzmeAlaniX && x <= yuzmeAlaniX + yuzmeAlaniGenislik &&
////        y >= yuzmeAlaniY && y <= yuzmeAlaniY + yuzmeAlaniYukseklik);
////}
//
//// Yüzme alanında mı?
//bool yuzmeAlaniIcindeMi(int x, int y) {
//    return (x >= yuzmeAlaniX && x <= yuzmeAlaniX + yuzmeAlaniGenislik - 10 &&
//        y >= yuzmeAlaniY && y <= yuzmeAlaniY + yuzmeAlaniYukseklik - 5);
//}
//
//void BaslangicaUcusGuncelle() {
//    if (!ucusAktif) return;
//
//
//
//    // 🚀 Karakteri başlangıca doğru hızlı hareket ettir
//    karakterX += ucusHizX;
//    karakterY += ucusHizY;
//
//    // 🚀 Başlangıç noktasına ulaştığında dur
//    if (karakterX <= hedefX || karakterY <= hedefY) {
//        karakterX = hedefX;
//        karakterY = hedefY;
//        ucusAktif = false;  // Uçuşu kapat
//
//        // 🚀 Düzgün şekilde durdur ve sıfırla
//        yuzmede = false;
//        animasyonKare = 0;
//        ICG_printf(MouseLogBox, "✅ Karakter Başlangıca Ulaştı! X=%d, Y=%d\n", karakterX, karakterY);
//    }
//
//    // 🚨 Ekranın dışına çıkmasını önleyelim
//    if (karakterX < 0) karakterX = 0;
//    if (karakterX > 800) karakterX = 800;
//    if (karakterY < 0) karakterY = 0;
//    if (karakterY > 600) karakterY = 600;
//}
//
//
//bool BaliklaCarpistiMi() {
//    int karakterGenislik = 20;  // Daha küçük hitbox
//    int karakterYukseklik = 20; // Daha küçük hitbox
//    int balikGenislik = 40;     // Balık için küçültülmüş hitbox
//    int balikYukseklik = 25;    // Balık için küçültülmüş hitbox
//
//    // Kaymayı dikkate alarak balık ve karakterin merkez koordinatlarını hesapla
//    int karakterMerkezX = karakterX + karakterGenislik / 2;
//    int karakterMerkezY = karakterY + karakterYukseklik / 2;
//
//    // Kaymayı dikkate alarak balığın merkez koordinatlarını hesapla
//    int balikMerkezX = fishX + balikGenislik / 2 - gecisKaymaMiktari;
//    int balikMerkezY = fishY + balikYukseklik / 2;
//
//    int carpismaMesafesiX = (karakterGenislik + balikGenislik) / 2 - 10; // Daraltılmış çarpışma alanı
//    int carpismaMesafesiY = (karakterYukseklik + balikYukseklik) / 2 - 10; // Daraltılmış çarpışma alanı
//
//    bool carpisti = abs(karakterMerkezX - balikMerkezX) < carpismaMesafesiX &&
//        abs(karakterMerkezY - balikMerkezY) < carpismaMesafesiY;
//
//    if (carpisti) {
//        BaslangicaUcusBaslat(); //Uçuş başlat
//        ICG_printf(MouseLogBox, "BALIKLA ÇARPIŞMA! Karakter uçuyor...\n");
//    }
//
//    return carpisti;
//}
//
////bool GoldCarpistiMi() {
////    if (!goldGorunur) return false;
////
////    // ✅ Tam olarak X=516, Y=416 olduğunda altını al!
////    if (abs(karakterX - 526) <= 2 && abs(karakterY - 460) <= 2)
////    {
////        goldGorunur = false;
////        ICG_printf(MouseLogBox, "✅ ALTIN ALINDI! Karakter X=%d, Y=%d | Altın X=%d, Y=%d\n",
////            karakterX, karakterY, goldX, goldY);
////        return true;
////    }
////    return false;
////}
//
//void ICGUI_Create() {
//    ICG_MWSize(800, 600);
//    ICG_MWTitle("Abnormal Faction Game");
//}
//
//void LoadGameAssets() {
//    ReadImage("enter.bmp", enterScreen);
//    ReadImage("dene.bmp", arkaplanilk);
//    ReadImage("arkaplandevamdene.bmp", arkaplandevam);
//    ReadImage("girl.bmp", Character);
//    ReadImage("girl.bmp", Yuzme);
//    ReadImage("kus.bmp", Bird);
//    ReadImage("fishh.bmp", Fish);
//    ReadImage("batt.bmp", Bat);
//    ReadImage("gold1.bmp", Gold);
//
//    // Koşma Animasyonu
//    ICBYTES charRunCoords{ {8, 9, 40, 60}, {58, 10, 40, 60}, {110, 10, 40, 60} };
//    for (int i = 0; i < 3; i++) {
//        Copy(Character, charRunCoords.I(1, i + 1), charRunCoords.I(2, i + 1),
//            charRunCoords.I(3, i + 1), charRunCoords.I(4, i + 1), CharacterRun[i]);
//    }
//
//    // Yüzme Animasyonu
//    ICBYTES swimCoords{ {8, 85, 52, 30}, {66, 85, 56, 33}, {130, 85, 53, 31}, {187, 85, 57, 32} };
//    for (int i = 0; i < 4; i++) {
//        Copy(Yuzme, swimCoords.I(1, i + 1), swimCoords.I(2, i + 1),
//            swimCoords.I(3, i + 1), swimCoords.I(4, i + 1), CharacterSwim[i]);
//    }
//
//    // Kuş Animasyonu
//    ICBYTES birdCoords{ {6, 2, 39, 24}, { 55,11,39,23 }, { 9,35,38,26 }, { 49,61,40,30 } };
//    for (int i = 0; i < 4; i++) {
//        Copy(Bird, birdCoords.I(1, i + 1), birdCoords.I(2, i + 1),
//            birdCoords.I(3, i + 1), birdCoords.I(4, i + 1), BirdFly[i]);
//    }
//
//    // Balık Animasyonu
//    ICBYTES fishCoords{ {16,30,53,37},{16,73,53,39},{84,30,51,37},{84,74,49,39} };
//    for (int i = 0; i < 4; i++) {
//        Copy(Fish, fishCoords.I(1, i + 1), fishCoords.I(2, i + 1),
//            fishCoords.I(3, i + 1), fishCoords.I(4, i + 1), FishSwim[i]);
//    }
//
//    // Yarasa Animasyonu
//    ICBYTES batCoords{ {5, 24, 49, 43}, {56, 24, 41, 27} };
//    for (int i = 0; i < 2; i++) {
//        Copy(Bat, batCoords.I(1, i + 1), batCoords.I(2, i + 1),
//            batCoords.I(3, i + 1), batCoords.I(4, i + 1), BatFly[i]);
//    }
//
//    DisplayImage(F1, enterScreen);
//
//    ICG_DestroyWidget(loadAssetsButton);
//
//    assetsYuklendi = true;
//}
//
//void UpdateScreen() {
//    // Arka plan kaydırma işlemi
//    ReadImage("dene.bmp", arkaplanilk);
//    BaslangicaUcusGuncelle();
//    if (karakterX >= 350) {
//        gecisBasladi = true;
//    }
//
//    if (gecisKaymaMiktari > 700) {
//        gecisKaymaMiktari = 700;  // Maksimum kayma
//    }
//    else if (gecisBasladi) {
//        gecisKaymaMiktari = karakterX - 350;
//    }
//
//    // İlk ve ikinci arka planı yükle
//    ReadImage("dene.bmp", arkaplanilk);
//    ReadImage("arkaplan2.bmp", arkaplan2);
//
//    // Geçici buffer oluştur
//    ICBYTES geciciArkaPlan;
//    Copy(arkaplanilk, 0, 0, 700, 500, geciciArkaPlan);
//    FillRect(geciciArkaPlan, 0, 0, 700, 500, 0);
//
//    // Eğer ilk arka plan kaymadıysa, kaydırarak ekleyelim
//    if (gecisKaymaMiktari < 700) {
//        PasteNon0(arkaplanilk, -gecisKaymaMiktari, 0, geciciArkaPlan);
//    }
//
//    // İkinci arka planı sağdan kaydır ve üstüne ekle
//    PasteNon0(arkaplan2, 700 - gecisKaymaMiktari, 0, geciciArkaPlan);
//
//    // Ekran üzerine güncellenmiş arka planı yerleştir
//    //DisplayImage(F1, geciciArkaPlan);
//
//    // Karakterin ekran konumunu belirle
//    int karakterEkranX = karakterX - gecisKaymaMiktari;
//    if (yuzmede) {
//        PasteNon0(CharacterSwim[animasyonKare % 4], karakterEkranX, karakterY, geciciArkaPlan);
//    }
//    else {
//        PasteNon0(CharacterRun[animasyonKare % 3], karakterEkranX, karakterY, geciciArkaPlan);
//    }
//
//    // Diğer objeleri ekrana çiz
//    PasteNon0(BirdFly[birdAnimasyonKare % 4], birdX - gecisKaymaMiktari, birdY, geciciArkaPlan);
//    BalikHareketi();  // Balık hareketi
//    //PasteNon0(FishSwim[fishAnimasyonKare % 2], fishX - gecisKaymaMiktari, fishY, geciciArkaPlan);
//    int fishFrame = (fishYon == -1) ? (fishAnimasyonKare % 2) : ((fishAnimasyonKare % 2) + 2);
//    PasteNon0(FishSwim[fishFrame], fishX, fishY, geciciArkaPlan);
//    PasteNon0(BatFly[batAnimasyonKare % 2], batX - gecisKaymaMiktari, batY, geciciArkaPlan);
//    
//    // Altını ekrana yerleştir
//    if (goldGorunur) {
//        PasteNon0(Gold, goldX - gecisKaymaMiktari, goldY, geciciArkaPlan);
//    }
//
//    // Altın çarpışması
//    if (GoldCarpistiMi()) {
//        ICG_printf(MouseLogBox, "Altın alındı!\n");
//        ICG_SLEdit(350, 381, 100, 25, "One Life Extra!");
//    }
//    
//
//    if (BaliklaCarpistiMi()) {
//        ICG_printf(MouseLogBox, "Karakter başlangıca uçuyor!\n");
//        ICG_SLEdit(500, 400, 100, 25, "LIFE 0!");
//    }
//
//    // 🎯 "One Life Extra" mesajını kontrol et
//    if (mesajGorunur) {
//        auto simdikiZaman = std::chrono::steady_clock::now();
//        auto gecenSure = std::chrono::duration_cast<std::chrono::milliseconds>(simdikiZaman - mesajBaslangicZamani).count();
//
//        if (gecenSure < mesajGorunurSuresi) {
//            ICG_SLEdit(350, 381, 150, 30, "One Life Extra!");
//        }
//        else {
//            mesajGorunur = false;  // Süre dolunca mesajı kaldır
//        }
//    }
//
//    // Ekran üzerinde güncellenmiş görüntü
//    DisplayImage(F1, geciciArkaPlan);
//}
//
//void yuzmeModuGuncelle() {
//    if (yuzmede && karakterX >= 566 && karakterY == 410) {
//        yuzmede = false;
//        yuzmedenCikti = true;
//        karakterY = 370;
//
//        gecisBasladi = true; // 🎯 İkinci arka planı kaydırmayı başlat!
//        UpdateScreen(); // 🎯 Ekranı güncelle!
//
//        ICG_printf(MouseLogBox, "Karakter yüzmeden çıktı ve yürümeye başladı! X=%d, Y=%d\n", karakterX, karakterY);
//    }
//
//    if (yuzmedenCikti) return;
//
//    if (!yuzmede && karakterY >= 370 && karakterX >= yuzmeAlaniX + 10) {
//        yuzmede = true;
//        karakterY = yuzmeAlaniY + 5;
//        animasyonKare = 0;
//    }
//
//    if (yuzmede && !yuzmeAlaniIcindeMi(karakterX, karakterY)) {
//        yuzmede = false;
//        karakterY = merdivenAltY;
//    }
//}
//
//void StartGame(void*) {
//    if (!assetsYuklendi) return; // Eğer varlıklar yüklenmediyse oyunu başlatma
//
//    // 🎯 "Start Game" butonunu kaldır
//    ICG_DestroyWidget(startGameButton);
//
//    oyunBasladi = true; // Oyun başladı
//    fishX = 574;
//    fishY = 440;
//
//    while (oyunCalisiyor) {
//        // 🎯 Animasyon karesi değiştir (sadece kuş, balık ve yarasa için)
//        static int frameCounter = 0;
//        frameCounter++;
//        if (frameCounter % 5 == 0) {
//            birdAnimasyonKare = (birdAnimasyonKare + 1) % 4;
//            fishAnimasyonKare = (fishAnimasyonKare + 1) % 2;
//            batAnimasyonKare = (batAnimasyonKare + 1) % 2;
//        }
//
//        // Kuş hareketi
//        birdX += birdYon * hareketHizi;
//        if (birdX <= 100 || birdX >= 700) birdYon *= -1;
//
//        // Balık hareketi
//        fishX += fishYon * hareketHizi;
//        if (fishX <= 202) fishYon = 1;
//        if (fishX >= 574) fishYon = -1;
//
//        // Balık hareketi
//        if (fishX <= fishMinX) fishYon = 1;
//        if (fishX >= fishMaxX) fishYon = -1;
//
//        // Balık Y ekseninde hafif dalgalanmalı
//        fishY += (rand() % 3 - 1);
//        if (fishY < 420) fishY = 420;
//        if (fishY > 473) fishY = 473;
//
//        // Yarasa hareketi
//        batX += batYon * hareketHizi;
//        if (batX <= 100 || batX >= 700) batYon *= -1;
//
//        // 🎯 Ekranı yenile
//        UpdateScreen();
//
//        Sleep(100);
//    }
//}
//void KeyboardInput(int key) {
//    bool hareketEtti = false;
//
//    // Yüzme modunu kontrol et
//    if (yuzmedenCikti) {
//        yuzmede = false;
//    }
//
//    // Yüzme modundan çıkarsa, yüzme modunu engelle
//    if (karakterX >= 576 && karakterY == 370) {
//        yuzmede = false;
//    }
//
//    // Arka plan kaymaya başlasın
//    if (karakterX >= 400) {
//        gecisBasladi = true;
//    }
//
//    // 🎯 Space tuşuna basıldığında karakter zıplasın
//    if (key == 32 && !ziplamaAktif) { // 32 -> Space tuşu ASCII kodu
//        ziplamaAktif = true;
//        int ziplamaYuksekligi = 50; // Zıplama yüksekliği
//        int ziplamaHizi = 5; // Her karede ne kadar yukarı çıksın
//
//        for (int i = 0; i < ziplamaYuksekligi / ziplamaHizi; i++) {
//            karakterY -= ziplamaHizi;
//            UpdateScreen();
//            Sleep(30); // Küçük bir gecikme ekleyerek animasyonu sağla
//        }
//
//        // Karakter tekrar aşağı insin
//        for (int i = 0; i < ziplamaYuksekligi / ziplamaHizi; i++) {
//            karakterY += ziplamaHizi;
//            UpdateScreen();
//            Sleep(30);
//        }
//
//        ziplamaAktif = false;
//    }
//
//    yuzmeModuGuncelle();  // Yüzme modunu kontrol et
//
//    // Merdiven hareketleri
//    if (merdivendeMi(karakterX, karakterY)) {
//        if (key == 38 && karakterY > merdivenUstY) {  // Yukarı çıkma
//            karakterY -= hareketMesafesi;
//            hareketEtti = true;
//        }
//        else if (key == 40 && karakterY < merdivenAltY) {  // Aşağı inme
//            karakterY += hareketMesafesi;
//            hareketEtti = true;
//        }
//
//        if (karakterY >= 370) {
//            karakterX += 10;  // Merdivenden çıktı
//        }
//    }
//    else if (yuzmede && !yuzmedenCikti) {  // Yüzme alanı içinde hareket etme
//        switch (key) {
//        case 37: // Sol
//            if (karakterX > yuzmeAlaniX) {
//                karakterX -= hareketMesafesi;
//                hareketEtti = true;
//            }
//            break;
//        case 39: // Sağ
//            if (karakterX < yuzmeAlaniX + yuzmeAlaniGenislik - 40) {
//                karakterX += hareketMesafesi;
//                hareketEtti = true;
//            }
//            break;
//        case 38: // Yukarı
//            if (karakterY > yuzmeAlaniY) {
//                karakterY -= hareketMesafesi;
//                hareketEtti = true;
//            }
//            break;
//        case 40: // Aşağı
//            if (karakterY < yuzmeAlaniY + yuzmeAlaniYukseklik - 40) {
//                karakterY += hareketMesafesi;
//                hareketEtti = true;
//            }
//            break;
//        }
//    }
//    else {  // Normal yürüyüş
//        if (key == 37 && karakterX > 50) { // Sol
//            karakterX -= hareketMesafesi;
//            hareketEtti = true;
//        }
//        else if (key == 39) { // Sağ
//            karakterX += hareketMesafesi;
//            hareketEtti = true;
//
//            // Arka plan kayması
//            if (gecisBasladi && gecisKaymaMiktari < 800) {
//                gecisKaymaMiktari += hareketMesafesi;
//            }
//        }
//    }
//
//    if (hareketEtti) {
//        animasyonKare = (animasyonKare + 1) % 4;
//        ICG_printf(MouseLogBox, "Karakter Konum: X=%d, Y=%d, Yüzme: %d\n", karakterX, karakterY, yuzmede);
//        UpdateScreen();  // Ekranı güncelle
//    }
//}
//
//
//void ICGUI_main() {
//    PlaySound("Remembrance.wav", NULL, SND_ASYNC);
//    F1 = ICG_FrameThin(5, 5, 800, 600);
//    ICG_Button(270, 250, 150, 45, "Load Assets", LoadGameAssets);
//    ICG_TButton(270, 295, 150, 45, "Start Game", StartGame, NULL);
//
//    LoadGameAssets(); // İlk olarak giriş ekranını yükle
//    DisplayImage(F1, enterScreen); // Giriş ekranını göster
//
//    MouseLogBox = ICG_MLEditSunken(10, 700, 600, 80, "", SCROLLBAR_V);
//
//    ICG_SetOnKeyPressed(KeyboardInput);
//}

#include <windows.h>
#include "icb_gui.h"
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>

bool ucusAktif = false;
int hedefX = 66, hedefY = 280; // Karakterin başlangıç noktası
float ucusHizX = 0, ucusHizY = 0;
const float ucusHizCarpani = 0.1; // Hız katsayısı

int F1;
ICBYTES arkaplanilk, arkaplandevam, Character, Bird, Fish, Bat, Gold, Yuzme;
ICBYTES CharacterRun[3], CharacterSwim[4], BirdFly[4], FishSwim[2], BatFly[2];

bool oyunCalisiyor = true;
bool yuzmedenCikti = false; // Yüzmeden çıkış durumu

bool oyunBasladi = false; // Oyun başlama durumu
ICBYTES enterScreen;       // Giriş ekranı için resim

int MouseLogBox;

// Karakter değişkenleri
int karakterX = 66, karakterY = 280;
const int hareketMesafesi = 10;
bool yuzmede = false;
bool ziplamaAktif = false;
int animasyonKare = 0;

// Kuş, balık ve yarasa için animasyon kareleri
int birdAnimasyonKare = 0;
int fishAnimasyonKare = 0;
int batAnimasyonKare = 0;

// Merdiven koordinatları
const int merdivenSolX = 116, merdivenSagX = 130;
const int merdivenUstY = 280, merdivenAltY = 370;

// Yüzme alanı koordinatları
const int yuzmeAlaniX = 175, yuzmeAlaniY = 415;
const int yuzmeAlaniGenislik = 486, yuzmeAlaniYukseklik = 84;

// Objelerin başlangıç konumları
int birdX = 440, birdY = 247, birdYon = -1;
int fishX = 546, fishY = 432, fishYon = -1;
int batX = 309, batY = 160, batYon = -1;
const int hareketHizi = 5;

// Altın konumu
int goldX = 500, goldY = 390;
bool goldGorunur = true;

int loadAssetsButton, startGameButton; // Butonları kontrol etmek için ID'ler
bool assetsYuklendi = false; // Varlıkların yüklenip yüklenmediğini takip eder


bool altinAlindi = false;
bool oyunDurdu = false; // Oyun durdu mu?

bool mesajGorunur = false; // "One Life Extra!" mesajı aktif mi?
int mesajGorunurSuresi = 2000; // Mesajın görünme süresi (milisaniye)
std::chrono::steady_clock::time_point mesajBaslangicZamani;

const int ekranGenisligi = 700; // Oyun penceresinin genişliği
const int toplamArkaplanGenisligi = 1400; // İki arkaplanın birleşimi (700px + 700px)

int arkaPlanX = 0;  // Arka planın X ekseninde kaymasını kontrol eden değişken
const int arkaPlanGecisBaslangici = 500; // Arka planın kaymaya başlayacağı X noktası
const int maksimumKayma = 100;

bool gecisBasladi = false;  // Arka plan geçişi başladı mı?
int gecisKaymaMiktari = 0;  // Arkaplan2'nin kayma miktarı
const int gecisHizi = 10;   // Her güncellemede kaç birim kayacak
const int gecisTamamlanmaMiktari = 200; // Geçiş tamamlanınca toplam kayma miktarı
bool ikinciArkaplanAktif = false; // arka plan


void ShowOneLifeExtraMessage() {
    ICG_SLEdit(300, 400, 200, 50, "One Life Extra!");
}

// Merdivende mi?
void BaslangicaUcusBaslat() {
    ucusAktif = true;

    // Eğer ekran kayıyorsa, başlangıca dönüşte bu kaymayı iptal et
    int gercekKarakterX = karakterX + (karakterX >= 356 ? gecisKaymaMiktari : 0);

    // SABİT BİR HIZ BELİRLE (YAVAŞ UÇMASINI ENGELLE)
    ucusHizX = (hedefX - gercekKarakterX) * 0.1; // X hızını hedefe göre ayarla
    ucusHizY = (hedefY - karakterY) * 0.1; // Y hızını hedefe göre ayarla

    ICG_printf(MouseLogBox, "🚀 Uçuş Başladı! Karakter X=%d (Gerçek: %d), Y=%d -> Hedef X=%d, Y=%d\n",
        karakterX, gercekKarakterX, karakterY, hedefX, hedefY);
}


void BaslangicaUcusGuncelle() {
    if (!ucusAktif) return;

    // Karakteri başlangıca doğru hızlı hareket ettir
    karakterX += ucusHizX;
    karakterY += ucusHizY;

    // Başlangıç noktasına ulaştığında dur
    if (karakterX <= hedefX || karakterY <= hedefY) {
        karakterX = hedefX;
        karakterY = hedefY;
        ucusAktif = false;  // Uçuşu kapat

        // Düzgün şekilde durdur ve sıfırla
        yuzmede = false;
        animasyonKare = 0;
        ICG_printf(MouseLogBox, "✅ Karakter Başlangıca Ulaştı! X=%d, Y=%d\n", karakterX, karakterY);
    }

    // Ekranın dışına çıkmasını önleyelim
    if (karakterX < 0) karakterX = 0;
    if (karakterX > 800) karakterX = 800;
    if (karakterY < 0) karakterY = 0;
    if (karakterY > 600) karakterY = 600;
}



bool BaliklaCarpistiMi() {
    int karakterGenislik = 20;
    int karakterYukseklik = 20;
    int balikGenislik = 40;
    int balikYukseklik = 25;

    // Eğer ekran kayması başladıysa karakterin gerçek X konumunu hesapla
    int gercekKarakterX = karakterX + (karakterX >= 356 ? gecisKaymaMiktari : 0);
    int gercekBalikX = fishX - gecisKaymaMiktari; // Balığın kaymasını da hesaba kat

    int karakterMerkezX = gercekKarakterX + karakterGenislik / 2;
    int karakterMerkezY = karakterY + karakterYukseklik / 2;
    int balikMerkezX = gercekBalikX + balikGenislik / 2;
    int balikMerkezY = fishY + balikYukseklik / 2;

    int carpismaMesafesiX = (karakterGenislik + balikGenislik) / 2 + 5;
    int carpismaMesafesiY = (karakterYukseklik + balikYukseklik) / 2 + 5;


    bool carpisti = abs(karakterMerkezX - balikMerkezX) < carpismaMesafesiX &&
        abs(karakterMerkezY - balikMerkezY) < carpismaMesafesiY;



    if (carpisti) {
        BaslangicaUcusBaslat();
        ICG_printf(MouseLogBox, "⚠ BALIKLA ÇARPIŞMA! Karakter başlangıca uçuyor... Karakter X=%d (Gerçek: %d), Y=%d\n",
            karakterX, gercekKarakterX, karakterY);
    }

    ICG_printf(MouseLogBox, "fishX: %d, gercekBalikX: %d\n", fishX, gercekBalikX);


    return carpisti;
}

bool GoldCarpistiMi() {
    if (!goldGorunur) return false;

    // Tam olarak X=516, Y=416 olduğunda altını al!
    if (abs(karakterX - 526) <= 2 && abs(karakterY - 460) <= 2)
    {
        goldGorunur = false;
        ICG_printf(MouseLogBox, "✅ ALTIN ALINDI! Karakter X=%d, Y=%d | Altın X=%d, Y=%d\n",
            karakterX, karakterY, goldX, goldY);
        return true;
    }
    return false;
}

bool merdivendeMi(int x, int y) {
    // Eğer karakter en altta (Y=370) ise artık merdivende değil
    if (y >= merdivenAltY) return false;

    return (x >= merdivenSolX && x <= merdivenSagX && y >= merdivenUstY && y <= merdivenAltY);
}


// Yüzme alanında mı?
bool yuzmeAlaniIcindeMi(int x, int y) {
    return (x >= yuzmeAlaniX && x <= yuzmeAlaniX + yuzmeAlaniGenislik - 10 &&
        y >= yuzmeAlaniY && y <= yuzmeAlaniY + yuzmeAlaniYukseklik - 5);
}



// Balık su alanında hareket etmeli
const int fishMinX = 250;  // Su içindeki minimum X koordinatı
const int fishMaxX = 500;  // Su içindeki maksimum X koordinatı
const int fishMinY = 430;  // Su seviyesine uygun minimum Y
const int fishMaxY = 450;  // Su içinde hafif yukarı aşağı hareket

void ICGUI_Create() {
    ICG_MWSize(800, 600);
    ICG_MWTitle("Abnormal Faction Game");
}

void LoadGameAssets() {
    ReadImage("enter.bmp", enterScreen);
    ReadImage("dene.bmp", arkaplanilk);
    ReadImage("arkaplan2.bmp", arkaplandevam);
    ReadImage("karakter.bmp", Character);
    ReadImage("karakter.bmp", Yuzme);
    ReadImage("kus.bmp", Bird);
    ReadImage("fishh.bmp", Fish);
    ReadImage("batt.bmp", Bat);
    ReadImage("gold1.bmp", Gold);

    // Koşma Animasyonu
    ICBYTES charRunCoords{ {8, 9, 40, 60}, {58, 10, 40, 60}, {110, 10, 40, 60} };
    for (int i = 0; i < 3; i++) {
        Copy(Character, charRunCoords.I(1, i + 1), charRunCoords.I(2, i + 1),
            charRunCoords.I(3, i + 1), charRunCoords.I(4, i + 1), CharacterRun[i]);
    }

    // Yüzme Animasyonu
    ICBYTES swimCoords{ {8, 85, 52, 30}, {66, 85, 56, 33}, {130, 85, 53, 31}, {187, 85, 57, 32} };
    for (int i = 0; i < 4; i++) {
        Copy(Yuzme, swimCoords.I(1, i + 1), swimCoords.I(2, i + 1),
            swimCoords.I(3, i + 1), swimCoords.I(4, i + 1), CharacterSwim[i]);
    }

    // Kuş Animasyonu
    ICBYTES birdCoords{ {6, 2, 39, 24}, { 55,11,39,23 }, { 9,35,38,26 }, { 49,61,40,30 } };
    for (int i = 0; i < 4; i++) {
        Copy(Bird, birdCoords.I(1, i + 1), birdCoords.I(2, i + 1),
            birdCoords.I(3, i + 1), birdCoords.I(4, i + 1), BirdFly[i]);
    }

    // Balık Animasyonu
    ICBYTES fishCoords{ {16,30,53,37},{16,73,53,39},{84,30,51,37},{84,74,49,39} };
    for (int i = 0; i < 4; i++) {
        Copy(Fish, fishCoords.I(1, i + 1), fishCoords.I(2, i + 1),
            fishCoords.I(3, i + 1), fishCoords.I(4, i + 1), FishSwim[i]);
    }

    // Yarasa Animasyonu
    ICBYTES batCoords{ {5, 24, 49, 43}, {56, 24, 41, 27} };
    for (int i = 0; i < 2; i++) {
        Copy(Bat, batCoords.I(1, i + 1), batCoords.I(2, i + 1),
            batCoords.I(3, i + 1), batCoords.I(4, i + 1), BatFly[i]);
    }

    DisplayImage(F1, enterScreen);

    ICG_DestroyWidget(loadAssetsButton);

    assetsYuklendi = true;
}

void UpdateScreen() {

    BaslangicaUcusGuncelle();  // Eğer uçuş devam ediyorsa güncelle

    if (mesajGorunur) {
        ShowOneLifeExtraMessage();
    }

    if (karakterX >= 356) {
        gecisBasladi = true;
    }

    if (gecisKaymaMiktari > 700) {
        gecisKaymaMiktari = 700;
    }
    else if (gecisBasladi) {
        gecisKaymaMiktari = karakterX - 356;
    }

    ReadImage("dene.bmp", arkaplanilk);
    ReadImage("arkaplan2.bmp", arkaplandevam);

    ICBYTES geciciArkaPlan;
    Copy(arkaplanilk, 0, 0, 700, 500, geciciArkaPlan);
    FillRect(geciciArkaPlan, 0, 0, 700, 500, 0);

    if (gecisKaymaMiktari < 700) {
        PasteNon0(arkaplanilk, -gecisKaymaMiktari, 0, geciciArkaPlan);
    }

    PasteNon0(arkaplandevam, 700 - gecisKaymaMiktari, 0, geciciArkaPlan);

    int karakterEkranX = karakterX - gecisKaymaMiktari;

    if (yuzmede) {
        PasteNon0(CharacterSwim[animasyonKare % 4], karakterEkranX, karakterY, geciciArkaPlan);
    }
    else {
        PasteNon0(CharacterRun[animasyonKare % 3], karakterEkranX, karakterY, geciciArkaPlan);
    }

    PasteNon0(BirdFly[birdAnimasyonKare % 4], birdX - gecisKaymaMiktari, birdY, geciciArkaPlan);
    PasteNon0(FishSwim[fishAnimasyonKare % 2], fishX - gecisKaymaMiktari, fishY, geciciArkaPlan);
    PasteNon0(BatFly[batAnimasyonKare % 2], batX - gecisKaymaMiktari, batY, geciciArkaPlan);

    if (goldGorunur) {
        PasteNon0(Gold, goldX - gecisKaymaMiktari, goldY, geciciArkaPlan);
    }

    //  Gold ile çarpışmayı kontrol et
    if (GoldCarpistiMi()) {
        ICG_printf(MouseLogBox, "Altınla çarpışma algılandı! \n");
        ICG_SLEdit(500, 400, 100, 25, "One Life Extra!");
    }
    if (BaliklaCarpistiMi()) {
        ICG_printf(MouseLogBox, "Altınla çarpışma algılandı! \n");
        ICG_SLEdit(500, 400, 100, 25, "LIFE 0!");
    }
    DisplayImage(F1, geciciArkaPlan);
}

void yuzmeModuGuncelle() {
    int gercekKarakterX = karakterX + gecisKaymaMiktari;

    //  Yüzme alanına giriş kontrolü (Yüzme alanına ilk kez giriyorsa)
    if (!yuzmede && karakterY >= merdivenAltY &&
        gercekKarakterX >= yuzmeAlaniX &&
        gercekKarakterX <= yuzmeAlaniX + yuzmeAlaniGenislik - 20) {

        yuzmede = true;
        karakterY = yuzmeAlaniY + 5; // Karakter suyun içine girsin
        animasyonKare = 0;
        ICG_printf(MouseLogBox, "Karakter yüzme moduna girdi! X=%d (Gerçek: %d), Y=%d\n",
            karakterX, gercekKarakterX, karakterY);
    }

    // Eğer karakter yüzmedeyse ve çıkış bölgesine geldiyse çıkmasını sağla
    if (yuzmede && gercekKarakterX >= yuzmeAlaniX + yuzmeAlaniGenislik + gecisKaymaMiktari) {
        yuzmede = false;
        yuzmedenCikti = true;
        karakterY = merdivenAltY; // Karakteri tekrar yere koy
        gecisBasladi = true; // İkinci arka plan kaymasını başlat
        UpdateScreen();
        ICG_printf(MouseLogBox, "Karakter yüzmeden çıktı ve yürümeye başladı! X=%d (Gerçek: %d), Y=%d\n",
            karakterX, gercekKarakterX, karakterY);
    }
}


void StartGame(void*) {
    if (!assetsYuklendi) return;

    ICG_DestroyWidget(startGameButton);
    oyunBasladi = true;

    fishX = 574;
    fishY = 440;

    while (oyunCalisiyor) {
        static int frameCounter = 0;
        frameCounter++;

        //  Animasyonları 5 frame'de bir değiştir
        if (frameCounter % 5 == 0) {
            //  Kuş animasyonu yönüne göre değiştir
            if (birdYon == -1) {
                birdAnimasyonKare = (birdAnimasyonKare + 1) % 2;
            }
            else {
                birdAnimasyonKare = 2 + (birdAnimasyonKare + 1) % 2;
            }

            //  Balık animasyonu yönüne göre değiştir
            if (fishYon == -1) {
                fishAnimasyonKare = (fishAnimasyonKare + 1) % 2;
            }
            else {
                fishAnimasyonKare = 2 + (fishAnimasyonKare + 1) % 2;
            }

            //  Yarasa animasyonu (Bunun yönü değişmiyor)
            batAnimasyonKare = (batAnimasyonKare + 1) % 2;
        }

        //  Kuş hareketi
        birdX += birdYon * hareketHizi;
        if (birdX <= 100 || birdX >= 700) birdYon *= -1;

        //  Balık hareketi
        // Balık hareketi ve dönüş ayarı
        fishX += fishYon * hareketHizi;

        if (fishX <= fishMinX) fishYon = 1;
        if (fishX >= fishMaxX) fishYon = -1;


        //  Balık hafif dalgalanmalı
        fishY += (rand() % 3 - 1);
        if (fishY < 420) fishY = 420;
        if (fishY > 473) fishY = 473;

        // Yarasa hareketi
        batX += batYon * hareketHizi;
        if (batX <= 100 || batX >= 700) batYon *= -1;

        // Ekranı güncelle
        UpdateScreen();
        Sleep(100);
    }
}


// Klavye Girişi
void KeyboardInput(int key) {
    if (mesajGorunur) {
        return; // Mesaj ekrandayken girişleri engelle
    }

    // Eğer oyun durduysa herhangi bir tuşa basınca devam et
    if (oyunDurdu) {
        oyunDurdu = false;  // Oyunu devam ettir
        ICG_printf(MouseLogBox, "Oyun devam ediyor!\n");
        UpdateScreen();
        return;
    }

    bool hareketEtti = false;


    //  Eğer karakter yüzme alanından çıkarsa yürümeye devam etmeli
    if (yuzmede && karakterX >= 566 && karakterY == 410) {
        yuzmede = false;
        yuzmedenCikti = true;
        karakterY = 370; // Karakteri yürüyüş moduna al
        ICG_printf(MouseLogBox, "Karakter yüzmeden çıktı ve yürümeye başladı! X=%d, Y=%d\n", karakterX, karakterY);
    }

    if (karakterX >= 400) {
        gecisBasladi = true;
    }

    if (key == 32 && !ziplamaAktif) { // 32 -> Space tuşu ASCII kodu
        ziplamaAktif = true;
        int ziplamaYuksekligi = 10; // Zıplama yüksekliği
        int ziplamaHizi = 5; // Her karede ne kadar yukarı çıksın

        for (int i = 0; i < ziplamaYuksekligi / ziplamaHizi; i++) {
            karakterY -= ziplamaHizi;
            UpdateScreen();
            Sleep(30); // Küçük bir gecikme ekleyerek animasyonu sağla
        }

        // Karakter tekrar aşağı insin
        for (int i = 0; i < ziplamaYuksekligi / ziplamaHizi; i++) {
            karakterY += ziplamaHizi;
            UpdateScreen();
            Sleep(30);
        }

        ziplamaAktif = false;
    }

    yuzmeModuGuncelle(); //  Yüzme modunu kontrol et

    //  Merdivende mi?
    if (merdivendeMi(karakterX, karakterY)) {
        if (key == 38 && karakterY > merdivenUstY) {
            karakterY -= hareketMesafesi;
            hareketEtti = true;
        }
        else if (key == 40 && karakterY < merdivenAltY) {
            karakterY += hareketMesafesi;
            hareketEtti = true;
        }

        if (karakterY >= 370) {
            karakterX += 10;
        }
    }
    //  Eğer yüzmede ise yüzme hareketlerini uygula
    else if (yuzmede && !yuzmedenCikti) {
        switch (key) {
        case 37: if (karakterX > yuzmeAlaniX) { karakterX -= hareketMesafesi; hareketEtti = true; } break;
        case 39: if (karakterX < yuzmeAlaniX + yuzmeAlaniGenislik - 40) { karakterX += hareketMesafesi; hareketEtti = true; } break;
        case 38: if (karakterY > yuzmeAlaniY) { karakterY -= hareketMesafesi; hareketEtti = true; } break;
        case 40: if (karakterY < yuzmeAlaniY + yuzmeAlaniYukseklik - 40) { karakterY += hareketMesafesi; hareketEtti = true; } break;
        }
    }
    // Eğer karakter yürümeye geçtiyse, ikinci arkaplana doğru ilerlemesini sağla
    else {
        if (key == 37 && karakterX > 50) { // Sol
            karakterX -= hareketMesafesi;
            hareketEtti = true;
        }
        else if (key == 39) { // Sağ
            karakterX += hareketMesafesi;
            hareketEtti = true;

            //  Eğer ikinci arkaplana geçtiyse, arkaplanı kaydır
            if (gecisBasladi && gecisKaymaMiktari < 800) {
                gecisKaymaMiktari += hareketMesafesi;
            }
        }
    }

    if (yuzmede && yuzmedenCikti) {
        yuzmede = false;
        karakterY = merdivenAltY;
        ICG_printf(MouseLogBox, "Karakter yüzmeden çıktı ve yürümeye başladı! X=%d, Y=%d\n", karakterX, karakterY);
    }


    if (hareketEtti) {
        animasyonKare = (animasyonKare + 1) % 4;
        ICG_printf(MouseLogBox, "Karakter Konum: X=%d, Y=%d, Yüzme: %d\n", karakterX, karakterY, yuzmede);
        UpdateScreen();
    }

    if (BaliklaCarpistiMi()) {
        ICG_printf(MouseLogBox, "Balıkla Çarpışma Algılandı!\n");
    }

}

void ICGUI_main() {
    PlaySound("Remembrance.wav", NULL, SND_ASYNC);

    F1 = ICG_FrameThin(5, 5, 800, 600);
    ICG_Button(270, 250, 150, 45, "Load Assets", LoadGameAssets);
    ICG_TButton(270, 295, 150, 45, "Start Game", StartGame, NULL);

    LoadGameAssets(); // İlk olarak giriş ekranını yükle
    DisplayImage(F1, enterScreen); // Giriş ekranını göster

    //MouseLogBox = ICG_MLEditSunken(10, 700, 600, 80, "", SCROLLBAR_V);

    ICG_SetOnKeyPressed(KeyboardInput);
}