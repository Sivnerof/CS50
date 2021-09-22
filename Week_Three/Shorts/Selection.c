#include <cs50.h>
#include <string.h>
#include <stdio.h>

/*

    Selection Sort Demonstration

*/

int userNumbers[10];
int length = 10;

void selectionSort(void);

int main(void)
{
    for (int i = 0; i < length; i++)
    {
        userNumbers[i] = get_int("Number: ");
    }

    selectionSort();

    return 0;
}

void selectionSort(void)
{
    int swap, location, j;

    // Iterrate through whole array
    for (int i = 0; i < length; i++)
    {
        // Set this variable to the position of array at this iteration
        location = i;

        // Nested loop that compares next position in array and sets flag
        for (j = i + 1; j < length; j++)
        {
            // Flag is set if this number is out of order
            if(userNumbers[location] > userNumbers[j])
            {
                location = j;
            }
        }

        // Catches flagged iteration
        if (location != i)
        {
            // Sets container variable to this iteration
            swap = userNumbers[i];

            // Now this space is safe to insert into with the value of the next location in array
            userNumbers[i] = userNumbers[location];

            // Now dump container variable into next location in array
            userNumbers[location] = swap;
        }

        printf("%i\n", userNumbers[i]);
    }
    return;
}