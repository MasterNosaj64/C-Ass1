#ifndef HEADER_FILE
#define HEADER_FILE

#define MAX_SIZE 64

typedef struct ListNode
{
    char *word;
    int num_of_references;
    struct ListNode *next_node;

} List;

int menu();
void menu_Options(int command, char *filename, int word_length_MAX, int processedLines, int processedWords, int wordStored, List *List_head, FILE *fp);

#endif