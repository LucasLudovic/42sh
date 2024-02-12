/*
** EPITECH PROJECT, 2023
** MY_STRSTR
** File description:
** Locate a substring
*/

#include "my.h"

static
int get_new_length(char const *str)
{
    int i = 0;

    while (str[i] != '\0')
        i += 1;
    return i;
}

static
int my_new_strcmp(char const *s1, char const *s2)
{
    long int value_s1 = 0;
    long int value_s2 = 0;
    long int length_s1 = get_new_length(s1);
    long int length_s2 = get_new_length(s2);
    long int i = 0;

    for (i; s1[i] != '\0'; i += 1)
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
    return s1[i] - s2[i];
}

char *my_strstr(char *str, char const *to_find)
{
    while (*str != '\0') {
        if (*str == *to_find && my_new_strcmp(str, to_find) == 0)
            return str;
        str += 1;
    }
    return 0;
}
