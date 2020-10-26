# include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //declare variable to hold the user's change
    float dollars;
    
    //declare variable to hold number of coins
    int coins = 0;
    int coins25 = 0;
    int coins10 = 0;
    int coins5 = 0;
    int coins1 = 0;
    
    
    //loop until user enters a positive number
    do
    {
        //prompt user for amount of change owed
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0);
    
    //convert change from dollars (float) to cents (int)
    int cents = round(dollars * 100);
    
    //check for quarters
    if (cents / 25 > 0)
    {
        coins25 = round(cents / 25);
        cents = cents % (coins25 * 25);
    }
    
    // check for dimes
    if (cents / 10 > 0)
    {
        coins10 = round(cents / 10);
        cents = cents % (coins10 * 10);
    }
    
    // check for nickels
    if (cents / 5 > 0)
    {
        coins5 = round(cents / 5);
        cents = cents % (coins5 * 5);
    }
    
    // check for pennies
    if (cents / 1 > 0)
    {
        coins1 = round(cents / 1);
        cents = cents % (coins1 * 1);
    }
   

    //output the amount of change owed in cents
    printf("Your remainder is %i cents.\n", cents);
    coins = coins25 + coins10 + coins5 + coins1;
    printf("%i\n", coins);
}
