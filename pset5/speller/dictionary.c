// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// variable to count the words entered into the dictionary
unsigned int dictionary_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    // hash word
    int hashedValue = hash(word);
    // create pointer to search for word in dictionary
    // set pointer to hashed table index
    node *checker = table[hashedValue];

    // iterate through list
    while (checker != NULL)
    {
        // if the word can be found in the list
        if (strcasecmp(checker->word, word) == 0)
        {
            return true;
        }
        // if the word is not found
        // check the next word in the list
        checker = checker->next;
    }
    // if the table index was NULL
    // or the word could not be found in the list
    return false;
}

// Hashes word to a number
// If using a hash function you found online
// remember to add a reference to where you found it
unsigned int hash(const char *word)
{
    // TODO

    // THE IDEAL HASH ALGORITHM
    // Perfect Hash Function (PHF)= A hash function for which there are no collisions (duplicates)
    // Minimal Perfect Hash Function (MPHF) = A PHF for which the hash table has no holes in it (that is, the hash table is only as big as the search list)

    //
    // no need to find middle ground to get smaller array with a little more collisions
    // will not save memory as everything needs to get loaded in anyway

    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictionary file
    FILE *fp = fopen(dictionary, "r");

    // return false if fopen() fails
    if (fp == NULL)
    {
        return false;
    }

    // declare placeholder for word
    char word[LENGTH+1];
    // declare placeholder for hashedValue
    int hashedValue;

    // read strings from the file one at a time until the end of the file
    while (fscanf(fp, "%s", word) != EOF)
    {
        // Create a placeholder node for each word
        node *n = malloc(sizeof(node));
        // remember to check if malloc returns NULL
        if (n == NULL)
        {
            return false;
        }
        // copy word into node
        strcpy(n->word, word);
        // hash word to obtain a hash value
        hashedValue = hash(word);
        // insert node into hash table at that location
        n->next = table[hashedValue];
        table[hashedValue] = n;

        // increment dictionary word count
        dictionary_size++;
    }

    // close file
    fclose(fp);

    // if entire dictionary successfully loaded into memory
    // return true
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // create a new node that will be the node we use to free each node in the list
    node *n = malloc(sizeof(node));
    // iterate through table[]
    for (int i = 0; i < N; i++)
    {
        // if table[i] is pointing to a list
        if (table[i] != NULL)
        {
            // set the new node as the header to that list
            n->next = table[i];

            // loop through each list
            while (n != NULL)
            {
                // hold on to next node so it isnt orphaned
                node *tmp = n->next;

                // free current node
                free(n);

                // set current node to next node
                n = tmp;
            }
        }
    }
    return true;
}
