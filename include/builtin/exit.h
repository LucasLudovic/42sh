/*
** EPITECH PROJECT, 2024
** Exit
** File description:
** Header to exit the shell
*/

#ifndef EXIT_H_
    #define EXIT_H_
    #include "dependencies/environment.h"

int exit_shell(environment_t *environment, char **arguments,
    int nb_arguments, int *alive);

#endif
