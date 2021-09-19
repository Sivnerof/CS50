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
char substituteChar(char individualChar, string keyArray, string alphabetArray);

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

    //Store key copy
    string key = (argv[1]);

    //Grab users plain text
    string plainText = get_string("plaintext: ");

    //Output enciphered result
    printf("ciphertext: ");

    //Handle symbols, spaces, non-alphabetical in function before passing off
    for (int i = 0, n = strlen(plainText); i < n; i++)
    {
        char cipherChar;

        //Pass to helper function
        if (isalpha(plainText[i]))
        {
            cipherChar = substituteChar(plainText[i], key, neededLetters);
        }

        //Output all others
        else
        {
            cipherChar = plainText[i];
        }

        printf("%c", cipherChar);
    }

    printf("\n");

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

char substituteChar(char individualChar, string keyArray, string alphabetArray)
{
    //Define two variables, one for result when found, other to find position in the alphabet array
    char subChar = 0;
    int x;

    //Preserve case
    if (isupper(individualChar))
    {
        //Loop through first array
        for (int i = 0, n = strlen(alphabetArray); i < n; i++)
        {
            //Catch and set position to variable
            if (individualChar == alphabetArray[i])
            {
                x = i;

                //Loop that many times through second array
                for (int j = 0, k = strlen(keyArray); j < k; j++)
                {
                    //Catch same position in second array
                    if (j == x)
                    {
                        //Bring back the result for cipher
                        subChar = toupper(keyArray[i]);
                    }
                }
            }
        }
    }

    //Same as above, preserve case
    if (islower(individualChar))
    {
        //Except here we set to uppercase so we can match first array
        individualChar = toupper(individualChar);

        //Loop through first array, catch position.
        for (int i = 0, n = strlen(alphabetArray); i < n; i++)
        {
            if (individualChar == alphabetArray[i])
            {
                x = i;

                //Use x as the stopping point and bring back the result
                for (int j = 0, k = strlen(keyArray); j < k; j++)
                {
                    if (j == x)
                    {
                        subChar = tolower(keyArray[i]);
                    }
                }
            }
        }
    }
    return subChar;
}