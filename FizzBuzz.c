#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    for (int i = 1; i <= 100; i++)
    {
        int c = 0;

        if (i % 3 == 0)
        {
            printf("Fizz");
            c++;
        }

        if (i % 5 == 0)
        {
            printf("Buzz");
            c++;
        }

        if (c == 0)
        {
            printf("%i", i);
        }

        printf("\n");

    }
}