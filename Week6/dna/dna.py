import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Wrong Usage")
        exit()

    # TODO: Read database file into a variable
    database = []
    with open(sys.argv[1]) as databaseFile:
        reader = csv.DictReader(databaseFile)
        for row in reader:
            database.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as sequenceFile:
        sequence = sequenceFile.read()

    # TODO: Find longest match of each STR in DNA sequence
    # create a list of the subsequences, skipping the name key
    subsequences = list(database[0].keys())[1:]
    # create a dict that will store subsequence and longest_match value
    matches = {}
    # go over each subsequence
    for subsequence in subsequences:
        # add new entry for subseqeunce to dict while saving the longest_match value
        matches[subsequence] = longest_match(sequence, subsequence)

    # TODO: Check database for matching profiles
    for person in database:
        match = 0
        for subsequence in subsequences:
            # go over all persons and compare them to the matches
            if int(person[subsequence]) == matches[subsequence]:
                match += 1

            # if all subsequences mathed, we got a winner!
            if match == len(subsequences):
                print(person["name"])
                return

    print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
