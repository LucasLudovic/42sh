/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** Parser
*/

#include <stddef.h>
#include <stdlib.h>
#include "my.h"
#include "my_macros.h"
#include "my_alloc.h"

static
char **split_semicolon(char **split_str, char *str)
{
    int nb_quotes = 0;
    int previous_position = 0;
    int nb_str = 1;

    for (size_t i = 0; str[i] != '\0'; i += 1) {
        if (str[i] == '"')
            nb_quotes += 1;
        if (str[i] == ';' && nb_quotes % 2 == 0) {
            split_str = my_realloc(split_str,
                sizeof(char *) * (nb_str + 2), sizeof(char *) * nb_str);
            split_str[nb_str - 1][i - previous_position] = '\0';
            split_str[nb_str] = my_strdup(&(str[i + 1]));
            split_str[nb_str + 1] = NULL;
            previous_position = i + 1;
            nb_str += 1;
        }
    }
    return split_str;
}

char **parse_semicolon(char *str)
{
    char **split_str = NULL;
    int nb_str = 1;

    if (str == NULL)
        return NULL;
    split_str = malloc(sizeof(char *) * (nb_str + 1));
    if (split_str == NULL)
        return NULL;
    split_str[0] = my_strdup(str);
    split_str[1] = NULL;
    split_str = split_semicolon(split_str, str);
    return split_str;
}
