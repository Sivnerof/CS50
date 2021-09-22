#include <cs50.h>
#include <stdio.h>
#include <string.h>

/*
    A program that takes names of candidates as command line arguments,
    along with individual votes for said candidates and produces the results of the plurality election.
*/

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Loop through comparing name and incrementing their vote
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;

}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Variables to be used for swapping name/votes in selection sort, and one to track position
    int position, swapInt;
    string swapName;

    for (int i = 0; i < (candidate_count - 1); i++)
    {
        // Set Position
        position = i;

        // Nested loop comparing first and second locations in array
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (candidates[position].votes > candidates[j].votes)
            {
                // Change position
                position = j;
            }
        }

        if (position != i)
        {
            // Move names and votes to their expected positions using container variables
            swapName = candidates[i].name;
            swapInt = candidates[i].votes;
            candidates[i].name = candidates[position].name;
            candidates[i].votes = candidates[position].votes;
            candidates[position].name = swapName;
            candidates[position].votes = swapInt;
        }
    }

    // Now that array is sorted, winner will always be at the end
    for (int i = candidate_count - 1; i > 0; i--)
    {
        // Print the last name in the array as winner
        if (candidates[i].votes > candidates[i - 1].votes)
        {
            printf("%s\n", candidates[i].name);
            return;
        }

        // In case of two way tie
        else if (candidates[i].votes == candidates[i - 1].votes && candidates[i].votes == candidates[i - 2].votes)
        {
            printf("%s\n", candidates[i].name);
            printf("%s\n", candidates[i - 1].name);
            printf("%s\n", candidates[i - 2].name);
            return;
        }

        // If the loop reaches here it's a 3 way tie
        else if (candidates[i].votes == candidates[i - 1].votes)
        {
            printf("%s\n", candidates[i].name);
            printf("%s\n", candidates[i - 1].name);
            return;
        }
    }

    return;
}
