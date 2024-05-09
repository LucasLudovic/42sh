/*
** EPITECH PROJECT, 2024
** Alias
** File description:
** Header for alias
*/

#ifndef ALIAS_H_
    #define ALIAS_H_
    #include "my_macros.h"
    #include "shell/my_shell.h"

int replace_alias(shell_t *shell, char **arguments, UNUSED int nb_arguments);
alias_t *destroy_alias(alias_t *alias);
int use_alias(shell_t *shell, char **argument);

#endif
