import sys

def main():
    # Get user intentions
    print("To encrypt a message type e, to decrypt type d")
    mode = input("Mode: ").lower()
    if mode != 'e' and mode != 'd':
        print("Enter valid mode")
        sys.exit(1)

    # Grab cipher key
    cipher_key = input("Enter encryption key: ")

    # Check if key is 26 alphabetical non-repeating characters
    if valid_cipherkey(cipher_key) == False:
        sys.exit(1)

    # Grab users plain or cipher text
    user_text = input("Enter text: ").lower()


    # Encrypt
    # Decrypt
    
    sys.exit(0)


def valid_cipherkey(key):
    if key.isalpha == False or len(key) != 26:
        print("Key must be 26 alphabetical characters only")
        return False

    valid_cipherkey = []
    for letters in range(len(key)):
        if key[letters] not in valid_cipherkey:
            valid_cipherkey.append(key[letters])
        else:
            print("Cipher key has repeating characters")
            return False

    return True

if __name__ == "__main__":
    main()