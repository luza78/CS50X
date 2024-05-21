#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Copies name to char array, loops through candidate names comparing input to candidate names
bool vote(string name)
{
    char n[25];
    strcpy(n, name);
    for (int i = 0; i < candidate_count; i++)
    {
        char c[25];
        strcpy(c, candidates[i].name);
        if (strcmp(n, c) == 0)
        {
            candidates[i].votes++;
            memset(n, '\0', 25);
            return true;
        }
    }
    return false;
}

// Uses bubble sort to sort the candidate array. Prints the highest vote count in array
void print_winner(void)
{
    int i, j;
    candidate temp;

    for (i = 0; i < candidate_count; i++)
    {
        for (j = i + 1; j < candidate_count; j++)
        {
            if (candidates[i].votes < candidates[j].votes)
            {
                temp = candidates[i];
                candidates[i] = candidates[j];
                candidates[j] = temp;
            }
        }
    }
    if (candidates[0].votes > candidates[1].votes)
    {
        printf("%s\n", candidates[0].name);
        return;
    }
    else if ((candidates[0].votes == candidates[1].votes) && (candidates[0].votes == candidates[2].votes))
    {
        printf("%s\n", candidates[0].name);
        printf("%s\n", candidates[1].name);
        printf("%s\n", candidates[2].name);
        return;
    }
    else if (candidates[0].votes == candidates[1].votes)
    {
        printf("%s\n", candidates[0].name);
        printf("%s\n", candidates[1].name);
    }
    return;
}