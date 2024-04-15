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

int change_name(char **arguments);
char *check_alias(alias_t *alias, char *arguments);
int replace_alias(shell_t *shell, char **arguments, UNUSED int nb_arguments);

#endif
