#include <cs50.h>
#include <string.h>
#include <stdio.h>

/*
    A program that simulates a Tideman runoff voting system

                         A  B  C  D  E  F
                        [0][1][2][3][4][5]

                A  [0]  [0][?][?][?][?][?] I
                B  [1]  [?][0][?][?][?][?] |
                C  [2]  [?][?][0][?][?][?] |
                D  [3]  [?][?][?][0][?][?] |
                E  [4]  [?][?][?][?][0][?] |
                F  [5]  [?][?][?][?][?][0] v
                         J ------------->
*/

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
bool pairComparisonCycle(int start, int end);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Catch candidates position in array
        if (strcmp(candidates[i], name) == 0)
        {
            // array ranks position is equal to incoming rank, value inserted is candidate location
            ranks[rank] = i;
            return true;
        }
    }
    // Handle false entries
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Loop through voter array
    for (int i = 0; i < candidate_count; i++)
    {
        // Side by side comparison with next number up
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Increment position at following coordinates
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // variable for incrementing position of pairs array
    int position = 0;

    // traversal of 2-D array of preferences
    for (int i = 0; i < candidate_count; i++)
    {
        // inner loop compares opposite side of adjacency matrix
        for (int j = 0; j < candidate_count; j++)
        {
            // here we catch the losing side
            if (preferences[i][j] > preferences[j][i])
            {
                // update pairs of winners/losers
                pairs[position].winner = i;
                pairs[position].loser = j;

                //Move position over one & increment pair count
                pair_count++;
                position++;
            }

        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Variables for swapping and setting positions
    int swapWinner, swapLoser, position;

    // Loop through all winner, loser pairs
    for (int i = 0; i < pair_count; i++)
    {
        // Set position (flag) to this current iteration
        position = i;

        // Side by side comparison, selection sort
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                // Set flag
                position = j;
            }
        }

        // If here we need to swap
        if (position != i)
        {
            // Use container variables to store swap pairs
            swapWinner = pairs[i].winner;
            swapLoser = pairs[i].loser;
            pairs[i].winner = pairs[position].winner;
            pairs[i].loser = pairs[position].loser;
            pairs[position].winner = swapWinner;
            pairs[position].loser = swapLoser;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    /*
    This article helps understand recursive function for lock_pairs problem
    https://gist.github.com/nicknapoli82/6c5a1706489e70342e9a0a635ae738c9
    */

    // Loop through pairs and send to helper function
    for (int i = 0; i < pair_count; i++)
    {
        // Filter pairs that would cause a loop around all candidates
        if (!pairComparisonCycle(pairs[i].winner, pairs[i].loser))
        {
            // Original route origin here
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

bool pairComparisonCycle(int start, int end)
{
    // If true the origin was looped back to
    if (end == start)
    {
        return true;
    }

    // Go through pairs
    for (int i = 0; i < pair_count; i++)
    {
        // Check if loser wins against candidate in this iteration
        if (locked[end][i])
        {
            // Check if that person loops back to original point
            if (pairComparisonCycle(start, i))
            {
                return true;
            }
        }
    }

    // No cycle if here
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // Loop through 2-D pair count
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            // Check if a user has a true value against an opponent in row
            // While their column is all false
            if (locked[i][j] == true && locked[j][i] == false)
            {
                // Winner
                printf("%s\n", candidates[i]);
            }
        }
    }
    return;
}