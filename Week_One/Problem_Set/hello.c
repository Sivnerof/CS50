#include <cs50.h>
#include <stdio.h>

/*
    Simple program that greets someone
*/

int main(void)
{
    string greetings = get_string("What's your name? ");
    printf("Hello, %s\n", greetings);
}