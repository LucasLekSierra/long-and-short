#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    char fileTxt[255];
    char *readFilename;
    char *shortFilename, *longFilename;
    int shortCount = 0, longCount = 0;
    
    // validation for argument count
    if (argc == 4)
    {
        readFilename = argv[1];
        shortFilename = argv[2];
        longFilename = argv[3];
    }
    else
    {
        printf("ERROR: long-short.c takes 3 arguments.\n");
        exit(1);
    }

    // open file (or end program if not found)
    FILE *readFile = fopen(readFilename, "r");
    if (readFile == NULL)
    {
        printf("Could not open file %s.\n", readFilename);
        exit(1);
    }
    
    // prepare to write to files
    FILE *shortFile = fopen(shortFilename, "w");
    if (shortFile == NULL)
    {
        printf("Could not open file %s.\n", readFilename);
        exit(1);
    }

    FILE *longFile = fopen(longFilename, "w");
    if (longFile == NULL)
    {
        printf("Could not open file %s.\n", readFilename);
        exit(1);
    }
    
    // check each line
    while (fgets(fileTxt, 255, readFile) != NULL)
    {
        // less than 20 characters: uppercase, put into short file
        if (strlen(fileTxt) < 20)
        {
            for (int i = 0; i < strlen(fileTxt); i++)
            {
                fileTxt[i] = toupper(fileTxt[i]);
            }

            shortCount++;
            fprintf(shortFile, "%s\n", fileTxt);
        }
        // 20 or more characters: lowercase, put into long file
        else
        {
            for (int i = 0; i < strlen(fileTxt); i++)
            {
                fileTxt[i] = tolower(fileTxt[i]);
            }

            longCount++;
            fprintf(longFile, "%s", fileTxt);
        }
    }
    
    // print counts for short and long lines
    printf("%d lines written to %s\n", shortCount, shortFilename);
    printf("%d lines written to %s\n", longCount, longFilename);

    // close files and end program
    fclose(readFile);
    fclose(shortFile);
    fclose(longFile);
}