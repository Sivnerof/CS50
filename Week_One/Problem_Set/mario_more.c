#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Prompt user for pyramid height within specified parameters
    int pyramidHeight;
    do
    {
        pyramidHeight = get_int("Height: ");
    }
    while (pyramidHeight < 1 || pyramidHeight > 8);

    /*
    Main for loop takes care of spaces between left/right aligned pyramids,
    and line breaks for each new row.
    */

    for (int i = 0; i < pyramidHeight; i++)
    {

        //right aligned pyramid spacing using deincrementation
        for (int j = pyramidHeight - 1; j > i; j--)
        {
            printf(" ");
        }

        //Right Aligned
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }

        printf("  ");

        //Left Aligned
        for (int l = 0; l <= i; l++)
        {
            printf("#");
        }

        printf("\n");

    }
}