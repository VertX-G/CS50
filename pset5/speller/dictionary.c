// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// size of array ±2x size of dataset
const unsigned int N = 131072; //2^17

// Hash table
node *table[N];

/*
// test prints and varriables to finetune hash function
// Calculate the largest hash number
int hashMax = 0;
*/

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
    
    // djb2
    // http://www.cse.yorku.ca/~oz/hash.html
    
    unsigned long hash = 5381;
    int c;
    
    // iterate through each letter of the word until you get the null terminator
    for (int i = 0; word[i] != '\0'; i++)
    {
        // calculate a hash for that letter
        c = tolower(word[i]);
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    
    /*
    // test prints and varriables to finetune hash function
    // calculate the largest hash number
    if (hashMax < hash)
    {
        hashMax = hash;
    }
    */
    
    // return the hash number as a mod of the array size
    return hash % N;
    
    /*-------------------------------------------------------------------------------------------------------*/
    
    /*    
    // hash only first letter
    int i = tolower(word[0])-97;
    return i;
    */
    
    /*-------------------------------------------------------------------------------------------------------*/
    
    /*   
    // hash to add all letters together
    int sum = 0;
    for (int j = 0; word[j] != '\0'; j++)
    {
        sum += tolower(word[j]);
    }
    
    if (hashMax < sum)
    {
        hashMax = sum;
    }
    
    return sum % N;
    */
    
    /*-------------------------------------------------------------------------------------------------------*/
    
    /*
    // hash that multiplies letters together based on their position
    int i = 0;
    int k = 31;
    for (int j = 0; word[j] != '\0'; j++)
    {
        i += (tolower(word[j]) * j * k);
    }
    
    if (hashMax < i)
    {
        hashMax = i;
    }
    
    return i % N;
    */    
    
    /*-------------------------------------------------------------------------------------------------------*/
    
    /*    
    // K&R Version 2
    // https://stackoverflow.com/a/45641002
    int i = 0;
    for (int j = 0; word[j] != '\0'; j++)
    {
        i = tolower(word[j]) + 31 * i;
    }
    
    if (hashMax < i)
    {
        hashMax = i;
    }
    
    return i % N;
    */
    
    /*-------------------------------------------------------------------------------------------------------*/
    
    /*
    // https://stackoverflow.com/a/2624210

    int i = 7;
    for (int j = 0; word[j] != '\0'; j++)
    {
        i = i*31 + tolower(word[j]);
    }
    
    if (hashMax < i)
    {
        hashMax = i;
    }
    
    return i % N;
    */
    
    /*-------------------------------------------------------------------------------------------------------*/
    
    /*
    // https://stackoverflow.com/a/7666799
    unsigned int hash = 0;
    unsigned int i = 0;
    for(hash = i = 0;word[i] != '\0'; i++)
    {
        hash += tolower(word[i]);
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    
    if (hashMax < (hash*-1))
    {
        hashMax = hash;
    }
    
    return hash % N;
    */

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
    char word[LENGTH + 1];
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
    
    
    /*
    // test prints and varriables to finetune hash function
    printf("\nhashMax = %i\n", hashMax);

    int collisions = 0;
    int blanks = 0;
    */
    
    // create a new node that will be the node we use to free each node in the list
    node *cursor = NULL;
    node *tmp = NULL;
    // iterate through table[]
    for (int i = 0; i < N; i++)
    {
        // if table[i] is pointing to a list
        if (table[i] != NULL)
        {
            // set the new node as the header to that list
            cursor = table[i];

            // loop through each list
            while (cursor != NULL)
            {
                /*
                // test prints and varriables to finetune hash function
                // count number of collisions
                if (cursor->next != NULL)
                {
                    collisions++;
                }
                */
                
                // hold on to next node so it isnt orphaned
                tmp = cursor->next;

                // free current node
                free(cursor);

                // set current node to next node
                cursor = tmp;
            }
        }
        
        /*
        // test prints and varriables to finetune hash function
        // count number of blank indexes in array
        else
        {
            blanks++;
        }
        */
    }
    /*
    // test prints and varriables to finetune hash function
    printf("\nblanks = %i\n", blanks);
    printf("\ncollisions = %i\n", collisions);
    */
    return true;
}