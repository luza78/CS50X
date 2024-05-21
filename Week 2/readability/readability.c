#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string);
int count_words(string);
int count_sentences(string);
string index(int letters, int words, int sentences, string grades[]);


int main(void)
{
    string grades[] = {"Before Grade 1", "Grade 1", "Grade 2", "Grade 3", "Grade 4", "Grade 5", "Grade 6", "Grade 7", "Grade 8", "Grade 9", "Grade 10", "Grade 11", "Grade 12", "Grade 13", "Grade 14", "Grade 15", "Grade 16+"};
    string word = get_string("Text: ");
    int letters = count_letters(word);
    int words = count_words(word);
    int sentences = count_sentences(word);
    string result = index(letters, words, sentences, grades);cd

    // Prints grade
    printf("%s\n", result);
}









// Counts alphabetic letters
int count_letters(string word)
{
    int letters = 0;
    int inputlength = strlen(word);

    for (int i = 0; i < inputlength; i++)
    {
        char c = word[i];
        if (isalpha(c))
        {
            letters++;
        }
    }
    return letters;
}

// counts words based on spaces + 1
int count_words(string word)
{
    int words = 0;
    int inputlength = strlen(word);

    for (int i = 0; i < inputlength; i++)
    {
        char s = word[i];
        if (isspace(s))
        {
            words++;
        }
    }
    return words += 1;
}

// Counts sentences
int count_sentences(string word)
{
    int sentences = 0;
    int inputlength = strlen(word);

    for (int i = 0; i < inputlength; i++)
    {
        char k = word[i];
        if ((k == '.') || (k == '?') || (k == '!'))
        {
            sentences++;
        }
    }
    return sentences;
}


// Grade coleman formula index that returns the grade
string index(int letters, int words, int sentences, string grades[])
{
    string output = "aaaaaaaaaaaaaa";
    float i = 0.00;
    float l = (((float) letters / (float) words) * 100);
    float s = (((float) sentences / (float) words) * 100);
    i = 0.0588 * l - 0.296 * s - 15.8;
    i = round(i);

    if (i < 1)
    {
        output = grades[0];
    }
    if (i > 16)
    {
        output = grades[16];
    }

    for (int j = 1; j < 17; j++)
    {
        if (i == j)
        {
            output = grades[j];
        }
    }
    return output;
}