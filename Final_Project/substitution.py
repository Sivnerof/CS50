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
    user_text = input("Enter text: ").upper()

    # Index to compare
    alpha_index = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

    # Encrypt
    if mode == 'e':
        result_text = encrypted_text(user_text, cipher_key, alpha_index)

    # Decrypt
    if mode == 'd':
        result_text = decrypted_text(user_text, cipher_key, alpha_index)
    
    # Print results for user to a .txt file
    with open("result.txt",'w',encoding = 'utf-8') as f:
        f.write(result_text)
    
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


def encrypted_text(text, key, alpha):
    encrypted_string = ""
    for i in range(len(text)):
        if text[i].isalpha() == True:
            encrypted_string += key[alpha.index(text[i])]
        else:
            encrypted_string += text[i]
    return encrypted_string


def decrypted_text(text, key, alpha):
    decrypted_string = ""
    for i in range(len(text)):
        if text[i].isalpha() == True:
            decrypted_string += alpha[key.index(text[i])]
        else:
            decrypted_string += text[i]
    return decrypted_string


if __name__ == "__main__":
    main()