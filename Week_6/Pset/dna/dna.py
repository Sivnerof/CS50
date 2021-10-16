"""
    Implement a program that matches a DNA sequence to the individual in the CSV files.
"""

from cs50 import get_string
import sys, csv


def main():

    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: /python dna.py [CSV FILE] [TEXT FILE]")

    # Read dna strand into memory
    dna_strand = read_dna(sys.argv[2])

    # Read dna samples of subjects into memory
    dna_samples = read_samples(sys.argv[1])
    print(dna_samples[0]['name'])

    # Get Short Tandem Repeats
    STR = get_str(dna_samples)
    print(STR)


    repeats = look_for_repeats(dna_strand, STR)

    return

# open dna text file and store contents
def read_dna(n):

    with open(n, 'r') as f:
        for line in f:
            dna = line

    return dna


def read_samples(n):
    dict_list = []
    with open(n, 'r') as f:
        reader = csv.DictReader(f)
        for line in reader:
            dict_list.append(line)
    return dict_list


def get_str(n):
    str_strip = list(n[0].keys())
    str_strip = str_strip[1:]
    return str_strip


def look_for_repeats(dna, strs):

    testlist = []
    test = dna.count(strs[0])
    print(test)

    counter = 0
    for i in strs:
        testlist.append(dna.count(strs[counter]))
        counter += 1
    print (testlist)

    return testlist


main()

"""
    For each STR compute longest run of consecutive repeats in the DNA sequence.

    Compare STR counts against each row in CSV file.



    You may find Python’s csv module helpful for reading CSV files into memory.
    You may want to take advantage of either csv.reader or csv.DictReader.
    The open and read functions may prove useful for reading text files into memory.
    Consider what data structures might be helpful for keeping tracking of information in your program.
    A list or a dict may prove useful.
    Python strings allow “slicing” (accessing a particular substring within a string).
    If s is a string, then s[i:j] will return a new string with just the characters of s,
    starting from character i up through (but not including) character j.
    It may be helpful to start by writing a function that,
    given both a DNA sequence and an STR as inputs, returns the maximum number of times that the STR repeats.
    You can then use that function in other parts of your program!


Your program should open the DNA sequence and read its contents into memory.
For each of the STRs (from the first line of the CSV file),
your program should compute the longest run of consecutive repeats of the STR in the DNA sequence to identify.
If the STR counts match exactly with any of the individuals in the CSV file,
your program should print out the name of the matching individual.

    You may assume that the STR counts will not match more than one individual.
    If the STR counts do not match exactly with any of the individuals in the CSV file, your program should print "No match".



DNA is really just a sequence of molecules called nucleotides,
arranged into a particular shape (a double helix).
Each nucleotide of DNA contains one of four different bases:
adenine (A), cytosine (C), guanine (G), or thymine (T).
Every human cell has billions of these nucleotides arranged in sequence.
Some portions of this sequence (i.e. genome) are the same, or at least very similar,
across almost all humans, but other portions of the sequence have a higher genetic diversity
and thus vary more across the population.

One place where DNA tends to have high genetic diversity is in Short Tandem Repeats (STRs).
An STR is a short sequence of DNA bases that tends to repeat consecutively numerous times at specific locations inside of a person’s DNA.
The number of times any particular STR repeats varies a lot among individuals.
In the DNA samples below, for example,
Alice has the STR AGAT repeated four times in her DNA,
while Bob has the same STR repeated five times.

Sample STRs

Using multiple STRs, rather than just one, can improve the accuracy of DNA profiling.
If the probability that two people have the same number of repeats for a single STR is 5%,
and the analyst looks at 10 different STRs,
then the probability that two DNA samples match purely by chance is about 1 in 1 quadrillion
(assuming all STRs are independent of each other).
So if two DNA samples match in the number of repeats for each of the STRs,
the analyst can be pretty confident they came from the same person. CODIS, The FBI’s DNA database,
uses 20 different STRs as part of its DNA profiling process.

What might such a DNA database look like? Well, in its simplest form,
you could imagine formatting a DNA database as a CSV file,
wherein each row corresponds to an individual,
and each column corresponds to a particular STR.

name,AGAT,AATG,TATC
Alice,28,42,14
Bob,17,22,19
Charlie,36,18,25

The data in the above file would suggest that Alice has the sequence AGAT repeated 28 times consecutively somewhere in her DNA,
the sequence AATG repeated 42 times, and TATC repeated 14 times.
Bob, meanwhile, has those same three STRs repeated 17 times, 22 times, and 19 times, respectively.
And Charlie has those same three STRs repeated 36, 18, and 25 times, respectively.

So given a sequence of DNA, how might you identify to whom it belongs?
Well, imagine that you looked through the DNA sequence for the longest consecutive sequence of
repeated AGATs and found that the longest sequence was 17 repeats long.
If you then found that the longest sequence of AATG is 22 repeats long,
and the longest sequence of TATC is 19 repeats long,
that would provide pretty good evidence that the DNA was Bob’s.
Of course, it’s also possible that once you take the counts for each of the STRs,
it doesn’t match anyone in your DNA database, in which case you have no match.

In practice, since analysts know on which chromosome and at which location in the DNA an STR will be found,
they can localize their search to just a narrow section of DNA. But we’ll ignore that detail for this problem.

Write a program that:
will take a sequence of DNA and a CSV file containing STR counts for
a list of individuals and then output to whom the DNA (most likely) belongs.

"""