import sys


def main():

    # Get key from user 
    cipher_key = input("Enter encryption key: ").lower().replace(" ", "")
    if cipher_key.isalpha() == False:
        print("Key must be alphabetical characters only")
        sys.exit(1)

    # Get  plaintext from user
    plain_text = input("Enter plaintext: ").lower().replace(" ", "")

    # Create cipherkey of same length as plaintext
    cipher_key = adjusted_length(cipher_key, len(plain_text))

    sys.exit(0)


def adjusted_length(key, text_length):
    adjusted_cipher = ""
    for letters in range(text_length):
        adjusted_cipher += key[letters % len(key)]
    return adjusted_cipher

if __name__ == "__main__":
    main()