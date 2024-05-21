#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
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

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int score = 0;
    string output = word;
    int wordlength = strlen(word);
    for (int i = 0; i < wordlength; i++)
    {
        char c = toupper(word[i]);
        switch (c)
        {
            case 'A':
                score += POINTS[0];
                break;

            case 'B':
                score += POINTS[1];
                break;

            case 'C':
                score += POINTS[2];
                break;

            case 'D':
                score += POINTS[3];
                break;

            case 'E':
                score += POINTS[4];
                break;

            case 'F':
                score += POINTS[5];
                break;

            case 'G':
                score += POINTS[6];
                break;

            case 'H':
                score += POINTS[7];
                break;

            case 'I':
                score += POINTS[8];
                break;

            case 'J':
                score += POINTS[9];
                break;

            case 'K':
                score += POINTS[10];
                break;

            case 'L':
                score += POINTS[11];
                break;

            case 'M':
                score += POINTS[12];
                break;

            case 'N':
                score += POINTS[13];
                break;

            case 'O':
                score += POINTS[14];
                break;

            case 'P':
                score += POINTS[15];
                break;

            case 'Q':
                score += POINTS[16];
                break;

            case 'R':
                score += POINTS[17];
                break;

            case 'S':
                score += POINTS[18];
                break;

            case 'T':
                score += POINTS[19];
                break;

            case 'U':
                score += POINTS[20];
                break;

            case 'V':
                score += POINTS[21];
                break;

            case 'W':
                score += POINTS[22];
                break;

            case 'X':
                score += POINTS[23];
                break;

            case 'Y':
                score += POINTS[24];
                break;

            case 'Z':
                score += POINTS[25];
                break;

            default:
                score += 0;
                break;
        }
    }
    return score;
}
