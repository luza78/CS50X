// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// N = First letter M = Second letter, index 0 if only one letter L = Length
const unsigned int N = 26;
const unsigned int M = 27;
const unsigned int L = 2;

// Hash table
node *table[N][M][L];

// Word count global
unsigned int wordcount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *cursor = NULL;
    int index = hash(word);
    int index2 = hash2(word);
    int index3 = hash3(word);

    cursor = table[index][index2][index3];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
            break;
        }

        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number by first letter
unsigned int hash(const char *word)
{
    return toupper(word[0]) - 'A';
}

// Hashes word to a number by second letter
unsigned int hash2(const char *word)
{
    if (strlen(word) > 1)
    {
        return toupper(word[1]) - 'A' + 1;
    }
    else
    {
        return 0;
    }
}

// Hashes word to a number, by length
unsigned int hash3(const char *word)
{
    if (strlen(word) <= 5)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Error could not open Dictionary");
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        int index = hash(word);
        int index2 = hash2(word);
        int index3 = hash3(word);

        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Malloc error loading dictionary");
            return false;
        }

        strcpy(n->word, word);
        n->next = table[index][index2][index3];
        table[index][index2][index3] = n;
        wordcount++;
        memset(&word[0], 0, sizeof(word));
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    return wordcount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *cursor = NULL;
    node *tmp = NULL;

    for (int j = 0; j < L; j++)
    {
        for (int k = 0; k < M; k++)
        {
            for (int i = 0; i < N; i++)
            {
                cursor = table[i][k][j];

                while (cursor != NULL)
                {
                    tmp = cursor;
                    cursor = cursor->next;
                    free(tmp);
                }
            }
        }
    }

    return true;
}
