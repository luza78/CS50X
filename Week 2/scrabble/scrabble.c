#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Gets input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Scores both words by passing them through the compute_score function
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Prints winner by comparing the return values of score1 and score2
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    if (score1 == score2)
    {
        printf("Tie!\n");
    }

}
// compute_score function
int compute_score(string word)
{
    // Initializing our return value int score, and getting string length from the input

    int score = 0;
    int wordlength = strlen(word);

    // Iterates through each letter of the input string. Changes input char to upper for comparison

    for (int i = 0; i < wordlength; i++)
    {
        char c = toupper(word[i]);
        int n = 0;
        char y = 'A';

        // If the input 'c' doesn't match y, it will loop through alphabet to compare until it finds a match

        while (c != y)
        {
            for (int j = 0; c != y && j < 25; j++)
            {
                n++;
                y++;
            }
        }

        // When a match is found, it increments the score by the points and ends the loop

        if (c == y)
        {
            score += POINTS[n];
            int j = 25;
            n = 0;
        }
    }

    return score;
}
