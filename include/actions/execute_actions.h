/*
** EPITECH PROJECT, 2024
** Actions
** File description:
** Header to execute the actions for the minishell project
*/

#ifndef ACTIONS_H_
    #define ACTIONS_H_
    #include "dependencies/environment.h"
    #include "builtin/builtin.h"
    #include "parser/parser.h"
    #include <stdbool.h>

int execute_action(shell_t *shell, builtin_t *builtin_array,
    char **arguments);
int check_dump(int wait_status);
bool is_executable(char *binary_name);

#endif
