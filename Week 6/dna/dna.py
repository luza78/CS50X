import csv
import sys


def main():

    # Check for correct command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py FILENAME.CSV FILENAME.TXT")

    # Populates a list with dicts from csv
    names = []
    with open(sys.argv[1]) as databasefile:
        file_reader = csv.DictReader(databasefile)
        for person in file_reader:
            names.append(person)

    # Checks what STRs are present in CSV returning True or False
    str_in_csv(names)

    # Reads DNA sequence file into a variable 'dna'
    with open(sys.argv[2], 'r') as file:
        dna = file.read()

    # Finds longest match of each STR in DNA sequence
    AGATC = longest_match(dna, "AGATC")
    TTTTTTCT = longest_match(dna, "TTTTTTCT")
    AATG = longest_match(dna, "AATG")
    TCTAG = longest_match(dna, "TCTAG")
    GATA = longest_match(dna, "GATA")
    TATC = longest_match(dna, "TATC")
    GAAA = longest_match(dna, "GAAA")
    TCTG = longest_match(dna, "TCTG")

    # Removes people that do not match from the list of dicts
    check_for_match(names, AGATC, TTTTTTCT, AATG, TCTAG, GATA, TATC, GAAA, TCTG)

    # Iterates through all dicts in names{}, if empty = "No match"
    # Else it will iterate through the dict, if it finds one that's not empty it will print the name
    # It also checks that the 'name' field is not empty, avoiding a potential key-error
    if all(not d for d in names):
        print("No match")
    else:
        for person in names:
            if len(person) > 0 and 'name' in person:
                print(person['name'])


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


def str_in_csv(names):
    global AGATC_in_data, TTTTTTCT_in_data, AATG_in_data, TCTAG_in_data, GATA_in_data, TATC_in_data, GAAA_in_data, TCTG_in_data
    AGATC_in_data = False
    TTTTTTCT_in_data = False
    AATG_in_data = False
    TCTAG_in_data = False
    GATA_in_data = False
    TATC_in_data = False
    GAAA_in_data = False
    TCTG_in_data = False

    for i in range(0, 1, 1):
        for word in names[0]:
            if word == "AGATC":
                AGATC_in_data = True
            if word == "TTTTTTCT":
                TTTTTTCT_in_data = True
            if word == "AATG":
                AATG_in_data = True
            if word == "TCTAG":
                TCTAG_in_data = True
            if word == "GATA":
                GATA_in_data = True
            if word == "TATC":
                TATC_in_data = True
            if word == "GAAA":
                GAAA_in_data = True
            if word == "TCTG":
                TCTG_in_data = True
    return

    # Checks if genome is in input sequence, then compare sequence to the input database
    # If a match is not found, they will be removed from the dict, and we continue iterating over each genome
    # Leaving us with only the matching members in the list of dicts


def check_for_match(names, AGATC, TTTTTTCT, AATG, TCTAG, GATA, TATC, GAAA, TCTG):
    if AGATC_in_data == True:
        for person in range(0, len(names), 1):
            if names[person] != False and names[person]['AGATC'] != str(AGATC):
                names[person].clear()

    if TTTTTTCT_in_data == True:
        for person in range(0, len(names), 1):
            if len(names[person]) > 0:
                if names[person]['TTTTTTCT'] != str(TTTTTTCT):
                    names[person].clear()
            else:
                continue

    if AATG_in_data == True:
        for person in range(0, len(names), 1):
            if len(names[person]) > 0:
                if names[person]['AATG'] != str(AATG):
                    names[person].clear()
            else:
                continue

    if TCTAG_in_data == True:
        for person in range(0, len(names), 1):
            if len(names[person]) > 0:
                if names[person]['TCTAG'] != str(TCTAG):
                    names[person].clear()
            else:
                continue

    if GATA_in_data == True:
        for person in range(0, len(names), 1):
            if len(names[person]) > 0:
                if names[person]['GATA'] != str(GATA):
                    names[person].clear()
            else:
                continue

    if TATC_in_data == True:
        for person in range(0, len(names), 1):
            if len(names[person]) > 0:
                if names[person]['TATC'] != str(TATC):
                    names[person].clear()
            else:
                continue

    if GAAA_in_data == True:
        for person in range(0, len(names), 1):
            if len(names[person]) > 0:
                if names[person]['GAAA'] != str(GAAA):
                    names[person].clear()
            else:
                continue

    if TCTG_in_data == True:
        for person in range(0, len(names), 1):
            if len(names[person]) > 0:
                if names[person]['TCTG'] != str(TCTG):
                    names[person].clear()
            else:
                continue


main()
