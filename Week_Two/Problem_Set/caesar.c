#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
    A program that uses a Caesar Cipher on user provided plaintext where the key to be used is inputted through a command line argument.
*/

string caesarCipher(int rotation, string userText);

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

    //Result is a valid Key
    int key = atoi(argv[1]);

    //User Inputs
    string plainText = get_string("plaintext: ");

    //Pass To function for rotation
    string cipherText = caesarCipher(key, plainText);

    //printf("ciphertext: \n");

    return 0;
}

string caesarCipher(int rotation, string userText)
{
    string testing;
    for(int i = 0, n = strlen(userText); i < n; i++)
    {
        if(isalpha(userText[i]))
        {
            userText[i] += 1;
        }
        //printf("%c", userText[i]);
        testing = userText;
    }
    return "test";
}

/*


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

