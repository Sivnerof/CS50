import sys

def main():
    # Get users intentions
    print("To encrypt a message type e, to decrypt type d")
    mode = input("Mode: ").lower()
    if mode != 'e' and mode != 'd':
        sys.exit("Enter valid mode")

    # Get user text file
    file_name = input("Enter name of text file: ")
    if file_name[len(file_name) - 4:] != ".txt":
        sys.exit("File must be a .txt file")

    # Get users message
    user_message = input("Enter message: ").upper()

    

    
    sys.exit(0)


if __name__ == "__main__":
    main()