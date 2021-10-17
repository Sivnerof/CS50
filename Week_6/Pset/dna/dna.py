"""
    Implement a program that matches a DNA sequence to the individual in the CSV files.
"""

from cs50 import get_string
import sys
import csv


def main():

    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: /python dna.py [CSV FILE] [TEXT FILE]")

    # Read dna strand into memory
    dna_strand = read_dna(sys.argv[2])

    # Read dna samples of subjects into memory
    dna_samples = read_samples(sys.argv[1])

    # Get Short Tandem Repeats
    STR = get_str(dna_samples)

    # Get list of repeat STRS
    repeats = look_for_repeats(dna_strand, STR)

    # Check dictionary for match
    outcome = identify_match(repeats, dna_samples)

    # Print results
    print(outcome)

    sys.exit(0)


# Open dna text file and store contents
def read_dna(n):

    with open(n, 'r') as f:
        for line in f:
            dna = line

    return dna


# Open and store info from csv samples
def read_samples(n):
    dict_list = []
    with open(n, 'r') as f:
        reader = csv.DictReader(f)
        for line in reader:
            dict_list.append(line)
    return dict_list


# Strip header of name and keep STR values
def get_str(n):
    str_strip = list(n[0].keys())
    str_strip = str_strip[1:]
    return str_strip


# Keep track of repeating STR's
def look_for_repeats(dna, strs):

    repeat_count = []
    position = 0

    # Go through all STR combinations in CSV
    for i in strs:

        # Create new position in test and set value to zero
        repeat_count.append(0)

        # Loop through dna
        for j in range(len(dna)):

            # Reset count
            str_max_found = 0

            # Find match
            if dna[j:(j + len(i))] == i:

                # Set position
                k = 0

                # Increment by match length and track repetitions
                while dna[(j + k):(j + k + len(i))] == i:
                    str_max_found += 1
                    k += len(i)

                # Swap previous count with larger repetition count
                if str_max_found > repeat_count[position]:
                    repeat_count[position] = str_max_found

        # Move position in list
        position += 1

    return repeat_count


# Find possible suspect
def identify_match(suspect, possibles):

    # Go through people from the csv
    for key in range(len(possibles)):

        # Reset list
        list_test = []

        # Grab persons STR counts
        for value in possibles[key]:

            # Store them in list
            list_test.append(possibles[key][value])

        # Remove name
        list_test = list_test[1:]

        # Convert STR string counts to ints
        for i in range(len(list_test)):
            list_test[i] = int(list_test[i])

        # Compare new list to one in question
        if list_test == suspect:

            # Found match
            return possibles[key]['name']

    # Failure to find match
    return "No match"


if __name__ == "__main__":
    main()
