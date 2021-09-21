#include <stdio.h>
#include <cs50.h>

/*
    A program that calculates how many steps any number will take getting back to one,
    using Collatz Conjecture.
*/

int collatzFunction(int userInt);
int main(void)
{
    int userInt = get_int("Number to be used: \n");

    if (userInt < 1)
    {
        printf("Positive numbers only\n");
        return 1;
    }

    int result = collatzFunction(userInt);
    printf("Times ran until base case: %i\n", result);
}

int collatzFunction(int a)
{
    if (a == 1)
        return 0;
    else if ((a % 2) == 0)
        return 1 + collatzFunction(a / 2);
    else
        return 1 + collatzFunction(3 * a + 1);
}