/*
** EPITECH PROJECT, 2024
** Unsetenv
** File description:
** Header to remove an env variable for the minishell1 project
*/

#ifndef UNSETENV_H_
#define UNSETENV_H_
#include "dependencies/environment.h"

int my_unsetenv(environment_t **environment, char **arguments,
              int nb_arguments, int *alive);

#endif