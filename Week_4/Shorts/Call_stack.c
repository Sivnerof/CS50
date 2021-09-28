#include <stdio.h>
#include <cs50.h>

long fact(int x);
int main(void)
{
    long factorial = get_int("Factorial of: ");
    printf("Factorial of %li is... ", factorial);
    printf("%li\n", fact(factorial));
    return 0;
}

long fact(int x)
{
    if (x == 1)
    {
        return 1;
    }
    else
    {
        return x * fact(x - 1);
    }
}