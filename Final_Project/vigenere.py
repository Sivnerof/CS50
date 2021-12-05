import sys


def main():

    # Get user intentions
    print("To encrypt a message type e, to decrypt type d")
    mode = input("Mode: ").lower()
    if mode != 'e' and mode != 'd':
        print("Enter valid mode")
        sys.exit(1)

    # Get key from user
    cipher_key = input("Enter encryption key: ").lower().replace(" ", "")
    if cipher_key.isalpha() == False:
        print("Key must be alphabetical characters only")
        sys.exit(1)

    # Get  plain or ciphertext from user
    user_text = input("Enter text: ").lower().replace(" ", "")
    if user_text.isalpha() == False and mode == 'e':
        print("Text must be alphabetical characters only")
        sys.exit(1)

    # Create cipherkey of same length as user text
    cipher_key = adjusted_length(cipher_key, len(user_text))

    # Get ASCII values of usertext
    user_text = ascii_values(user_text)

    # Get ASCII values of encryption key
    cipher_key = ascii_values(cipher_key)

    if mode == 'e':
        # Encrypt
        result_text = encrypt_text(user_text, cipher_key)

    elif mode == 'd':
        # Decrypt
        result_text = decrypt_text(user_text, cipher_key)

    # Print results for user to a .txt file
    with open("result.txt",'w',encoding = 'utf-8') as f:
        f.write(result_text)

    sys.exit(0)


def adjusted_length(key, text_length):
    adjusted_cipher = ""
    for letters in range(text_length):
        adjusted_cipher += key[letters % len(key)]
    return adjusted_cipher


def ascii_values(reg_string):
    converted_values = []
    for letters in reg_string:
        converted_values.append(ord(letters) - ord("a"))
    return converted_values


def encrypt_text(text_values, key_values):
    encrypted_string = ""
    for number in range(len(text_values)):
        encrypted_string += chr(((text_values[number] + key_values[number]) % 26) + ord("a"))
    return encrypted_string


def decrypt_text(text_values, key_values):
    decrypted_string = ""
    for number in range(len(text_values)):
        decrypted_string += chr(((text_values[number] - key_values[number]) % 26) + ord("a"))
    return decrypted_string


if __name__ == "__main__":
    main()