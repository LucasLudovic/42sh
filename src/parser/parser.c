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
char ***split_semi_colon(char **arguments)
{
    int size_alloc = 1;
    char ***split_str = NULL;
    int nb_quotes = 0;

    if (arguments == NULL)
        return NULL;
    split_str = malloc(sizeof(char **) * (size_alloc + 1));
    if (split_str == NULL)
        return NULL;
    split_str[0] = arguments;
    split_str[1] = NULL;
    return split_str;
    for (size_t i = 0; arguments[i] != NULL; i += 1) {
        for (size_t j = 0; arguments[i][j] != '\0'; j += 1) {
            if (arguments[i][j] == '"')
                nb_quotes += 1;
            if (arguments[i][j] == ';' && nb_quotes % 2 == 0) {
                split_str[size_alloc] = &arguments[i];
                size_alloc += 1;
            }
        }
    }
    return split_str;
}

char ***parse_values(char **arguments)
{
    char ***ordered_value = NULL;

    if (arguments == NULL)
        return NULL;
    ordered_value = split_semi_colon(arguments);
    return ordered_value;
}

char **split_semi_colon2(char *str)
{
    char **split_str = NULL;
    int nb_quotes = 0;
    int number_str = 1;

    if (str == NULL)
        return NULL;
    split_str = malloc(sizeof(char *) * (number_str + 1));
    if (split_str == NULL)
        return NULL;
    split_str[0] = my_strdup(str);
    split_str[1] = NULL;
    for (size_t i = 0; str[i] != '\0'; i += 1) {
        if (str[i] == '"')
            nb_quotes += 1;
        if (str[i] == ';' && nb_quotes % 2 == 0) {
            split_str = my_realloc(split_str, sizeof(char *) * (number_str + 1), sizeof(char *) * (number_str + 2));
            split_str[number_str - 1][i] = '\0';
            split_str[number_str] = my_strdup(&str[i + 1]);
            split_str[number_str + 1] = NULL;
            number_str += 1;
        }
    }
    return split_str;
}
