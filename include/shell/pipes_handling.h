/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** pipes_handling.h
*/

#ifndef PIPES_HANDLING_H_
    #define PIPES_HANDLING_H_

    #include "shell/my_shell.h"
    #include "parser/parser.h"

void pipes_handling(shell_t *my_shell, builtin_t *builtin_array,
    char **split_arguments, pipes_splits_t **pipes_split);
void destroy_user_arguments(char **user_arguments);

#endif
