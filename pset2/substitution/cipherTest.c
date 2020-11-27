#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    char c = get_char("character: ");
    int i = get_int("increment: ");
    char a = c + i;
    printf("%c\n",a);
}