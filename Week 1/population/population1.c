#include <cs50.h>
#include <stdio.h>


    // s is start pop
    // e is end pop

    // g is growth - amount of llamas born
    // f is growth minus death / year
    // y is years

int main(void)
{
    // TODO: Prompt for start size
    int s;
    do
        {s = get_int("start pop, must bepositive int: ");
        }
    while (s < 9);

    // TODO: Prompt for end size
    int e;
    do
        {e = get_int("End pop, must be positive int: ");
        }
    while (e <= s);

    // TODO: Calculate number of years until we reach threshold
    // g is growth / year
    // f is growth minus death / in a year
    // y is years to reach e
    int y = (0);
    int g = (s / 3 + s);
    

    do
{
        int f = (g - (s / 4));
        y ++;
       return y;
}
    while (f <= e);

    // TODO: Print number of years

    printf("%i\n", y);


}