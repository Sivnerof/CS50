import sys

def main():
    # Get  plain or ciphertext from user
    user_text = input("Enter text: ").upper()

    # Encrypt/Decrypt
    result_text = rot_thirteen(user_text)

    # Print results for user to a .txt file
    with open("result.txt",'w',encoding = 'utf-8') as f:
        f.write(result_text)
    
    sys.exit(0)


def rot_thirteen(text):
    result = ""
    for i in range(len(text)):
        if text[i].isalpha() == True:
            result += chr(((ord(text[i]) - ord('A') + 13) % 26) + ord('A'))
        else:
            result += text[i]
    return result


if __name__ == "__main__":
    main()