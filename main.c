#include <time.h>
#include <stdio.h>
#include "search_engine.h"

int main() {
    char searchWord[MAX_WORD_LENGTH];
    char fileList[MAX_FILES][MAX_LINE_LENGTH];
    int fileCount = 0;
    char tempFilename[MAX_LINE_LENGTH];
    int searchMode = 1;

    // --- LOG DOSYASI HAZIRLIĞI ---
    // 'sonuclar.txt' dosyasını yazma modunda ("w") açıyoruz
    FILE *logFile = fopen("sonuclar.txt", "w");
    if (logFile == NULL) {
        printf("Uyari: Rapor dosyasi olusturulamadi, sadece ekrana yazdirilacak.\n");
    }

    // --- GİRİŞ EKRANI ---
    printf("================================================\n");
    printf("               METIN ARAMA SISTEMI          \n");
    printf("================================================\n\n");

    printf("Aranacak kelimeyi giriniz: ");
    scanf("%255s", searchWord);

    // --- MOD SEÇİMİ ---
    printf("\nArama Modu Seciniz:\n");
    printf("1 - Normal Arama (Kelime icinde de sayilir)\n");
    printf("2 - Tam Eslesme (Sadece bagimsiz kelime sayilir)\n");
    printf("Seciminiz (1/2): ");
    
    // Hatalı giriş kontrolü
    if (scanf("%d", &searchMode) != 1 || (searchMode != 1 && searchMode != 2)) {
        printf(COLOR_RED "Hatali secim! Varsayilan olarak Normal Arama secildi.\n" COLOR_RESET);
        searchMode = 1;
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // Giriş tamponunu temizle
    }

    int exactMatch = (searchMode == 2) ? 1 : 0;

    // --- DOSYA LİSTESİ ALMA ---
    printf("\nTaranacak dosya adlarini giriniz (Bitirmek icin 'bitir' yaziniz).\n");
    while (fileCount < MAX_FILES) {
        printf("%d. Dosya adi: ", fileCount + 1);
        scanf("%255s", tempFilename);

        if (strcmp(tempFilename, "bitir") == 0) break;

        strcpy(fileList[fileCount], tempFilename);
        fileCount++;
    }

    if (fileCount == 0) {
        printf("\nHic dosya girilmedi. Program kapatiliyor.\n");
        if(logFile) fclose(logFile);
        return 0;
    }

    printf("\n================ SONUCLAR ==================\n");
    if(logFile) fprintf(logFile, "--- ARAMA DETAYLARI ---\n");

    // --- ARAMA İŞLEMİ VE ZAMAN ÖLÇÜMÜ ---
    clock_t startTime = clock(); // Süre ölçümünü başlat
    int grandTotalOccurrences = 0;

    for (int i = 0; i < fileCount; i++) {
        // Her dosya için arama fonksiyonunu çağır ve sonuçları topla
        grandTotalOccurrences += searchInSingleFile(fileList[i], searchWord, exactMatch, logFile);
    }

    clock_t endTime = clock(); // Süre ölçümünü bitir
    double timeSpent = (double)(endTime - startTime) / CLOCKS_PER_SEC * 1000.0;

    // --- FİNAL RAPORU (Hem Ekrana Hem Dosyaya) ---
    printf("\n================ PROJE RAPORU ==================\n");
    printf("Aranan Kelime    : %s\n", searchWord);
    printf("Arama Modu       : %s\n", exactMatch ? "Tam Eslesme" : "Normal Arama");
    printf("Taranan Dosya    : %d adet\n", fileCount);
    printf("Toplam Frekans   : %d\n", grandTotalOccurrences);
    printf("Arama Suresi     : %.2f ms\n", timeSpent);
    printf("================================================\n");

    if(logFile) {
        fprintf(logFile, "\n================ PROJE RAPORU ==================\n");
        fprintf(logFile, "Aranan Kelime    : %s\n", searchWord);
        fprintf(logFile, "Arama Modu       : %s\n", exactMatch ? "Tam Eslesme" : "Normal Arama");
        fprintf(logFile, "Taranan Dosya    : %d adet\n", fileCount);
        fprintf(logFile, "Toplam Frekans   : %d\n", grandTotalOccurrences);
        fprintf(logFile, "Arama Suresi     : %.2f ms\n", timeSpent);
        fprintf(logFile, "================================================\n");
        
        fclose(logFile); // Log dosyasını güvenli bir şekilde kapat
        printf("\nTum sonuclar 'sonuclar.txt' dosyasina kaydedildi.\n");
    }

    return 0;
}
