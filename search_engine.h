#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// --- RENK TANIMLAMALARI ---
// Terminal çıktısını daha okunaklı hale getirmek için ANSI renk kodları
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

// --- SISTEM SINIRLARI ---
#define MAX_LINE_LENGTH 1024  // Bir satırın maksimum karakter uzunluğu
#define MAX_WORD_LENGTH 256   // Aranacak kelimenin maksimum uzunluğu
#define MAX_FILES 10          // Aynı anda taranabilecek maksimum dosya sayısı

// --- FONKSIYON PROTOTIPLERI ---
// Program genelinde kullanılacak fonksiyonların imzaları
void toLowerCase(char *str);
int countWordInLine(const char *line, const char *word, int exactMatch);
// logFile parametresi: Sonucların dosyaya yazılması için eklenen dosya işaretçisi
int searchInSingleFile(const char *filename, const char *searchWord, int exactMatch, FILE *logFile);

#endif
