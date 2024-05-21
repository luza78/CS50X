# TODO
import cs50
import math


def main():

    # Asks how many cents customer is owed
    cents = get_cents()

    # Calculates number of quarters
    quarters = calculate_quarters(cents)
    cents = cents - 0.25 * quarters
    cents = round(cents, 2)

    # Calculates number of dimes
    dimes = calculate_dimes(cents)
    cents = cents - 0.10 * dimes
    cents = round(cents, 2)

    # Calculates number of nickels
    nickels = calculate_nickels(cents)
    cents = cents - 0.05 * nickels
    cents = round(cents, 2)

    # Calculates number of pennies
    pennies = calculate_pennies(cents)
    cents = cents - 0.01 * pennies
    cents = round(cents, 2)

    # Adds total coins
    total_coins = quarters + dimes + nickels + pennies

    # Prints total coins with a \n
    print(total_coins)


def get_cents():
    while True:
        change = cs50.get_float("Change owed: ")
        if change > 0.00:
            return change


def calculate_quarters(cents):
    quarters = 0
    cents = round(cents, 2)
    if cents >= 0.25:
        quarters = cents / 0.25
        quarters = math.floor(quarters)

    return quarters


def calculate_dimes(cents):
    dimes = 0
    if cents >= 0.10:
        dimes = cents / 0.10
        dimes = math.floor(dimes)

    return dimes


def calculate_nickels(cents):
    nickels = 0
    if cents >= 0.05:
        nickels = cents / 0.05
        nickels = math.floor(nickels)

    return nickels


def calculate_pennies(cents):
    pennies = 0
    if cents >= 0.01:
        pennies = cents / 0.01
        pennies = math.floor(pennies)

    return pennies


main()

