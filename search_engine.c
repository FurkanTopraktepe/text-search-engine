#include "search_engine.h"

// Metni küçük harfe çeviren fonksiyon
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Satır içinde kelime sayan fonksiyon
int countWordInLine(const char *line, const char *word) {
    int count = 0;
    const char *tmp = line;
    int wordLen = strlen(word);

    while ((tmp = strstr(tmp, word)) != NULL) {
        count++;
        tmp += wordLen;
    }
    return count;
}

// Dosya içinde arama yapan ana işçi fonksiyon
int searchInSingleFile(const char *filename, const char *searchWord) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        // Hata mesajını KIRMIZI yapıyoruz
        printf(COLOR_RED "[HATA] '%s' dosyasi okunamadi veya yok. Atlaniyor...\n" COLOR_RESET, filename);
        return 0;
    }

    char buffer[MAX_LINE_LENGTH];
    int lineNumber = 1;
    int fileOccurrences = 0;

    char lowerSearchWord[MAX_WORD_LENGTH];
    strcpy(lowerSearchWord, searchWord);
    toLowerCase(lowerSearchWord);

    // Dosya adını SARI ile vurguluyoruz
    printf(COLOR_YELLOW "\n>>> [%s] dosyasi taraniyor...\n" COLOR_RESET, filename);

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char lowerLine[MAX_LINE_LENGTH];
        strcpy(lowerLine, buffer);
        toLowerCase(lowerLine);

        int occurrencesInLine = countWordInLine(lowerLine, lowerSearchWord);

        if (occurrencesInLine > 0) {
            // Ekranda alt alta düzgün görünmesi için orijinal satırın sonundaki 'Enter' (\n) karakterini siliyoruz
            buffer[strcspn(buffer, "\n")] = 0;

            // Satır numarasını ve bulunan cümleyi CYAN (Açık Mavi) ve YEŞİL kullanarak basıyoruz
            printf(COLOR_CYAN "    Satir %-4d " COLOR_RESET, lineNumber); // %-4d hizalama yapar
            printf("| " COLOR_GREEN "(%d kez)" COLOR_RESET " -> %s\n", occurrencesInLine, buffer);

            fileOccurrences += occurrencesInLine;
        }
        lineNumber++;
    }

    fclose(file);
    printf("--- [%s] taramasi bitti. Toplam: %d ---\n", filename, fileOccurrences);
    return fileOccurrences;
}