import sys

def main():
    # Get user intentions
    print("To encrypt a message type e, to decrypt type d")
    mode = input("Mode: ").lower()
    if mode != 'e' and mode != 'd':
        print("Enter valid mode")
        sys.exit(1)

    # Grab cipher key
    try:
        cipher_key = int(input("Enter encryption key: "))
        if cipher_key < 0:
            sys.exit(1)
    except:
        print("Key must be a positive integer")
        sys.exit(1)
    
    # Get  plain or ciphertext from user
    user_text = input("Enter text: ").lower().replace(" ", "")
    
    # encrypt
    # decrypt
    # print
    sys.exit(0)


if __name__ == "__main__":
    main()