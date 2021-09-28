#include<stdio.h>
#include<cs50.h>
#include<ctype.h>
#include<string.h>
#include<math.h>

/*
    A program that calculates the reading level of a users supllied text,
    according to grade level using the Coleman-Liau formula.
*/

int colemanLiau(string usersString);

int main(void)
{
    //Get users input
    string userText = get_string("Text: ");

    //Pass to function for calculation
    int gradeLevel = colemanLiau(userText);

    //Handles under first grade reading levels
    if (gradeLevel < 1)
    {
        printf("Before Grade 1\n");
    }

    //Handles reading levels above 16
    else if (gradeLevel > 16)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("Grade %i\n", gradeLevel);
    }

    return 0;
}

int colemanLiau(string usersString)
{
    int letters = 0;
    int words = 1;
    int sentences = 0;

    //Loops through all characters in users provided string
    for (int i = 0, n = strlen(usersString); i < n; i++)
    {
        //Catches all alphabetical characters and increments their count
        if (isalpha(usersString[i]))
        {
            letters++;
        }

        //Identifies all white space as the ending of a word
        else if (isspace(usersString[i]))
        {
            words++;
        }

        //Identifies these three as the ends of sentences
        else if (usersString[i] == '!' || usersString[i] == '?' || usersString[i] == '.')
        {
            sentences++;
        }
    }

    //Coleman-Liau Index
    float L = (((float) letters / words) * 100);
    float S = (((float) sentences / words) * 100);
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    return index;
}