#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//TASK:
//program must accept a single command line argument (key)
//key must be 26 unique alhpabetical characters (no punctuation marks)
//key must be case-insensitive
//if received argument does not fit the criteria, program should printf error message and return a value of 1 from main
//characters entered in plaintext that are not alphabetic (ike numbers or punctuation) should also be output in ciphertext, but without being substituted

//program must preserve case of plaintext

//after successfully outputting ciphertext, program should print a newline and exit by returning 0 from main

int error(string keyError);

//Get key as argv
int main(int argc, string argv[])
{
    //VALIDATE KEY
    //check key length
    //check for non-alphabetic characters
    //check for repeated characters (case insensitive)
    //return error if not

    //check whether the user has entered an argument for the key
    if (argc != 2)
    {
        return error("Error retreiving key!");
    }

    string key = argv[1];

    //check whether the key is 26 characters
    if (strlen(key) != 26)
    {
        return error("Error: Key does not contain 26 characters!");
    }

    //check characters are alphabetic and no duplicates ------ maybe change this to external function
    for (int i = 0; i < strlen(key); i++)
    {
        //check if all characters are alphabetical
        char c = key[i];
        c = tolower(c);

        //check whether there are any duplicate characters
        if (c < 'a' || c > 'z')
        {
            return error("Error: Key contains non-alphabetic character!");
        }

        //check for duplicate characters
        for (int j = 0; j < strlen(key); j++)
        {
            char d = tolower(key[j]);

            if (j != i)
            {
                if (d == c)
                {
                    return error("Error: Key contains duplicate characters!");
                }
            }
        }
    }

    //GET PLAINTEXT
    string plaintext = get_string("plaintext: ");

    //ENCIPHER
    //for each alphabetic character, determine what letter it maps to
    //preserve case
    //leave non-alphabetic characters as-is and unchanged
    string ciphertext = plaintext;

    //for each plainTextChar in plaintext
    for (int i = 0; i < strlen(plaintext); i++)
    {
        //if character is a punctuation mark, add it to ciphertext string

        char character = tolower(plaintext [i]);

        if (character < 'a' || character > 'z')
        {
            ciphertext [i] = plaintext [i];
        }

        //if character is alphabetic,
        //get distance between lowercase plaintext letter and lowercase key letter,
        //add that distance to standard plaintext letter,
        //and place that new letter in current ciphertext string array position.
        else
        {
            char plainTextChar = plaintext[i];

            //get alphabetical index of current character in plaintext string
            int indexPT = character - 'a';

            //get the cipherkey replacement for current character in plaintext string
            char cipherKey = tolower(key[indexPT]);

            //get the distance between the plainstring character and the cipherkey character
            int cipherKeyDist = cipherKey - character;

            //add the cipherkey distance to the plaintext character
            //this works whether plaintext character is upper or lower case
            char cipherChar = plainTextChar + cipherKeyDist;
            ciphertext[i] = cipherChar;
        }

    }

    //PRINT CIPHERTEXT
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

//Error
int error(string keyError)
{
    printf("%s\nPlease enter a 26 character key of non-repeating, alphabetic characters\n", keyError);
    return 1;
}