// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 500;

// Hash table
node *table[N];

int size_of_dict;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{

    // Find index position of word
    int index = hash(word);

    // Create cursor
    node *cursor = table[index];

    // Traverse linked list updating cursor
    while (cursor != NULL)
    {
        // Case compare insensitively word and word at cursor
        if (strcasecmp(cursor->word, word) == 0)
        {
            // Found
            return true;
        }

        // Update the cursor
        cursor = cursor->next;
    }

    // Word mispelled
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hashed = 0;

    // Loop through each letter of word
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        hashed += tolower(word[i]);
    }

    // Fit into bucket
    return hashed % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open file
    FILE *dict = fopen(dictionary, "r");

    // if invalid
    if (dict == NULL)
    {
        return false;
    }

    // Create buffer for temporary storage
    char buffer[LENGTH + 1];

    // Read until end of file
    while (fscanf(dict, "%s", buffer) != EOF)
    {

        // Malloc enough for each new node
        node *n = malloc(sizeof(node));

        // Check that malloc didn't pass back a garbage value
        if (n == NULL)
        {
            return false;
        }

        // Copy buffers storage into each new node
        strcpy(n->word, buffer);

        n->next = NULL;

        // Get back index position of buffers storage
        int index = hash(buffer);

        // Create new index position if none exists
        if (table[index] == NULL)
        {
            table[index] = n;
        }

        // Set node next, set index
        else
        {
            n->next = table[index];
            table[index] = n;
        }

        // Increment word count for use in size function
        size_of_dict++;
    }

    // Load succesful, close files, return.
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return count we created in load function
    return size_of_dict;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Loop through table
    for (int i = 0; i < N; i++)
    {
        // Create cursor
        node *deletion_cursor = table[i];

        // Loop through nodes
        while (deletion_cursor != NULL)
        {

            // Set temporary cursor equal to deletion
            node *temp_cursor = deletion_cursor;

            // Point cursor to next element
            deletion_cursor = deletion_cursor->next;

            // free node before deletion cursor
            free(temp_cursor);
        }

        // None left to free
        if (deletion_cursor == NULL && i == N - 1)
        {
            return true;
        }
    }

    // Failure to unload
    return false;
}
