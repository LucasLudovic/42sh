/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** pipes_handling.c
*/

#include "shell/my_shell.h"
#include "parser/parser.h"
#include <stdio.h>
#include <stdlib.h>

void destroy_user_arguments(char **user_arguments)
{
    if (user_arguments == NULL)
        return;
    for (size_t i = 0; user_arguments[i] != NULL; i += 1)
        free(user_arguments[i]);
    free(user_arguments);
}

void pipes_handling(shell_t *my_shell, builtin_t *builtin_array,
    char **split_arguments, pipes_splits_t **pipes_split)
{
    *pipes_split = parse_pipes(split_arguments);
    execute_pipe(my_shell, builtin_array, *pipes_split);
    destroy_user_arguments(split_arguments);
}
