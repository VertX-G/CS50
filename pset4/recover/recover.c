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

    // File Name variable
    string rawFileName = argv[1];

    // New File Name
    int strCharLen = 3; // "000"
    strCharLen += 4; // allow for ".jpg" filename extention
    strCharLen += 1; // allow for null termination character
    //char * newFileName = malloc(strCharLen);
    //string newFileName = "###.jpg";
    char newFileName[8] = "###.jpg";

    // New File Number
    int newFileNum =  0;

    // declare buffer
    BYTE buffer[512];
    // variable to check for end of file
    int eof;

    // open the Raw file
    FILE * rawFile = fopen(rawFileName, "r");

    // open a new file
    FILE * newFile = fopen(newFileName, "w");

    int testCounter = 0;

    do
    {
        // read first 512 block into the buffer
        //
        // read the file (into array of bytes)
        // fread(data, size, number, inputr);
        // data = pointer to where to store data you are reading
        // size = size of each element to read
        // number = number of elements to read
        // inptr = FILE * to read from
        eof = fread(buffer, 512, 1, rawFile);

        // test first 4 bytes of buffer for jpeg header
        //
        // bitwise arithmetic:
        // (buffer[3] & 0xf0) == 0xe0
        if (eof == 1 && buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)// && buffer[3] == ... && )
        {
            // test prints
            testCounter++;
            printf("%i  ", testCounter);
            printf("%x\n", buffer[3]);

            // if a new file is already open
            // close the file in order to create a new one
            /*if (fopen(newFileName, "a") == NULL)
            {
                fclose(newFile);
            }*/

            // if this will be the first jpeg file
/*            if (newFileName == "###.jpg")
            {
                fclose(newFile);
                // Start new JPEG file
                //
                // Generate new file name
                sprintf(newFileName, "%03i.jpg", newFileNum);
                // increment file name for next file
                newFileNum ++;

                // create a New File
                newFile = fopen(newFileName, "w");
            }
*/

            fclose(newFile);

            printf("%03i.jpg\n", newFileNum);
            sprintf(newFileName, "%03i.jpg", newFileNum);
            //newFileName = "000.jpg";
            // increment file name for next file
            newFileNum ++;

            // create a New File
            newFile = fopen(newFileName, "w");


            // write data to new file
            //
            // FILE *img = fopen(jpegFileName, "w");
            // fwrite(data, size, number, outptr);
            // data = pointer to bytes that will be written to file
            // size = size of each element to write
            // number = number of elements to write
            // outptr = FILE * to write to
            fwrite (buffer, 512, 1, newFile);

        }
        // if a file has already been created, and the new block is not the start of a new jpeg
        // append to already open file
        else if (fopen(newFileName, "a") != NULL && buffer[0] != 0xff && buffer[1] != 0xd8 && buffer[2] != 0xff)
        {
            fwrite (buffer, 512, 1, newFile);
        }


    }
    while (eof == 1);

    // if a file is created and the new block is not the start of a new jpeg
    // append to already open file

    // Close Raw File
    fclose(rawFile);
    // Free newFileName allocated memory
    free(newFileName);

}
