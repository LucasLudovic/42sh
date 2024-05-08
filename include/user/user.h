/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** Header for user inputs
*/

#ifndef USER_H_
    #define USER_H_
    #include "shell/my_shell.h"
    #define NEXT 0
    #define PREV 1

void execute_escape_sequence(shell_t *shell, char *user_input,
    long *position[2], char c);
char **get_user_arguments(shell_t *shell, char **user_arguments);
void update_input(shell_t *shell, char *user_input, long *position[2], char c);

#endif
