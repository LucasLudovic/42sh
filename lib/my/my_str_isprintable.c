/*
** EPITECH PROJECT, 2023
** MY_STR_ISPRINTABLE
** File description:
** Check if character is printable
*/

#include <stddef.h>
#include "my.h"

int my_str_isprintable(char const *str)
{
    int condition = 0;

    if (str == NULL)
        return FALSE;
    for (int i = 0; str[i] != '\0'; i += 1) {
        condition = str[i] < 0 || str[i] > 127;
        if (condition)
            return FALSE;
    }
    return TRUE;
}
