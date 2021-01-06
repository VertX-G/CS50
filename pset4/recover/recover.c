#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t BYTE;

/*
    STILL TO RESOLVE:

    If forensic image cannot be opened for reading, program should inform user as much, and main should return '1'

    Figure out how to use "malloc" for new file name string generation

*/

// Error function
int error(string keyError)
{
    printf("%s\n", keyError);
    return 1;
}

// Main Function
int main(int argc, char *argv[])
{
    // if 1 command line argument is not included
    if (argc != 2)
    {
        // return message and error
        return error("Please enter a command line argument with the name of the forensic image you want to recover.");
    }

    // Raw file - Name variable
    string rawFileName = argv[1];

    // open the Raw file
    FILE *rawFile = fopen(rawFileName, "r");

    // declare a new file
    FILE *newFile;

    // New file - Name
    int strCharLen = 3; // "000"
    strCharLen += 4; // allow for ".jpg" filename extention
    strCharLen += 1; // allow for null termination character
//    char* newFileName = malloc(strCharLen * sizeof(char));
//    // after using malloc, always check to make sure it doesnt return NULL
//    string newFileName = "###.jpg";
    char newFileName[8] = "###.jpg";

    // New file - Number
    int newFileNum = -1;

    // declare buffer
    BYTE buffer[512];
    // variable to check for end of file
    int eof;

    // read 512 block into the buffer
    // + check that block read correctly
    //
    // read the file (into array of bytes)
    // fread(data, size, number, inputr);
    // data = pointer to where to store data you are reading
    // size = size of each element to read
    // number = number of elements to read
    // inptr = FILE * to read from
    while (fread(buffer, 512, 1, rawFile) == 1)
    {
        // test first 4 bytes of buffer for jpeg header and start a new file
        //
        // bitwise arithmetic: (buffer[3] & 0xf0) == 0xe0
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)// && (buffer[3] & 0xf0) == 0xe0)
        {
            // if this is not the first jpeg file
            if (newFileNum != -1)
            {
                // close the file to start a new one
                fclose(newFile);
            }

            // increment file name for next file
            newFileNum ++;

            // generate sequential name for new file
            sprintf(newFileName, "%03i.jpg", newFileNum);
            // sprintf(*newFileName, "%03i.jpg", newFileNum);

            // create a new file to write to
            newFile = fopen(newFileName, "w");

            // print recovered file info to console
            printf("%i  ", newFileNum);
            printf("buffer[3] = %x\n", buffer[3]);

            // write data to new file
            //
            // fwrite(data, size, number, outptr);
            // data = pointer to bytes that will be written to file
            // size = size of each element to write
            // number = number of elements to write
            // outptr = FILE * to write to
            fwrite(buffer, 512, 1, newFile);
        }

        // if this is not the first file
        // append buffer to current file
        else if (newFileNum != -1)
        {
            fwrite(buffer, 512, 1, newFile);
        }
    }

    // Close Raw File
    fclose(rawFile);
    // Free newFileName allocated memory
//    free(newFileName);
}
