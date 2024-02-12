/*
** EPITECH PROJECT, 2023
** MY_PUT_NBR
** File description:
** Display number with however number I want
*/

#include "my.h"

static
int counting_digit(int number)
{
    int numberOfDigit = 1;

    while (number / 10 != 0) {
        numberOfDigit += 1;
        number = number / 10;
    }
    return numberOfDigit;
}

static
int my_power(int number, int pow)
{
    int result = 1;

    for (int i = pow; i > 0; i -= 1) {
        result = result * number;
    }
    return result;
}

static
int check_if_negativ(int number)
{
    if (number < 0)
        return 1;
    else
        return 0;
}

int my_put_nbr(int nb)
{
    long int number = nb;
    int number_of_digit = counting_digit(nb);
    int isNegativ = check_if_negativ(nb);

    if (isNegativ == 1) {
        my_putchar('-');
        number = number * -1;
    }
    for (int i = number_of_digit - 1; i >= 0; i -= 1) {
        my_putchar((number / my_power(10, i)) + 48);
        number = number % my_power(10, i);
    }
    return 0;
}
