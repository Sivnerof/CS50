import sys

def main():
    # Get  plain or ciphertext from user
    user_text = input("Enter text: ")

    # Encrypt/Decrypt
    result_text = rot_47(user_text)

    # Print results for user to a .txt file
    with open("result.txt",'w',encoding = 'utf-8') as f:
        f.write(result_text)
    
    sys.exit(0)


def rot_47(text):
    result = ""
    for i in range(len(text)):
        if ord(text[i]) >= ord('!') and ord(text[i]) <= ord('~'):
            result += chr(((ord(text[i]) + 14) % 94) + ord('!'))
        else:
            result += text[i]
    return result


if __name__ == "__main__":
    main()