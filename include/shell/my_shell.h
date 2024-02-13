/*
** EPITECH PROJECT, 2024
** My Macros
** File description:
** Header file for minishell project
*/

#ifndef MY_SHELL_H_
    #define MY_SHELL_H_
    #include "dependencies/environment.h"

typedef struct shell_s {
    int alive;
    environment_t *environment;
} shell_t;

int my_shell(char **env);

#endif
