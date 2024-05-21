#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool validate_userkey(string userkey);
string substitute(string userkey, string plaintext, char lowercase[], char uppercase[]);

int main(int argc, string argv[])
{
    char lowercase[25];
    char uppercase[25];
    // checks for valid number of cmd line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    string userkey = argv[1];


    //checks for valid string input
    if (validate_userkey(userkey) == false)
    {
        printf("Error invalid key length. Must be 26 non repeated characters\n");
        return 1;
    }


    string plaintext = get_string("plaintext: ");

    // makes upper and lowercase copy of cipher
    for (int j = 0; j < strlen(userkey); j++)
    {
        lowercase[j] = tolower(userkey[j]);
        uppercase[j] = toupper(userkey[j]);
    }

    string ciphertext = substitute(userkey, plaintext, lowercase, uppercase);

    printf("ciphertext: %s\n", ciphertext);
}







// Checks if userinput is valid
bool validate_userkey(string userkey)
{
    if (strlen(userkey) == 26)
    {
        for (int i = 0; i < strlen(userkey); i++)
        {
            char c = userkey[i];
            if (isalpha(c) == false)
            {
                return false;
            }
            for (int j = i + 1; j < 26; j++)
                if (c == userkey[j])
                {
                    return false;
                }
        }
    }
    else
    {
        return false;
    }
    return true;
}

// Substitutes the plain text, with either upper or lowercase copies of the cipherkey
string substitute(string userkey, string plaintext, char lowercase[], char uppercase[])
{
    string word = plaintext;

    for (int i = 0; i < strlen(plaintext); i++)
    {
        char c = plaintext[i];
        switch (c)
        {
            case 'a':
                word[i] = lowercase[0];
                break;

            case 'A':
                word[i] = uppercase[0];
                break;

            case 'b':
                word[i] = lowercase[1];
                break;

            case 'B':
                word[i] = uppercase[1];
                break;

            case 'c':
                word[i] = lowercase[2];;
                break;

            case 'C':
                word[i] = uppercase[2];
                break;

            case 'd':
                word[i] = lowercase[3];
                break;

            case 'D':
                word[i] = uppercase[3];
                break;

            case 'e':
                word[i] = lowercase[4];
                break;

            case 'E':
                word[i] = uppercase[4];
                break;

            case 'f':
                word[i] = lowercase[5];
                break;

            case 'F':
                word[i] = uppercase[5];
                break;

            case 'g':
                word[i] = lowercase[6];
                break;

            case 'G':
                word[i] = uppercase[6];
                break;

            case 'h':
                word[i] = lowercase[7];
                break;

            case 'H':
                word[i] = uppercase[7];
                break;

            case 'i':
                word[i] = lowercase[8];
                break;

            case 'I':
                word[i] = uppercase[8];
                break;

            case 'j':
                word[i] = lowercase[9];
                break;

            case 'J':
                word[i] = uppercase[9];
                break;

            case 'k':
                word[i] = lowercase[10];
                break;

            case 'K':
                word[i] = uppercase[10];
                break;

            case 'l':
                word[i] = lowercase[11];
                break;

            case 'L':
                word[i] = uppercase[11];
                break;

            case 'm':
                word[i] = lowercase[12];
                break;

            case 'M':
                word[i] = uppercase[12];
                break;

            case 'n':
                word[i] = lowercase[13];
                break;

            case 'N':
                word[i] = uppercase[13];
                break;

            case 'o':
                word[i] = lowercase[14];
                break;

            case 'O':
                word[i] = uppercase[14];
                break;

            case 'p':
                word[i] = lowercase[15];
                break;

            case 'P':
                word[i] = uppercase[15];
                break;

            case 'q':
                word[i] = lowercase[16];
                break;

            case 'Q':
                word[i] = uppercase[16];
                break;

            case 'r':
                word[i] = lowercase[17];
                break;

            case 'R':
                word[i] = uppercase[17];
                break;

            case 's':
                word[i] = lowercase[18];
                break;

            case 'S':
                word[i] = uppercase[18];
                break;

            case 't':
                word[i] = lowercase[19];
                break;

            case 'T':
                word[i] = uppercase[19];
                break;

            case 'u':
                word[i] = lowercase[20];
                break;

            case 'U':
                word[i] = uppercase[20];
                break;

            case 'v':
                word[i] = lowercase[21];
                break;

            case 'V':
                word[i] = uppercase[21];
                break;

            case 'w':
                word[i] = lowercase[22];
                break;

            case 'W':
                word[i] = uppercase[22];
                break;

            case 'x':
                word[i] = lowercase[23];
                break;

            case 'X':
                word[i] = uppercase[23];
                break;

            case 'y':
                word[i] = lowercase[24];
                break;

            case 'Y':
                word[i] = uppercase[24];
                break;

            case 'z':
                word[i] = lowercase[25];
                break;

            case 'Z':
                word[i] = uppercase[25];
                break;

            default:
                word[i] = word[i];
                break;
        }
    }
    return word;
}