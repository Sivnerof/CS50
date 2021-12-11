import sys
import random
import os

def main():
    # Get users intentions
    print("To encrypt a message type e, to decrypt type d")
    mode = input("Mode: ").lower()
    if mode != 'e' and mode != 'd':
        sys.exit("Enter valid mode")

    # Get user text file
    file_name = input("Enter name of text file: ")
    if os.path.isfile(file_name) == False:
        sys.exit("File name does not exist")
    elif file_name[len(file_name) - 4:] != ".txt":
        sys.exit("File must be a .txt file")

    # Get users message
    if mode == 'e':
        user_message = input("Enter message: ").upper()
        for i in range(len(user_message)):
            if user_message[i].isalpha() == False and user_message[i].isspace() == False:
                sys.exit("Message must only be alphabetical letters or spaces, no symbols or numbers.")

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
    file_strings = []
    with open(file) as f:
        for lines in f:
            if lines.isspace() == False:
                file_strings.append(lines.upper())

    for i in range(len(message)):
        rand_index = random.randrange(len(file_strings))
        if message[i] in file_strings[rand_index]:
            # Randomize spaces so they stop coming out at zero
            # Also remember to strip whitespace on both sides
            word = 0
            if message[i].isspace() == False:
                for j in file_strings[rand_index]:
                    if j == " ":
                        word += 1
                    elif j == message[i]:
                        break
            print(f"{message[i]} was found at position: {file_strings[rand_index].index(message[i])} on line {rand_index} it is word number {word}")
        else:
            for k in range(len(file_strings)):
                if message[i] in file_strings[k]:
                    word = 0
                    for l in file_strings[k]:
                        if l == " ":
                            word += 1
                        elif l == message[i]:
                            break
                    print(f"{message[i]} was found at position {file_strings[k].index(message[i])} on line {k} it is word number {word}")
                    break


if __name__ == "__main__":
    main()