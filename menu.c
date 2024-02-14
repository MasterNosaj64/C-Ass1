#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "menu.h"
#include "main.h"

int error_Checking(int word_length)
{
    float integer_ERROR_CHECKING;

    if (scanf("%f", &integer_ERROR_CHECKING) != 1)
    {

        printf("ERROR: Invalid word size\n");
        scanf("%*[^\n]");
        return -1;
    }
    else
    {
        word_length = integer_ERROR_CHECKING;
        if ((word_length != integer_ERROR_CHECKING) || (word_length < 0))
        {
            printf("ERROR: Invalid word size\n");
            scanf("%*[^\n]");
            return -1;
        }
        else
        {
            scanf("%*[^\n]");
            return word_length;
        }
    }
    return -1;
}

/*Menu Display and  user selection */
int menu()
{
    int picked_Number;
    char ESC = 27;
    /*Menu */
    printf("%c[1m",ESC); printf("1."); printf("%c[0m",ESC); printf(" Display "); printf("%c[1m",ESC); printf("statistics"); printf("%c[0m",ESC); printf(" about the processed words.\n");
    printf("%c[1m",ESC); printf("2."); printf("%c[0m",ESC); printf(" List "); printf("%c[1m",ESC); printf("all"); printf("%c[0m",ESC); printf(" the words found in ascending sorted order.\n");
    printf("%c[1m",ESC); printf("3."); printf("%c[0m",ESC); printf(" List all the words found "); printf("%c[1m",ESC); printf("greater"); printf("%c[0m",ESC); printf(" than a certain length.\n");
    printf("%c[1m",ESC); printf("4."); printf("%c[0m",ESC); printf(" List all of the words found "); printf("%c[1m",ESC); printf("less"); printf("%c[0m",ESC); printf(" than a certain length.\n");
    printf("%c[1m",ESC); printf("5."); printf("%c[0m",ESC); printf(" List all the words found "); printf("%c[1m",ESC); printf("equal"); printf("%c[0m",ESC); printf(" to a certain length.\n");
    printf("%c[1m",ESC); printf("6."); printf("%c[0m",ESC); printf(" Write all the words found to a "); printf("%c[1m",ESC); printf("file"); printf("%c[0m",ESC); printf(".\n");
    printf("%c[1m",ESC); printf("9."); printf(" Exit"); printf("%c[0m",ESC); printf(" the program.\n");
    /*User selection */
    scanf("%d", &picked_Number);
    if ((picked_Number < 1) || (picked_Number > 9))
    {
        scanf("%*[^\n]");
        return 7; /*using 7 cause it is an invalid picked_Number */
    }
    else
    {
        return picked_Number;
    }
} /*End of menu  */

void menu_Options(int command, char *file_Name, int word_length_MAX, int processed_Lines, int processed_Words, int word_Stored, List *List_head, FILE *fp)
{

    List *List_cursor = List_head;
    int word_Length = 0;
    char output_File_Name[32];
    char over_Write_Option[32];

    while (command != 9)
    {

        switch (command)
        {
        case 1:
        {
            printf("                       Input filename: %s\n", file_Name);
            printf("                      Lines processed: %4d\n", processed_Lines);
            printf("                      Words processed: %4d\n", processed_Words);
            printf("          Words stored in linked list: %4d\n", word_Stored);
            printf("\n");
            break;
        }

        break;
        case 2:
            while (List_cursor != NULL)
            {
                printf("                             Word %4d: %s\n", word_length_MAX, List_cursor->word);
                List_cursor = List_cursor->next_node;
            }
            printf("\n");
            List_cursor = List_head;
            break;
        case 3: /*Words found greater than defined length */
            printf("Enter the minimum word length: ");

            word_Length = error_Checking(word_Length);
            printf("\n");
            while ((List_cursor != NULL) && (word_Length != -1))
            {

                if ((signed int)strlen(List_cursor->word) > word_Length)
                {
                    printf("                             Word %4d: %s\n", word_Length, List_cursor->word);
                }

                List_cursor = List_cursor->next_node;
            }
            printf("\n");
            List_cursor = List_head;
            break;
        case 4:
            printf("Enter the maximum word length: ");
            word_Length = error_Checking(word_Length);
            printf("\n");
            while ((List_cursor != NULL) && (word_Length != -1))
            {

                if ((signed int)strlen(List_cursor->word) < word_Length)
                {
                    printf("                             Word %4d: %s\n", word_Length, List_cursor->word);
                }

                List_cursor = List_cursor->next_node;
            }
            printf("\n");
            List_cursor = List_head;
            break;

        case 5:
            printf("Enter the exact word length: ");
            word_Length = error_Checking(word_Length);
            printf("\n");
            while ((List_cursor != NULL) && (word_Length != -1))
            {

                if ((signed int)strlen(List_cursor->word) == word_Length)
                {
                    printf("                             Word %4d: %s\n", word_Length, List_cursor->word);
                }

                List_cursor = List_cursor->next_node;
            }
            printf("\n");
            List_cursor = List_head;
            break;

        case 6:
            printf("Enter the filename: ");
            scanf("%s", output_File_Name);
            if (access(output_File_Name, F_OK) != -1)
            {
                /*file exists*/
                printf("File Exists\n");
                printf("Do you wish to overwrite %s? (y/n)\n", output_File_Name);
                if ((scanf("%s", over_Write_Option) != 1) || ((tolower(over_Write_Option[0]) != 'n') && (tolower(over_Write_Option[0]) != 'y')))
                {
                    printf("ERROR: Invalid input\n");
                    scanf("%*[^\n]");
                    break;
                }
                else if (tolower(over_Write_Option[0]) == 'n')
                {
                    break;
                }
            }

            fp = fopen(output_File_Name, "w");

            if (fp == NULL)
            {

                if (errno == 13)
                {
                    printf("File %s cannot be opened. \n", output_File_Name);
                    break;
                }
                else
                {
                    perror("");
                    break;
                }
            }
            else
            {
                while (List_cursor != NULL)
                {
                    fprintf(fp, "%s\n", List_cursor->word);
                    List_cursor = List_cursor->next_node;
                }
                List_cursor = List_head;
                fclose(fp);
                printf("%4d words written to %s\n", word_Stored, output_File_Name);
            }
            break;

        case 9:
            break;

        default:
            printf("\ninvalid input\n");
            break;

        } /*End of swtich */
        command = menu();
    } /*End of while */
    printf("Goodbye. \n");
    /*free memory allocated */
    while (List_head != NULL)
    {
        List_head = List_cursor->next_node;
        free(List_cursor->word); /*frees word */
        free(List_cursor);       /*frees node */
        List_cursor = List_head;
    }
}