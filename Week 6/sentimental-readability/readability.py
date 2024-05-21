import cs50


def main():

    # A list of grades
    grades = ["Before Grade 1", "Grade 1", "Grade 2", "Grade 3", "Grade 4", "Grade 5", "Grade 6", "Grade 7",
              "Grade 8", "Grade 9", "Grade 10", "Grade 11", "Grade 12", "Grade 13", "Grade 14", "Grade 15", "Grade 16+"]

    text = cs50.get_string("Enter Text: ")

    # Pass the input text into a function, that returns multiple values
    letters, words, sentences = count_all(text)

    # Pass the data into the function, running the index formula, thereby outputting a grade from our list
    result = index_formula(letters, words, sentences, grades)

    print(result)

# Loops through each character, checking if letter, word, or sentence. Word starts at 1, because at the end of a sentence there is no space.


def count_all(text):
    letters = 0
    words = 1
    sentences = 0

    for c in text:
        if c.isalpha():
            letters += 1
            continue
        if c.isspace():
            words += 1
            continue
        if c == ".":
            sentences += 1
            continue
        if c == "!":
            sentences += 1
            continue
        if c == "?":
            sentences += 1

    return letters, words, sentences

# Based on the formula results, loops through our list until it finds a match


def index_formula(letters, words, sentences, grades):
    average_letters = (letters / words) * 100
    average_sentences = (sentences / words) * 100

    result = 0.0588 * average_letters - 0.296 * average_sentences - 15.8
    result = round(result)

    if result < 1:
        return grades[0]
    elif result > 16:
        return grades[16]

    grading = 2

    for i in range(2, 17, 1):
        if result == grading:
            return grades[grading]
        grading += 1


main()
