#include "search_engine.h" // Kendi yazdığımız kütüphaneyi dahil ediyoruz (Tırnak içinde yazılır)

// 1. Metni küçük harfe çeviren yardımcı fonksiyon
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// 2. Satır içinde kelime sayan fonksiyon
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

// 3. Tek bir dosya içinde arama yapan ana işçi fonksiyon
int searchInSingleFile(const char *filename, const char *searchWord) {
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        printf("[HATA] '%s' dosyasi okunamadi veya yok. Atlaniyor...\n", filename);
        return 0;
    }

    char buffer[MAX_LINE_LENGTH];
    int lineNumber = 1;
    int fileOccurrences = 0;

    char lowerSearchWord[MAX_WORD_LENGTH];
    strcpy(lowerSearchWord, searchWord);
    toLowerCase(lowerSearchWord);

    printf("\n>>> [%s] dosyasi taraniyor...\n", filename);

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char lowerLine[MAX_LINE_LENGTH];
        strcpy(lowerLine, buffer);
        toLowerCase(lowerLine);

        int occurrencesInLine = countWordInLine(lowerLine, lowerSearchWord);

        if (occurrencesInLine > 0) {
            printf("    -> Satir %d: %d kez bulundu.\n", lineNumber, occurrencesInLine);
            fileOccurrences += occurrencesInLine;
        }
        lineNumber++;
    }

    fclose(file);
    printf("--- [%s] tamamlandi. Bu dosyada %d kez bulundu. ---\n", filename, fileOccurrences);
    return fileOccurrences;
}