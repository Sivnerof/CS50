#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
    A program that uses a Caesar Cipher on user provided plaintext where the key to be used is inputted through a command line argument.
*/

int main(int argc, string argv[])
{
    //Handle too many arguments
    if(argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //Handle non numeric arguments
    for(int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if(!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    printf("%s\n", argv[1]);
    //string plainText = get_string("plaintext: ");
    //printf("ciphertext: \n");

    return 0;
}

/*

Usage: ./caesar key

At the time the user executes the program, they should decide, by providing a command-line argument,
on what the key should be in the secret message they’ll provide at runtime.
We shouldn’t necessarily assume that the user’s key is going to be a number;
though you may assume that, if it is a number, it will be a positive integer.

More formally, Caesar’s algorithm (i.e., cipher) encrypts messages by “rotating” each letter by k positions.
More formally, if p is some plaintext (i.e., an unencrypted message),
pi is the ith character in p, and k is a secret key (i.e., a non-negative integer), then each letter, ci, in the ciphertext, c, is computed as

ci = (pi + k) % 26

wherein % 26 here means “remainder when dividing by 26.”
This formula perhaps makes the cipher seem more complicated than it is,
but it’s really just a concise way of expressing the algorithm precisely.
Indeed, for the sake of discussion,
think of A (or a) as 0, B (or b) as 1, …, H (or h) as 7, I (or i) as 8, …, and Z (or z) as 25.
Suppose that Caesar just wants to say Hi to someone confidentially using,
this time, a key, k, of 3.
And so his plaintext, p, is Hi, in which case his plaintext’s first character, p0, is H (aka 7), and his plaintext’s second character, p1, is i (aka 8).
His ciphertext’s first character, c0, is thus K, and his ciphertext’s second character, c1, is thus L.






*/