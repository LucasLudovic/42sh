/*
** EPITECH PROJECT, 2024
** Which
** File description:
** Header to retrieve a binary absolute path for the minishell1 project
*/

#ifndef WHICH_H_
    #define WHICH_H_
    #include "dependencies/environment.h"

char *get_function_absolute_path(environment_t *environment,
    char **arguments);

#endif
