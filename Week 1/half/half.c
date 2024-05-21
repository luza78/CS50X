// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value

#include <cs50.h>
#include <stdio.h>

float half(float bill, float tax, int tip);

int main(void)
{
    float bill_amount = get_float("Bill before tax and tip: ");
    float tax_percent = get_float("Sale Tax Percent: ");
    int tip_percent = get_int("Tip percent: ");

    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

// TODO: Complete the function

float half(float bill, float tax, int tip)
{
    float bill_after_tax = (bill * (tax / 100) + bill);
    float bill_after_tip = (bill_after_tax * (tip / 100.0) + bill_after_tax);
    float split = bill_after_tip / 2;
    return split;
}

    //tax = (bill_amount * (tax_percent / 100));
    //tip = (bill_amount + tax * (tip_percent / 100));