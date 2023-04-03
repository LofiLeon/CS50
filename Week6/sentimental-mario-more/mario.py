# TODO

from sys import argv

# get height
while True:
    try:
        height = int(input("Height: "))
        if (height >= 1) and (height <= 8):
            break
    except:
        print("", end="")


# print blocks
for i in range(height):
    whiteSpaces = height - i - 1
    blocks = height - whiteSpaces
    j = 0

    # first whitespaces
    while j < whiteSpaces:
        print(" ", end="")
        j += 1

    j = 0

    # first batch
    while j < blocks:
        print("#", end="")
        j += 1

    j = 0

    # spaces
    print(" ", end="")
    print(" ", end="")

    # second batch
    while j < blocks:
        print("#", end="")
        j += 1

    print()
