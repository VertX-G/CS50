#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t BYTE;

/*
    Program should accept 1 command line argument - the name of a forensic image from which to recover JPEGs
    else should remind user it needs 1 command line argument and main should return '1'
    If forensic image cannot be opened for reading, program should inform user as much, and main should return '1'
    If the program uses 'malloc' it must not leak any memory

    JPEG header you are looking for:
    first three bytes: 0xff 0xd8 0xff
    last byte: 0xe0, 0xe1, 0xe2, ..., 0xef


    Pseudocode:

    Open memory card
    Repeat until end of card:
        read 512 bytes into a buffer
        if start of new JPEG
            if first jpeg
                write first file
            else
                close current
                open and write new file
        else
            if already found JPEG
                keep writing to current jpeg
    close any remaining files
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

    // give file a variable name
    string rawFileName = argv[1];
    // declare buffer
    BYTE buffer[512];
    // variable to check for end of file
    int eof;

    // open the file
    FILE *file = fopen(rawFileName, "r");

    // read the file (into array of bytes)
    // fread(data, size, number, inputr);
    // data = pointer to where to store data you are reading
    // size = size of each element to read
    // number = number of elements to read
    // inptr = FILE * to read from


    int testCounter = 0;

    do
    {
        // read first 512 block into the buffer
        eof = fread(buffer, 512, 1, file);

        // test first 4 bytes of buffer for jpeg header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)// && buffer[3] == ... && )
        {
            // test prints
            testCounter++;
            printf("%i  ", testCounter);
            printf("%x\n", buffer[3]);
        }
    }
    while (eof == 1);

    //fclose(file);

    // check if
    // buffer[0] == 0xff
    // buffer[1] == 0xd8
    // buffer[2] == 0xff
    //
    // bitwise arithmetic:
    // (buffer[3] & 0xf0) == 0xe0
    // this is beginning of new JPEG

    // Make new JPEG
    // Filenames: ###.jpg, starting at 000.jpg
    //
    // declare jpegFileName & initialise with 7 characters (###.jpg)
    // sprintf(jpegfileName, "%03i.jpg", newNumber);
    //
    // Write to new JPEG file
    // FILE *img = fopen(jpegFileName, "w");
    // fwrite(data, size, number, outptr);
    // data = pointer to bytes that will be written to file
    // size = size of each element to write
    // number = number of elements to write
    // outptr = FILE * to write to
    //
    // fread returns the number of items of size 'size' were read

    // test print included command line argument
    //char d = 0xd8;
/*
    for(int i=0; i<4; i++)
    {
        //if (buffer[i] == d)
        //{
            printf("%x\n", buffer[i]);
        //}

    }
*/
}
