# Implementation of cash.c in python
from cs50 import get_float

# Handle negative values
while True:
    change_owed = get_float("Change owed: ")
    if change_owed > 0:
        break

# Convert to pennies
change_in_pennies = round(change_owed * 100)

# Coin count
coin_total = 0

# Subtract Quarters and increment coin count
while change_in_pennies >= 25:
    change_in_pennies -= 25
    coin_total += 1

# Same but with Dimes
while change_in_pennies >= 10:
    change_in_pennies -= 10
    coin_total += 1

# Nickles
while change_in_pennies >= 5:
    change_in_pennies -= 5
    coin_total += 1

# Pennies
while change_in_pennies >= 1:
    change_in_pennies -= 1
    coin_total += 1

# Minimum amount of coins needed to give back
print(coin_total)