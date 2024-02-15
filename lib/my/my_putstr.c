/*
** EPITECH PROJECT, 2023
** MY_PUTSTR
** File description:
** Display a string
*/

#include <stddef.h>
#include "my.h"

int my_putstr(char const *str)
{
    if (str == NULL)
        return FAILURE;
    while (*str != '\0') {
        my_putchar(*str);
        str += 1;
    }
    return SUCCESS;
}
