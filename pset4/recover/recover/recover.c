#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>

/*
    Program should accept 1 command line argument - the name of a forensic image from which to recover JPEGs
    else should remind user it needs 1 command line argument and main should return '1'
    If forensic image cannot be opened for reading, program should inform user as much, and main should return '1'
    If the program uses 'malloc' it must not leak any memory
*/

// Error function
int error(string keyError)
{
    printf("%s\n", keyError);
    return 1;
}

int main(int argc, char *argv[])
{
    // if 1 command line argument is not included
    if (argc != 2)
    {
        // return message and error
        return error("Please enter a command line argument with the name of the forensic image you want to recover.");
    }

    // test print included command line argument
    printf("%s\n", argv[1]);
}
