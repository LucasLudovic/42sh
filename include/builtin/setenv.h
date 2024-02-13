/*
** EPITECH PROJECT, 2024
** Setenv
** File description:
** Header to add or modify the env for the minishell1 project
*/

#ifndef SETENV_H_
    #define SETENV_H_
    #include "dependencies/environment.h"

int my_setenv(environment_t *environment, char **arguments,
    int nb_arguments, int *alive);

#endif
