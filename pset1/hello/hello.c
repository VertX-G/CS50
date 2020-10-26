#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Requests user to input name
    string name = get_string("What is your name?\n");
    
    // Returns hello, 'user name'
    printf("hello, %s\n", name);
}