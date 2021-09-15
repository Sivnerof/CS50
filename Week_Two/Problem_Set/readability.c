#include<stdio.h>
#include<cs50.h>
#include<ctype.h>
#include<string.h>
#include<math.h>

int countLetters(string usersString);

int main(void)
{
    //Get users input
    string userText = get_string("Text: ");
    int userTextLength = countLetters(userText);
    //printf("Grade %i\n", );

    return 0;
}

//Count overall length of users input
int countLetters(string usersString)
{
    int letters = 0;
    int words = 1;
    int sentences = 0;
    for(int i = 0, n = strlen(usersString); i < n; i++)
    {
        if(isalpha(usersString[i]))
        {
            letters++;
        }
        else if(isspace(usersString[i]))
        {
            words++;
        }
        else if(usersString[i] == '!' || usersString[i] == '?' || usersString[i] == '.')
        {
            sentences++;
        }
    }
    printf("letters: %i\n", letters);
    printf("spaces: %i\n", words);
    printf("sentences: %i\n", sentences);

    float L = (((float) letters / words) * 100);
    float S = (((float) sentences / words) * 100);
    printf("test: %f\n", L);
    printf("test: %f\n", S);
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    printf("index: %i", index);


    return letters;
}





/*
index = 0.0588 * L - 0.296 * S - 15.8
Here, L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.



Example = Congratulations! Today is your day. You're off to Great Places! You're off and away!
The text the user inputted has 65 letters, 4 sentences, and 14 words.


65 letters per 14 words is an average of about 464.29 letters per 100 words.
And 4 sentences per 14 words is an average of about 28.57 sentences per 100 words.
Plugged into the Coleman-Liau formula, and rounded to the nearest whole number, we get an answer of 3: so this passage is at a third grade reading level.


Your program should print as output "Grade X" where X is the grade level computed by the Coleman-Liau formula, rounded to the nearest integer.
If the resulting index number is 16 or higher (equivalent to or greater than a senior undergraduate reading level),
your program should output "Grade 16+" instead of giving the exact index number.
If the index number is less than 1, your program should output "Before Grade 1".


*/