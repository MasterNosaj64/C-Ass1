#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include "main.h"

/*
Student: Jason Waid & Muhammadu Ahmadu
Student #:040912687 & 040776232
Program: Computer Engineering Technology
Course: CST8234 - Assign1
Date: July 15th 2019
Updates: 
            -Code Tweaks-
            Implemented Linked List
            Implemented Menu for displaying stats, the list and looking for words in the linked list
            implemented code for printing words to a text file
*/

/************************************************************************************************** 
 * Code creates a node, returns a pointer to the node
*/

List *create_Node(char *word_buffer)
{
    List *node = malloc(sizeof(List));
    node->word = malloc(sizeof(word_buffer));
    node->num_of_references = 1;
    strcpy(node->word, word_buffer);
    return node;
}
/************************************************************************************************** 
 * Code searches the list for duplicates, returns true or false
*/
int search_List(char *word_buffer, List *List_head)
{
    List *temp = List_head;
    while (temp != NULL)
    {
        if ((strcmp(word_buffer, temp->word)) == 0)
        {
            printf("                 Duplicate word found: %s\n", word_buffer);
            temp->num_of_references++;
            return 1; /* true */
        }
        if (temp->next_node == NULL)
        {
            return 0;
        }
        else
        {
            temp = temp->next_node;
        }
    }
    return 0; /* false */
}
/************************************************************************************************** 
 * Code Inserts Nodes at the correct location, using insertion sort
 * updates the pointer of the neighboring node
*/
void *insertion_Sort(List *New_word, List *List_cursor, List *List_head)
{
    List_cursor = List_head;
    while (List_cursor != NULL)
    {
        if (List_cursor->word < New_word->word)
        {
            New_word->next_node = List_cursor->next_node;
            List_cursor->next_node = New_word;
            break;
        }
        List_cursor = List_cursor->next_node;
    }
    return 0;
}

int main(int argc, char **argv)
{

    char file_buffer[256];
    char *input_buffer = file_buffer;
    char word_buffer[64];

    List *List_head = NULL;
    List *List_cursor = List_head;
    List *temp = NULL;

    int word_length_MAX = 3;
    int i;
    char *wordlength_ERRORCHECKING = argv[2];
    float wordlength_INT_ERROR_CHECK;
    int word_size;
    int num_accepted_words = 0;
    int num_words_processed = 0;
    int num_words_less_than_MAX = 0;
    int num_spaces = 0;
    int num_lines_processed = 0;
    FILE *fp;

    if (argc >= 2)
    {
        if (argc == 3)
        {

            for (i = 0; wordlength_ERRORCHECKING[i]; i++)
            {
                if (isalpha(wordlength_ERRORCHECKING[i]))
                {
                    printf("ERROR: %s is not a valid word size\n", wordlength_ERRORCHECKING);
                    return 0;
                }
            }

            sscanf(argv[2], "%f", &wordlength_INT_ERROR_CHECK);
            word_length_MAX = wordlength_INT_ERROR_CHECK;

            if ((wordlength_INT_ERROR_CHECK != word_length_MAX) || (wordlength_INT_ERROR_CHECK < 0))
            {
                printf("ERROR: %s is not a valid word size\n", wordlength_ERRORCHECKING);
                return 0;
            }
        }

        else if (argc > 3)
        {
            printf("Too many Arguments. Max is 3\n");
            return 0;
        }

        fp = fopen(argv[1], "r");

        if (fp == NULL)
        {
            if (errno == 2)
            {
                printf("File %s not found. Terminating.\n", argv[1]);
                return 0;
            }
            else if (errno == 13)
            {
                printf("File %s cannot be opened. Terminating\n", argv[1]);
                return 0;
            }
            else
            {
                perror("");
                return 0;
            }
        }
    }
    else
    {
        printf("<filename> missing.");
        printf("\nUsage: ./lab4 <filename>\n");
        return 0;
    }

    while (!feof(fp))
    {
        fgets(file_buffer, 255, fp);
        word_size = 0;
        num_lines_processed++;
        input_buffer = file_buffer;

        /*converts to lower case*/
        for (i = 0; input_buffer[i]; i++)
        {
            if ((isalpha(input_buffer[i]) && (isupper(input_buffer[i]))))
            {
                input_buffer[i] = tolower(input_buffer[i]);
            }
        }

        while (sscanf(input_buffer, "%s", word_buffer) != EOF)
        {
            /*Resets List cursor to begining of list */
            List_cursor = List_head;
            num_spaces = 0;
            word_size = 0;

            /*Logic for counting spaces before word*/
            for (i = 0; isspace(input_buffer[i]); i++)
            {
                num_spaces++;
            }

            /*determines # of bytes used by word*/
            for (i = 0; word_buffer[i]; i++)
            {
                word_size++;
            }

            /*Logic checking word size*/
            if (word_size < word_length_MAX + 1)
            {
                printf("   Word found less than %2d characters: %s\n", word_length_MAX + 1, word_buffer);
                num_words_less_than_MAX++;
            }
            else
            {
                if (List_cursor == NULL)
                {
                    List_cursor = create_Node(word_buffer);
                    List_head = List_cursor;
                    num_accepted_words++;
                }
                else if (search_List(word_buffer, List_cursor) == 0) /*Logic for adding new word, if no matches found*/
                {
                    /*assigns word to new node*/
                    temp = create_Node(word_buffer);
                    insertion_Sort(temp, List_cursor, List_head);
                    num_accepted_words++;
                }
            }
            num_words_processed++;
            input_buffer = input_buffer + word_size + num_spaces; /*makes up for spaces and word size when incrementing buffer*/
            List_cursor = List_head;
        }
    }
    printf("\n");
    fclose(fp);
    menu_Options(menu(), argv[1], word_length_MAX, num_lines_processed, num_words_processed, num_accepted_words, List_head, fp);
    return 0;
}