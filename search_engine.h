#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Sabit değerlerimiz
#define MAX_LINE_LENGTH 1024
#define MAX_WORD_LENGTH 256
#define MAX_FILES 10

// Fonksiyon Prototipleri (Sadece isimleri ve aldıkları parametreler)
void toLowerCase(char *str);
int countWordInLine(const char *line, const char *word);
int searchInSingleFile(const char *filename, const char *searchWord);

#endif // SEARCH_ENGINE_H