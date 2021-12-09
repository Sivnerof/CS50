import sys
import random

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
    
    # Turn string into list
    user_message = string_convert(user_message)

    # Grab positions of letters in file
    letter_coords(user_message, file_name)

    sys.exit(0)


def string_convert(message):
    new_message = []
    for i in range(len(message)):
        new_message.append(message[i])
    return new_message


def letter_coords(message, file):
    """
    test = []
    line_position = 0
    word_position = 0
    with open(file) as f:
        for lines in f:
            test.append(lines.upper())

    for i in range(len(test)):
        for j in test[i]:
            if j == ' ':
                word_position += 1
        line_position += 1
    print(line_position, word_position)
    print(test[0].index('C'))

    testing = random.randrange(len(test))
    print(testing)
    print(testing)
    print(test[testing])
    """
    pass



    


if __name__ == "__main__":
    main()