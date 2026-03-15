#include "search_engine.h"

// String ifadedeki tum harfleri kucuk harfe ceviren fonksiyon
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Verilen satirin icinde aranan kelimenin kac defa gectigini hesaplar
int countWordInLine(const char *line, const char *word, int exactMatch) {
    int count = 0;
    const char *tmp = line;
    int wordLen = strlen(word);

    // strstr ile kelimeyi satir icinde ariyoruz
    while ((tmp = strstr(tmp, word)) != NULL) {
        if (exactMatch) {
            // Tam eslesme modu: Kelimenin sagi ve solunda harf/rakam olmamali
            int isStartBoundary = (tmp == line) || !isalnum((unsigned char)*(tmp - 1));
            int isEndBoundary = !isalnum((unsigned char)*(tmp + wordLen));

            // Eger bagimsiz bir kelimeyse sayaci artiriyoruz
            if (isStartBoundary && isEndBoundary) {
                count++;
            }
        } else {
            // Normal mod: Kelime baska bir kelimenin icinde gecse bile say
            count++;
        }

        // Sonraki eslesmeyi bulmak icin pointer'i ilerletiyoruz
        tmp += wordLen;
    }
    return count;
}

// Belirtilen dosyayi acip satir satir okuyan ve sonuclari yazdiran fonksiyon
int searchInSingleFile(const char *filename, const char *searchWord, int exactMatch) {
    FILE *file = fopen(filename, "r");

    // Dosya acilirken hata olusursa kullaniciya bilgi ver ve gec
    if (file == NULL) {
        printf(COLOR_RED "Hata: '%s' dosyasi okunamadi veya bulunamadi.\n" COLOR_RESET, filename);
        return 0;
    }

    char buffer[MAX_LINE_LENGTH];
    int lineNumber = 1;
    int fileOccurrences = 0;

    // Buyuk/kucuk harf duyarsiz arama yapabilmek icin aranan kelimeyi kucuk harfe ceviriyoruz
    char lowerSearchWord[MAX_WORD_LENGTH];
    strcpy(lowerSearchWord, searchWord);
    toLowerCase(lowerSearchWord);

    printf(COLOR_YELLOW "\n--- [%s] Dosyasi Taraniyor ---\n" COLOR_RESET, filename);

    // Dosyayi satir satir oku
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Orijinal satiri bozmamak icin kopyasini alip kucuk harfe ceviriyoruz
        char lowerLine[MAX_LINE_LENGTH];
        strcpy(lowerLine, buffer);
        toLowerCase(lowerLine);

        int occurrencesInLine = countWordInLine(lowerLine, lowerSearchWord, exactMatch);

        // Eger bu satirda kelime bulunduysa ekrana yazdir
        if (occurrencesInLine > 0) {
            // Ekranda alt satira inmemesi icin satir sonundaki \n karakterini siliyoruz
            buffer[strcspn(buffer, "\n")] = 0;

            printf(COLOR_CYAN "Satir %-4d " COLOR_RESET, lineNumber);
            printf("| " COLOR_GREEN "(%d kez) " COLOR_RESET "-> %s\n", occurrencesInLine, buffer);

            fileOccurrences += occurrencesInLine;
        }
        lineNumber++;
    }

    fclose(file);
    printf("[%s] icinde toplam %d eslesme bulundu.\n", filename, fileOccurrences);
    return fileOccurrences;
}