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

int execute_action(environment_t *environment, builtin_t *builtin_array,
    char **arguments, int *alive);

#endif
