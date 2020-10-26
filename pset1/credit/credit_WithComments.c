#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //declare variable
    long cc;
    int counter = 0;
    int ones;
    int everyOther;
    int notOther = 0;
    long testNumber;
    int firstNum;
    int secondNum;

    //loop to ensure user inputs correct format
    do
    {
        cc = get_long("Please enter a credit card number: ");
    }
    while (cc < 0);
    
    //checksum
    testNumber = cc;
    
    //loop through each digit of the creditcard number
    //because we use testNumber / 10 to remove the last digit, when we reach the last digit, testNumber / 10 will be >1
    while (testNumber >= 1)
    {
        //get the 'ones' value
        ones = testNumber % 10;
        //remove the last digit from the number
        testNumber = round(testNumber / 10);
        //increment the counter
        counter ++;
        
//        printf("testNumber = %li\nones = %i\n", testNumber, ones);
        
        //save the first digit
        if (testNumber < 10 && testNumber > 0)
        {
            firstNum = testNumber;
        }
        
        //save the second digit
        if (testNumber < 100 && testNumber > 9)
        {
            secondNum = testNumber % 10;
        }
        
        //get the digits of every other number starting from the second to last
        //multiply them by 2, and all of the resulting digits together
        if (counter > 1 && counter % 2 == 0)
        {
            ones = ones * 2;
            
            if (ones > 9)
            {
                everyOther = everyOther + (ones % 10);
                everyOther = everyOther + (ones / 10);
//                printf("Adding double digit to everyOther\n");
            }
            else
            {
                everyOther = everyOther + ones;
//                printf("Adding single digit to everyOther\n");
            }
        }
        
        //add together the digits of the ones that were not multiplied by 2
        if (counter % 2 == 1)
        {
//            printf("Adding to notOther\n");
//            printf("ones = %i\n", ones);
            notOther = notOther + ones;
//            printf("notOther = %i\n", notOther);
        }
    }
    
    printf("%i + %i\n", everyOther, notOther);
    //do the checksum
    if ((everyOther + notOther) % 10 == 0)
    {
        
        //if the checksum passes

        printf("Starting CheckSum\nCounter = %i\nFirst digit = %i\nSecond digit = %i\n ", counter, firstNum, secondNum);
        
        //Check the number of digits & first and second numbers for AMEX
        if (counter == 15 && firstNum == 3 && (secondNum == 4 || secondNum == 7))
        {
            printf("AMEX\n");
        }
        
        //Check the number of digits & first and second numbers for MASTERCARD
        else if (counter == 16 && firstNum == 5 && secondNum >= 1 && secondNum <= 5)
        {
            printf("MASTERCARD\n");
        }
        
        //Check the number of digits & first number for VISA
        else if ((counter == 13 || counter == 16) && firstNum == 4)
        {
            printf("VISA\n");
        }
        
        //if none of the above passes, print INVALID
        else
        {
            printf("INVALID\n");
        }
    }
    
    //if the checksum fails, print INVALID
    else
    {
        printf("INVALID\n");
    }

    //print credit card number
//    printf("CC = %li\n", cc);
}