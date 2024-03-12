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
    unsigned *semi_colon_positions = NULL;
    int size_alloc = 1;
    char ***split_str = NULL;
    int nb_quotes = 0;

    if (arguments == NULL)
        return NULL;
    semi_colon_positions = malloc(sizeof(char **) * (size_alloc + 1));
    if (semi_colon_positions == NULL)
        return NULL;
    split_str[0] = arguments;
    split_str[1] = NULL;
    return split_str;
    for (size_t i = 0; arguments[i] != NULL; i += 1) {
        for (size_t j = 0; arguments[i][j] != '\0'; j += 1) {
            if (arguments[i][j] == '"')
                nb_quotes += 1;
            if (arguments[i][j] == ';' && nb_quotes % 2 == 0) {
                if (semi_colon_positions == NULL)
                    split_str = malloc(sizeof(char **) * (size_alloc + 1));
                //semi_colon_positions[size_alloc - 1] = i;
                //semi_colon_positions[size_alloc] = 0;
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
