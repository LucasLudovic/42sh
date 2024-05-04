/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** set_local_varaible.h
*/

#ifndef SET_LOCAL_VARIABLE_H_
    #define SET_LOCAL_VARIABLE_H_

    #include "../shell/my_shell.h"

int set_local_variable(shell_t *my_shell);
void retrieve_variable(shell_t *shell, char **arguments);
void free_local_variable(variable_t *variable);
void update_return_value(shell_t *shell);

#endif
