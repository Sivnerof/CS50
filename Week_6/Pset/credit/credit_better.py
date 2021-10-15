"""
    Luhn's algorithm used in python.
    Explained by a CS50 teaching fellow in Week 6 super section.
    https://cs50.harvard.edu/college/2021/fall/supersections/6/

"""

# Card length globals
MIN_LENGTH = 13
MAX_LENGTH = 16
INVALID_LENGTH = 14


def main():

    # Grab card number from user
    num = input("Card Number: ")

    # Check for invalid input
    if not num.isdigit():
        print(f"Sorry, {num}, is not a card number. Try again.")


    # Check length
    if not check_length(num):
        print("Invalid card length, try again...")

    # Run algorith
    if not check_luhns(num):
        print("FAILED TO PASS CHECKSUM")

    # Print card
    print_card(num)

    return


def check_length(n):

    length = len(n)

    # Check for invalid length of card
    if length >= MIN_LENGTH and length <= MAX_LENGTH and length != INVALID_LENGTH:
        return True

    else:
        return False


def check_luhns(n):

    checksum = 0

    # Loop through card
    for i in range(len(n)):

        # Grab individual digits
        digit = n[len(n) - 1 - i]

        # If digit is evenly positioned
        if i % 2 == 0:

            # Sum as normal
            checksum += int(digit)

        # Every other digit
        else:

            # Multiply by two, and sum.
            # If digit overflows, mod and divide.
            checksum +=  ((int(digit) * 2) % 10 + (int(digit) * 2 // 10))

    # Mod last digit
    if checksum % 10 == 0:

        # Passes
        return True

    # Fake
    else:
        return False

def print_card(n):

    # Grab first two digits of card
    first_num = int(n[0])
    second_num = int(n[1])

    # American Express Check
    if first_num == 3 and (second_num == 4 or second_num == 7):
        print("AMEX")

    # Mastercard check
    elif first_num == 5 and (second_num > 0 and second_num < 6):
        print("MASTERCARD")

    # Visa check
    elif first_num == 4:
        print("VISA")

    # None of the above
    else:
        print("INVALID")

    return


main()