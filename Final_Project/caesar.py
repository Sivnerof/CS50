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
    if user_text.isalpha() == False and mode == 'e':
        print("Text must be alphabetical characters only")
        sys.exit(1)
    
    # Get ascii values of user provided text
    user_text = ascii_values(user_text)
    
    # Encrypt
    if mode == 'e':
        result_text = encrypt_text(user_text, cipher_key)

    # Decrypt
    if mode == 'd':
        result_text = decrypt_text(user_text, cipher_key)

    # Print results for user to a .txt file
    with open("result.txt",'w',encoding = 'utf-8') as f:
        f.write(result_text)

    sys.exit(0)


def ascii_values(text):
    ascii_list = []
    for letters in range(len(text)):
        ascii_list.append(ord(text[letters]))
    return ascii_list


def encrypt_text(text, key):
    encrypted_string = ""
    for i in range(len(text)):
        encrypted_string += chr((((text[i] + key) - ord('a')) % 26) + ord('a')) 
    return encrypted_string


def decrypt_text(text, key):
    decrypted_string = ""
    for i in range(len(text)):
        decrypted_string += chr((((text[i] - key) - ord('a')) % 26) + ord('a'))
    return decrypted_string


if __name__ == "__main__":
    main()