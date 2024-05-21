#include <cs50.h>
#include <stdio.h>

int year(int start, int end);

int main(void)
{
    // Prompt for start size
    int startpop;
    do
    {
        startpop = get_int("start pop, must be positive int: ");
    }
    while (startpop < 9);


    // Prompt for end size

    int endpop;
    do
    {
        endpop = get_int("end pop, must be positive int higher than start pop: ");
    }
    while (endpop < startpop);


    // Calling year function
    year(startpop, endpop);



    // Prints number of years
    printf("Years: %i\n", year(startpop, endpop));
}












// Year counting function
int year(int start, int end)
{
    int y = 0;
    while (start < end)
    {
        y++;
        start = (start / 3) + start - (start / 4);
        if (start >= end)
        {
            return y;
        }
    }



    return 0;
}