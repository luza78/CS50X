// Practice using structs
// Practice writing a linear search function

/**
 * Beach Burger Shack has the following 10 items on their menu
 * Burger: $9.5
 * Vegan Burger: $11
 * Hot Dog: $5
 * Cheese Dog: $7
 * Fries: $5
 * Cheese Fries: $6
 * Cold Pressed Juice: $7
 * Cold Brew: $3
 * Water: $2
 * Soda: $2
*/

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Number of menu items
// Adjust this value (10) to number of items input below
#define NUM_ITEMS 4

// Menu itmes have item name and price
typedef struct
{
    string item;
    float price;
}
menu_item;

// Array of menu items
menu_item menu[NUM_ITEMS];

// Add items to menu
void add_items(void);

// Calculate total cost
float get_cost(string item);

int main(void)
{
    add_items();

    printf("\nWelcome to Beach Burger Shack!\n");
    printf("Choose from the following menu to order. Press enter when done.\n\n");

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        printf("%s: $%.2f\n", menu[i].item, menu[i]. price);
    }
    printf("\n");

    float total = 0;
    while (true)
    {
        string item = get_string("Enter a food item: ");
        if (strlen(item) == 0)
        {
            printf("\n");
            break;
        }

        total += get_cost(item);
    }

    printf("Your total cost is: $%.2f\n", total);
}

// Add at least the first for items to the menu array
void add_items(void)
{
    menu[0].item = "Burger";
    menu[0].price = 9.50;

    menu[1].item = "Cheese Fries";
    menu[1].price = 6;

    menu[2].item = "Soda";
    menu[2].price = 2;

    menu[3].item = "Water";
    menu[3].price = 2;
    return;
}

// Search through the menu array to find an item's cost
float get_cost(string item)
{

    char k[50];
    strcpy(k, item);
    char l[50];
    for (int j = 0; j < strlen(k) ; j++)
    {
        k[j] = tolower(k[j]);
    }
    string c = k;

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        for (int o = 0; o < strlen(menu[i].item); o++)
        {
            l[o] = tolower(menu[i].item[o]);
        }
        if (strcmp(l, c) == 0)
        {
            return (menu[i].price);
            break;
        }
        else
        {
            memset(l, '\0', 50);
        }
    }
    printf("Item \"%s\" not found \n", c);
    return 0.0;
}
