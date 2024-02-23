/*
** EPITECH PROJECT, 2024
** Str is alpha num
** File description:
** Check if a str is an alphanum
*/

#include <stddef.h>
#include "my.h"

int my_str_is_alpha_num(char *str)
{
    if (str == NULL)
        return FALSE;
    for (size_t i = 0; str[i] != '\0'; i += 1) {
        if ((str[i] < 'a' || str[i] > 'z') &&
            (str[i] < 'A' || str[i] > 'Z') &&
            (str[i] < '0' || str[i] > '9'))
            return FALSE;
    }
    return TRUE;
}
