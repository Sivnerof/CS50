#include <cs50.h>
#include <stdio.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    return 0;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    return;
}

/*
Let’s open up runoff.c to take a look at what’s already there. We’re defining two constants: MAX_CANDIDATES for the maximum number of candidates in the election, and MAX_VOTERS for the maximum number of voters in the election.

Next up is a two-dimensional array preferences. The array preferences[i] will represent all of the preferences for voter number i, and the integer preferences[i][j] here will store the index of the candidate who is the jth preference for voter i.

Next up is a struct called candidate. Every candidate has a string field for their name, and int representing the number of votes they currently have, and a bool value called eliminated that indicates whether the candidate has been eliminated from the election. The array candidates will keep track of all of the candidates in the election.

The program also has two global variables: voter_count and candidate_count.

Now onto main. Notice that after determining the number of candidates and the number of voters, the main voting loop begins, giving every voter a chance to vote. As the voter enters their preferences, the vote function is called to keep track of all of the preferences. If at any point, the ballot is deemed to be invalid, the program exits.

Once all of the votes are in, another loop begins: this one’s going to keep looping through the runoff process of checking for a winner and eliminating the last place candidate until there is a winner.

The first call here is to a function called tabulate, which should look at all of the voters’ preferences and compute the current vote totals, by looking at each voter’s top choice candidate who hasn’t yet been eliminated. Next, the print_winner function should print out the winner if there is one; if there is, the program is over. But otherwise, the program needs to determine the fewest number of votes anyone still in the election received (via a call to find_min). If it turns out that everyone in the election is tied with the same number of votes (as determined by the is_tie function), the election is declared a tie; otherwise, the last-place candidate (or candidates) is eliminated from the election via a call to the eliminate function.

If you look a bit further down in the file, you’ll see that these functions — vote, tabulate, print_winner, find_min, is_tie, and eliminate — are all left to up to you to complete!

Complete the vote function.

    The function takes arguments voter, rank, and name. If name is a match for the name of a valid candidate, then you should update the global preferences array to indicate that the voter voter has that candidate as their rank preference (where 0 is the first preference, 1 is the second preference, etc.).
    If the preference is successfully recorded, the function should return true; the function should return false otherwise (if, for instance, name is not the name of one of the candidates).
    You may assume that no two candidates will have the same name.

Hints

    Recall that candidate_count stores the number of candidates in the election.
    Recall that you can use strcmp to compare two strings.
    Recall that preferences[i][j] stores the index of the candidate who is the jth ranked preference for the ith voter.

Complete the tabulate function.

    The function should update the number of votes each candidate has at this stage in the runoff.
    Recall that at each stage in the runoff, every voter effectively votes for their top-preferred candidate who has not already been eliminated.

Hints

    Recall that voter_count stores the number of voters in the election.
    Recall that for a voter i, their top choice candidate is represented by preferences[i][0], their second choice candidate by preferences[i][1], etc.
    Recall that the candidate struct has a field called eliminated, which will be true if the candidate has been eliminated from the election.
    Recall that the candidate struct has a field called votes, which you’ll likely want to update for each voter’s preferred candidate.

Complete the print_winner function.

    If any candidate has more than half of the vote, their name should be printed to stdout and the function should return true.
    If nobody has won the election yet, the function should return false.

Hints

    Recall that voter_count stores the number of voters in the election. Given that, how would you express the number of votes needed to win the election?

Complete the find_min function.

    The function should return the minimum vote total for any candidate who is still in the election.

Hints

    You’ll likely want to loop through the candidates to find the one who is both still in the election and has the fewest number of votes. What information should you keep track of as you loop through the candidates?

Complete the is_tie function.

    The function takes an argument min, which will be the minimum number of votes that anyone in the election currently has.
    The function should return true if every candidate remaining in the election has the same number of votes, and should return false otherwise.

Hints

    Recall that a tie happens if every candidate still in the election has the same number of votes. Note, too, that the is_tie function takes an argument min, which is the smallest number of votes any candidate currently has. How might you use that information to determine if the election is a tie (or, conversely, not a tie)?

Complete the eliminate function.

    The function takes an argument min, which will be the minimum number of votes that anyone in the election currently has.
    The function should eliminate the candidate (or candidates) who have min number of votes.

*/