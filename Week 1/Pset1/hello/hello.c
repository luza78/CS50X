#include <stdio.h>
#include <cs50.h>

string get_name(void);

int main(void)
{


    // Prints return of get name
    printf("hello, %s\n", get_name());
}






// get_name function
string get_name(void)
{
    string name = get_string("What's your name? ");
    return name;
}