#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>

/*

   ___            _                _        _      _               _        _
  / __|   _  _   | |__     ___    | |_     (_)    | |_    _  _    | |_     (_)     ___    _ _
  \__ \  | +| |  | '_ \   (_-<    |  _|    | |    |  _|  | +| |   |  _|    | |    / _ \  | ' \
  |___/   \_,_|  |_.__/   /__/_   _\__|   _|_|_   _\__|   \_,_|   _\__|   _|_|_   \___/  |_||_|
_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|
"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'

    A program that uses a 26 character long key provided by the user at the command line,
    which will be used to encipher their also provided plaintext.
*/

bool validCheck(string userKey, char neededChar);

int main(int argc, string argv[])

{
    //Handles too many/no arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //Handles non-alphabetical keys or wrong length
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isalpha(argv[1][i]) || strlen(argv[1]) != 26)
        {
            printf("fail");
            return 1;
        }
    }

    //Create array and bool to be checked against users key
    bool validKey = false;
    string neededLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    //Loops through Alphabet passing every individual char to helper function
    for (int i = 0, n = strlen(neededLetters); i < n; i++)
    {
        validKey = validCheck(argv[1], neededLetters[i]);

        //Handles wrong keys
        if (validKey == false)
        {
            printf("fail");
            return 1;
        }
    }

    printf("Argv: %s\n", argv[1]);

    return 0;
}

bool validCheck(string userKey, char neededChar)
{
    //Helper function for key validation
    bool x = false;
    for (int i = 0, n = strlen(userKey); i < n; i++)
    {
        //Grabs lowercase letters
        if (islower(userKey[i]))
        {
            //Converts to upper so we can match to correct array
            userKey[i] = toupper(userKey[i]);

            if (userKey[i] == neededChar)
            {
                x = true;
            }

            //Convert back to original case so we can preserve original form
            userKey[i] = tolower(userKey[i]);
        }

        //Check again this time with upper case
        if (isupper(userKey[i]))
        {
            if (userKey[i] == neededChar)
            {
                x = true;
            }
        }

    }
    return x;
}

/*

    Your program must output plaintext: (without a newline) and then prompt the user for a string of plaintext (using get_string).
    Your program must output ciphertext: (without a newline) followed by the plaintext’s corresponding ciphertext, with each alphabetical character in the plaintext substituted for the corresponding character in the ciphertext; non-alphabetical characters should be outputted unchanged.
    Your program must preserve case: capitalized letters must remain capitalized letters; lowercase letters must remain lowercase letters.
    After outputting ciphertext, you should print a newline. Your program should then exit by returning 0 from main.
*/