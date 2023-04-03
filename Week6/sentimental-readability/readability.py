# TODO

import re
from cs50 import get_string


def main():

    num_chars = 0
    num_words = 1
    num_sentences = 0

    # get string as user input
    text = get_string("Text: ")

    for i in range(len(text)):
        if text[i].isalpha():
            num_chars += 1
        elif text[i].isspace():
            num_words += 1
        elif text[i] == '.' or text[i] == '!' or text[i] == '?':
            num_sentences += 1

    print("Hello")
    # calculate averages per 100 words
    averageLetters = num_chars * 100.0 / num_words
    averageSentences = num_sentences * 100.0 / num_words

    # calculate index
    index = round(0.0588 * averageLetters - 0.296 * averageSentences - 15.8)

    # print grade "Grade 16+" & "Before Grade 1".
    if index > 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")


main()