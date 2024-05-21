#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    // TODO
    int primenumbers = number % 2; // && number > 2;
         if (primenumbers == true)
    // do (primenumbers + 1 !≡ (primenumbers %) + 1);
            return primenumbers;
    else
{

    return false;
}
}

    do (int primetest = primenumbers / n);
    
    while (primetest == false);

    for (int n = primetest == true && > primenumbers; n++)
    else
{
    return false
}