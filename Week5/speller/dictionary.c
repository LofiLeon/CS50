// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

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

// number of words in dictionary
unsigned int words;

// current hash value
unsigned int hash_value;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    hash_value = hash(word);

    // get start of linked list where the word is in the hash table
    node *cursor = table[hash_value];

    // go through linked list until word found
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int value = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        value += tolower(word[i]);
    }
    return value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open dicitionary
    FILE *dict = fopen(dictionary, "r");
    if (dictionary == NULL)
    {
        printf("Could not open dictionary.\n");
        return false;
    }

    // read words one by one into hash table
    char word[LENGTH + 1];
    while (fscanf(dict, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        // copy word into node
        strcpy(n->word, word);
        hash_value = hash(word);
        n->next = table[hash_value];
        table[hash_value] = n;
        words++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (words > 0)
    {
        return words;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // iterate through all buckets in hash table
    for (int i = 0; i < N; i++)
    {
        // get start of each linked list
        node *cursor = table[i];

        // free each word in bucket one by one with help of tmp pointer
        while (cursor != 0)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        if (cursor == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
