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
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Word count global
unsigned int wordcount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *cursor = NULL;
    int index = hash(word);
    cursor = table[index];

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

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
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

        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Malloc error loading dictionary");
            return false;
        }

        strcpy(n->word, word);
        n->next = table[index];
        table[index] = n;
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

    for (int i = 0; i < N; i++)
    {
        cursor = table[i];

        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }

    return true;
}
