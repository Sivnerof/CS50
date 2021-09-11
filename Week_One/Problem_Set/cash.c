#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //A program that uses greedy algorithm to calculate least amount of coins owed back

    //Prompt user for change owed and Handles negative values
    float changeOwed;
    do
    {
        changeOwed = get_float("Change owed: ");
    }
    while (changeOwed < 0);

    //Converts dollars to cents
    int changeInPennies = round(changeOwed * 100);

    //Remove chunks of 25, 10, 5, 1 repeatedly while incrementing the coin total
    int coinTotal = 0;
    while (changeInPennies >= 25)
    {
        changeInPennies -= 25;
        coinTotal++;
    }

    while (changeInPennies >= 10)
    {
        changeInPennies -= 10;
        coinTotal++;
    }

    while (changeInPennies >= 5)
    {
        changeInPennies -= 5;
        coinTotal++;
    }

    while (changeInPennies >= 1)
    {
        changeInPennies -= 1;
        coinTotal++;
    }

    //Prints least amount of coins needed to give back
    printf("%i", coinTotal);
}