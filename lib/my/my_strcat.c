/*
** EPITECH PROJECT, 2023
** MY_STRCAT
** File description:
** Concatenate two strings
*/

#include <stddef.h>

static
int get_length(char *str)
{
    int i = 0;

    while (str[i] != '\0')
        i += 1;
    return i;
}

static
char *my_new_strcpy(char *dest, char const *src)
{
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i += 1;
    }
    dest[i] = '\0';
    return dest;
}

char *my_strcat(char *dest, char const *src)
{
    if (dest == NULL || src == NULL)
        return dest;
    my_new_strcpy(dest + get_length(dest), src);
    return dest;
}
