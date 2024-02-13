/*
** EPITECH PROJECT, 2024
** Env
** File description:
** Header to display the environment for the minishell1 project
*/

#ifndef ENV_H_
    #define ENV_H_
    #include "dependencies/environment.h"

int env(environment_t *environment, char **arguments,
    int nb_arguments, int *alive);

#endif
