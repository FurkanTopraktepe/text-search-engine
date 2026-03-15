#include <time.h>
#include "search_engine.h" // Motorumuzun başlık dosyasını ekliyoruz

int main() {
    char searchWord[MAX_WORD_LENGTH];
    char fileList[MAX_FILES][MAX_LINE_LENGTH];
    int fileCount = 0;
    char tempFilename[MAX_LINE_LENGTH];

    printf("====================================================\n");
    printf("       GELISMIS METIN ARAMA MOTORU (v2.0)           \n");
    printf("====================================================\n\n");

    printf("Aranacak kelimeyi giriniz: ");
    scanf("%255s", searchWord);

    printf("\nDosya adlarini tek tek giriniz (Orn: metin1.txt).\n");
    printf("Baska dosya eklemek istemediginizde 'bitir' yaziniz.\n");
    printf("----------------------------------------------------\n");

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
        printf("\nHic dosya girmediniz. Program sonlandiriliyor.\n");
        return 0;
    }

    printf("\n================ ARAMA BASLIYOR ====================\n");

    clock_t startTime = clock();
    int grandTotalOccurrences = 0;

    // Burada search_engine.c içindeki fonksiyonu çağırıyoruz
    for (int i = 0; i < fileCount; i++) {
        grandTotalOccurrences += searchInSingleFile(fileList[i], searchWord);
    }

    clock_t endTime = clock();
    double timeSpent = (double)(endTime - startTime) / CLOCKS_PER_SEC * 1000.0;

    printf("\n================ FINAL RAPORU ======================\n");
    printf("Aranan Kelime    : '%s'\n", searchWord);
    printf("Taranan Dosya    : %d adet\n", fileCount);
    printf("Toplam Bulunma   : %d kez\n", grandTotalOccurrences);
    printf("Arama Suresi     : %.2f milisaniye\n", timeSpent);
    printf("====================================================\n");

    return 0;
}