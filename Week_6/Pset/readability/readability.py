"""
    Re-implementation of readability.c in the python language.
    A program that calculates the reading level of a users supllied text,
    according to grade level using the Coleman-Liau formula.
"""

from cs50 import get_string


def main():

    # Get text to be graded
    user_text = get_string("Text: ")

    # Send to formula
    grade = grade_level(user_text)

    # Print grade level
    print_grade(grade)

    return


def grade_level(n):

    # Letter, word, sentence count
    letter, word, sentence = 0, 1, 0

    # Loop through text
    for i in n:

        # Increment letters
        if i.isalpha():
            letter += 1

        # Count spaces as start of new words
        if i.isspace():
            word += 1

        # Use these 3 symbols as end of sentence identifiers
        if i in ['?', '.', '!']:
            sentence += 1

    # Apply Coleman-Liau formula
    L = (letter / word) * 100
    S = (sentence / word) * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    return index


def print_grade(n):

    # Handle Kindergarten and below
    if n < 1:
        print("Before Grade 1")

    # Handle reading levels above 16
    elif n > 16:
        print("Grade 16+")

    # Print grade
    else:
        print(f"Grade {n}")

    return


main()
