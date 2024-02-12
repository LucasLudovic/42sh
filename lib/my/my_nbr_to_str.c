/*
** EPITECH PROJECT, 2023
** MY_PUT_NBR
** File description:
** Display number with however number I want
*/

#include "my.h"
#include <stddef.h>
#include <stdlib.h>

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

static
char *my_positiv_to_str(unsigned int nb)
{
    long int number = nb;
    int number_of_digit = counting_digit(nb);
    char *str = NULL;

    str = malloc(sizeof(char) * (number_of_digit + 1));
    for (int i = number_of_digit - 1; i >= 0; i -= 1) {
        str[number_of_digit - i - 1] = (number / my_power(10, i)) + 48;
        number = number % my_power(10, i);
    }
    str[number_of_digit] = '\0';
    return str;
}

char *my_nbr_to_str(int number)
{
    char *positiv_str = NULL;
    char *str = NULL;
    int number_of_digit = counting_digit(number);
    int negativ = check_if_negativ(number);

    str = malloc(sizeof(char) * number_of_digit + negativ + 1);
    if (negativ == 1) {
        str[0] = '-';
        number *= -1;
    }
    positiv_str = my_positiv_to_str(number);
    if (negativ == 1) {
        str = my_strcat(str, positiv_str);
    } else
        str = my_strcpy(str, positiv_str);
    str[number_of_digit + negativ] = '\0';
    free(positiv_str);
    return str;
}
