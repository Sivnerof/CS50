from cs50 import get_int

# Handles invalid inputs and repromts user
while True:
    pyramid_size = get_int("Height: ")
    if pyramid_size <= 8 and pyramid_size >= 1:
        break

# Increment through pyramid printing out decreasing number of spaces
# with increasing number of hashes
for i in range(1, pyramid_size + 1):
    print(" " * (pyramid_size - i) + "#" * i)