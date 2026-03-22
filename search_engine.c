#include "search_engine.h"

// Gelen metindeki tüm harfleri küçük harfe çevirir (Case-insensitive arama için)
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Bir satır içerisinde hedef kelimenin kaç kez geçtiğini bulan fonksiyon
int countWordInLine(const char *line, const char *word, int exactMatch) {
    int count = 0;
    const char *tmp = line;
    int wordLen = strlen(word);

    // Satır içinde kelimeyi aramaya başla
    while ((tmp = strstr(tmp, word)) != NULL) {
        if (exactMatch) {
            // Tam eşleşme kontrolü: Kelimenin önünde ve arkasında harf/rakam var mı?
            // isalnum: Karakterin alfanumerik (harf/sayı) olup olmadığını kontrol eder
            int isStartBoundary = (tmp == line) || !isalnum((unsigned char)*(tmp - 1));
            int isEndBoundary = !isalnum((unsigned char)*(tmp + wordLen));

            if (isStartBoundary && isEndBoundary) {
                count++;
            }
        } else {
            // Normal arama: Kelime herhangi bir yerde geçiyorsa say
            count++;
        }
        // Aynı kelimeyi tekrar saymamak için imleci kelime boyu kadar ilerlet
        tmp += wordLen;
    }
    return count;
}

// Tek bir dosyayı açıp satır satır tarayan ana işlevsel fonksiyon
int searchInSingleFile(const char *filename, const char *searchWord, int exactMatch, FILE *logFile) {
    FILE *file = fopen(filename, "r"); // Dosyayı okuma modunda aç

    // Dosya bulunamazsa hata mesajını hem ekrana hem log dosyasına yaz
    if (file == NULL) {
        printf(COLOR_RED "Hata: '%s' dosyasi okunamadi veya bulunamadi.\n" COLOR_RESET, filename);
        if(logFile) fprintf(logFile, "Hata: '%s' dosyasi bulunamadi.\n", filename);
        return 0;
    }

    char buffer[MAX_LINE_LENGTH];
    int lineNumber = 1;
    int fileOccurrences = 0;
    
    // Aramayı küçük harf üzerinden yapmak için aranan kelimeyi dönüştür
    char lowerSearchWord[MAX_WORD_LENGTH];
    strcpy(lowerSearchWord, searchWord);
    toLowerCase(lowerSearchWord);

    printf(COLOR_YELLOW "\n--- [%s] Dosyasi Taraniyor ---\n" COLOR_RESET, filename);
    if(logFile) fprintf(logFile, "\n--- [%s] Dosyasi Taraniyor ---\n", filename);

    // Dosyayı sonuna kadar satır satır oku
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Satırı küçük harfe çevirerek karşılaştırmaya hazırla
        char lowerLine[MAX_LINE_LENGTH];
        strcpy(lowerLine, buffer);
        toLowerCase(lowerLine);

        int occurrencesInLine = countWordInLine(lowerLine, lowerSearchWord, exactMatch);

        // Eğer bu satırda eşleşme varsa ekrana ve dosyaya yazdır
        if (occurrencesInLine > 0) {
            buffer[strcspn(buffer, "\n")] = 0; // Satır sonundaki yeni satır karakterini temizle
            
            // Konsol çıktısı (renkli)
            printf(COLOR_CYAN "Satir %-4d " COLOR_RESET "| " COLOR_GREEN "(%d kez) " COLOR_RESET "-> %s\n", lineNumber, occurrencesInLine, buffer);
            
            // Dosya çıktısı (renksiz ve temiz metin)
            if(logFile) fprintf(logFile, "Satir %-4d | (%d kez) -> %s\n", lineNumber, occurrencesInLine, buffer);
            
            fileOccurrences += occurrencesInLine;
        }
        lineNumber++;
    }

    fclose(file); // Açılan metin dosyasını kapat
    printf("[%s] icinde toplam %d eslesme bulundu.\n", filename, fileOccurrences);
    if(logFile) fprintf(logFile, "[%s] icinde toplam %d eslesme bulundu.\n", filename, fileOccurrences);
    
    return fileOccurrences;
}
