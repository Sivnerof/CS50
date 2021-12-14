import sys

def main():
    # Get user intentions
    print("To encrypt a message type e, to decrypt type d")
    mode = input("Mode: ").lower()
    if mode != 'e' and mode != 'd':
        sys.exit("Enter valid mode")

    # Grab cipher key
    try:
        cipher_key = int(input("Enter encryption key: "))
        if cipher_key < 0:
            sys.exit(1)
    except:
        sys.exit("Key must be a positive integer")
    
    # Get  plain or ciphertext from user
    user_text = input("Enter text: ").lower()
    
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
        if text[letters].isalpha():    
            ascii_list.append(ord(text[letters]))
        else:
            ascii_list.append(text[letters])
    return ascii_list


def encrypt_text(text, key):
    encrypted_string = ""
    for i in range(len(text)):
        if type(text[i]) == int:
            encrypted_string += chr((((text[i] + key) - ord('a')) % 26) + ord('a')) 
        else:
            encrypted_string += str(text[i])
    return encrypted_string


def decrypt_text(text, key):
    decrypted_string = ""
    for i in range(len(text)):
        if type(text[i]) == int:
            decrypted_string += chr((((text[i] - key) - ord('a')) % 26) + ord('a'))
        else:
            decrypted_string += str(text[i])
    return decrypted_string


if __name__ == "__main__":
    main()