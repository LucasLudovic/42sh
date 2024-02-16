/*
** EPITECH PROJECT, 2023
** MY_STR_ISUPPER
** File description:
** Check if only alpha and upper
*/

#include <stddef.h>
#include "my.h"

int my_str_isupper(char const *str)
{
    int condition = 0;

    if (str == NULL)
        return FALSE;
    for (int i = 0; str[i] != '\0'; i += 1) {
        condition = str[i] < 65 || str[i] > 90;
        if (condition)
            return FALSE;
    }
    return TRUE;
}
