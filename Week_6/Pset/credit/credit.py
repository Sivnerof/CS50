# Implementation of credit.c in python

"""
DISCLAIMER: This program is in no way intended to be pythonic.
            It is a direct translation of a C program I made,
            when I first started learning the language.
"""

from cs50 import get_int

# Handle negative inputs
while True:
    card_number = get_int("Number: ")
    if card_number > 0:
        break

# Declare variables
card_number_copy, card_length, sum_of_non_multiplied, sum_bit, carry_bit, sum_of_multiplied, total_sum_validated, is_amex, is_mastercard, is_visa = 0, 0, 0, 0, 0, 0, 0, False, False, False

while card_number > 0:

    # Start card length counter up here to use as if else modulo / counter for card length
    card_length += 1

    # Take last digit of card number, example 4 in 4003600000000014
    card_number_copy = card_number % 10

    # Every other starting from right most
    if card_length % 2 == 0:

        # Multiply by two
        card_number_copy *= 2

        # Handle carry bit if sum is overflowed
        # Storing sum in one variable and carry in another adding them and bringing them back together
        if card_number_copy > 9:

            # Right most bit used then knocked off
            sum_bit = card_number_copy % 10
            card_number_copy //= 10

            # Now repeated with the left bit
            carry_bit = card_number_copy % 10
            card_number_copy = sum_bit + carry_bit

        # Result is stored in the sum of all others to be multiplied
        sum_of_multiplied += card_number_copy

    else:
        # Here we take the ones we never multiplied and just add them together
        sum_of_non_multiplied += card_number_copy % 10

    # Here we set some booleans to true if the first two digits seem to belong to a certain issuer

    # Mastecard
    if ((card_number % 100 == 51 or card_number % 100 == 52 or card_number % 100 == 53 or card_number % 100 == 54 or card_number % 100 == 55) and card_number < 99):
        is_mastercard = True

    # Amex
    elif ((card_number % 100 == 34 or card_number % 100 == 37) and card_number < 99):
        is_amex = True

    # Visa, here we use mod and card number length 10 instead because Visa is recognized by the single digit 4
    elif ((card_number % 10 == 4) and card_number < 10):
        is_visa = True

    # Knock off right most digit and repeat the process
    card_number = card_number // 10

# Now take everything, add it together and modulo again to check that last digit is zero
total_sum_validated = ((sum_of_non_multiplied + sum_of_multiplied) % 10)

# Final verification process
if total_sum_validated == 0:
    if is_mastercard == True and card_length == 16:
        print("MASTERCARD")

    elif is_amex == True and card_length == 15:
        print("AMEX")

    elif is_visa == True and (card_length == 13 or card_length == 16):
        print("VISA")

    else:
        print("INVALID")

else:
    print("INVALID")
