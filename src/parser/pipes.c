/*
** EPITECH PROJECT, 2024
** Minishell2
** File description:
** Adding the pipe function
*/

#include <stdlib.h>
#include <unistd.h>
#include "actions/execute_actions.h"
#include "builtin/builtin.h"
#include "my.h"
#include "my_macros.h"
#include "my_alloc.h"

static
char **split_pipes(char ***split_str, char *str)
{
    int nb_quotes = 0;
    int previous_position = 0;
    int nb_str = 1;

    for (size_t i = 0; str[i] != '\0'; i += 1) {
        if (str[i] == '"')
            nb_quotes += 1;
        if (str[i] == '|' && nb_quotes % 2 == 0) {
            *split_str = my_realloc(*split_str,
                sizeof(char *) * (nb_str + 2), sizeof(char *) * nb_str);
            (*split_str)[nb_str - 1][i - previous_position] = '\0';
            (*split_str)[nb_str] = my_strdup(&(str[i + 1]));
            (*split_str)[nb_str + 1] = NULL;
            previous_position = i + 1;
            nb_str += 1;
        }
    }
    return *split_str;
}

char **parse_pipes(char ***split_str, char *str)
{
    int nb_str = 1;

    if (str == NULL || split_str == NULL)
        return NULL;
    *split_str = malloc(sizeof(char *) * (nb_str + 1));
    if (*split_str == NULL)
        return NULL;
    (*split_str)[0] = my_strdup(str);
    (*split_str)[1] = NULL;
    *split_str = split_pipes(split_str, str);
    return *split_str;
}

char **parse_pipe(char *str)
{
    char **pipes_array = NULL;
    int descriptor[2] = { 0 };

    if (str == NULL)
        return NULL;
    if (pipe(descriptor) != 0) {
        display_error("Unable to pipe\n");
        return NULL;
    }
    return pipes_array;
}
