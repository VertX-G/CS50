#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;

    do
    {
        // Prompt user to input "Height" for the pyramid
        height = get_int("Height: ");
    }

    //Check whether the number input by the user falls within our required range
    while (height < 1 || height > 8);

    //make the correct number of rows
    for (int i = 1; i <= height; i++)
    {
        //make the correct number of spaces per row
        for (int j = height - i; j > 0; j--)
        {
            printf(" ");
        }

        //make the correct number of "#" per row for the first pyramid
        for (int k = i; k > 0; k--)
        {
            printf("#");
        }
        
        //make the space between the pyramids
        printf("  ");
        
        //make the correct number of "#" per row for the second pyramid
        for (int k = i; k > 0; k--)
        {
            printf("#");
        }
        

        //Go to a new line for the next row of "#"
        printf("\n");
    }

}