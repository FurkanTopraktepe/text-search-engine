#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024
#define MAX_WORD_LENGTH 256

// 1. Bir metni tamamen küçük harfe çeviren fonksiyon
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// 2. Bir satırın içinde aranan kelimenin kaç kez geçtiğini bulan fonksiyon
int countWordInLine(const char *line, const char *word) {
    int count = 0;
    const char *tmp = line;
    int wordLen = strlen(word);

    // strstr fonksiyonu, kelimeyi bulursa bulduğu noktanın adresini, bulamazsa NULL döner
    while ((tmp = strstr(tmp, word)) != NULL) {
        count++;
        tmp += wordLen; // Bulduğumuz kelimenin sonrasından aramaya devam et
    }
    return count;
}

// 3. Dosyayı açıp, satır satır okuyan ve arama işlemlerini yöneten ana fonksiyon
void searchInFile(const char *filename, const char *searchWord) {
    FILE *file = fopen(filename, "r");
    
    // Dosya açılamazsa hata ver ve çık
    if (file == NULL) {
        printf("Hata: '%s' dosyasi bulunamadi veya acilamadi!\n", filename);
        return;
    }

    char buffer[MAX_LINE_LENGTH];
    int lineNumber = 1;
    int totalOccurrences = 0;

    // Aranan kelimeyi en baştan küçük harfe çeviriyoruz (case-insensitive için)
    char lowerSearchWord[MAX_WORD_LENGTH];
    strcpy(lowerSearchWord, searchWord);
    toLowerCase(lowerSearchWord);

    printf("\n>>> '%s' dosyasi icerisinde '%s' kelimesi araniyor...\n", filename, searchWord);
    printf("------------------------------------------------------\n");

    // Dosyayı sonuna kadar (EOF) satır satır oku
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        
        // Okunan satırın orijinalini bozmamak için kopyasını alıp küçük harfe çeviriyoruz
        char lowerLine[MAX_LINE_LENGTH];
        strcpy(lowerLine, buffer);
        toLowerCase(lowerLine);

        // Satır içinde kelime arama fonksiyonumuzu çağırıyoruz
        int occurrencesInLine = countWordInLine(lowerLine, lowerSearchWord);

        // Eğer kelime bu satırda bulunduysa raporla
        if (occurrencesInLine > 0) {
            printf("Satir %d: Kelime bu satirda %d kez bulundu.\n", lineNumber, occurrencesInLine);
            totalOccurrences += occurrencesInLine;
        }
        lineNumber++; // Bir sonraki satıra geç
    }

    printf("------------------------------------------------------\n");
    printf("ARAMA TAMAMLANDI: Kelime toplam %d kez bulundu.\n\n", totalOccurrences);

    fclose(file); // İşimiz bitince dosyayı mutlaka kapatıyoruz (Bellek yönetimi)
}

int main() {
    char searchWord[MAX_WORD_LENGTH];
    char filename[MAX_LINE_LENGTH];

    printf("--- METIN ARAMA MOTORU ---\n");
    
    printf("Aranacak kelimeyi giriniz: ");
    scanf("%255s", searchWord); // Kullanıcıdan tek bir kelime al

    printf("Arama yapilacak dosya adini giriniz (Orn: metin.txt): ");
    scanf("%255s", filename);

    // Arama fonksiyonunu tetikle
    searchInFile(filename, searchWord);

    return 0;
}