/*
** EPITECH PROJECT, 2023
** MY_PUTSTR
** File description:
** Display a string
*/

#include "my.h"

int my_putstr(char const *str)
{
    while (*str != '\0') {
        my_putchar(*str);
        str += 1;
    }
    return 0;
}
