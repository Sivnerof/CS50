// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    // TODO: Allocate memory for new person

    // Generation with parent data
    if (generations > 1)
    {
        // TODO: Recursively create blood type histories for parents

        // TODO: Randomly assign child alleles based on parents
    }

    // Generation without parent data
    else
    {
        // TODO: Set parent pointers to NULL

        // TODO: Randomly assign alleles
    }

    // TODO: Return newly created person
    return NULL;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // TODO: Handle base case

    // TODO: Free parents

    // TODO: Free child
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    printf("Generation %i, blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}

/*
Possible blood type combinations: OO, OA, OB, AO, AA, AB, BO, BA, and BB.
For example, if one parent has blood type AO and the other parent has blood type BB,
then the child’s possible blood types would be AB and OB, depending on which allele is received from each parent.
Similarly, if one parent has blood type AO and the other OB, then the child’s possible blood types would be AO, OB, AB, and OO.

Take a look at the distribution code in inheritance.c.

Notice the definition of a type called person.
Each person has an array of two parents, each of which is a pointer to another person struct.
Each person also has an array of two alleles, each of which is a char (either 'A', 'B', or 'O').

Now, take a look at the main function.
The function begins by “seeding” (i.e., providing some initial input to) a random number generator,
which we’ll use later to generate random alleles.
The main function then calls the create_family function
to simulate the creation of person structs for a family of 3 generations
(i.e. a person, their parents, and their grandparents).
We then call print_family to print out each of those family members and their blood types.
Finally, the function calls free_family to free any memory that was previously allocated with malloc.

The create_family and free_family functions are left to you to write!

Complete the implementation of inheritance.c, such that it creates a family of a specified generation size and assigns blood type alleles to each family member. The oldest generation will have alleles assigned randomly to them.

    The create_family function takes an integer (generations) as input and should allocate (as via malloc) one person for each member of the family of that number of generations, returning a pointer to the person in the youngest generation.
        For example, create_family(3) should return a pointer to a person with two parents, where each parent also has two parents.
        Each person should have alleles assigned to them. The oldest generation should have alleles randomly chosen (as by calling the random_allele function), and younger generations should inherit one allele (chosen at random) from each parent.
        Each person should have parents assigned to them. The oldest generation should have both parents set to NULL, and younger generations should have parents be an array of two pointers, each pointing to a different parent.

We’ve divided the create_family function into a few TODOs for you to complete.

    First, you should allocate memory for a new person. Recall that you can use malloc to allocate memory, and sizeof(person) to get the number of bytes to allocate.
    Next, we’ve included a condition to check if generations > 1.
        If generations > 1, then there are more generations that still need to be allocated. Your function should set both parents by recursively calling create_family. (How many generations should be passed as input to each parent?) The function should then set both alleles by randomly choosing one allele from each parent.
        Otherwise (if generations == 1), then there will be no parent data for this person. Both parents should be set to NULL, and each allele should be generated randomly.
    Finally, your function should return a pointer for the person that was allocated.

The free_family function should accept as input a pointer to a person, free memory for that person, and then recursively free memory for all of their ancestors.

    Since this is a recursive function, you should first handle the base case. If the input to the function is NULL, then there’s nothing to free, so your function can return immediately.
    Otherwise, you should recursively free both of the person’s parents before freeing the child.


    You might find the rand() function useful for randomly assigning alleles. This function returns an integer between 0 and RAND_MAX, or 32767.
        In particular, to generate a pseudorandom number that is either 0 or 1, you can use the expression rand() % 2.
    Remember, to allocate memory for a particular person, we can use malloc(n), which takes a size as argument and will allocate n bytes of memory.
    Remember, to access a variable via a pointer, we can use arrow notation.
        For example, if p is a pointer to a person, then a pointer to this person’s first parent can be accessed by p->parents[0].

*/