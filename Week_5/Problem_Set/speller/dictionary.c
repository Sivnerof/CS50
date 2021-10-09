// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

int size_of_dict;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open file
    FILE* dict = fopen(dictionary, "r");

    // if valid
    if (dict != NULL)
    {

        // Create buffer for temporary storage
        char buffer[LENGTH + 1];

        // Read until end of file
        while(fscanf(dict, "%s", buffer) != EOF)
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

    // If here unsuccesful
    return false;

    /*
    Open dictionary
        fopen
        null
    Read strings one at a time
        fscanf(file, "%s", word)
        fscanf returns EOF at end of file
        need buffer here
    Create new node for each word
        use malloc
        check null
        copy word using strcopy
    Hash word to obtain a hash value
        use hash function
        func hash takes string returns index
    Insert node into hash table at that location
        hash table is array of linked lists
        set pointers in correct order!!

        remember to close files/free memory
    */
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
