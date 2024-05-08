/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Header for which builtin
*/

#ifndef WHICH_BUILTIN_H_
    #define WHICH_BUILTIN_H_
    #include "my_macros.h"
    #include "shell/my_shell.h"

int which(shell_t *shell, char **arguments, UNUSED int nb_arguments);

#endif
