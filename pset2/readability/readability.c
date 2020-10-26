#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int num_letters(string s);
int num_words(string s);
int num_sent(string s);
void get_index(float l, float w, float s);

int main(void)
{
    //prompt user for input text
    string text = get_string("Text: ");

    //count number of letters in text
    int letters = num_letters(text);

    //count number of words in text
    int words = num_words(text);

    //count number of sentences in text
    int sentences = num_sent(text);

    //output "GradeX" (rounded to nearest int)
    get_index(letters, words, sentences);
    
//    printf("%i letter(s)\n%i word(s)\n%i sentence(s)\n", letters, words, sentences);
}

int num_letters(string s)
{
    int n = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        char c = s[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        {
            n++;
        }
    }
    return n;
}

int num_words(string s)
{
    int n = 1;
    for (int i = 0; i < strlen(s); i++)
    {
        char c = s[i];
        if (c == ' ')
        {
            n++;
        }
    }
    return n;
}

int num_sent(string s)
{
    int n = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        char c = s[i];
        if (c == '.' || c == '!' || c == '?')
        {
            n++;
        }
    }
    return n;
}

void get_index(float l, float w, float s)
{
    float avgL = 100 / w * l;
    float avgS = 100 / w * s;
    
    float i = round(0.0588 * avgL - 0.296 * avgS - 15.8);
    
    if (i < 1)
    {
        printf("Before Grade 1\n");
    }
    
    else if (i > 16)
    {
        printf("Grade 16+\n");
    }
    
    else
    {
        printf("Grade %.0f\n", i);
    }
}
