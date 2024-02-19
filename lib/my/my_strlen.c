/*
** EPITECH PROJECT, 2023
** MY_STRLEN
** File description:
** Return the size of a string
*/

#include <stddef.h>

int my_strlen(char const *str)
{
    char const *ptr = str;
    int counter = 0;

    if (str == NULL)
        return 0;
    while (*ptr != '\0') {
        counter += 1;
        ptr += 1;
    }
    return counter;
}
