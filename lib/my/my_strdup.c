/*
** EPITECH PROJECT, 2023
** MY_STRDUP
** File description:
** Allocate memory and copy string
*/

#include <stdlib.h>
#include "my.h"

char *my_strdup(char const *src)
{
    int size = my_strlen(src);
    int i = 0;
    char *dest = malloc(sizeof(char) * (size + 1));

    while (src[i] != '\0') {
        dest[i] = src[i];
        i += 1;
    }
    dest[i] = '\0';
    return dest;
}
