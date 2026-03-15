#include <time.h>
#include "search_engine.h"

int main() {
    char searchWord[MAX_WORD_LENGTH];
    char fileList[MAX_FILES][MAX_LINE_LENGTH];
    int fileCount = 0;
    char tempFilename[MAX_LINE_LENGTH];
    int searchMode = 1;

    printf("================================================\n");
    printf("               METIN ARAMA SISTEMI          \n");
    printf("================================================\n\n");

    printf("Aranacak kelimeyi giriniz: ");
    scanf("%255s", searchWord);

    // Kullanicidan arama tercihi aliniyor
    printf("\nArama Modu Seciniz:\n");
    printf("1 - Normal Arama (Ornek: 'el' kelimesi 'elma' icinde de sayilir)\n");
    printf("2 - Tam Eslesme (Sadece bagimsiz 'el' kelimesi sayilir)\n");
    printf("Seciminiz (1/2): ");
    scanf("%d", &searchMode);

    int exactMatch = (searchMode == 2) ? 1 : 0;

    printf("\nTaranacak dosya adlarini giriniz (Ornek: metin.txt).\n");
    printf("Dosya girisini bitirmek icin 'bitir' yaziniz.\n");
    printf("------------------------------------------------\n");

    // Kullanici bitir yazana kadar veya max dosya sayisina ulasana kadar dosya adlarini aliyoruz
    while (fileCount < MAX_FILES) {
        printf("%d. Dosya adi: ", fileCount + 1);
        scanf("%255s", tempFilename);

        if (strcmp(tempFilename, "bitir") == 0) {
            break;
        }

        strcpy(fileList[fileCount], tempFilename);
        fileCount++;
    }

    if (fileCount == 0) {
        printf("\nHic dosya girilmedi. Program kapatiliyor.\n");
        return 0;
    }

    printf("\n================ SONUCLAR ==================\n");

    // Arama suresini olcmek icin saati baslatiyoruz
    clock_t startTime = clock();
    int grandTotalOccurrences = 0;

    // Girilen butun dosyalari donguyle arama fonksiyonuna gonderiyoruz
    for (int i = 0; i < fileCount; i++) {
        grandTotalOccurrences += searchInSingleFile(fileList[i], searchWord, exactMatch);
    }

    clock_t endTime = clock();
    // Gecen sureyi milisaniye cinsinden hesapliyoruz
    double timeSpent = (double)(endTime - startTime) / CLOCKS_PER_SEC * 1000.0;

    // Proje isterlerindeki raporlama kismi
    printf("\n================ PROJE RAPORU ==================\n");
    printf("Aranan Kelime    : %s\n", searchWord);
    printf("Arama Modu       : %s\n", exactMatch ? "Tam Eslesme" : "Normal Arama");
    printf("Taranan Dosya    : %d adet\n", fileCount);
    printf("Toplam Frekans   : %d\n", grandTotalOccurrences);
    printf("Arama Suresi     : %.2f ms\n", timeSpent);
    printf("================================================\n");

    return 0;
}