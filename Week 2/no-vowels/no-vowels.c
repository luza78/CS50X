// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string replace(string inputword);

int main(int argc, string argv[])
{
// checks cmd line args
    if (argv[1] == 0)
    {
        printf("Error, add argument\n");
        return 1;
    }
    if (argv[2] != 0)
    {
        printf("Error, too many arguments\n");
        return 1;
    }
// calling replace
    string inputword = argv[1];
    string word = replace(inputword);

// prints new word
    printf("%s \n", word);

}



//replace vowels function
string replace(string inputword)
{
    string output = inputword;
    int wordlength = strlen(inputword);
    int i;

    for (i = 0; i < wordlength; i++)
    {
        char letter = inputword[i];
        switch (letter)
        {
            case 'A':
                output[i] = '6';
                break;

            case 'a':
                output[i] = '6';
                break;

            case 'E':
                output[i] = '3';
                break;

            case 'e':
                output[i] = '3';
                break;

            case 'I':
                output[i] = '1';
                break;

            case 'i':
                output[i] = '1';
                break;

            case 'O':
                output[i] = '0';
                break;

            case 'o':
                output[i] = '0';
                break;

            default:
                output[i] = letter;
                break;
        }
    }
    return output;
}