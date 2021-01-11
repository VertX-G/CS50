// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
// If using a hash function you found online
// remember to add a reference to where you found it
unsigned int hash(const char *word)
{
    // TODO
    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    // Open dictionary file
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)                                         // remember to check if fopen() returns NULL
    {
        return false;
    }

    char word[LENGTH+1];
    int hashedValue;

    // read strings from the file one at a time (loop)
    // find out whether the below only reads one line at a time, or how to use "\n" to indicate end of line
    while (fscanf(fp, "%s", word) != EOF)                  // until fscanf returns EOF
    {
        // Create a new node for each word
        node *n = malloc(sizeof(node)); // remember to check if malloc returns NULL
        // copy word into node
        strcpy(n->word, word);
        // hash word to obtain a hash value
        hashedValue = hash(word);
        // insert node into hash table at that location
        n->next = table[hashedValue];
        table[hashedValue] = n; 
    }
    
    // close file
    fclose(fp);
    
    // if successfully loaded entire dictionary into memory
    // return true
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
