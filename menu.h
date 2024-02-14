#ifndef MENU_HEADER_FILE
#define MENU_HEADER_FILE
#include "main.h"
int menu();
void menu_Options(int command, char *filename, int word_length_MAX, int processedLines, int processedWords, int wordStored, List *list_head, FILE *fp);

#endif