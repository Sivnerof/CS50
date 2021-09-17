#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
    A program that uses a Caesar Cipher on user provided plaintext where the key to be used is inputted through a command line argument.
*/

char rotatePlain(char individualChar, int keyUsed);

int main(int argc, string argv[])
{
    //Handles too many arguments
    if(argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //Handle non-numeric arguments
    for(int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if(!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    //Key to be used in rotation
    int key = atoi(argv[1]);

    //User provided input
    string plainText = get_string("plaintext:  ");

    //Result
    char singleRot;
    printf("ciphertext: ");

    //Individual chars sent to function
    for(int i = 0, n = strlen(plainText); i < n; i++)
    {
        singleRot = rotatePlain(plainText[i], key);
        printf("%c", singleRot);
    }
    printf("\n");

    return 0;
}

//Rotate Plain Text
char rotatePlain(char individualChar, int keyUsed)
{
    if(isalpha(individualChar))
    {
        individualChar += keyUsed;
    }
    return individualChar;
}